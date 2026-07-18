#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutture.h"
#include "implementazione.h"
#include "ordinamento.h"
#include "utente.h"

#define NOME_FILE "dati_logistica.txt"

void pulisciBuffer() {
    while(getchar() != '\n');
}

int chiediScelta() {
    int s;
    printf("\nScelta: ");
    scanf("%d", &s);
    pulisciBuffer();
    return s;
}

int main() {
    ListaUtenti db = caricaDaFile(NOME_FILE);
    CodaSpedizioni coda;
    inizializzaCoda(&coda);
