#ifndef MySysCalls_H
#define MySysCalls_H



/* #SOI #lab5 MySysCalls */
int do_hole_map()
{
    unsigned int buffSize = mm_in.m1_i1; /* size of user buffer */
    struct hole* hp = hole_head;
    unsigned int mmBuff[2*NR_HOLES + 1]; /* buffer which contain information about holes */
    unsigned int mmBuffCount = 0;

      while(hp != NIL_HOLE && hp->h_base < swap_base)
    {        
        if( (buffSize-mmBuffCount) < 3 )
            break;
        mmBuff[mmBuffCount++] = hp->h_len;
        mmBuff[mmBuffCount++] = hp->h_base;

        hp = hp->h_next;
    }

    mmBuff[mmBuffCount] = 0;

    /* from MM process copy Data segment to calling process */
    /* mm_in.m1_p1 contains pointer to user data buffer */
	sys_copy(MM_PROC_NR, D, mmBuff,
			mm_in.m_source, D, (phys_bytes) mm_in.m1_p1,
			(phys_bytes) mmBuffCount);

  return 0;
}

/* #SOI #lab5 MySysCalls */
int do_worst_fit()
{
  if(mm_in.m1_i1==1)
    enableWorstFit = 1;
  else
    enableWorstFit = 0;

  return 0;
}

#endif
