#include <stdio.h>

#include <stdlib.h>

#include <string.h>



#define TAILLE 20

#define MAX_VOITURES 100



typedef struct{

	char marque[TAILLE];

	char modele[TAILLE];

	char plaque[9];

	int statut;

}Voiture;







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



        // Extraction des données

        char *marque = strtok(ligne, ",");

        char *modele = strtok(NULL, ":");

        char *plaque = strtok(NULL, "/");

        char *statutStr = strtok(NULL, "/");



        if (marque && modele && plaque && statutStr) {

            strcpy(voitures[*nbVoitures].marque, marque);

            strcpy(voitures[*nbVoitures].modele, modele);

            strcpy(voitures[*nbVoitures].plaque, plaque);

            voitures[*nbVoitures].statut = atoi(statutStr);



            (*nbVoitures)++;

        }

    }



    fclose(fichier);

}













void afficherTableau(Voiture voitures[], int nbVoitures) {

    printf("Liste des voitures :\n");

    for (int i = 0; i < nbVoitures; i++) {

        printf(" %s,  %s,  %s,  %d\n", 

               voitures[i].marque, 

               voitures[i].modele, 

               voitures[i].plaque, 

               voitures[i].statut);

    }

}



int main() {

    Voiture voitures[MAX_VOITURES];

    int nbVoitures = 0;



    lireFichierEtRemplirTableau("Voiture.txt", voitures, &nbVoitures);

    afficherTableau(voitures, nbVoitures);



    return 0;

}