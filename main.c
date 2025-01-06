#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { 
    int choix; 
    char prenom[50], nom[50]; 
    FILE *file;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Se connecter\n");
        printf("2. Liste de nos voitures\n");
        printf("3. Reserver une voiture\n");
        printf("4. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrer votre prenom : "); 
                scanf("%s", prenom); 
                printf("Entrer votre nom : ");
                scanf("%s", nom);

                file = fopen("utilisateurs.txt", "a");
                if (file == NULL) {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    exit(EXIT_FAILURE);
                }

                fprintf(file, "Prenom: %s, Nom: %s\n", prenom, nom);
                fclose(file);

                printf("Bienvenue, %s %s ! Vos informations ont été enregistrées.\n", prenom, nom);
                break;

            case 2:


            case 3:
            

            case 4:
                printf("Fin du programme.\n");
                return 0;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
               
        }

    return 0;
    }
}
