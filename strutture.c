#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

Utente* creaUtente(const char* username, const char* password, const char* codiceCliente) {
    Utente* nuovo = (Utente*)malloc(sizeof(Utente));
    if (nuovo != NULL) {
        strcpy(nuovo->username, username);
        strcpy(nuovo->password, password);
        strcpy(nuovo->codiceCliente, codiceCliente);
        nuovo->saldoCredito = 0.0;
        nuovo->storico = NULL;
        nuovo->next = NULL;
    }
    return nuovo;
}

void inserisciUtente(ListaUtenti* lista, Utente* nuovoUtente) {
    if (nuovoUtente == NULL) return;
    if (*lista == NULL) {
        *lista = nuovoUtente;
    } else {
        Utente* temp = *lista;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nuovoUtente;
    }
}

Utente* cercaUtentePerUsername(ListaUtenti lista, const char* username) {
    Utente* curr = lista;
    while (curr != NULL) {
        if (strcmp(curr->username, username) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

Utente* cercaUtentePerCodice(ListaUtenti lista, const char* codiceCliente) {
    Utente* curr = lista;
    while (curr != NULL) {
        if (strcmp(curr->codiceCliente, codiceCliente) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

bool eliminaUtente(ListaUtenti* lista, const char* username) {
    Utente* curr = *lista;
    Utente* prec = NULL;
    while (curr != NULL) {
        if (strcmp(curr->username, username) == 0) {
            if (prec == NULL) *lista = curr->next;
            else prec->next = curr->next;

            Spedizione* s = curr->storico;
            while (s != NULL) {
                Spedizione* nextS = s->next;
                free(s);
                s = nextS;
            }

            free(curr);
            return true;
        }
        prec = curr;
        curr = curr->next;
    }
    return false;
}

void inizializzaCoda(CodaSpedizioni *coda) {
    coda->front = NULL;
    coda->rear = NULL;
}
