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

