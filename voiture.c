#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voiture.h"
#include "historique.h"

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100
#define MAX_VOITURES 100

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
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau(filePath, voitures, &nbVoitures);

    // Trier les voitures
    trierTableau(voitures, nbVoitures);

    // Afficher uniquement les marques et modèles triés
    for (int i = 0; i < nbVoitures; i++) {
        printf("Marque: %s, Modèle: %s\n", voitures[i].marque, voitures[i].modele);
    }
}

int listereserv() {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);

    // Filtrer les voitures réservées
    Voiture voituresReservees[MAX_VOITURES];
    int nbReservees = 0;

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].statut == 1) { // Réservée
            voituresReservees[nbReservees++] = voitures[i];
        }
    }

    // Trier les voitures réservées
    trierTableau(voituresReservees, nbReservees);

    // Afficher les voitures réservées triées
    afficherTableau(voituresReservees, nbReservees);

    return 0;
}


// Fonction pour calculer le prix de la location
void calcul_prix(int nbresemaines) {
    int prix = 100 * nbresemaines; // Prix de base pour 1 semaine : 100
    printf("Vous en aurez pour %d€.\n", prix); // Affichage du prix
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
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);

    // Trier les voitures pour effectuer une recherche dichotomique
    trierTableau(voitures, nbVoitures);

    // Afficher toutes les voitures
    AfficherTableau(voitures, nbVoitures);

    // Demander les critères de recherche
    char marqueRecherchee[50], modeleRecherche[50];
    printf("\nEntrez la marque de la voiture à rechercher : ");
    scanf(" %[^\n]", marqueRecherchee);
    printf("Entrez le modèle de la voiture à rechercher : ");
    scanf(" %[^\n]", modeleRecherche);

    // Recherche dichotomique
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

        normaliserChaine(voitures[milieu].marque, marqueVoiture);
        normaliserChaine(voitures[milieu].modele, modeleVoiture);

        int comparaisonMarque = strcmp(marqueVoiture, marqueNormalisee);
        if (comparaisonMarque < 0) {
            gauche = milieu + 1;
        } else if (comparaisonMarque > 0) {
            droite = milieu - 1;
        } else {
            int comparaisonModele = strcmp(modeleVoiture, modeleNormalisee);
            if (comparaisonModele < 0) {
                gauche = milieu + 1;
            } else if (comparaisonModele > 0) {
                droite = milieu - 1;
            } else {
                return milieu;

            }
        }
    }
    return -1;
}

void reserverVoiture(const char *filename) {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau(filename, voitures, &nbVoitures);

    char marque[50], modele[50];
    printf("\nEntrer la marque de la voiture : ");
    scanf(" %[^\n]", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf(" %[^\n]", modele);

    int voitureTrouvee = 0;

    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(voitures[i].marque, marque) == 0 && strcmp(voitures[i].modele, modele) == 0) {
            voitureTrouvee = 1;
            if (voitures[i].statut == 0) {
                voitures[i].statut = 1; // Marquer comme réservée
                printf("La voiture %s %s a été réservée avec succès.\n", voitures[i].marque, voitures[i].modele);

                HistoriqueReservation reservation;
                reservation.id_location = lireDernierId() + 1;
                mettreAJourDernierId(reservation.id_location);

                printf("Entrez votre prénom : ");
                scanf("%s", reservation.prenom);
                printf("Entrez votre nom : ");
                scanf("%s", reservation.nom);
                printf("Entrez la durée de la location en semaines : ");
                scanf("%d", &reservation.nbresemaines);

                // Enregistrer la réservation dans l'historique
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

    if (!voitureTrouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        sauvegarderVoitures(filename, voitures, nbVoitures);
    }
}


int lireDernierId() {
    FILE *file = fopen("last_id.txt", "r");
    if (file == NULL) {
        return 0; // Retourne 0 si le fichier n'existe pas encore

    }

    int dernierId;
    fscanf(file, "%d", &dernierId);
    fclose(file);
    return dernierId;

}

void mettreAJourDernierId(int nouvelId) {
    FILE *file = fopen("last_id.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de la mise à jour du dernier ID");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d", nouvelId);
    fclose(file);

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
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau(filename, voitures, &nbVoitures);

    char marque[50], modele[50];
    printf("Entrer la marque de la voiture : ");
    scanf(" %[^\n]", marque);
    printf("Entrer le modèle de la voiture : ");
    scanf(" %[^\n]", modele);

    int voitureTrouvee = 0;

    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(voitures[i].marque, marque) == 0 && strcmp(voitures[i].modele, modele) == 0) {
            voitureTrouvee = 1;
            if (voitures[i].statut == 1) {
                voitures[i].statut = 0; // Marquer comme disponible
                printf("La réservation de la voiture %s %s a été arrêtée.\n", voitures[i].marque, voitures[i].modele);
            } else {
                printf("La voiture %s %s n'est pas réservée.\n", voitures[i].marque, voitures[i].modele);
            }
            break;
        }
    }

    if (!voitureTrouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        sauvegarderVoitures(filename, voitures, nbVoitures);
    }
}

void supprimerVoiture(const char *filename) {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau(filename, voitures, &nbVoitures);

    char marque[50], modele[50];
    printf("Entrer la marque de la voiture à supprimer : ");
    scanf(" %[^\n]", marque);
    printf("Entrer le modèle de la voiture à supprimer : ");
    scanf(" %[^\n]", modele);

    int voitureTrouvee = 0;

    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(voitures[i].marque, marque) == 0 && strcmp(voitures[i].modele, modele) == 0) {
            voitureTrouvee = 1;
            // Décaler les voitures pour supprimer l'entrée
            for (int j = i; j < nbVoitures - 1; j++) {
                voitures[j] = voitures[j + 1];
            }
            nbVoitures--;
            break;
        }
    }

    if (!voitureTrouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        sauvegarderVoitures(filename, voitures, nbVoitures);
        printf("La voiture %s %s a été supprimée avec succès.\n", marque, modele);
    }
}

void viderTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


