/* #SOI */

PUBLIC int do_getprocnr(void)
{
	int procNr;
	for (procNr = 0; procNr < NR_PROCS; ++procNr)
	{
		if (((mproc[procNr].mp_flags & IN_USE) != 0) && (mproc[procNr].mp_pid == pid))
			return procNr;
	}
	return ENOENT;
}

PUBLIC int do_getpspri(void)
{
	message msg;
	int result;
	msg = mm_in;
	msg.m1_i1 = who;
	/*msg.m_u.m_m1.m1i1 = who;*/ /* change only caller process parameters */
	result = _taskcall(SYSTASK, SYS_GETPSPRI, &msg);
	mm_in = msg; /* process subpriority */
	return result;
}

PUBLIC int do_setpspri(void)
{
	message msg;
	msg = mm_in;
	msg.m1_i1 = who;
	/*msg.m_u.m_m1.m1i1 = who;*/ /* change only caller process parameters */
	/* in msg.m_u.m_m1.m1i2 is new process subpriority */
	return _taskcall(SYSTASK, SYS_SETPSPRI, &msg);
}
