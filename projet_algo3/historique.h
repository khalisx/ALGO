#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "voiture.h"

typedef struct {
    int id_location;    
    char prenom[50];    
    char nom[50];       
    char marque[50];  
    char modele[50];    
    int nbresemaines;   
} HistoriqueReservation;

void enregistrer_historique(HistoriqueReservation reservation);
void afficherHistorique();

#endif
