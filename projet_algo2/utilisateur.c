#include <stdio.h>
#include <stdlib.h>
#include "utilisateur.h"

// Fonction pour enregistrer un utilisateur
void enregistrerUtilisateur(Utilisateur *utilisateur) {
    FILE *file;
    file = fopen("utilisateurs.txt", "a");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Prenom: %s, Nom: %s\n", utilisateur->prenom, utilisateur->nom);
    fclose(file);
    printf("Bienvenue, %s %s ! Vos informations ont été enregistrées.\n", utilisateur->prenom, utilisateur->nom);
}

void demanderUtilisateur(Utilisateur *utilisateur) {
    printf("Entrer votre prenom : ");
    scanf("%s", utilisateur->prenom);
    printf("Entrer votre nom : ");
    scanf("%s", utilisateur->nom);
}