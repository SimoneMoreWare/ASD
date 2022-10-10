#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAXR    1000
#define STR     31
#define CMD     6
#define FILE_IN "log.txt"

typedef struct {
  int a;
  int m;
  int g;
} data_t;

typedef struct {
  int h;
  int m;
  int s;
} ora_t;

typedef struct {
  char codice[STR];
  char partenza[STR];
  char destinazione[STR];
  char data_str[STR];
  char orap_str[STR];
  char orad_str[STR];
  int ritardo;
  data_t data;
  ora_t p, d;
} voce_t;

typedef struct tabella_ {
  int n_voci;
  voce_t log[MAXR];
} tabella_t;

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comando_e;

tabella_t leggiTabella();

int dataSTR2INT(data_t data);
comando_e leggiComando(char comandi[][STR]);
void stampaComandi(char comandi[][STR]);
void selezionaDati(tabella_t tab, comando_e cmd);

int main(void) {

  char comandi[][STR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
  int continua = 1;
  comando_e cmd;
  tabella_t tab;

  tab = leggiTabella();

  stampaComandi(comandi);
  do {
    cmd = leggiComando(comandi);
		switch(cmd) {
			case r_date:
        selezionaDati(tab, r_date);
				break;
			case r_partenza:
        selezionaDati(tab, r_partenza);
				break;
			case r_capolinea:
        selezionaDati(tab, r_capolinea);
				break;
			case r_ritardo:
        selezionaDati(tab, r_ritardo);
				break;
			case r_ritardo_tot:
        selezionaDati(tab, r_ritardo_tot);
				break;
			case r_fine:
				continua = 0;
				break;
      default:
        stampaComandi(comandi);
		}
	} while(continua);
	return 0;
}


int confrontaDate1(data_t d1, data_t d2) {
  if (d1.a != d2.a)
    return (d1.a-d2.a);
  else if (d1.m != d2.m)
    return (d1.m-d2.m);
  else if (d1.g != d2.g)
    return (d1.g-d2.g);
  else return 0;
}

int confrontaDate2(data_t d1, data_t d2) {
  int data1, data2, ris;

  data1= dataSTR2INT(d1);
  data2= dataSTR2INT(d2);
  if (data1 <= data2)
    ris = -1;
  else
    ris = 1;
  return ris;
}

int dataSTR2INT(data_t data) {
  return 10000*data.a+100*data.m+data.g;
}

tabella_t leggiTabella() {
  int i;
  tabella_t tab;
  FILE *in = fopen(FILE_IN, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d", &tab.n_voci);
  for (i=0; i<tab.n_voci; i++) {
    fscanf(in, "%s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_str, tab.log[i].orap_str, tab.log[i].orad_str, &tab.log[i].ritardo);
    sscanf (tab.log[i].data_str,"%d/%d/%d", &tab.log[i].data.a,&tab.log[i].data.m,&tab.log[i].data.g);
    sscanf (tab.log[i].orap_str,"%d:%d:%d", &tab.log[i].p.h,&tab.log[i].p.m,&tab.log[i].p.s);
    sscanf (tab.log[i].orad_str,"%d:%d:%d", &tab.log[i].d.h,&tab.log[i].d.m,&tab.log[i].d.s);
  }

  return tab;
}

comando_e leggiComando(char comandi[][STR]) {
  int i;
  char cmd[STR];
  printf("Comando > ");
  scanf("%s", cmd);
  for (i=0; i<CMD; i++) {
	if (strcmp(cmd, comandi[i]) == 0)
      return (comando_e) i;
  }
  return -1;
}

void stampaComandi(char comandi[][STR]) {
  int i;
  printf("Comandi disponibili:");
  for (i=0;i<CMD;i++)
    printf(" %s", comandi[i]);
  printf("\n");
}

void stampaVoce(voce_t v) {
  printf("Tratta [%s] da %s a %s del %s (dalle %s alle %s, con ritardo di %d minut%c)\n", v.codice, v.partenza, v.destinazione, v.data_str, v.orap_str, v.orap_str, v.ritardo, ((v.ritardo == 1) ? 'o' : 'i'));
}

void selezionaDati(tabella_t tab, comando_e cmd) {
  data_t d1, d2;
  char target[STR];
  int i, tot=0;
  if (cmd == r_date) {
    printf("Inserire prima data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d1.a,&d1.m,&d1.g);
    printf("Inserire seconda data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d2.a,&d2.m,&d2.g);
  } else if (cmd == r_partenza) {
    printf("Inserire luogo di partenza: ");
    scanf("%s", target);
  } else if (cmd == r_capolinea) {
    printf("Inserire luogo di destinazione: ");
    scanf("%s", target);
  } else if(cmd == r_ritardo) {
    printf("Inserire prima data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d1.a,&d1.m,&d1.g);
    printf("Inserire seconda data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d2.a,&d2.m,&d2.g);
  } else if(cmd == r_ritardo_tot) {
    printf("Inserire codice della tratta: ");
    scanf("%s", target);
  }

  for (i=0; i<tab.n_voci; i++) {
    switch(cmd) {
      case r_date:
          if (confrontaDate1(d1, tab.log[i].data) <= 0 && confrontaDate1(tab.log[i].data, d2) <= 0)
            stampaVoce(tab.log[i]);
          break;
      case r_partenza:
          if (!strcmp(tab.log[i].partenza, target))
            stampaVoce(tab.log[i]);
          break;
      case r_capolinea:
          if (!strcmp(tab.log[i].destinazione, target))
            stampaVoce(tab.log[i]);
          break;
      case r_ritardo:
          if (confrontaDate1(d1, tab.log[i].data) <= 0 && confrontaDate1(tab.log[i].data, d2) <= 0 && tab.log[i].ritardo > 0)
            stampaVoce(tab.log[i]);
          break;
      case r_ritardo_tot:
          if (!strcmp(tab.log[i].codice, target))
            tot += tab.log[i].ritardo;
          break;

      default: {
      }
    }
  }

  if (cmd == r_ritardo_tot)
    printf("Ritardo totale %d\n", tot);
}
