#define CACHE_WRITEBACK_SHIFT 6
#define CACHE_WRITEBACK_GRANULE (1 << CACHE_WRITEBACK_SHIFT)

#define TOS_ARGS_SIZE		0x40
#define TOS_ARG0		0x0
#define TOS_ARG1		0x8
#define TOS_ARG2		0x10
#define TOS_ARG3		0x18
#define TOS_ARG4		0x20
#define TOS_ARG5		0x28
#define TOS_ARG6		0x30
#define TOS_ARG7		0x38
#define TOS_ARGS_END		0x40

typedef struct tos_args {
	uint64_t _regs[TOS_ARGS_END >> 3];
} __aligned(CACHE_WRITEBACK_GRANULE) toskargs_t;

typedef uint32_t linux_vector_isn_t;

typedef struct linux_vectors {
	linux_vector_isn_t yield_smc_entry;
	linux_vector_isn_t fast_smc_entry;
	linux_vector_isn_t cpu_on_entry;
	linux_vector_isn_t cpu_off_entry;
	linux_vector_isn_t cpu_resume_entry;
	linux_vector_isn_t cpu_suspend_entry;
	linux_vector_isn_t sel1_intr_entry;
	linux_vector_isn_t system_off_entry;
	linux_vector_isn_t system_reset_entry;
	linux_vector_isn_t abort_yield_smc_entry;
} linux_vectors_t;

extern tos_vectors_t linuxd_vector_table;

tos_args_t *tos_cpu_resume_main(uint64_t max_off_pwrlvl,
				uint64_t arg1,
				uint64_t arg2,
				uint64_t arg3,
				uint64_t arg4,
				uint64_t arg5,
				uint64_t arg6,
				uint64_t arg7);
tos_args_t *tos_cpu_suspend_main(uint64_t arg0,
				 uint64_t arg1,
				 uint64_t arg2,
				 uint64_t arg3,
				 uint64_t arg4,
				 uint64_t arg5,
				 uint64_t arg6,
				 uint64_t arg7);
tos_args_t *tos_cpu_on_main(void);
tos_args_t *tos_cpu_off_main(uint64_t arg0,
			     uint64_t arg1,
			     uint64_t arg2,
			     uint64_t arg3,
			     uint64_t arg4,
			     uint64_t arg5,
			     uint64_t arg6,
			     uint64_t arg7);

tos_args_t *tos_abort_smc_handler(uint64_t func,
				  uint64_t arg1,
				  uint64_t arg2,
				  uint64_t arg3,
				  uint64_t arg4,
				  uint64_t arg5,
				  uint64_t arg6,
				  uint64_t arg7);

tos_args_t *tos_smc_handler(uint64_t func,
			       uint64_t arg1,
			       uint64_t arg2,
			       uint64_t arg3,
			       uint64_t arg4,
			       uint64_t arg5,
			       uint64_t arg6,
			       uint64_t arg7);

tos_args_t *tos_system_reset_main(uint64_t arg0,
				uint64_t arg1,
				uint64_t arg2,
				uint64_t arg3,
				uint64_t arg4,
				uint64_t arg5,
				uint64_t arg6,
				uint64_t arg7);

tos_args_t *tos_system_off_main(uint64_t arg0,
				uint64_t arg1,
				uint64_t arg2,
				uint64_t arg3,
				uint64_t arg4,
				uint64_t arg5,
				uint64_t arg6,
				uint64_t arg7);
