#ifndef VOITURE_H
#define VOITURE_H

#include "utils.h"

typedef struct {
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut;
} Voiture;

void afficherVoitures(const char *filename);
void ajouterVoiture(const char *filename);
int chargerVoitures(const char *filename, Voiture voitures[], int *car_count);
int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count);

#endif
