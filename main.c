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
int scelta = -1;
    while (scelta != 0) {
        printf("\n--- GESTIONALE SPEDIZIONI ---\n");
        printf("1. Accedi come Amministratore (Admin)\n");
        printf("2. Accedi come Cliente\n");
        printf("0. Esci\n");
        scelta = chiediScelta();

        if (scelta == 1) {
            int adminChoice = -1;
            while(adminChoice != 0) {
                printf("\n-- MENU ADMIN --\n");
                printf("1. Registra un nuovo Cliente\n");
                printf("2. Elabora la coda delle spedizioni\n");
                printf("3. Visualizza Fatturato Aziendale\n");
                printf("0. Torna indietro\n");
                adminChoice = chiediScelta();

                if (adminChoice == 1) {
                    char u[50], p[50], c[15];
                    printf("Username: "); scanf("%s", u);
                    printf("Password: "); scanf("%s", p);
                    printf("Codice Cliente: "); scanf("%s", c);
                    pulisciBuffer();

                    Utente* nuovo = creaUtente(u, p, c);
                    inserisciUtente(&db, nuovo);
                    salvaSuFile(db, NOME_FILE);
                    printf("Cliente salvato.\n");
                }
                else if (adminChoice == 2) {
                    elaboraCoda(db, dataOggi, &coda);
                    salvaSuFile(db, NOME_FILE);
                }
                else if (adminChoice == 3) {
                    calcolaFatturatoTotale(db);
                }
            }
        }
        else if (scelta == 2) {
            char u[50], p[50];
            printf("Username: "); scanf("%s", u);
            printf("Password: "); scanf("%s", p);
            pulisciBuffer();

            Utente* utente = cercaUtentePerUsername(db, u);
            if (utente != NULL && strcmp(utente->password, p) == 0) {

                int clientChoice = -1;
                while(clientChoice != 0) {
                    printf("\n-- BENVENUTO %s -- (Saldo: %.2lf EUR)\n", utente->username, utente->saldoCredito);
                    printf("1. Ricarica Credito\n");
                    printf("2. Richiedi Spedizione\n");
                    printf("3. Visualizza Storico\n");
                    printf("4. Riordina Storico per Costo\n");
                    printf("5. Traccia un Pacco (Ricerca per Tracking)\n");
                    printf("0. Logout\n");
                    clientChoice = chiediScelta();

                    if(clientChoice == 1) {
                        double imp;
                        printf("Importo: "); scanf("%lf", &imp); pulisciBuffer();
                        ricaricaPortafoglio(utente, imp, dataOggi);
                        salvaSuFile(db, NOME_FILE);
                    }
                    else if(clientChoice == 2) {
                        char dest[15]; double costo;
                        printf("Codice Destinatario: "); scanf("%s", dest);
                        printf("Costo Spedizione: "); scanf("%lf", &costo); pulisciBuffer();
                        richiediSpedizione(utente, db, dest, costo, &coda);
                    }
                    else if(clientChoice == 3) {
                        stampaStorico(utente);
                    }
                    else if(clientChoice == 4) {
                        ordinaStoricoPerCosto(utente);
                        printf("Storico riordinato decrescente.\n");
                    }
                    else if(clientChoice == 5) {
                        char trk[15];
                        printf("Inserisci Codice Tracking (es. TRK-1234): ");
                        scanf("%s", trk);
                        pulisciBuffer();
                        cercaPerTracking(utente, trk);
                    }
                }
            } else {
                printf("Credenziali errate.\n");
            }
        }
    }

    printf("Chiusura del gestionale in corso...\n");
    while (db != NULL) {
        char tempUsr[50];
        strcpy(tempUsr, db->username);
        eliminaUtente(&db, tempUsr);
    }
    return 0;
}
