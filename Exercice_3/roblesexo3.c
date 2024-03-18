#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un horaire de train.
typedef struct HoraireTrain {
    char* villeDepart;      // Ville de départ
    char* villeArrivee;     // Ville d'arrivée
    char* heureDepart;      // Heure de départ
    char* heureArrivee;     // Heure d'arrivée
    int distance;           // Distance entre les deux villes en kilomètres
    struct HoraireTrain* suivant; 
} HoraireTrain;

// Structure pour la liste des horaires de trains.
typedef struct TrainHoraireListe {
    HoraireTrain* head;  
} TrainHoraireListe;

//Pourquoi ce choix :
//La structure TrainHoraireListe permet de gérer une liste d'horaires grace a une liste chaînée, offrant une liberté
//dans l'ajout et la suppression des horaires sans contraintes de taille prédéfinie, et permettant ainsi des modifications dynamiques.


/**
 * Ajoute un nouvel horaire de train à la liste des horaires.
 * 
 * @param liste La liste des horaires de train à laquelle ajouter le nouvel horaire.
 * @param villeDepart La ville de départ du train.
 * @param villeArrivee La ville d'arrivée du train.
 * @param heureDepart L'heure de départ du train.
 * @param heureArrivee L'heure d'arrivée du train.
 * @param distance La distance entre la ville de départ et la ville d'arrivée.
 * 
 * Cette fonction crée un nouvel horaire de train et l'ajoute en tête de la liste fournie.
 */
void ajouterHoraire(TrainHoraireListe* liste, char* villeDepart, char* villeArrivee, char* heureDepart, char* heureArrivee, int distance) {
    HoraireTrain* nouveau = (HoraireTrain*)malloc(sizeof(HoraireTrain));
    nouveau->villeDepart = strdup(villeDepart);    //dupli des chaînes pour éviter les modifications extérieures.
    nouveau->villeArrivee = strdup(villeArrivee);
    nouveau->heureDepart = strdup(heureDepart);
    nouveau->heureArrivee = strdup(heureArrivee);
    nouveau->distance = distance;
    nouveau->suivant = liste->head;
    liste->head = nouveau;
}

/**
 * Affiche tous les trains partant d'une ville spécifique.
 * 
 * @param liste La liste des horaires de train à parcourir.
 * @param villeDepart La ville de départ pour laquelle afficher les horaires.
 * 
 * Cette fonction parcourt la liste des horaires de train et affiche les informations
 * pour tous les trains partant de la ville spécifiée.
 */
void afficherTrainsDepart(TrainHoraireListe* liste, char* villeDepart) {
    HoraireTrain* actuel = liste->head;
    while (actuel != NULL) {
        if (strcmp(actuel->villeDepart, villeDepart) == 0) {
            printf("%s -> %s | Départ : %s - Arrivée : %s | Distance : %d km\n",
                   actuel->villeDepart, actuel->villeArrivee, actuel->heureDepart, actuel->heureArrivee, actuel->distance);
        }
        actuel = actuel->suivant;
    }
}

/**
 * Détermine et affiche l'horaire de train ayant la vitesse moyenne la plus élevée.
 * 
 * @param liste La liste des horaires de train à examiner.
 * 
 * Cette fonction parcourt la liste des horaires de train, calcule la vitesse moyenne
 * pour chaque trajet et détermine le trajet ayant la vitesse moyenne la plus élevée.
 */
void trajetVitesseMax(TrainHoraireListe* liste) {
    HoraireTrain* actuel = liste->head;
    double vitesseMax = 0;
    HoraireTrain* trajetMax = NULL;

    while (actuel != NULL) {
        //extraction des heures et minutes 
        int hd, md, ha, ma;
        sscanf(actuel->heureDepart, "%2d:%2d", &hd, &md);
        sscanf(actuel->heureArrivee, "%2d:%2d", &ha, &ma);
        

        //durée totale en minutes
        int dureeMinutes = (ha * 60 + ma) - (hd * 60 + md);
        if (dureeMinutes < 0) {
            dureeMinutes += 24 * 60;  //jour suivant
        }

        // Conversion de la durée en heures pour calculer la vitesse
        double dureeHeures = dureeMinutes / 60.0;
        double vitesse = (dureeHeures > 0) ? (double)actuel->distance / dureeHeures : 0;

        if (vitesse > vitesseMax) {
            vitesseMax = vitesse;
            trajetMax = actuel;
        }

        actuel = actuel->suivant;
    }

    if (trajetMax != NULL) {
        printf("Trajet le plus rapide trouvé : %s -> %s | Vitesse moyenne : %.2f km/h\n", 
               trajetMax->villeDepart, trajetMax->villeArrivee, vitesseMax);
    } else {
        printf("Aucun trajet trouvé.\n");
    }
}



/**
 * Trie la liste des horaires de train par ordre croissant d'heure de départ.
 * 
 * @param liste La liste des horaires de train à trier.
 * 
 * Cette fonction trie la liste fournie en place, en utilisant le tri à bulles adapté
 * pour les listes chaînées. Elle modifie l'ordre des éléments de la liste pour que les horaires
 * soient classés par ordre croissant selon leur heure de départ.
 */
void trierHoraires(TrainHoraireListe* liste) {
    int modifie;
    do {
        modifie = 0;
        HoraireTrain **cur = &(liste->head);
        while (*cur != NULL && (*cur)->suivant != NULL) {
            HoraireTrain *a = *cur;
            HoraireTrain *b = a->suivant;
            if (strcmp(a->heureDepart, b->heureDepart) > 0) { // Si l'heure de départ de a est plus tard que celle de b
                // Echanger a et b
                a->suivant = b->suivant;
                b->suivant = a;
                *cur = b;
                modifie = 1;
            }
            cur = &((*cur)->suivant);
        }
    } while (modifie);
}


/**
 * Trouve et affiche le moyen le plus rapide pour aller d'une ville de départ à une ville d'arrivée 
 * avec au plus une correspondance.
 * 
 * @param liste La liste des horaires de train à examiner.
 * @param villeDepart La ville de départ.
 * @param villeArrivee La ville d'arrivée.
 * 
 * Cette fonction recherche tous les trajets directs et les trajets avec une correspondance allant 
 * de la ville de départ à la ville d'arrivée, et détermine le trajet le plus rapide.
 */
void trouverTrajetRapide(TrainHoraireListe* liste, char* villeDepart, char* villeArrivee) {
    HoraireTrain* direct = NULL;
    HoraireTrain* premierTrain = NULL;
    HoraireTrain* deuxiemeTrain = NULL;
    double tempsMin = 99999; //initialise avec une grande valeur pour la comparaison

    // Parcourir tous les trajets possibles
    for (HoraireTrain* depart = liste->head; depart != NULL; depart = depart->suivant) {
        if (strcmp(depart->villeDepart, villeDepart) == 0) {
            if (strcmp(depart->villeArrivee, villeArrivee) == 0) {
                //trajet direct, calcule de la durée
                int hd, md, ha, ma;
                sscanf(depart->heureDepart, "%2d:%2d", &hd, &md);
                sscanf(depart->heureArrivee, "%2d:%2d", &ha, &ma);
                double duree = (ha * 60 + ma) - (hd * 60 + md);
                if (duree < 0) duree += 1440; //jour suivant
                if (duree < tempsMin) {
                    tempsMin = duree;
                    direct = depart;
                }
            } else {
                //chercher une correspondance
                for (HoraireTrain* correspondance = liste->head; correspondance != NULL; correspondance = correspondance->suivant) {
                    if (strcmp(correspondance->villeDepart, depart->villeArrivee) == 0 && strcmp(correspondance->villeArrivee, villeArrivee) == 0) {
                        // Vérifier le temps de correspondance
                        int hd, md, ha, ma, hc, mc;
                        sscanf(depart->heureArrivee, "%2d:%2d", &ha, &ma);
                        sscanf(correspondance->heureDepart, "%2d:%2d", &hc, &mc);
                        double attente = (hc * 60 + mc) - (ha * 60 + ma);
                        if (attente < 0) attente += 1440; //jour suivant
                        
                        //correspondance valide si l'attente est entre 5 minutes et 2 heures
                        if (attente >= 5 && attente <= 120) {
                            double dureeTotale = attente + ((ha * 60 + ma) - (sscanf(depart->heureDepart, "%2d:%2d", &hd, &md), hd * 60 + md));
                            if (dureeTotale < tempsMin) {
                                tempsMin = dureeTotale;
                                premierTrain = depart;
                                deuxiemeTrain = correspondance;
                            }
                        }
                    }
                }
            }
        }
    }

    // Afficher le résultat
    if (direct != NULL) {
        printf("Trajet direct le plus rapide de %s à %s: %s -> %s | Départ : %s - Arrivée : %s | Durée: %.0f mins\n",
               villeDepart, villeArrivee, direct->villeDepart, direct->villeArrivee, direct->heureDepart, direct->heureArrivee, tempsMin);
    } else if (premierTrain != NULL && deuxiemeTrain != NULL) {
        printf("Trajet avec correspondance le plus rapide de %s à %s:\n1er train: %s -> %s | Départ : %s - Arrivée : %s\n2e train: %s -> %s | Départ : %s - Arrivée : %s | Durée totale: %.0f mins\n",
               villeDepart, villeArrivee, 
               premierTrain->villeDepart, premierTrain->villeArrivee, premierTrain->heureDepart, premierTrain->heureArrivee,
               deuxiemeTrain->villeDepart, deuxiemeTrain->villeArrivee, deuxiemeTrain->heureDepart, deuxiemeTrain->heureArrivee, tempsMin);
    } else {
        printf("Aucun trajet trouvé de %s à %s.\n", villeDepart, villeArrivee);
    }
}


void libererListeHoraires(TrainHoraireListe* liste) {
    HoraireTrain* actuel = liste->head;
    while (actuel != NULL) {
        HoraireTrain* aSupprimer = actuel; 
        actuel = actuel->suivant; 

        //libération des chaînes de caractères 
        free(aSupprimer->villeDepart);
        free(aSupprimer->villeArrivee);
        free(aSupprimer->heureDepart);
        free(aSupprimer->heureArrivee);

        //libération du noeud
        free(aSupprimer);
    }
    liste->head = NULL;
}


int main() {
    // Création de la liste des horaires de trains
    TrainHoraireListe* liste = (TrainHoraireListe*)malloc(sizeof(TrainHoraireListe));
    liste->head = NULL;

    // Ajout des horaires à la liste
    ajouterHoraire(liste, "Lille", "Paris", "08:00", "08:59", 237);
    ajouterHoraire(liste, "Lille", "Lyon", "07:00", "10:00", 709);
    ajouterHoraire(liste, "Lille", "Calais", "15:19", "18:34", 110);
    ajouterHoraire(liste, "Paris", "Marseille", "12:00", "18:00", 900);
    ajouterHoraire(liste, "Lyon", "Marseille", "10:07", "15:01", 450);
    ajouterHoraire(liste, "Lyon", "Marseille", "11:50", "17:00", 450);

    printf("Trains au départ de Lille:\n");
    afficherTrainsDepart(liste, "Lille");
    printf("\n");

    printf("Trajet à la plus grande vitesse moyenne:\n");
    trajetVitesseMax(liste);
    printf("\n");

    printf("Trajet le plus rapide de Lyon à Marseille:\n");
    trouverTrajetRapide(liste, "Lyon", "Marseille");
    printf("\n");

    printf("Horaires triés par heure de départ:\n");
    trierHoraires(liste);
    afficherTrainsDepart(liste, "Lille");  //pour afficher les horaires triés de Lille, par exemple
    afficherTrainsDepart(liste, "Lyon");   //pour afficher les horaires triés de Lyon, par exemple
    printf("\n");

    // Libération de la mémoire allouée pour la liste et les horaires
    libererListeHoraires(liste);
    free(liste);

    return 0;
}
