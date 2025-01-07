#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id_location;
    char prenom[50];
    char nom[50];
    char marque[50];
    char modele[50];
    int nbresemaines;
} HistoriqueReservation;

//utilisateurs.txt

int connexion(HistoriqueReservation *p, HistoriqueReservation *n) {
    FILE *file;
    
    printf("Entrer votre prenom : "); 
    scanf("%s", p->prenom); 
    
    printf("Entrer votre nom : ");
    scanf("%s", n->nom);
    
    file = fopen("utilisateurs.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "Prenom: %s, Nom: %s\n", p->prenom, n->nom);
    fclose(file);

    printf("Bienvenue, %s %s ! Vos informations ont été enregistrées.\n", p->prenom, n->nom);
    
    return 0;
}

/*int main() {
    HistoriqueReservation p;
    HistoriqueReservation n;
    
    connexion(&p, &n);
    
    return 0;
}*/
