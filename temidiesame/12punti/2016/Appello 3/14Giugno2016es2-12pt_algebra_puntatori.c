/*
Si scriva una funzione separaParole che, a partire da una stringa contenente parole separate da spazi, generi
un vettore di stringhe (vettore di puntatori a caratteri) contenente le singole parole, prive di spazi e duplicate
mediante allocazione dinamica. La funzione deve essere richiamabile, ad esempio, nel modo seguente:
char frase[1000], **parole;
int n, i;
…
fgets(frase,1000,stdin);
n = separaParole(frase,&parole);
for (i=0; i<n; i++)
 printf(“parola %d -> %s\n”, parole[i]);
…
Si scriva il prototipo e il contenuto della funzione. Si noti che il puntatore parole viene utilizzato per un vettore
(allocato dinamicamente) di puntatori a char: ogni casella punterà a una delle parole generate dalla stringa
originale. Il vettore di stringhe viene ritornato per riferimento (o meglio, se ne passa per valore il puntatore).
Per semplicità è lecito ipotizzare che gli spazi che separano le parole non siano multipli.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000

int separaparole(char* frase, char*** parole);
int main()
{
	int i;
	int n;
	char** parole;
	char frase[1000] = { "ciao mi chiamo xxxx piacere di conoscerti" };
	n = separaparole(frase, &parole);
	for (i = 0; i < n; i++)
	{
		printf("%s\n", parole[i]);

	}
	return 0;
}

int separaparole(char* frase, char*** parole)
{
	int i = 0,j=0;
	int n=0;
	char parola[N];
	int len = strlen(frase);
	int lenint;
	while (i < len)
	{
		sscanf(frase + i, "%s", parola);
		lenint = strlen(parola);
		i = i + lenint + 1;
		n++;
	}
	i = 0;
	(*parole) = calloc(n, sizeof(char*));
	while (i < n)
	{
		sscanf(frase + j, "%s", parola);
		lenint = strlen(parola);
			(*parole)[i] = _strdup(parola);
		i++;
		j = j + lenint + 1;
	}
	return n;
}
