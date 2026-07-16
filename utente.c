#include <stdio.h>
#include "utente.h" 

void salvaSuFile(ListaUtenti lista, const char* nomeFile) {
    FILE* fp = fopen(nomeFile, "w");
    if (fp == NULL) return;

    Utente* curr = lista;
    while (curr != NULL) {
       
        fprintf(fp, "%s %s %s %.2lf\n", curr->username, curr->password, curr->codiceCliente, curr->saldoCredito);
        curr = curr->next;
    }
    fclose(fp);
}

ListaUtenti caricaDaFile(const char* nomeFile) {
    FILE* fp = fopen(nomeFile, "r");
    if (fp == NULL) return NULL; 

    ListaUtenti lista = NULL;
    char usr[50], pwd[50], cod[15];
    double sal;

    while (fscanf(fp, "%s %s %s %lf", usr, pwd, cod, &sal) == 4) {
        Utente* u = creaUtente(usr, pwd, cod);
        if (u != NULL) {
            u->saldoCredito = sal;
            inserisciUtente(&lista, u);
        }
    }
    fclose(fp);
    return lista;
}
