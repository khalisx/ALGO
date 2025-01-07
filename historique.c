                printf("La voiture %s %s a été réservée avec succès.\n", voitures[i].marque, voitures[i].modele);

                voitures[i].statut = 1; // Marquer comme louée



                // Demander des informations supplémentaires pour l'historique

                HistoriqueReservation reservation;

                printf("Entrez votre prénom: ");

                scanf("%s", reservation.prenom);

                printf("Entrez votre nom: ");

                scanf("%s", reservation.nom);

                printf("Entrez la durée de la location en semaines: ");

                scanf("%d", &reservation.nbresemaines);

                strcpy(reservation.marque, voitures[i].marque);

                strcpy(reservation.modele, voitures[i].modele);



                

                enregistrer_historique(reservation);

            } else {

                printf("La voiture %s %s est déjà réservée.\n", voitures[i].marque, voitures[i].modele);

            }

            break;

        }

    }



    if (!voiture_trouvee) {

        printf("Erreur : La voiture %s %s n'existe pas.\n", marque, modele);

        return;

    }



    // Sauvegarder les mises à jour dans le fichier

    sauvegarderVoitures(filename, voitures, car_count);

}



int main() {

    while (1) {

        printf("\nMenu:\n");

        printf("1. Réserver une voiture\n");

        printf("2. Afficher l'historique des réservations\n");

        printf("3. Quitter\n");

        printf("Votre choix: ");

        int choix;

        scanf("%d", &choix);



        if (choix == 1) {

            reserverVoiture("voiture.txt");

        } else if (choix == 2) {

            afficherHistorique();

        } else if (choix == 3) {

            printf("Fin du programme.\n");

            break;

        } else {

            printf("Choix invalide. Veuillez réessayer.\n");

        }

    }



    return 0;

}