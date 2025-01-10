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

int main() {
    int choix; 
    Utilisateur utilisateur;
    while (1) {
        afficherMenuPrincipal();
        scanf("%d", &choix);
        switch (choix) {
            case 1: 
                demanderUtilisateur(&utilisateur);
                enregistrerUtilisateur(&utilisateur); break;
            case 2:     
                case2(); break;
            case 3:
                case3(); break;
            case 4: 
                case4(); break;
            case 5:
                afficherHistorique(); break;
            case 6:
                printf("Fin du programme.\n"); return 0;
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}