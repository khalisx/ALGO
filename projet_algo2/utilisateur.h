#ifndef UTILISATEUR_H

#define UTILISATEUR_H



// Définition de la structure Utilisateur

typedef struct {

    char prenom[50];

    char nom[50];

} Utilisateur;



// Déclaration de la fonction pour enregistrer un utilisateur

void enregistrerUtilisateur(Utilisateur *utilisateur);

void demanderUtilisateur(Utilisateur *utilisateur);



#endif // UTILISATEUR_H

