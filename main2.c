#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100

void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count);
void listCarModels(const char *filePath);

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
        getchar();  // Consomme le caractère de nouvelle ligne restant

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
                while (1) {
                    printf("1. Rechercher une voiture en particulier\n");
                    printf("2. Liste de nos voitures\n");
                    printf("3. Retour au menu principal\n");
                    printf("Votre choix: ");
                    scanf("%d", &choix);
                    getchar();  // Consomme le caractère de nouvelle ligne restant

                    switch (choix) {
                        case 1:
                            // Fonction pour rechercher une voiture (à implémenter)
                            break;

                        case 2:
                            listCarModels("voiture.txt");
                            break;

                        case 3:
                            goto main_menu;  // Retourne au menu principal
                            break;

                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                }

            case 3:
                // Fonctionnalité de réservation à implémenter
                break;

            case 4:
                printf("Fin du programme.\n");
                return 0;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

main_menu: // Étiquette pour retourner au menu principal
    return 0;
}

void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count) {
    char temp[MAX_MODEL_LENGTH];
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(models[i], models[j]) > 0) {
                strcpy(temp, models[i]);
                strcpy(models[i], models[j]);
                strcpy(models[j], temp);
            }
        }
    }
}

void listCarModels(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char models[MAX_CARS][MAX_MODEL_LENGTH];
    int modelCount = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        char *delimiter = strchr(line, ':');
        if (delimiter != NULL) {
            size_t modelLength = delimiter - line;
            strncpy(models[modelCount], line, modelLength);
            models[modelCount][modelLength] = '\0';  // Ajouter le caractère nul de fin
            modelCount++;
        }
    }

    fclose(file);

    // Trier les modèles par ordre alphabétique
    sortModelsAlphabetically(models, modelCount);

    // Afficher les modèles triés
    for (int i = 0; i < modelCount; i++) {
        printf("%s\n", models[i]);
    }
}