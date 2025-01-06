#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 20
#define MAX_VOITURES 100

typedef struct {
    char marque[TAILLE];
    char modele[TAILLE];
    char plaque[9];
    int statut;
} Voiture;

void lireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[200];
    *nbVoitures = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (*nbVoitures >= MAX_VOITURES) {
            printf("Limite maximale de voitures atteinte.\n");
            break;
        }

        // Suppression du saut de ligne à la fin de la ligne
        ligne[strcspn(ligne, "\n")] = '\0';

        // Extraction des données en utilisant strtok
        char *marque = strtok(ligne, ",");
        char *modele = strtok(NULL, ":");
        char *plaque = strtok(NULL, "/");
        char *statutStr = strtok(NULL, "/");

        if (marque && modele && plaque && statutStr) {
            // Copie des données extraites dans la structure Voiture
            strncpy(voitures[*nbVoitures].marque, marque, sizeof(voitures[*nbVoitures].marque) - 1);
            strncpy(voitures[*nbVoitures].modele, modele, sizeof(voitures[*nbVoitures].modele) - 1);
            strncpy(voitures[*nbVoitures].plaque, plaque, sizeof(voitures[*nbVoitures].plaque) - 1);
            voitures[*nbVoitures].statut = atoi(statutStr);

            // Assurez-vous que la plaque est bien terminée par un caractère nul
            voitures[*nbVoitures].plaque[8] = '\0';

            (*nbVoitures)++;
        }
    }

    fclose(fichier);
}

void trierTableau(Voiture voitures[], int nbVoitures) {
    for (int i = 0; i < nbVoitures - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < nbVoitures; j++) {
            // Comparer les marques
            if (strcmp(voitures[j].marque, voitures[indiceMin].marque) < 0) {
                indiceMin = j;
            } else if (strcmp(voitures[j].marque, voitures[indiceMin].marque) == 0) {
                // Si les marques sont identiques, comparer les modèles
                if (strcmp(voitures[j].modele, voitures[indiceMin].modele) < 0) {
                    indiceMin = j;
                }
            }
        }

        // Échanger les voitures
        if (indiceMin != i) {
            Voiture temp = voitures[i];
            voitures[i] = voitures[indiceMin];
            voitures[indiceMin] = temp;
        }
    }
}

void afficherTableau(Voiture voitures[], int nbVoitures) {
    printf("Liste des voitures disponibles :\n");
    int trouve = 0;  // Pour vérifier s'il y a des voitures disponibles

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].statut == 1) {  // Afficher uniquement les voitures avec statut 1 (disponibles)
            printf("%s, %s\n",  // Affiche uniquement marque et modèle
                   voitures[i].marque, 
                   voitures[i].modele);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune voiture disponible.\n");
    }
}

int main() {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    lireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);
    
    printf("Avant le tri :\n");
    afficherTableau(voitures, nbVoitures);

    // Tri des voitures
    trierTableau(voitures, nbVoitures);
    
    printf("\nAprès le tri :\n");
    afficherTableau(voitures, nbVoitures);

    return 0;
}
