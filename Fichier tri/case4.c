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

typedef struct {
    int id_location;    
    char prenom[50];    
    char nom[50];       
    char marque[50];  
    char modele[50];    
    int nbresemaines;   

} HistoriqueReservation;


void ajouterVoiture(const char *filename);
void supprimerVoiture(const char *filename);
void arreterReservation(const char *filename);
void afficherVoituresDisponibles(const char *filename);




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