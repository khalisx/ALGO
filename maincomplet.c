#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100
#define MAX_VOITURES 100
#define TAILLE 20
typedef struct{
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut;
}Voiture;

typedef struct{
    char prenom[50];
    char nom[50];
}client;

void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count);
void listCarModels(const char *filePath);
int listereserv();
void afficherTableau(Voiture voitures[], int nbVoitures);
void trierTableau(Voiture voitures[], int nbVoitures);
void lireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures);

// Fonction pour convertir une chaîne en minuscules
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int chargerVoitures(Voiture voitures[], int *car_count) {
    FILE *file = fopen("voiture.txt", "r"); 
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier voiture.txt.\n");
        return -1;
    }

    *car_count = 0;

    while (fscanf(file, "%[^,],%[^:]:%[^/]/%d\n", 
                  voitures[*car_count].marque, 
                  voitures[*car_count].modele, 
                  voitures[*car_count].immatriculation, 
                  &voitures[*car_count].statut) == 4) {
        (*car_count)++;
        if (*car_count >= 50) {
            printf("Limite maximale de voitures atteinte.\n");
            break;
        }
    }

    fclose(file);
    return 0;
}

int sauvegarderVoitures(Voiture voitures[], int car_count) {
    FILE *file = fopen("voiture.txt", "w"); 
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier voiture.txt.\n");
        return -1;
    }

    for (int i = 0; i < car_count; i++) {
        fprintf(file, "%s,%s:%s/%d\n", 
                voitures[i].marque, 
                voitures[i].modele, 
                voitures[i].immatriculation, 
                voitures[i].statut);
    }

    fclose(file);
    return 0;
}

void reserverVoiture() {
    Voiture voitures[50];
    int car_count;

    // Charger les données depuis "voiture.txt"
    if (chargerVoitures(voitures, &car_count) != 0) {
        return;
    }

    char marque[50], modele[50];
    printf("\nEntrer la marque de la voiture : ");
    scanf("%s", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf("%s", modele);

    toLowerCase(marque);
    toLowerCase(modele);

    // Cherche la voiture et vérifier son statut
    int voiture_trouvee = 0;
    for (int i = 0; i < car_count; i++) {
        char marque_lower[50], modele_lower[50];
        strcpy(marque_lower, voitures[i].marque);
        strcpy(modele_lower, voitures[i].modele);
        toLowerCase(marque_lower);
        toLowerCase(modele_lower);

        if (strcmp(marque_lower, marque) == 0 && strcmp(modele_lower, modele) == 0) {
            voiture_trouvee = 1;
            if (voitures[i].statut == 0) {
                printf("La voiture %s %s a été réservée avec succès.\n", voitures[i].marque, voitures[i].modele);
                voitures[i].statut = 1; 
            } else {
                printf("La voiture %s %s est déjà réservée.\n", voitures[i].marque, voitures[i].modele);
            }
            break;
        }
    }

    if (!voiture_trouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
        return;
    }
    sauvegarderVoitures(voitures, car_count);
}


int main() { 
    int choix, count, statut;  
    char prenom[50], nom[50]; 
    Voiture voitures[50];
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
                            // Retour au menu principal
                            break;

                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }

                    if (choix == 3) break; // Si l'utilisateur choisit de revenir au menu principal
                }
                break;

            case 3:
                while (1) {
                    printf("1. Liste des Voitures disponibles\n");
                    printf("2. Réserver une voiture\n");
                    printf("3. Retour au menu principal\n");
                    printf("Votre choix: ");
                    scanf("%d", &choix);
                    getchar();  // Consomme le caractère de nouvelle ligne restant

                    switch (choix) {
                        case 1:
                            listereserv();
                            break;

                        case 2:
                            reserverVoiture();
                            break;

                        case 3:
                            // Retour au menu principal
                            break;

                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }

                    if (choix == 3) break; // Si l'utilisateur choisit de revenir au menu principal
                }
                break;

            case 4:
                printf("Fin du programme.\n");
                return 0;
            
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }
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
        char *immatriculation = strtok(NULL, "/");
        char *statutStr = strtok(NULL, "/");

        if (marque && modele && immatriculation && statutStr) {
            // Copie des données extraites dans la structure Voiture
            strncpy(voitures[*nbVoitures].marque, marque, sizeof(voitures[*nbVoitures].marque) - 1);
            strncpy(voitures[*nbVoitures].modele, modele, sizeof(voitures[*nbVoitures].modele) - 1);
            strncpy(voitures[*nbVoitures].immatriculation, immatriculation, sizeof(voitures[*nbVoitures].immatriculation) - 1);
            voitures[*nbVoitures].statut = atoi(statutStr);

            // Assurez-vous que la plaque est bien terminée par un caractère nul
            voitures[*nbVoitures].immatriculation[8] = '\0';

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

int listereserv() {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    lireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);
    
    // Tri des voitures
    trierTableau(voitures, nbVoitures);
    
    afficherTableau(voitures, nbVoitures);

    return 0;
}
