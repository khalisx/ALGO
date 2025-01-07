#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100
#define MAX_VOITURES 100


typedef struct {
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut;
} Voiture;

void toLowerCase(char *str);
void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count);
int chargerVoitures(const char *filename, Voiture voitures[], int *car_count);
int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count);
void reserverVoiture(const char *filename);
void ajouterVoiture(const char *filename);
void arreterReservation(const char *filename);
void afficherVoituresDisponibles(const char *filename);
void afficherVoitures(const char *filename);
void afficherMenuPrincipal();
void afficherMenuAdmin();

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int chargerVoitures(const char *filename, Voiture voitures[], int *car_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return -1;
    }

    *car_count = 0;

    while (fscanf(file, "%[^,],%[^:]:%[^/]/%d\n", 
                  voitures[*car_count].marque, 
                  voitures[*car_count].modele, 
                  voitures[*car_count].immatriculation, 
                  &voitures[*car_count].statut) == 4) {
        (*car_count)++;
        if (*car_count >= MAX_CARS) {
            printf("Limite maximale de voitures atteinte.\n");
            break;
        }
    }

    fclose(file);
    return 0;
}

int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
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

void reserverVoiture(const char *filename) {
    Voiture voitures[MAX_CARS];
    int car_count;

    if (chargerVoitures(filename, voitures, &car_count) != 0) {
        return;
    }

    char marque[50], modele[50];
    printf("\nEntrer la marque de la voiture : ");
    scanf("%s", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf("%s", modele);

    toLowerCase(marque);
    toLowerCase(modele);

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
    } else {
        sauvegarderVoitures(filename, voitures, car_count);
    }
}

void ajouterVoiture(const char *filename) {
    Voiture nouvelle_voiture;

    printf("Entrer la marque de la voiture : ");
    scanf("%s", nouvelle_voiture.marque);
    printf("Entrer le modèle de la voiture : ");
    scanf("%s", nouvelle_voiture.modele);
    printf("Entrer l'immatriculation de la voiture : ");
    scanf("%s", nouvelle_voiture.immatriculation);

    nouvelle_voiture.statut = 0;

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    fprintf(file, "%s,%s:%s/%d\n", 
            nouvelle_voiture.marque, 
            nouvelle_voiture.modele, 
            nouvelle_voiture.immatriculation, 
            nouvelle_voiture.statut);
    fclose(file);

    printf("La voiture %s %s a été ajoutée avec succès.\n", nouvelle_voiture.marque, nouvelle_voiture.modele);
}

void arreterReservation(const char *filename) {
    Voiture voitures[MAX_CARS];
    int car_count;

    if (chargerVoitures(filename, voitures, &car_count) != 0) {
        return;
    }

    char marque[50], modele[50];
    printf("Entrer la marque de la voiture : ");
    scanf("%s", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf("%s", modele);

    toLowerCase(marque);
    toLowerCase(modele);

    int voiture_trouvee = 0;
    for (int i = 0; i < car_count; i++) {
        char marque_lower[50], modele_lower[50];
        strcpy(marque_lower, voitures[i].marque);
        strcpy(modele_lower, voitures[i].modele);
        toLowerCase(marque_lower);
        toLowerCase(modele_lower);

        if (strcmp(marque_lower, marque) == 0 && strcmp(modele_lower, modele) == 0) {
            voiture_trouvee = 1;
            if (voitures[i].statut == 1) {
                voitures[i].statut = 0;
                printf("La réservation de la voiture %s %s a été arrêtée.\n", voitures[i].marque, voitures[i].modele);
            } else {
                printf("La voiture %s %s n'est pas réservée.\n", voitures[i].marque, voitures[i].modele);
            }
            break;
        }
    }

    if (!voiture_trouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        sauvegarderVoitures(filename, voitures, car_count);
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

void afficherVoituresDisponibles(const char *filename) {
    FILE *file = fopen("voiture.txt", "r");
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

    sortModelsAlphabetically(models, modelCount);

    // Afficher les modèles triés
    for (int i = 0; i < modelCount; i++) {
        printf("%s\n", models[i]);
    }
}

void afficherVoitures(const char *filename) {
    FILE *file = fopen("voiture.txt", "r");
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

    sortModelsAlphabetically(models, modelCount);

    for (int i = 0; i < modelCount; i++) {
        printf("%s\n", models[i]);
    }
}

void supprimerVoiture(const char *filename) {
    Voiture voitures[MAX_CARS];
    int car_count;

    // Charger les voitures depuis le fichier
    if (chargerVoitures(filename, voitures, &car_count) != 0) {
        return;
    }

    char marque[50], modele[50];
    printf("Entrer la marque de la voiture à supprimer : ");
    scanf("%s", marque);
    printf("Entrer le modèle de la voiture à supprimer : ");
    scanf("%s", modele);

    toLowerCase(marque);
    toLowerCase(modele);

    int voiture_trouvee = 0;

    // Rechercher et supprimer la voiture
    for (int i = 0; i < car_count; i++) {
        char marque_lower[50], modele_lower[50];
        strcpy(marque_lower, voitures[i].marque);
        strcpy(modele_lower, voitures[i].modele);
        toLowerCase(marque_lower);
        toLowerCase(modele_lower);

        if (strcmp(marque_lower, marque) == 0 && strcmp(modele_lower, modele) == 0) {
            voiture_trouvee = 1;
            // Décaler les éléments après la voiture supprimée
            for (int j = i; j < car_count - 1; j++) {
                voitures[j] = voitures[j + 1];
            }
            car_count--; // Réduire le nombre de voitures
            printf("La voiture %s %s a été supprimée avec succès.\n", marque, modele);
            break;
        }
    }

    if (!voiture_trouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
        return;
    }

    sauvegarderVoitures(filename, voitures, car_count);
}

void afficherMenuPrincipal() {
    printf("\nMenu principal :\n");
    printf("1. Se connecter\n");
    printf("2. Liste de nos voitures\n");
    printf("3. Réserver une voiture\n");
    printf("4. Mode Admin\n");
    printf("5. Quitter\n");
    printf("Votre choix : ");
}

void afficherMenuAdmin() {
    printf("\n--- Mode Admin ---\n");
    printf("1. Ajouter une voiture\n");
    printf("2. Supprimer une voiture\n");
    printf("3. Arrêter une réservation\n");
    printf("4. Afficher les voitures disponibles\n");
    printf("5. Retour au menu principal\n");
    printf("Votre choix : ");
}


int main() {
    int choix;
    char prenom[50], nom[50]; 
    FILE *file; 

    while (1) {
        afficherMenuPrincipal();
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
                afficherVoitures("voiture.txt");
                break;
            case 3:
                reserverVoiture("voiture.txt");
                break;
            case 4: {
                int admin_choix;
                while (1) {
                    afficherMenuAdmin();
                    scanf("%d", &admin_choix);

                    if (admin_choix == 4) break;

                    switch (admin_choix) {
                        case 1:
                            ajouterVoiture("voiture.txt");
                            break;
                        case 2: 
                            supprimerVoiture("voiture.txt");
                            break; 
                        case 3:
                            arreterReservation("voiture.txt");
                            break;
                        case 4:
                            afficherVoituresDisponibles("voiture.txt");
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                }
                break;
            }
            case 5:
                printf("Fin du programme.\n");
                return 0;
            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
