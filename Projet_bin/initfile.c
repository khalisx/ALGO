#include "initfile.h"


// Fonction pour initialiser le fichier Voiture.dat
void initialiserFichier(const char *nomFichier, size_t tailleStructure) {
    FILE *fichier = fopen(nomFichier, "rb");
    if (fichier) {
        // Le fichier existe déjà, on ne le réinitialise pas
        fclose(fichier);
        return;
    }

    fichier = fopen(nomFichier, "wb");
    if (!fichier) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }

    // Allocation dynamique pour le Header
    Header *entete = (Header *)malloc(sizeof(Header));
    if (!entete) {
        perror("Erreur d'allocation mémoire pour le Header");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    // Récupération de la date actuelle
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Initialisation de l'entête
    entete->jour = tm_info->tm_mday;
    entete->mois = tm_info->tm_mon + 1; // Les mois commencent à 0
    entete->annee = tm_info->tm_year + 1900; // Années depuis 1900
    entete->NbRecord = 0;
    entete->LengthHeader = sizeof(Header);
    entete->LengthRecord = tailleStructure;

    // Écriture de l'entête dans le fichier
    fwrite(entete, sizeof(Header), 1, fichier);

    // Libération de la mémoire allouée pour le Header
    free(entete);

    fclose(fichier);
    printf("Fichier %s initialisé avec succès.\n", nomFichier);
}

void placerCurseurApresHeader(FILE *fichier) {
    Header entete;
    fread(&entete, sizeof(Header), 1, fichier);
    fseek(fichier, entete.LengthHeader, SEEK_SET);
}
