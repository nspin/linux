#include <linux/arm-smccc.h>
#include <linux/serial_core.h>

#define FID 0xf200000a

static void smc_putchar(char c)
{
	struct arm_smccc_res res;
	arm_smccc_smc(FID, (unsigned long) c, 0, 0, 0, 0, 0, 0, &res);
}

static void smc_earlycon_write(struct console *console, const char *buf, unsigned n)
{
	const char *end = buf + n;
	while (buf < end) {
		smc_putchar(*buf++);
	}
}

static int __init smc_earlycon_setup(struct earlycon_device *device, const char *opt)
{
	device->con->write = smc_earlycon_write;
	return 0;
}
EARLYCON_DECLARE(smc, smc_earlycon_setup);
