#ifndef STRUTTURE_H_INCLUDED
#define STRUTTURE_H_INCLUDED

#include <stdbool.h>


typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;


typedef struct spedizione {
    Data dataOperazione;
    char tracking[15];          
    char tipoSpedizione[30];
    char destinatario[50];
    double costoSpedizione;
    struct spedizione *next;
} Spedizione;


typedef struct utente {
    char username[50];
    char password[50];
    char codiceCliente[15];
    double saldoCredito;
    Spedizione *storico;
    struct utente *next;
} Utente;

typedef Utente* ListaUtenti;


typedef struct nodoCoda {
    char usernameMittente[50];
    char codiceDestinatario[15];
    char tracking[15];           
    double costoSpedizione;
    struct nodoCoda *next;
} NodoCodaSpedizione;

typedef struct {
    NodoCodaSpedizione *front;
    NodoCodaSpedizione *rear;
} CodaSpedizioni;


Utente* creaUtente(const char* username, const char* password, const char* codiceCliente);
void inserisciUtente(ListaUtenti* lista, Utente* nuovoUtente);
Utente* cercaUtentePerUsername(ListaUtenti lista, const char* username);
Utente* cercaUtentePerCodice(ListaUtenti lista, const char* codiceCliente);
bool eliminaUtente(ListaUtenti* lista, const char* username);

void inizializzaCoda(CodaSpedizioni *coda);
void enqueueSpedizione(CodaSpedizioni *coda, const char* mittente, const char* codiceDest, double costo, const char* track);
NodoCodaSpedizione* dequeueSpedizione(CodaSpedizioni *coda);
void aggiungiSpedizione(Utente* u, Data d, const char* tipo, const char* destinatario, double costo, const char* track);

#endif
