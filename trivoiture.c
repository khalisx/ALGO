#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 50

typedef struct {
    char marque[TAILLE];
    char modele[TAILLE];
    char plaque[9];
    int statut;
} Voiture;

// Prototypes des fonctions

char convertirEnMinuscule(char c);
void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee);
void lireFichierEtRemplirTableau(const char *nomFichier, Voiture **voitures, int *nbVoitures, int *tailleTableau);
void afficherTableau(Voiture *voitures, int nbVoitures);
void trierTableau(Voiture *voitures, int nbVoitures);
int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele);



int main() {

    Voiture *voitures = NULL; 
    int nbVoitures = 0;
    int tailleTableau = 0;

    // Lire le fichier et remplir le tableau
    lireFichierEtRemplirTableau("voiture.txt", &voitures, &nbVoitures, &tailleTableau);

    // Trier le tableau
    trierTableau(voitures, nbVoitures);
    afficherTableau(voitures, nbVoitures);

    // Recherche d'une voiture
    char marqueRecherchee[TAILLE], modeleRecherche[TAILLE];
    printf("\nEntrez la marque de la voiture à rechercher : ")
    scanf(" %[^\n]", marqueRecherchee);
    printf("Entrez le modèle de la voiture à rechercher : ");
    scanf(" %[^\n]", modeleRecherche);

    int indice = rechercheDichotomique(voitures, nbVoitures, marqueRecherchee, modeleRecherche);

    if (indice != -1) {

        printf("Voiture trouvée : Marque: %s, Modèle: %s, Plaque: %s, Statut: %d\n",

               voitures[indice].marque,
               voitures[indice].modele,
               voitures[indice].plaque,
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
    *tailleTableau = 10;
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

                strncpy((*voitures)[*nbVoitures].plaque, debutPlaque, taillePlaque);
                (*voitures)[*nbVoitures].plaque[taillePlaque] = '\0';

                (*voitures)[*nbVoitures].statut = atoi(debutStatut);

                (*nbVoitures)++;

            }

        }

    }

    fclose(fichier);

}



void afficherTableau(Voiture *voitures, int nbVoitures) {

    printf("Liste des voitures :\n");
    for (int i = 0; i < nbVoitures; i++) {
        printf("Marque: %s, Modèle: %s, Plaque: %s, Statut: %d\n", 
               voitures[i].marque, 
               voitures[i].modele, 
               voitures[i].plaque, 
               voitures[i].statut);
    }
}



void trierTableau(Voiture *voitures, int nbVoitures) /*tri par sélection*/ {
    for (int i = 0; i < nbVoitures - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < nbVoitures; j++) {
            char marque1[TAILLE], marque2[TAILLE];
            char modele1[TAILLE], modele2[TAILLE];

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
    char marqueNormalisee[TAILLE], modeleNormalisee[TAILLE];
    char marqueVoiture[TAILLE], modeleVoiture[TAILLE];

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
