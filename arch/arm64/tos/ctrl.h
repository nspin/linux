#ifndef TOS_CTRL_H
#define TOS_CTRL_H

#include <linux/ioctl.h>

struct tos_ioctl_smc {
    unsigned long regs[8];
    unsigned long res[4];
};

#define TOS_IOCTL_MAGIC 0x33
#define TOS_SMC _IOWR(TOS_IOCTL_MAGIC, 0, struct tos_ioctl_smc)

#endif
