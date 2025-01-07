#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut; // 0 = Disponible, 1 = Louée
} Voiture;

typedef struct {
    int id_location;    
    char prenom[50];    
    char nom[50];       
    char marque[50];  
    char modele[50];    
    int nbresemaines;   
} HistoriqueReservation;

static int id_location = 1;  // Compteur pour l'ID de la location

// Fonction pour convertir une chaîne en minuscules
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Fonction pour calculer le prix de la location
void calcul_prix(int nbresemaines) {
    int prix = 100 * nbresemaines; // Prix de base pour 1 semaine : 100
    printf("Vous en aurez pour %d€.\n", prix); // Affichage du prix
}

// Fonction pour charger les données du fichier
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
        if (*car_count >= 50) {
            printf("Limite maximale de voitures atteinte.\n");
            break;
        }
    }

    fclose(file);
    return 0;
}

// Fonction pour sauvegarder les données mises à jour
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

// Fonction pour enregistrer l'historique des réservations
void enregistrer_historique(HistoriqueReservation reservation) {
    FILE *file = fopen("historique_reservations.txt", "a");  // Ouvre le fichier en mode ajout
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "ID Location: %d\n", reservation.id_location);
    fprintf(file, "Prénom: %s\n", reservation.prenom);
    fprintf(file, "Nom: %s\n", reservation.nom);
    fprintf(file, "Marque: %s\n", reservation.marque);
    fprintf(file, "Modèle: %s\n", reservation.modele);
    fprintf(file, "Durée: %d semaine(s)\n", reservation.nbresemaines);

    fclose(file);
    printf("La réservation a été enregistrée dans l'historique.\n");
}

// Fonction pour afficher l'historique des réservations
void afficherHistorique() {
    FILE *file = fopen("historique_reservations.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier historique.\n");
        return;
    }

    char ligne[100];
    printf("\nHistorique des réservations :\n");
    while (fgets(ligne, sizeof(ligne), file)) {
        printf("%s", ligne);
    }

    fclose(file);
}

// Fonction pour réserver une voiture
void reserverVoiture(const char *filename) {
    Voiture voitures[50];
    int car_count;

    if (chargerVoitures(filename, voitures, &car_count) != 0) {
        return;
    }

    char marque[50], modele[50];
    printf("\nEntrer la marque de la voiture : ");
    scanf("%s", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf("%s", modele);

    // Convertir les saisies utilisateur en minuscules
    toLowerCase(marque);
    toLowerCase(modele);

    // Chercher la voiture et vérifier son statut
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
                voitures[i].statut = 1; // Marquer comme louée

                // Demander des informations supplémentaires pour l'historique
                HistoriqueReservation reservation;
                printf("Entrez votre prénom: ");
                scanf("%s", reservation.prenom);
                printf("Entrez votre nom: ");
                scanf("%s", reservation.nom);
                printf("Entrez la durée de la location en semaines: ");
                scanf("%d", &reservation.nbresemaines);

                // Calcul du prix
                calcul_prix(reservation.nbresemaines);

                strcpy(reservation.marque, voitures[i].marque);
                strcpy(reservation.modele, voitures[i].modele);

                enregistrer_historique(reservation);
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

    // Sauvegarder les mises à jour dans le fichier
    sauvegarderVoitures(filename, voitures, car_count);
}

int main() {
    while (1) {
        printf("\nMenu:\n");
        printf("1. Réserver une voiture\n");
        printf("2. Afficher l'historique des réservations\n");
        printf("3. Quitter\n");
        printf("Votre choix: ");

        int choix;
        scanf("%d", &choix);

        if (choix == 1) {
            reserverVoiture("voiture.txt");
        } else if (choix == 2) {
            afficherHistorique();
        } else if (choix == 3) {
            printf("Fin du programme.\n");
            break;
        } else {
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
