	.macro restore_args_call_smc
	ldp	x6, x7, [x0, #TSP_ARG6]
	ldp	x4, x5, [x0, #TSP_ARG4]
	ldp	x2, x3, [x0, #TSP_ARG2]
	ldp	x0, x1, [x0, #TSP_ARG0]
	smc	#0
	.endm

.global tos_vector_table
tos_vector_table:
    b tos_yield_smc_entry
    b tos_fast_smc_entry
    b tos_cpu_on_entry
    b tos_cpu_off_entry
    b tos_cpu_resume_entry
    b tos_cpu_suspend_entry
    b tos_sel1_intr_entry
    b tos_system_off_entry
    b tos_system_reset_entry
    b tos_abort_yield_smc_entry

	/*---------------------------------------------
	 * This entrypoint is used by the TSPD when this
	 * cpu is to be turned off through a CPU_OFF
	 * psci call to ask the TSP to perform any
	 * bookeeping necessary. In the current
	 * implementation, the TSPD expects the TSP to
	 * re-initialise its state so nothing is done
	 * here except for acknowledging the request.
	 * ---------------------------------------------
	 */
func tsp_cpu_off_entry
	bl	tsp_cpu_off_main
	restore_args_call_smc
endfunc tsp_cpu_off_entry

	/*---------------------------------------------
	 * This entrypoint is used by the TSPD when the
	 * system is about to be switched off (through
	 * a SYSTEM_OFF psci call) to ask the TSP to
	 * perform any necessary bookkeeping.
	 * ---------------------------------------------
	 */
func tsp_system_off_entry
	bl	tsp_system_off_main
	restore_args_call_smc
endfunc tsp_system_off_entry

	/*---------------------------------------------
	 * This entrypoint is used by the TSPD when the
	 * system is about to be reset (through a
	 * SYSTEM_RESET psci call) to ask the TSP to
	 * perform any necessary bookkeeping.
	 * ---------------------------------------------
	 */
func tsp_system_reset_entry
	bl	tsp_system_reset_main
	restore_args_call_smc
endfunc tsp_system_reset_entry

	/*---------------------------------------------
	 * This entrypoint is used by the TSPD when this
	 * cpu is turned on using a CPU_ON psci call to
	 * ask the TSP to initialise itself i.e. setup
	 * the mmu, stacks etc. Minimal architectural
	 * state will be initialised by the TSPD when
	 * this function is entered i.e. Caches and MMU
	 * will be turned off, the execution state
	 * will be aarch64 and exceptions masked.
	 * ---------------------------------------------
	 */
