/*
Scrivere la funzione char *charErase (char *str, int *pos); che riceve una stringa str e un
vettore di interi pos e restituisce la stringa ottenuta da str cancellando i caratteri nelle posizioni indicate dal
vettore pos. La stringa ritornata va opportunamente allocata. Il vettore pos ha dimensione ignota, ma il suo
ultimo elemento contiene il valore -1.
Ad esempio, se la stringa str è T h i s I s A S t r i n g e il vettore pos contiene 7 4 2 0 11 -1
occorre cancellare dalla stringa str i caratteri S, I, i, T, n e restituire la stringa contenente
h s s A t r i g
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char* charerase(char* str, int* pos);

int main()
{
	char* str = _strdup("ThisIsAString");
	int pos[6] = { 7,4,2,0,11,-1 };
	char* newstr = charerase(str, pos);
	printf("%s", newstr);
	return 0;
	
}
char* charerase(char* str, int* pos)
{
	int len = strlen(str);
	int* mark = calloc(len, sizeof(int));
	int i = 0, count = 0;;
	while (pos[i] != -1)
	{
		mark[pos[i]] = 1;
		i++;
	}
	int newlen = len - i;
	char* str1 = calloc(newlen+1, sizeof(char));
	i = 0;
	int j = 0;
	while (i < len)
	{
		if (mark[i] == 0)
		{
			str1[j] = str[i];
			i++;
			j++;
		}
		else
		{
			i++;
		}
	}
	return str1;

}
