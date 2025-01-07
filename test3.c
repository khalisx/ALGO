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
void enregistrer_historique(HistoriqueReservation reservation);
void afficherHistorique();
void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count);
void listCarModels(const char *filePath);
int listereserv();
char convertirEnMinuscule(char c);
void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee);
void lireFichierEtRemplirTableau(const char *nomFichier, Voiture **voitures, int *nbVoitures, int *tailleTableau);
void LireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures);
void afficherTableau(Voiture voitures[], int nbVoitures);
void AfficherTableau(Voiture *voitures, int nbVoitures);
void trierTableau(Voiture *voitures, int nbVoitures);
int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele);


void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
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
void LireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures) {
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



int listereserv() {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);
    
    // Tri des voitures
    trierTableau(voitures, nbVoitures);
    
    afficherTableau(voitures, nbVoitures);

    return 0;
}


// Fonction pour calculer le prix de la location
void calcul_prix(int nbresemaines) {
    int prix = 100 * nbresemaines; // Prix de base pour 1 semaine : 100
    printf("Vous en aurez pour %d€.\n", prix); // Affichage du prix
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

int recherche() {

    Voiture *voitures = NULL; 
    int nbVoitures = 0;
    int tailleTableau = 0;

    // Lire le fichier et remplir le tableau
    lireFichierEtRemplirTableau("Voiture.txt", &voitures, &nbVoitures, &tailleTableau);

    // Trier le tableau
    trierTableau(voitures, nbVoitures);
    afficherTableau(voitures, nbVoitures);

    // Recherche d'une voiture
    char marqueRecherchee[MAX_VOITURES], modeleRecherche[MAX_VOITURES];
    printf("\nEntrez la marque de la voiture à rechercher : ");
    scanf(" %[^\n]", marqueRecherchee);
    printf("Entrez le modèle de la voiture à rechercher : ");
    scanf(" %[^\n]", modeleRecherche);

    int indice = rechercheDichotomique(voitures, nbVoitures, marqueRecherchee, modeleRecherche);

    if (indice != -1) {

        printf("Voiture trouvée : Marque: %s, Modèle: %s, Plaque: %s, Statut: %d\n",

               voitures[indice].marque,
               voitures[indice].modele,
               voitures[indice].immatriculation,
               voitures[indice].statut);

    } else {

        printf("Voiture non trouvée.\n");
    }



    // Libérer la mémoire allouée
    free(voitures);

    return 0;

}


char convertirEnMinuscule(char c) {

    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // Décalage ASCII pour passer en minuscule
    }

    return c;
}


// Fonction pour normaliser les caractères

void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee) {

    while (*chaineOrigine) {
        unsigned char c = (unsigned char)*chaineOrigine;

        // Remplacement explicite des caractères accentués avec leurs valeurs numériques
        if (c == 0xC3) {
            unsigned char suivant = (unsigned char)*(chaineOrigine + 1);

            if (suivant == 0xA0 || suivant == 0xA1 || suivant == 0xA2 || suivant == 0xA3 || suivant == 0xA4 || suivant == 0xA5) {
                c = 'a';
                chaineOrigine++;
            } else if (suivant == 0xA8 || suivant == 0xA9 || suivant == 0xAA || suivant == 0xAB) {
                c = 'e';
                chaineOrigine++;
            } else if (suivant == 0xAC || suivant == 0xAD || suivant == 0xAE || suivant == 0xAF) {
                c = 'i';
                chaineOrigine++;
            } else if (suivant == 0xB2 || suivant == 0xB3 || suivant == 0xB4 || suivant == 0xB5 || suivant == 0xB6 || suivant == 0xB7) {
                c = 'o';
                chaineOrigine++;
            } else if (suivant == 0xB9 || suivant == 0xBA || suivant == 0xBB || suivant == 0xBC || suivant == 0xBD || suivant == 0xBE) {
                c = 'u';
                chaineOrigine++;
            } else if (suivant == 0xA7) {
                c = 'c';
                chaineOrigine++;
            } else if (suivant == 0xB1) {
                c = 'n';
                chaineOrigine++;
            }

        }

        *chaineNormalisee = convertirEnMinuscule(c);
        chaineOrigine++;
        chaineNormalisee++;

    }

    *chaineNormalisee = '\0'; // Terminer la chaîne normalisée

}



void lireFichierEtRemplirTableau(const char *nomFichier, Voiture **voitures, int *nbVoitures, int *tailleTableau) {

    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[200];
    *nbVoitures = 0;
    *tailleTableau = MAX_VOITURES;
    *voitures = malloc(*tailleTableau * sizeof(Voiture));

    if (*voitures == NULL) {
        perror("Erreur lors de l'allocation mémoire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (*nbVoitures >= *tailleTableau) {
            *tailleTableau *= 2;
            *voitures = realloc(*voitures, *tailleTableau * sizeof(Voiture));
            if (*voitures == NULL) {
                perror("Erreur lors du redimensionnement mémoire");
                fclose(fichier);
                exit(EXIT_FAILURE);
            }
        }

        ligne[strcspn(ligne, "\n")] = '\0';
        char *debutModele = strchr(ligne, ',');
        char *debutPlaque = debutModele ? strchr(debutModele + 1, ':') : NULL;
        char *debutStatut = debutPlaque ? strchr(debutPlaque + 1, '/') : NULL;

        if (debutModele && debutPlaque && debutStatut) {
            debutModele++;
            debutPlaque++;
            debutStatut++;

            int tailleMarque = debutModele - ligne - 1;
            int tailleModele = debutPlaque - debutModele - 1;
            int taillePlaque = debutStatut - debutPlaque - 1;

            if (tailleMarque > 0 && tailleModele > 0 && taillePlaque > 0) {
                strncpy((*voitures)[*nbVoitures].marque, ligne, tailleMarque);
                (*voitures)[*nbVoitures].marque[tailleMarque] = '\0';

                strncpy((*voitures)[*nbVoitures].modele, debutModele, tailleModele);
                (*voitures)[*nbVoitures].modele[tailleModele] = '\0';

                strncpy((*voitures)[*nbVoitures].immatriculation, debutPlaque, taillePlaque);
                (*voitures)[*nbVoitures].immatriculation[taillePlaque] = '\0';

                (*voitures)[*nbVoitures].statut = atoi(debutStatut);

                (*nbVoitures)++;

            }

        }

    }

    fclose(fichier);

}

void afficherTableau(Voiture voitures[], int nbVoitures) {
    printf("Liste des voitures disponibles :\n");
    int trouve = 0;  // Pour vérifier s'il y a des voitures disponibles

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].statut == 0) {  // Afficher uniquement les voitures avec statut 1 (disponibles)
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



void AfficherTableau(Voiture *voitures, int nbVoitures) {

    printf("Liste des voitures :\n");
    for (int i = 0; i < nbVoitures; i++) {
        printf("Marque: %s, Modèle: %s, Plaque: %s, Statut: %d\n", 
               voitures[i].marque, 
               voitures[i].modele, 
               voitures[i].immatriculation, 
               voitures[i].statut);
    }
}



void trierTableau(Voiture *voitures, int nbVoitures) /*tri par sélection*/ {
    for (int i = 0; i < nbVoitures - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < nbVoitures; j++) {
            char marque1[MAX_VOITURES], marque2[MAX_VOITURES];
            char modele1[MAX_VOITURES], modele2[MAX_VOITURES];

            normaliserChaine(voitures[j].marque, marque1);
            normaliserChaine(voitures[indiceMin].marque, marque2);
            normaliserChaine(voitures[j].modele, modele1);
            normaliserChaine(voitures[indiceMin].modele, modele2);

            if (strcmp(marque1, marque2) < 0) {
                indiceMin = j;
            } else if (strcmp(marque1, marque2) == 0) {
                if (strcmp(modele1, modele2) < 0) {
                    indiceMin = j;
                }

            }

        }

        if (indiceMin != i) {
            Voiture temp = voitures[i];
            voitures[i] = voitures[indiceMin];
            voitures[indiceMin] = temp;
        }

    }

}



int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele) {

    int gauche = 0;
    int droite = nbVoitures - 1;
    char marqueNormalisee[MAX_VOITURES], modeleNormalisee[MAX_VOITURES];
    char marqueVoiture[MAX_VOITURES], modeleVoiture[MAX_VOITURES];

    // Normaliser les paramètres de recherche
    normaliserChaine(marque, marqueNormalisee);
    normaliserChaine(modele, modeleNormalisee);

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;

        // Normaliser la marque et le modèle de la voiture courante

        normaliserChaine(voitures[milieu].marque, marqueVoiture);

        normaliserChaine(voitures[milieu].modele, modeleVoiture);

        // Comparer les marques

        int comparaisonMarque = strcmp(marqueVoiture, marqueNormalisee);

        if (comparaisonMarque < 0) {
            gauche = milieu + 1;
        } else if (comparaisonMarque > 0) {
            droite = milieu - 1;
        } else {

            // Marques identiques, comparer les modèles

            int comparaisonModele = strcmp(modeleVoiture, modeleNormalisee);
            if (comparaisonModele < 0) {
                gauche = milieu + 1;
            } else if (comparaisonModele > 0) {
                droite = milieu - 1;
            } else {

                // Marque et modèle trouvés

                return milieu;

            }

        }

    }

    // Non trouvé

    return -1;

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
    printf("5. Historique des locations\n");
    printf("6. Quitter\n");
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
                while (1) {
                    printf("1. Rechercher une voiture en particulier\n");
                    printf("2. Liste de nos voitures\n");
                    printf("3. Retour au menu principal\n");
                    printf("Votre choix: ");
                    scanf("%d", &choix);
                    getchar();  // Consomme le caractère de nouvelle ligne restant

                    switch (choix) {
                        case 1:
                            recherche();
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
                            reserverVoiture("voiture.txt");
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
            afficherHistorique();
            break;
            case 6:
                printf("Fin du programme.\n");
                return 0;
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}