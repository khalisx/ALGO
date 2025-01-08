#include <stdio.h>
#include <stdlib.h>
#include "historique.h"

void enregistrer_historique(HistoriqueReservation reservation) {
    FILE *file = fopen("historique_reservations.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "ID Location: %d\n", reservation.id_location);
    fprintf(file, "Prénom: %s\n", reservation.prenom);
    fprintf(file, "Nom: %s\n", reservation.nom);
    fprintf(file, "Marque: %s\n", reservation.marque);
    fprintf(file, "Modèle: %s\n", reservation.modele);
    fprintf(file, "Durée: %d semaine(s)\n", reservation.nbresemaines);

    fclose(file);
    printf("La réservation a été enregistrée dans l'historique.\n");
}

void afficherHistorique() {
    FILE *file = fopen("historique_reservations.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier historique.\n");
        return;
    }

    char ligne[100];
    printf("\nHistorique des réservations :\n");
    while (fgets(ligne, sizeof(ligne), file)) {
        printf("%s", ligne);
    }
    fclose(file);
}
