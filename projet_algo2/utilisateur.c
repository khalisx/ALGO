#include <stdio.h>

#include <stdlib.h>

#include "utilisateur.h"



// Fonction pour enregistrer un utilisateur

void enregistrerUtilisateur(Utilisateur *utilisateur) {

    FILE *file;



    // Ouvrir le fichier pour ajouter les informations de l'utilisateur

    file = fopen("utilisateurs.txt", "a");



    if (file == NULL) {

        printf("Erreur lors de l'ouverture du fichier.\n");

        exit(EXIT_FAILURE); // Quitter le programme en cas d'erreur d'ouverture

    }



    // Écrire les informations dans le fichier

    fprintf(file, "Prenom: %s, Nom: %s\n", utilisateur->prenom, utilisateur->nom);



    // Fermer le fichier

    fclose(file);



    // Afficher un message de confirmation

    printf("Bienvenue, %s %s ! Vos informations ont été enregistrées.\n", utilisateur->prenom, utilisateur->nom);

}



void demanderUtilisateur(Utilisateur *utilisateur) {

    printf("Entrer votre prenom : ");

    scanf("%s", utilisateur->prenom);

    printf("Entrer votre nom : ");

    scanf("%s", utilisateur->nom);

}