#include "initfile.h"
#include "voiture.h"

void saisiVoiture(const char *nomFichier) {
    Voiture voiture;

    printf("Saisir la marque de la voiture : ");
    fgets(voiture.marque, sizeof(voiture.marque), stdin);
    voiture.marque[strcspn(voiture.marque, "\n")] = '\0'; // Retirer le saut de ligne

    printf("Saisir le modèle de la voiture : ");
    fgets(voiture.modele, sizeof(voiture.modele), stdin);
    voiture.modele[strcspn(voiture.modele, "\n")] = '\0'; // Retirer le saut de ligne

    printf("Saisir la plaque d'immatriculation : ");
    fgets(voiture.immatriculation, sizeof(voiture.immatriculation), stdin);
    voiture.immatriculation[strcspn(voiture.immatriculation, "\n")] = '\0'; // Retirer le saut de ligne

    voiture.statut = 0; // Statut par défaut

    ajouterVoiture(nomFichier, voiture);
}


void saisirMarqueEtModele(char *marque, char *modele) {
    printf("Saisir la marque de la voiture : ");
    fgets(marque, MAX_VOITURES, stdin);
    marque[strcspn(marque, "\n")] = '\0'; // Supprimer le saut de ligne

    printf("Saisir le modèle de la voiture : ");
    fgets(modele, MAX_VOITURES, stdin);
    modele[strcspn(modele, "\n")] = '\0'; // Supprimer le saut de ligne
}

// Fonction pour ajouter un enregistrement
void ajouterVoiture(const char *nomFichier, Voiture voiture) {
    FILE *fichier = fopen(nomFichier, "r+b");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lecture et mise à jour de l'entête
    Header entete;
    fread(&entete, sizeof(Header), 1, fichier);

    // Positionnement à la fin des enregistrements
    fseek(fichier, 0, SEEK_END);

    // Initialisation du champ supprime
    voiture.supprime[0] = ' ';

    // Écriture de l'enregistrement
    fwrite(&voiture, sizeof(Voiture), 1, fichier);

    // Mise à jour du nombre d'enregistrements dans l'entête
    entete.NbRecord++;

    // Retour en début de fichier pour mettre à jour l'entête
    fseek(fichier, 0, SEEK_SET);
    fwrite(&entete, sizeof(Header), 1, fichier);

    fclose(fichier);
    printf("Enregistrement ajouté avec succès.\n");
}


void supprimerVoiture(const char *nomFichier, Voiture voitures[], int nbVoitures, const char *marque, const char *modele) {
    FILE *fichier = fopen(nomFichier, "r+b");  // Ouvrir le fichier en lecture/écriture binaire
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s.\n", nomFichier);
        return;
    }

    Header entete;
    fread(&entete, sizeof(Header), 1, fichier); // Lire l'en-tête pour connaître la position initiale des enregistrements

    int voitureTrouvee = 0;

    // Chercher la voiture à supprimer
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(voitures[i].marque, marque) == 0 && strcmp(voitures[i].modele, modele) == 0) {
            // Marquer comme supprimée
            voitures[i].supprime[0] = '*';

            // Calculer la position exacte de l'enregistrement dans le fichier
            long position = entete.LengthHeader + (i * entete.LengthRecord);

            // Positionner le curseur à l'emplacement de l'enregistrement à modifier
            fseek(fichier, position, SEEK_SET);

            // Écrire l'enregistrement modifié
            fwrite(&voitures[i], sizeof(Voiture), 1, fichier);

            printf("Voiture %s %s marquée comme supprimée.\n", marque, modele);
            voitureTrouvee = 1;
            break;
        }
    }

    if (!voitureTrouvee) {
        printf("Voiture %s %s non trouvée.\n", marque, modele);
    }

    fclose(fichier);
}


// Fonction pour afficher le contenu du fichier
void afficherContenuFichierVoiture(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "rb");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lecture de l'entête
    Header entete;
    fread(&entete, sizeof(Header), 1, fichier);
    printf("--- Contenu du fichier %s ---\n", nomFichier);
    printf("Date de mise à jour : %02d/%02d/%04d\n", entete.jour, entete.mois, entete.annee);
    printf("Nombre d'enregistrements : %d\n", entete.NbRecord);
    printf("Taille de l'entête : %d octets\n", entete.LengthHeader);
    printf("Taille des enregistrements : %d octets\n", entete.LengthRecord);

    // Lecture des enregistrements
    Voiture voiture;
    printf("\n--- Enregistrements ---\n");
    for (int i = 0; i < entete.NbRecord; i++) {
        fread(&voiture, sizeof(Voiture), 1, fichier);
        printf("Enregistrement %d :\n", i + 1);
        printf("  Supprimé : %c\n", voiture.supprime[0]);
        printf("  Marque : %s\n", voiture.marque);
        printf("  Modèle : %s\n", voiture.modele);
        printf("  Immatriculation : %s\n", voiture.immatriculation);
        printf("  Statut : %d\n", voiture.statut);
        printf("--------------------\n");
    }

    fclose(fichier);
}




void LireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures) {
    FILE *fichier = fopen(nomFichier, "rb");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    *nbVoitures = 0;

    // Placer le curseur juste après l'en-tête
    placerCurseurApresHeader(fichier);

    Voiture voiture;
    while (fread(&voiture, sizeof(Voiture), 1, fichier) == 1) {
        if (*nbVoitures >= MAX_VOITURES) {
            printf("Limite maximale de voitures atteinte.\n");
            break;
        }

        // Vérifier si la voiture n'est pas marquée comme supprimée (supprime[0] == ' ')
        if (voiture.supprime[0] == ' ') {
            voitures[*nbVoitures] = voiture;
            (*nbVoitures)++;
        }
    }

    fclose(fichier);
}

void trierTableau(Voiture *voitures, int nbVoitures) {
    for (int i = 0; i < nbVoitures - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < nbVoitures; j++) {
            char marque1[50], marque2[50];
            char modele1[50], modele2[50];

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

        // Ignorer les caractères non pertinents (comme les espaces et astérisques) dans la marque de la voiture
        int indexMarque = 0;
        while (voitures[milieu].marque[indexMarque] == ' ' || voitures[milieu].marque[indexMarque] == '*') {
            indexMarque++;
        }

        // Copier la marque sans les caractères non pertinents
        strcpy(marqueVoiture, &voitures[milieu].marque[indexMarque]);

        normaliserChaine(marqueVoiture, marqueVoiture);
        normaliserChaine(voitures[milieu].modele, modeleVoiture);

        // Comparer la marque
        int comparaisonMarque = strcmp(marqueVoiture, marqueNormalisee);
        if (comparaisonMarque < 0) {
            gauche = milieu + 1;
        } else if (comparaisonMarque > 0) {
            droite = milieu - 1;
        } else {
            // Si la marque est égale, comparer le modèle
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


char convertirEnMinuscule(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // Décalage ASCII pour passer en minuscule
    }
    return c;
}

void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee) {
    while (*chaineOrigine == '*' || *chaineOrigine == ' ' || *chaineOrigine == '?') {
        chaineOrigine++; // Ignorer les caractères inutiles au début
    }

    while (*chaineOrigine) {
        unsigned char c = (unsigned char)*chaineOrigine;
        
        // Gestion des caractères accentués (UTF-8)
        if (c == 0xC3) { 
            unsigned char suivant = (unsigned char)*(chaineOrigine + 1);
            if (suivant == 0xA0 || suivant == 0xA1 || suivant == 0xA2 || suivant == 0xA3 || suivant == 0xA4 || suivant == 0xA5) {
                c = 'a'; // Transformation des accents en caractères non accentués
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
        
        *chaineNormalisee = tolower(c); // Mettre en minuscule
        chaineOrigine++;
        chaineNormalisee++;
    }
    *chaineNormalisee = '\0'; // Fin de chaîne
}
