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
    Voiture *voitures = NULL;
    int nbVoitures = 0, tailleTableau = 0;
 
    lireFichierEtRemplirTableau(filePath, &voitures, &nbVoitures, &tailleTableau);
 
    // Trier les voitures
    trierTableau(voitures, nbVoitures);
 
    // Afficher uniquement les marques et modèles triés
    for (int i = 0; i < nbVoitures; i++) {
        printf("Marque: %s, Modèle: %s\n",
               voitures[i].marque,
               voitures[i].modele);
    }
 
    // Libérer la mémoire
    free(voitures);
}
 
int listereserv() {
    Voiture *voitures = NULL;
    int nbVoitures = 0, tailleTableau = 0;
    lireFichierEtRemplirTableau("voiture.txt", &voitures, &nbVoitures, &tailleTableau);
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
    afficherTableau(voitures, nbVoitures);
    // Libérer la mémoire
    free(voitures);
    return 0;
 
}
// Fonction pour calculer le prix de la location
void calcul_prix(int nbresemaines) {
    int prix = 100 * nbresemaines; // Prix de base pour 1 semaine : 100
    printf("Vous en aurez pour %d€.\n", prix); // Affichage du prix
    }

int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count) {
    // Ouvrir le fichier en mode écriture
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s pour écriture.\n", filename);
        return -1;
    }

    // Parcourir toutes les voitures et les écrire dans le fichier
    for (int i = 0; i < car_count; i++) {
        // Vérifier si la voiture est supprimée (indiquée par un champ `supprime` ou autre)
        if (voitures[i].supprime) {
            fprintf(file, "*%s,%s:%s/%d\n",
                    voitures[i].marque,          // Ajouter un astérisque devant la marque
                    voitures[i].modele,
                    voitures[i].immatriculation,
                    voitures[i].statut);
        } else {
            fprintf(file, "%s,%s:%s/%d\n",
                    voitures[i].marque,
                    voitures[i].modele,
                    voitures[i].immatriculation,
                    voitures[i].statut);
        }
    }

    // Fermer le fichier
    fclose(file);

    printf("Les données ont été sauvegardées avec succès dans %s.\n", filename);
    return 0;
}





 
int recherche() {
    Voiture *voitures = NULL;
    int nbVoitures = 0;
    int tailleTableau = 0;
 
    // Lire le fichier et remplir le tableau
    lireFichierEtRemplirTableau("voiture.txt", &voitures, &nbVoitures, &tailleTableau);
 
    // Trier le tableau
    trierTableau(voitures, nbVoitures);
    AfficherTableau(voitures, nbVoitures);
 
    // Recherche d'une voiture
    char marqueRecherchee[MAX_VOITURES], modeleRecherche[MAX_VOITURES];
    printf("\nEntrez la marque de la voiture à rechercher : ");
    scanf(" %[^\n]", marqueRecherchee);
 
    // Supprimer le '?' si l'utilisateur en a mis un devant la marque
    if (marqueRecherchee[0] == '?') {
        memmove(marqueRecherchee, marqueRecherchee + 1, strlen(marqueRecherchee));
    }
 
    printf("Entrez le modèle de la voiture à rechercher : ");
    scanf(" %[^\n]", modeleRecherche);
 
    // Normaliser les entrées utilisateur pour la recherche
    char marqueRechercheeNormalisee[MAX_VOITURES], modeleRechercheNormalisee[MAX_VOITURES];
    normaliserChaine(marqueRecherchee, marqueRechercheeNormalisee);
    normaliserChaine(modeleRecherche, modeleRechercheNormalisee);
 
    // Recherche dichotomique
    int indice = rechercheDichotomique(voitures, nbVoitures, marqueRechercheeNormalisee, modeleRechercheNormalisee);
   
    if (indice != -1) {
        // Affichage des informations de la voiture trouvée
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

    while (*chaineOrigine == '*' || *chaineOrigine == ' ' || *chaineOrigine == '?') {
        chaineOrigine++;
    }

    while (*chaineOrigine) {
        unsigned char c = (unsigned char)*chaineOrigine;
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
    *chaineNormalisee = '\0';
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
                // Remplissage des champs de la voiture
                strncpy((*voitures)[*nbVoitures].marque, ligne, tailleMarque);
                (*voitures)[*nbVoitures].marque[tailleMarque] = '\0';
 
                strncpy((*voitures)[*nbVoitures].modele, debutModele, tailleModele);
                (*voitures)[*nbVoitures].modele[tailleModele] = '\0';
 
                strncpy((*voitures)[*nbVoitures].immatriculation, debutPlaque, taillePlaque);
                (*voitures)[*nbVoitures].immatriculation[taillePlaque] = '\0';
 
                // Le statut : actif (1) ou supprimé (0)
                (*voitures)[*nbVoitures].statut = atoi(debutStatut);
 
                // Déterminer si la voiture est marquée comme supprimée
                // Si la marque commence par un astérisque, la voiture est supprimée
                (*voitures)[*nbVoitures].supprime = ((*voitures)[*nbVoitures].marque[0] == '*') ? 1 : 0;
 
                // Si la voiture est marquée comme supprimée, enlever l'astérisque de la marque
                if ((*voitures)[*nbVoitures].supprime) {
                    memmove((*voitures)[*nbVoitures].marque, (*voitures)[*nbVoitures].marque + 1, strlen((*voitures)[*nbVoitures].marque));
                }
 
                // Incrémenter le nombre de voitures lues
                (*nbVoitures)++;
            }
        }
    }
 
    fclose(fichier);
}
 
// Fonction pour nettoyer les points d'interrogation
void nettoyerTexte(char *texte) {
    int j = 0;
    for (int i = 0; texte[i] != '\0'; i++) {
        if (texte[i] != '?') {
            texte[j++] = texte[i];
        }
    }
    texte[j] = '\0'; // Terminer la chaîne proprement
}

void afficherTableau(Voiture voitures[], int nbVoitures) {
    printf("Liste des voitures disponibles :\n");
    int trouve = 0;

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].statut == 0) {  // Afficher uniquement les voitures disponibles
            char marque[50], modele[50];
            strcpy(marque, voitures[i].marque);
            strcpy(modele, voitures[i].modele);
            nettoyerTexte(marque);
            nettoyerTexte(modele);

            printf("%s, %s\n", marque, modele);
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
        char marque[50], modele[50];
        strcpy(marque, voitures[i].marque);
        strcpy(modele, voitures[i].modele);
        nettoyerTexte(marque);
        nettoyerTexte(modele);

        printf("Marque: %s, Modèle: %s, Plaque: %s, Statut: %d\n",
               marque, modele,
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
 
        // Ignorer l'astérisque et l'espace au début de la marque de la voiture
        int indexMarque = 0;
        while (voitures[milieu].marque[indexMarque] == ' ' || voitures[milieu].marque[indexMarque] == '*') {
            indexMarque++;
        }
 
        // Copie de la marque sans l'astérisque et l'espace au début
        strcpy(marqueVoiture, &voitures[milieu].marque[indexMarque]);
 
        normaliserChaine(marqueVoiture, marqueVoiture);
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
                return milieu;  // Voiture trouvée
            }
        }
    }
    return -1;  // Si la voiture n'est pas trouvée
}
 
void reserverVoiture(const char *filename) {
    Voiture *voitures = NULL;
    int nbVoitures = 0, tailleTableau = 0;
 
    lireFichierEtRemplirTableau(filename, &voitures, &nbVoitures, &tailleTableau);
    char marque[50], modele[50];
 
    printf("\nEntrer la marque de la voiture : ");
    fgets(marque, sizeof(marque), stdin);
    marque[strcspn(marque, "\n")] = '\0';
    printf("Entrer le modèle de la voiture : ");
    fgets(modele, sizeof(modele), stdin);
    modele[strcspn(modele, "\n")] = '\0';
 
    char marqueNormalisee[50], modeleNormalisee[50];
    normaliserChaine(marque, marqueNormalisee);
    normaliserChaine(modele, modeleNormalisee);
 
    int voitureTrouvee = 0;
 
    for (int i = 0; i < nbVoitures; i++) {
        char marqueTableau[50], modeleTableau[50];
        normaliserChaine(voitures[i].marque, marqueTableau);
        normaliserChaine(voitures[i].modele, modeleTableau);
 
        if (strcmp(marqueTableau, marqueNormalisee) == 0 && strcmp(modeleTableau, modeleNormalisee) == 0) {
            voitureTrouvee = 1;
            if (voitures[i].statut == 0) {
                printf("La voiture %s %s a été réservée avec succès.\n", voitures[i].marque, voitures[i].modele);
                voitures[i].statut = 1;
 
                int dernierId = lireDernierId();
 
                // Créer une nouvelle réservation
                HistoriqueReservation reservation;
                reservation.id_location = dernierId + 1;
                mettreAJourDernierId(reservation.id_location);

                printf("Entrez votre prénom: ");
                scanf("%s", reservation.prenom);
                printf("Entrez votre nom: ");
                scanf("%s", reservation.nom);
                printf("Entrez la durée de la location en semaines: ");
                scanf("%d", &reservation.nbresemaines);
 
                // Calcul du prix et enregistrement de l'historique
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
 
    // Libérer la mémoire allouée
 
    free(voitures);
 
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
    Voiture *voitures = NULL;
    int car_count = 0, taille_tableau = 0;
 
    lireFichierEtRemplirTableau(filename, &voitures, &car_count, &taille_tableau);
    char marque[50], modele[50];
    char marque_normalisee[50], modele_normalisee[50];
 
    printf("Entrer la marque de la voiture : ");
    viderTampon(); // Vider le tampon avant fgets
    fgets(marque, sizeof(marque), stdin);
    marque[strcspn(marque, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
 
    printf("Entrer le modèle de la voiture : ");
    fgets(modele, sizeof(modele), stdin);
    modele[strcspn(modele, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
 
    normaliserChaine(marque, marque_normalisee);
    normaliserChaine(modele, modele_normalisee);
 
    int voiture_trouvee = 0;
    for (int i = 0; i < car_count; i++) {
        char marque_voiture_normalisee[50], modele_voiture_normalisee[50];
        normaliserChaine(voitures[i].marque, marque_voiture_normalisee);
        normaliserChaine(voitures[i].modele, modele_voiture_normalisee);
 
        if (strcmp(marque_voiture_normalisee, marque_normalisee) == 0 &&
            strcmp(modele_voiture_normalisee, modele_normalisee) == 0) {
 
            voiture_trouvee = 1;
 
            if (voitures[i].statut == 1) {
                voitures[i].statut = 0;
                printf("La réservation de la voiture %s %s a été arrêtée.\n",
                       voitures[i].marque, voitures[i].modele);
            } else {
                printf("La voiture %s %s n'est pas réservée.\n",
                       voitures[i].marque, voitures[i].modele);
            }
            break;
        }
    }
 
    if (!voiture_trouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        sauvegarderVoitures(filename, voitures, car_count);
    }
 
    free(voitures);
}
 
void supprimerVoiture(const char *filename) {
    Voiture *voitures = NULL;
    int car_count = 0, taille_tableau = 0;

    // Charger les voitures depuis le fichier
    lireFichierEtRemplirTableau(filename, &voitures, &car_count, &taille_tableau);

    char marque[50], modele[50];
    char marque_normalisee[50], modele_normalisee[50];

    printf("Entrer la marque de la voiture à supprimer : ");
    viderTampon(); // Vider le tampon avant fgets
    fgets(marque, sizeof(marque), stdin);
    marque[strcspn(marque, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Entrer le modèle de la voiture à supprimer : ");
    fgets(modele, sizeof(modele), stdin);
    modele[strcspn(modele, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    // Normaliser les entrées utilisateur
    normaliserChaine(marque, marque_normalisee);
    normaliserChaine(modele, modele_normalisee);

    int voiture_trouvee = 0;

    for (int i = 0; i < car_count; i++) {
        char marque_voiture_normalisee[50], modele_voiture_normalisee[50];
        normaliserChaine(voitures[i].marque, marque_voiture_normalisee);
        normaliserChaine(voitures[i].modele, modele_voiture_normalisee);

        if (strcmp(marque_voiture_normalisee, marque_normalisee) == 0 &&
            strcmp(modele_voiture_normalisee, modele_normalisee) == 0) {
            voiture_trouvee = 1;

            // Ajouter un astérisque uniquement si la voiture n'en a pas déjà un
            if (voitures[i].marque[0] != '*') {
                char marque_temp[50];
                snprintf(marque_temp, sizeof(marque_temp), "*%s", voitures[i].marque);
                strncpy(voitures[i].marque, marque_temp, sizeof(voitures[i].marque) - 1);
                voitures[i].marque[sizeof(voitures[i].marque) - 1] = '\0'; // Assurez la terminaison
            }
            printf("La voiture %s %s a été marquée comme supprimée.\n",
                   marque, modele);
            break;
        }
    }

    if (!voiture_trouvee) {
        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);
    } else {
        // Sauvegarder les modifications dans le fichier
        sauvegarderVoitures(filename, voitures, car_count);
    }

    // Libérer la mémoire allouée
    free(voitures);
}

 
void viderTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void case2(){ 
    int choix;
    while (1) {
        printf("1. Rechercher une voiture en particulier\n");
        printf("2. Liste de nos voitures\n");
        printf("3. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar();  // Consomme le caractère de nouvelle ligne restant

        switch (choix) {
            case 1: // Option 1 : Recherche d'une voiture
                recherche(); break;
            case 2: // Option 2 : Liste de toutes les voitures
                listCarModels("voiture.txt"); break;
            case 3: // Option 3 : Retour au menu principal
                break; 
            default: // Gère les choix invalide
                printf("Choix invalide. Veuillez réessayer.\n");
            }
    if (choix == 3) break; // Quitte la boucle si l'utilisateur choisit de revenir au menu principal
    }
}

void case3(){
    int choix; 
    while (1) {
        printf("1. Liste des Voitures disponibles\n");
        printf("2. Réserver une voiture\n");
        printf("3. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar();  // Consomme le caractère de nouvelle ligne restant

        switch (choix) {
            case 1: // Option 1 : Afficher les voitures disponibles
                listereserv(); break;                           
            case 2: // Option 2 : Réserver une voiture
                reserverVoiture("voiture.txt"); break;
            case 3: // Option 3 : Retour au menu principal
                break;
            default: // Gère les choix invalides
                printf("Choix invalide. Veuillez réessayer.\n");
        }
        if (choix == 3) break; // Quitte la boucle si l'utilisateur choisit de revenir au menu principal
    }
}

void case4() {
    int admin_choix;
    int retour = 0;  // Variable pour quitter le menu Admin
    while (!retour) {    // Boucle pour afficher le menu Admin jusqu'à l'arrêt
        afficherMenuAdmin();    // Affiche le menu Admin
        scanf("%d", &admin_choix);

        switch (admin_choix) {
            case 1:   // Option 1 : Ajouter une voiture
                ajouterVoiture("voiture.txt"); break;
            case 2: // Option 2 : Supprimer une voiture
                supprimerVoiture("voiture.txt"); break;
            case 3:  // Option 3 : Arrêter une réservation
                arreterReservation("voiture.txt"); break;
            case 4: // Option 4 : Afficher les voitures disponibles
                listereserv(); break;
            case 5:  // Option 5 : Retour au menu principal
                printf("Retour au menu principal...\n");
                retour = 1;  // Change la variable pour quitter la boucle
                break;
            default: // Gère les choix invalides
                printf("Choix invalide.\n");
        }
    }
}


 