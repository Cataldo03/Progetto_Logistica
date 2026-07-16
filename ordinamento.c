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
