/* main */
if (funz_ric(...) == 0) 
  printf("soluzione non trovata\n");

/* funzione ricorsiva */
int funz_ric(...) {
 if (condizione di terminazione)
   if (condizione di accettazione) {
     ...    
     return 1;
   else
     return 0;
   }
 for (ciclo sulle scelte) {
    scelta; 
    if (funz_ric(...))
      return 1;
    ...    
  }
  return 0;
}

