#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ordinamento.h"

void ordinaStoricoPerCosto(Utente* u) {
    if (u->storico == NULL || u->storico->next == NULL) return;

    bool scambiato = true;
    Spedizione* ptr1;
    Spedizione* lptr = NULL;

    while (scambiato) {
        scambiato = false;
        ptr1 = u->storico;

        while (ptr1->next != lptr) {
            if (ptr1->costoSpedizione < ptr1->next->costoSpedizione) {
                Spedizione temp = *ptr1;
                Spedizione* next1 = ptr1->next;
                Spedizione* next2 = ptr1->next->next;

                *ptr1 = *(ptr1->next);
                ptr1->next = next1;
                *(ptr1->next) = temp;
                ptr1->next->next = next2;

                scambiato = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}
void stampaStorico(Utente* u) {
    Spedizione* s = u->storico;
    if (s == NULL) {
        printf("Nessun movimento trovato.\n");
        return;
    }
    while (s != NULL) {
        printf("[%02d/%02d/%04d] %-10s | %-10s | Verso: %-10s | %.2lf EUR\n",
            s->dataOperazione.giorno, s->dataOperazione.mese, s->dataOperazione.anno,
            s->tracking, s->tipoSpedizione, s->destinatario, s->costoSpedizione);
        s = s->next;
    }
}

void cercaPerTracking(Utente* u, const char* trackDaCercare) {
    Spedizione* s = u->storico;
    while (s != NULL) {
        if (strcmp(s->tracking, trackDaCercare) == 0) {
            printf("\n--- PACCO TROVATO ---\n");
            printf("Data: %02d/%02d/%04d\n", s->dataOperazione.giorno, s->dataOperazione.mese, s->dataOperazione.anno);
            printf("Stato: %s\n", s->tipoSpedizione);
            printf("Destinazione: %s\n", s->destinatario);
            printf("Costo: %.2lf EUR\n", s->costoSpedizione);
            return;
        }
        s = s->next;
    }
    printf("\nNessun pacco trovato con il codice: %s\n", trackDaCercare);
}

