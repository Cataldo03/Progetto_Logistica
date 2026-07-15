#ifndef IMPLEMENTAZIONE_H_INCLUDED
#define IMPLEMENTAZIONE_H_INCLUDED

#include "strutture.h"
#include <stdbool.h>

bool ricaricaPortafoglio(Utente* u, double importo, Data d);
bool richiediSpedizione(Utente* mittente, ListaUtenti db, const char* dest, double costo, CodaSpedizioni* coda);
void elaboraCoda(ListaUtenti db, Data d, CodaSpedizioni* coda);
void calcolaFatturatoTotale(ListaUtenti db);

#endif
