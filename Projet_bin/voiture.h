#ifndef VOITURE_H
#define VOITURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VOITURES 100

#include "initfile.h"



typedef struct {
    char supprime[1]; // Contient un caractere espace par défaut ou un "*" si jamais l'enregistrement doit être supprimé
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut;
} Voiture;

void saisiVoiture(const char *nomFichier);
void saisirMarqueEtModele(char *marque, char *modele);
void ajouterVoiture(const char *nomFichier, Voiture voiture);
void supprimerVoiture(const char *nomFichier, Voiture voitures[], int nbVoitures, const char *marque, const char *modele);

void afficherContenuFichierVoiture(const char *nomFichier);

void LireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures);
void trierTableau(Voiture *voitures, int nbVoitures);
int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele);

void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee);
char convertirEnMinuscule(char c);


#endif
