// En-tête de protection contre les inclusions multiples
#ifndef TRAIN_HORAIRE_H
#define TRAIN_HORAIRE_H

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

// Déclaration des fonctions
void ajouterHoraire(TrainHoraireListe* liste, char* villeDepart, char* villeArrivee, char* heureDepart, char* heureArrivee, int distance);
void afficherTrainsDepart(TrainHoraireListe* liste, char* villeDepart);
void trajetVitesseMax(TrainHoraireListe* liste);
void trierHoraires(TrainHoraireListe* liste);
void trouverTrajetRapide(TrainHoraireListe* liste, char* villeDepart, char* villeArrivee);
void libererListeHoraires(TrainHoraireListe* liste);

#endif // TRAIN_HORAIRE_H
