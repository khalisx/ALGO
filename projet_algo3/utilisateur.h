#ifndef UTILISATEUR_H
#define UTILISATEUR_H

typedef struct {
    char prenom[50];
    char nom[50];
} Utilisateur;

void enregistrerUtilisateur(Utilisateur *utilisateur);
void demanderUtilisateur(Utilisateur *utilisateur);

#endif

