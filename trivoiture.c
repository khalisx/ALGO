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



// Convertir un caractère en minuscule sans utiliser ctype.h

char convertirEnMinuscule(char c) {

    if (c >= 'A' && c <= 'Z') {

        return c + ('a' - 'A'); // Décalage ASCII pour passer en minuscule

    }

    return c;

}



// Fonction pour supprimer les accents et convertir en minuscules

void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee) {

    const char *accentues = "áàâäãåéèêëíìîïóòôöõúùûüçñÁÀÂÄÃÅÉÈÊËÍÌÎÏÓÒÔÖÕÚÙÛÜÇÑ";

    const char *nonAccentues = "aaaaaaeeeeiiiiooooouuuucnAAAAAAEEEEIIIIOOOOOUUUUCN";



    while (*chaineOrigine) {

        char c = *chaineOrigine;

        const char *p = strchr(accentues, c); // Cherche si le caractère est accentué

        if (p) {

            c = nonAccentues[p - accentues]; // Remplace par l'équivalent sans accent

        }

        *chaineNormalisee = convertirEnMinuscule(c); // Convertir en minuscule

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



void trierTableau(Voiture *voitures, int nbVoitures) {

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



int main() {

    Voiture *voitures = NULL;

    int nbVoitures = 0;

    int tailleTableau = 0;



    lireFichierEtRemplirTableau("Voiture.txt", &voitures, &nbVoitures, &tailleTableau);



    trierTableau(voitures, nbVoitures);

    printf("\nAprès le tri :\n");

    afficherTableau(voitures, nbVoitures);



    char marqueRecherchee[TAILLE], modeleRecherche[TAILLE];

    printf("\nEntrez la marque de la voiture à rechercher : ");

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



    free(voitures);

    return 0;

}
