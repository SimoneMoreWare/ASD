/*
t1 t2 puntatori ad alberi binari

verificare se i due alberi sono isomorfi, alberi strutturalmente identici, stessi valori disposti nello stesso modo.

*/

//simile alla visita in pre order ecc...

int TREEisomorph(link t1,link t2){
    if(t1==NULL && t2==NULL) return 1; //gli alberi sono entrambi vuoti oppure sono giunto ai figli

    if(t1==NULL || t2==NULL) return 0;     // Se uno solo è null, gli alberi non sono isomorfi, sincero me ne ero dimenticato
    
    
    // Se le chiavi dei nodi correnti sono uguali, verifica se gli alberi sinistri e destri dei  nodi correnti sono isomorfi

    if(KEYcmp(t1->key,t2->key)==0){
        return TREEisomorph(t1->left,t2->left) && TREEisomorph(t1->right,t2->right);
    }
    return 0; // Se le chiavi dei nodi correnti sono diverse, gli alberi non sono isomorfi
}

/*
Questa funzione riceve come argomenti due puntatori a strutture di tipo "link", chiamati "t1" e "t2". Il suo scopo è quello di verificare se gli alberi binari puntati da "t1" e "t2" sono isomorfi, ovvero se hanno la stessa struttura e contengono gli stessi valori.

La funzione si basa sulla ricorsione sugli alberi. In particolare, viene effettuata una verifica a tre passi:

Se entrambi gli alberi sono null, gli alberi sono isomorfi.
Se uno solo degli alberi è null, gli alberi non sono isomorfi.
Se le chiavi dei nodi correnti sono uguali, la funzione si richiama sui sottoalberi sinistro e destro dei nodi correnti, verificando se anche questi sono isomorfi. Se le chiavi dei nodi correnti sono diverse, gli alberi non sono isomorfi.
La funzione utilizza la funzione "KEYcmp" per confrontare le chiavi dei nodi correnti. Se questa funzione restituisce 0, le chiavi sono uguali, altrimenti sono diverse.

La funzione restituisce 1 se gli alberi sono isomorfi, 0 altrimenti.
*/
