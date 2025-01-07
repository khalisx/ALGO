#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100
#define MAX_VOITURES 100

void afficherHistorique();

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