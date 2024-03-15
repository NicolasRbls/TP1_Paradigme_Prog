#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "robleslisteint.h"


/** 
Affiche le menu principal de l'application et récupère le choix de l'utilisateur.
@return Choix de l'utilisateur.
*/
int menu()
{
    int choix = 0;
    printf("1 Creer une liste d'entiers compris entre 0 et 20 de taille aleatoire comprise entre 1 et 20\n"
        "2 Ajouter un élément entier aléatoire (compris entre 0 et 20) en tête de liste\n"
        "3 Inserer un élément entier aléatoire dans sa place dans la liste suivant l'ordre croissant des premiers éléments\n"
        "4 Supprimer l'élément de tête\n"
        "5 Supprimer tous les maillons d'une valeur donnee\n"
        "6 Detruire liste\n"
        "7 Sauver la liste courante en binaire dans le fichier \"saveliste.bin\"\n"
        "8 Charger une liste depuis le fichier \"savelist.bin\"\n");

    scanf("%d", &choix);
    rewind(stdin);

    return choix;
}


int main()
{
    maillon_int* premier = NULL;
    maillon_int* nouveau;
    int fin = 0;
    int i, nb;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: //Creer une liste de taille aleatoire
            nb = rand() % 20 + 1; // Taille aléatoire entre 1 et 20
            for (int i = 0; i < nb; i++) {
                nouveau = init_elt();
                ajout_tete_v2(&premier, nouveau); // Utilisation de la version 2
            }
            parcourir(premier);
            break;

        case 2: // Ajouter
            nouveau = init_elt();
            ajout_tete_v2(&premier, nouveau); // Utilisation de la version 2
            parcourir(premier);
            break;

        case 3: // Inserer (ordre croissant)
            nouveau = init_elt();
            inserer2(&premier, nouveau); // Utilisation de la version 2
            parcourir(premier);
            break;

        case 4: //Supprimer debut:
            supprimer_debut(&premier); // Utilisation de la version pointeur direct
            parcourir(premier);
            break;

        case 5: // Supprimer un maillon d'une valeur donnee
            printf("Entrez la valeur à supprimer: ");
            scanf("%d", &nb);
            critere_supp_un2(&premier, nb); // Utilisation de la version 2
            parcourir(premier);
            break;

        case 6: // detruire liste
            detruire_liste2(&premier); // Utilisation de la version 2
            break;

        case 7: // Sauver liste
            sauver_liste(premier);
            break;

        case 8: // Charger liste
            premier = load_liste();
            parcourir(premier);
            break;

        default:
            fin = 1;
            break;
        }
        
    }
    detruire_liste2(&premier); //liste libérée à la fin
    return 0;
}