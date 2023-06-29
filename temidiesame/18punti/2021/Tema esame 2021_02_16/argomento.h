#ifndef ARGOMENTO_H_INCLUDED
#define ARGOMENTO_H_INCLUDED

#define CAR 200

typedef struct{
    char nome[CAR];
}Argomento;

Argomento ARGOMENTOcrea(char *nome);

#endif // ARGOMENTO_H_INCLUDED
