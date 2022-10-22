/*
 * file composto da un numero indenfinito di righe
 * forma
 * <codice> <nome> <cognome> <data_dinascita> <via> <citta> <cap>
 *      <data_nascita> formato gg/mm/aaaa
 *      <cap> numero intero
 *      <campirimanenti> stringhe senzaspazi max50char
 *      <codice> formato AXXXXX dove X rappresenta una cifra tra 0-9, univoco
 *
 * dettagli anagrafica racchiusi in un opportuno dato di tipo item
 *
 * anagrafica va memorizzata in una lista ordinata per data di nascita
 *      le persone piu giovani appaiono prima nella lista
 *      
 * primo passo: inizializzare lista vuota
 * 
 * funzionalità
 * acquisizione ed inserimento ordinato di un nuovo elemento in lista da tastiera
 * acquisizione ed inserimento ordinato di nuovi elementi in lista da tastiera
 * ricerca per codice 
 * cancellazione con estrazione del dato di un elemento dalla lista previa ricerca per codice
 * cancellazione con estrazione del dato di tutti gli elementi con date comprese tra 2 date lette da testiera 
 *      suggerimento: implemtnetare una funzione che estrae e restituisce al programma chiamante il primo degli elementi appartenenti all intervallo
 *                    il programma chiamante itera la chiamata di questa funzione
 *                    stamapando il risultato per tutti gli elementi dell'intervallo
 * stampa della lista su file
 * 
 * per le funzioni di ricerca e cancellazione è richiesto che la funzione che opera sulle liste ritorni l'elemento trovato o cancellato al programma chiamante che provvede alla stampa
 */

#define MAXN 50

