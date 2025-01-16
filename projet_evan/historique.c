#include <stdio.h>
#include <stdlib.h>
#include "historique.h"

// Fonction pour enregistrer l'historique des réservations en binaire
void enregistrer_historique(HistoriqueReservation reservation) {
    FILE *file = fopen("historique_reservations.txt", "ab");  // Ouvre le fichier en mode ajout binaire
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&reservation, sizeof(HistoriqueReservation), 1, file);  // Écrit la structure entière en binaire

    fclose(file);
    printf("La réservation a été enregistrée dans l'historique.\n");
}

// Fonction pour afficher l'historique des réservations à partir d'un fichier binaire
void afficherHistorique() {
    FILE *file = fopen("historique_reservations.txt", "rb");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier historique.\n");
        return;
    }

    HistoriqueReservation reservation;
    printf("\nHistorique des réservations :\n");

    // Lit et affiche chaque enregistrement jusqu'à la fin du fichier
    while (fread(&reservation, sizeof(HistoriqueReservation), 1, file)) {
        printf("ID Location: %d\n", reservation.id_location);
        printf("Prénom: %s\n", reservation.prenom);
        printf("Nom: %s\n", reservation.nom);
        printf("Marque: %s\n", reservation.marque);
        printf("Modèle: %s\n", reservation.modele);
        printf("Durée: %d semaine(s)\n\n", reservation.nbresemaines);
    }
    fclose(file);
}
