#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct {

char marque[50];

char modele[50];

int statut;

}Voiture;



typedef struct{

char prenom[50];

char nom[50];

}client;





int calculPrix(int nbresemaines) {

int prix_par_semaines=100;

int prix_total=prix_par_semaines*nbresemaines;

return prix_total;



}





int main() { 

    int choix;

    int nbresemaine; 

    char prenom[50], nom[50]; 

    char marque[50], modele[50];

    FILE *file;



    while (1) {

        printf("\nMenu:\n");

        printf("1. Se connecter\n");

        printf("2. Liste de nos voitures\n");

        printf("3. Reserver une voiture\n");

        printf("4. Quitter\n");

        printf("Votre choix: ");

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

                    scanf("%d",&choix);

                    switch (choix) {

                    case 1:

                        //fonction pour rechercher une voiture



                    case 2: 

                        //fonction avec juste la liste des voitures 

                    }

                }



            case 3:

                printf("Entrer la marque de la voiture choisie : "); 

                scanf("%s", marque); 

                printf("Entrer le modele de la voiture choisie : ");

                scanf("%s", modele);

                printf("Combien de temps désirez vous louez la voiture");

                scanf("%d",&nbresemaine);

                int resultat = calculPrix(nbresemaine);

                 printf("Le prix total pour %d semaine(s) est de %.2d euros.\n", nbresemaine, resultat);



                

                break; 



            case 4:

                printf("Fin du programme.\n");

                return 0;



            default:

                printf("Choix invalide. Veuillez réessayer.\n");

               

        }



    return 0;

    }

    

    }

