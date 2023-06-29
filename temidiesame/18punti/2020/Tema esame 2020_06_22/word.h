#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED
#define MAX 20

typedef enum{VERO, FALSO}Boolean;

typedef struct{
    char parola[MAX+1];
    Boolean preso;
}Word;

typedef enum{PRIMA, DOPO, UGUALE}Simboli;

Word WORDcrea(char *parola);
Simboli WORDcompare(Word w1, Word w2);


#endif // WORD_H_INCLUDED
