typedef struct tabella *TS;

TS TScrea(int maxN);
void TSlibera(TS t);
int TSdimensione(TS t);
int TSaggiungi(TS t, char *str);
int TScerca(TS t, char *str);
int TScercaOAggiungi(TS t, char *str);
char *TSleggiIndice(TS t, int id);
