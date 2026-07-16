#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementazione.h"

bool ricaricaPortafoglio(Utente* u, double importo, Data d) {
    if (importo <= 0) return false;
    u->saldoCredito += importo;
    aggiungiSpedizione(u, d, "Ricarica", "Account", importo, "---");
    printf("Ricarica di %.2lf completata.\n", importo);
    return true;
}

bool richiediSpedizione(Utente* mittente, ListaUtenti db, const char* dest, double costo, CodaSpedizioni* coda) {
    if (costo <= 0 || (mittente->saldoCredito - costo) < 0) {
        printf("Errore: Credito insufficiente o costo non valido.\n");
        return false;
    }
    mittente->saldoCredito -= costo;

    
    char trackingGenerato[15];
    sprintf(trackingGenerato, "TRK-%d", (rand() % 9000) + 1000);

    enqueueSpedizione(coda, mittente->username, dest, costo, trackingGenerato);
    printf("Spedizione registrata! Il tuo codice tracking e': %s\n", trackingGenerato);
    return true;
}

void elaboraCoda(ListaUtenti db, Data d, CodaSpedizioni* coda) {
    if (coda->front == NULL) {
        printf("Coda vuota. Nessun pacco da elaborare.\n");
        return;
    }
    while (coda->front != NULL) {
        NodoCodaSpedizione* pacco = dequeueSpedizione(coda);
        Utente* mitt = cercaUtentePerUsername(db, pacco->usernameMittente);
        Utente* dest = cercaUtentePerCodice(db, pacco->codiceDestinatario);

        if (mitt != NULL) {
            aggiungiSpedizione(mitt, d, "Inviato", pacco->codiceDestinatario, pacco->costoSpedizione, pacco->tracking);

            if (dest != NULL) {
                dest->saldoCredito += pacco->costoSpedizione;
                aggiungiSpedizione(dest, d, "Ricevuto", mitt->codiceCliente, pacco->costoSpedizione, pacco->tracking);
            }
        }
        free(pacco);
    }
    printf("Tutti i pacchi sono stati smistati.\n");
}
void calcolaFatturatoTotale(ListaUtenti db) {
    double totaleFatturato = 0.0;
    int pacchiSpediti = 0;

    Utente* currUtente = db;
    while (currUtente != NULL) {
        Spedizione* currSped = currUtente->storico;

        while (currSped != NULL) {
            if (strcmp(currSped->tipoSpedizione, "Inviato") == 0) {
                totaleFatturato += currSped->costoSpedizione;
                pacchiSpediti++;
            }
            currSped = currSped->next;
        }
        currUtente = currUtente->next;
    }

    printf("\n=== RESOCONTO AZIENDALE HUB LOGISTICO ===\n");
    printf("Pacchi processati in totale: %d\n", pacchiSpediti);
    printf("Fatturato Lordo Generato: %.2lf EUR\n", totaleFatturato);
    printf("=========================================\n");
}
