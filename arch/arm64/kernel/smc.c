#include <linux/arm-smccc.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(smccc_smc, struct arm_smccc_regs __user *, regs, struct arm_smccc_res __user *, res, struct arm_smccc_quirk __user *, quirk)
{
	arm_smccc_smc_quirk(regs->a0, regs->a1, regs->a2, regs->a3, regs->a4, regs->a5, regs->a6, regs->a7, res, quirk);
	return 0;
}
