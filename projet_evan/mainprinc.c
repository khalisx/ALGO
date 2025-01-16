#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voiture.h"
#include "historique.h"
#include "utilisateur.h"

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

#include <stdio.h>
#include <stdlib.h>

int main() {
    int choix;
    char prenom[50], nom[50];
    Utilisateur utilisateur;

    while (1) {
        afficherMenuPrincipal();
        scanf("%d", &choix);
        switch (choix) {
            case 1: 
                demanderUtilisateur(&utilisateur);
                enregistrerUtilisateur(&utilisateur); break;
                break;
            case 2:
                while (1) {
                    printf("1. Rechercher une voiture en particulier\n");
                    printf("2. Liste de nos voitures\n");
                    printf("3. Retour au menu principal\n");
                    printf("Votre choix: ");
                    scanf("%d", &choix);
                    getchar(); 
                    switch (choix) {
                        case 1:
                            recherche();
                            break;
                        case 2:
                            listCarModels("voiture.txt");
                            break;
                        case 3:
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                    if (choix == 3) break;
                }
                break;
            case 3:
                while (1) {
                    printf("1. Liste des Voitures disponibles\n");
                    printf("2. Réserver une voiture\n");
                    printf("3. Retour au menu principal\n");
                    printf("Votre choix: ");
                    scanf("%d", &choix);
                    getchar(); 
                    switch (choix) {
                        case 1:
                            listereserv();
                            break;
                        case 2:
                            reserverVoiture("voiture.txt");
                            break;
                        case 3:
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                    if (choix == 3) break;
                }
                break;
            case 4: {
                int admin_choix;
                int retour = 0; 
                while (!retour) {
                    afficherMenuAdmin();
                    scanf("%d", &admin_choix);
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
                            listereserv();
                            break;
                        case 5: 
                            printf("Retour au menu principal...\n");
                            retour = 1;
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
