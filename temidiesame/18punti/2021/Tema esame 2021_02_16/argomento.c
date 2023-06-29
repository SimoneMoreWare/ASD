#include "argomento.h"
#include <string.h>

Argomento ARGOMENTOcrea(char *nome){
    Argomento a;
    strcpy(a.nome, nome);
    return a;
}
