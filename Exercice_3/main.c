#include "trainHoraire.h"

int main() {
    TrainHoraireListe* liste = (TrainHoraireListe*)malloc(sizeof(TrainHoraireListe));
    liste->head = NULL;

    int choix;
    char villeDepart[50], villeArrivee[50];
    char heureDepart[6], heureArrivee[6];
    int distance;

    // Ajout des horaires à la liste
    ajouterHoraire(liste, "Lille", "Paris", "08:00", "08:59", 237);
    ajouterHoraire(liste, "Lille", "Lyon", "07:00", "10:00", 709);
    ajouterHoraire(liste, "Lille", "Calais", "15:19", "18:34", 110);
    ajouterHoraire(liste, "Paris", "Marseille", "12:00", "18:00", 900);
    ajouterHoraire(liste, "Lyon", "Marseille", "10:07", "15:01", 450);
    ajouterHoraire(liste, "Lyon", "Marseille", "11:50", "17:00", 450);

    do {
        printf("\n--- Menu Gestion des Horaires de Train ---\n");
        printf("1. Ajouter un horaire de train\n");
        printf("2. Afficher tous les trains partant d'une ville spécifique\n");
        printf("3. Afficher le trajet à la plus grande vitesse moyenne\n");
        printf("4. Trier les horaires par heure de départ\n");
        printf("5. Trouver le trajet le plus rapide avec au plus une correspondance\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        getchar(); // consomme le '\n' restant

        switch (choix) {
            case 1:
                printf("Ville de départ : ");
                scanf("%49s", villeDepart);
                printf("Ville d'arrivée : ");
                scanf("%49s", villeArrivee);
                printf("Heure de départ (HH:MM) : ");
                scanf("%5s", heureDepart);
                printf("Heure d'arrivée (HH:MM) : ");
                scanf("%5s", heureArrivee);
                printf("Distance en km : ");
                scanf("%d", &distance);

                ajouterHoraire(liste, villeDepart, villeArrivee, heureDepart, heureArrivee, distance);
                break;
            case 2:
                printf("Ville de départ pour l'affichage (Majuscule en debut de mot) : ");
                scanf("%49s", villeDepart);
                afficherTrainsDepart(liste, villeDepart);
                break;
            case 3:
                trajetVitesseMax(liste);
                break;
            case 4:
                trierHoraires(liste);
                printf("Horaires triés avec succès.\n");
                break;
            case 5:
                printf("Ville de départ : ");
                scanf("%49s", villeDepart);
                printf("Ville d'arrivée : ");
                scanf("%49s", villeArrivee);
                trouverTrajetRapide(liste, villeDepart, villeArrivee);
                break;
            case 6:
                printf("Quitter\n");
                break;
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
        }
    } while (choix != 6);

    // Libération de la mémoire allouée pour la liste et les horaires
    libererListeHoraires(liste);
    free(liste);

    return 0;
}
