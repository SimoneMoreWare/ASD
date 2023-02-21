/* main */
...
int stop = 0;
...
funz_ric(...  , &stop);
...

/* funzione ricorsiva  */

void funz_ric(..., int *stop_ptr) {
  ...
  if (condizione di terminazione) {
    ...
    (*stop_ptr) = 1;
  }
  return;
  for (i = 0; condizione su i && (*stop_ptr)==0; i++) {
    ... 
    funz_ric(..., stop_ptr);
    ...    
  }
  return;
}

