#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "voiture.h"
#include "initfile.h"

int main() {
    const char *nomFichier = "Voiture.dat";
    int choix;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Initialiser le fichier Voiture.dat\n");
        printf("2. Ajouter un enregistrement\n");
        printf("3. Supprimer un enregistrement\n");
        printf("4. Afficher le contenu du fichier\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Pour consommer le caractère '\n' laissé par scanf

        switch (choix) {
            case 1:
                // Ajout de la taille des enregistrements à initialiser
                initialiserFichier(nomFichier, sizeof(Voiture));
                break;
            case 2:
                saisiVoiture(nomFichier);
                break;
            case 3: {
                Voiture voitures[MAX_VOITURES];
                int nbVoitures = 0;
                LireFichierEtRemplirTableau(nomFichier, voitures, &nbVoitures);

                char marqueSaisie[50], modeleSaisie[50];
                printf("Saisir la marque de la voiture à supprimer : ");
                fgets(marqueSaisie, sizeof(marqueSaisie), stdin);
                marqueSaisie[strcspn(marqueSaisie, "\n")] = '\0';

                printf("Saisir le modèle de la voiture à supprimer : ");
                fgets(modeleSaisie, sizeof(modeleSaisie), stdin);
                modeleSaisie[strcspn(modeleSaisie, "\n")] = '\0';

                supprimerVoiture(nomFichier, voitures, nbVoitures, marqueSaisie, modeleSaisie);
                break;
            }
            case 4:
                afficherContenuFichierVoiture(nomFichier);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}
