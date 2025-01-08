#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "voiture.h"

// Structure pour représenter une réservation dans l'historique
typedef struct {
    int id_location;    
    char prenom[50];    
    char nom[50];       
    char marque[50];  
    char modele[50];    
    int nbresemaines;   
} HistoriqueReservation;

// Fonction pour enregistrer une réservation dans l'historique
void enregistrer_historique(HistoriqueReservation reservation);

// Fonction pour afficher l'historique des réservations
void afficherHistorique();

#endif
