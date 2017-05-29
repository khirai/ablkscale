/*
    ablkscale.c:

    Copyright (C) 2107 Kelly Hirai

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/
#include "csdl.h"
#include "ablkscale.h"
#include <math.h>


static int ablkscaleinit(CSOUND *csound, ABLKSCALE *p)
{
   /* Initialise gain value */

    return OK;
}

/*
 * Run-time computation code
 */

static int ablkscale(CSOUND *csound, ABLKSCALE *p)
{
  MYFLT *ain = p->ain;
  MYFLT *aout = p->aout;
  MYFLT kscale = *(p->kscale);
  uint32_t osmpcnt,osmpposold,osmpposnew;  
  uint32_t offset = p->h.insdshead->ksmps_offset;
  uint32_t early  = p->h.insdshead->ksmps_no_end;
  uint32_t i, nsmps = CS_KSMPS;
  
  /* Process ksmps samples */
  if (UNLIKELY(offset)) memset(aout, '\0', offset*sizeof(MYFLT));
  if (UNLIKELY(early)) {
    nsmps -= early;
    memset(&aout[nsmps], '\0', early*sizeof(MYFLT));
  }
  osmpcnt=0;
  osmpposold=offset;
  for (i=offset;i<nsmps;i++) {
    /* the new shorter position */
    osmpposnew=(int)((int)(i-offset)*kscale+offset);
    if (osmpposold == osmpposnew) {
      osmpcnt++;  /*count the number of smps accumulated on the position*/
    }
    else {        /*average the old samples and reset count  */
      aout[osmpposold]=aout[osmpposold]/osmpcnt;
      osmpcnt=0;
    }
    aout[osmpposnew] += ain[i]; /*accumulate samples at the new position */
    osmpcnt++;
    osmpposold=osmpposnew;
  }
  /* aout[osmpposnew]=aout[osmpposnew]/osmpcnt; */ /* never more then 1 sample  or zero? */
  return OK;
}

#define S(x)    sizeof(x)



static OENTRY localops[] = {
 "ablkscale", S(ABLKSCALE), 0, 4, "a","ak",(SUBR)ablkscaleinit,
  NULL, (SUBR)ablkscale }
;

LINKAGE

/*  int ablkscale_init_(CSOUND *csound) */
/* { */
/*     return csound->AppendOpcodes(csound, &(localops[0]), */
/*                                  (int) (sizeof(localops) / sizeof(OENTRY))); */
/* } */


