

PUBLIC int do_getprocnr(void)
{
	int procNr;
	for(procNr = 0; procNr < NR_PROCS; ++procNr)
	{
		if( ( (mproc[procNr].mp_flags & IN_USE) != 0) && (mproc[procNr].mp_pid == pid) )
			return procNr;
	}
	return ENOENT;
} 

PUBLIC int do_getpspri(void)
{
	return 0;
}

PUBLIC int do_setpspri(void)
{
	return 0;
}
