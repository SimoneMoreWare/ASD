#ifndef TS_H_INCLUDED
#define TS_H_INCLUDED

typedef struct ts_t *TS;

TS TSinit(int maxN);
int TSaggiungi(TS ts, char *str);
int TScerca(TS th, char *str);
int TScercaOaggiungi(TS ts, char *str);
void TSlibera(TS ts);
char *TSleggi(TS ts, int i);

#endif /* TS_H_INCLUDED */
