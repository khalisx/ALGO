#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int listereserv() {
    Voiture voitures[MAX_VOITURES];
    int nbVoitures = 0;

    LireFichierEtRemplirTableau("voiture.txt", voitures, &nbVoitures);
    
    // Tri des voitures
    trierTableau(voitures, nbVoitures);
    
    afficherTableau(voitures, nbVoitures);

    return 0;}

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

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

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

// Fonction pour calculer le prix de la location
void calcul_prix(int nbresemaines) {
    int prix = 100 * nbresemaines; // Prix de base pour 1 semaine : 100
    printf("Vous en aurez pour %d€.\n", prix); // Affichage du prix
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
