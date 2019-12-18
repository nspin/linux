#define DEBUG

#include <linux/arm-smccc.h>
#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/uaccess.h>

#include "ctrl.h"

static struct dentry *tos_file;

static long tos_smc(struct tos_ioctl_smc *smc)
{
    struct arm_smccc_res res;

    arm_smccc_smc(
        smc->regs[0], smc->regs[1], smc->regs[2], smc->regs[3],
        smc->regs[4], smc->regs[5], smc->regs[6], smc->regs[7],
        &res
        );

    smc->res[0] = res.a0;
    smc->res[1] = res.a1;
    smc->res[2] = res.a2;
    smc->res[3] = res.a3;

    return 0;
}

static long unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long argp)
{
    long ret = 0;

    switch (cmd) {

        case TOS_SMC: {

            struct tos_ioctl_smc smc;
            struct tos_ioctl_smc __user *smc_user;
            smc_user = (struct tos_ioctl_smc __user *)argp;

            if (copy_from_user(&smc.regs, (void __user *)smc_user->regs, sizeof(smc.regs))) {
                return -EFAULT;
            }

            ret = tos_smc(&smc);

            if (copy_to_user((void __user *)smc_user->res, &smc.res, sizeof(smc.res))) {
                return -EFAULT;
            }

            break;
        }

        default:

            return -EINVAL;
            break;

    }

    return 0;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = unlocked_ioctl
};

static int tos_init(void)
{
    tos_file = debugfs_create_file("tos", 0, NULL, NULL, &fops);
    return 0;
}

static void tos_exit(void)
{
    debugfs_remove(tos_file);
}

module_init(tos_init)
module_exit(tos_exit)
