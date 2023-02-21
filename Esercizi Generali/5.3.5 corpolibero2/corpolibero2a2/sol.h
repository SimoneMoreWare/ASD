/* quasi ATD Item: vettore di interi non negativi 
   con terminatore -1 */

#ifndef SOL_INCLUDED
#define SOL_INCLUDED

typedef struct sol_s *SOL;

SOL SOLnew(int n);
SOL SOLdup(SOL s);
void SOLcopy(SOL sDest, SOL sSrc);
void SOLfree(SOL s);
int SOLreadI(SOL s, int i);
void SOLwriteI(SOL s, int i, int val);
void SOLread(SOL s, float *dp, float *pp);
void SOLwrite(SOL s, float d, float p);
int SOLreadN(SOL s);
void SOLwriteN(SOL s, int n);
float SOLreadD(SOL s);
void SOLwriteD(SOL s, float w);
float SOLreadP(SOL s);
void SOLwriteP(SOL s, float p);

#endif
