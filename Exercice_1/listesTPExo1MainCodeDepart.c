#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

typedef struct maillon {
    int val;
    struct maillon* p_suiv;
}maillon_int;


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

/** 
Initialise un nouveau maillon avec une valeur aléatoire.
@return Pointeur vers le nouveau maillon.
*/
maillon_int* init_elt()
{
    maillon_int* p_nv_elt = malloc(sizeof(maillon_int));
    p_nv_elt->val = rand() % 21;
    p_nv_elt->p_suiv = NULL;
    return p_nv_elt;
}

/** 
Ajoute un nouvel élément en tête de liste (version 1).
@param p_tete Pointeur sur l'élément de tête de la liste.
@param p_nv_elt Pointeur vers le nouvel élément à ajouter.
@return Nouveau pointeur sur l'élément de tête de la liste.
@precondition Aucune.
@postcondition Le nouvel élément est ajouté en tête de liste.
*/
maillon_int* ajout_tete_v1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = p_tete;
    p_tete = p_nv_elt;
    return p_tete;
}

/** 
Ajoute un nouvel élément en tête de liste (version 2).
@param p_p_tete Pointeur sur le pointeur de l'élément de tête de la liste.
@param p_nv_elt Pointeur vers le nouvel élément à ajouter.
@return Void.
@precondition Aucune.
@postcondition L'élément est ajouté en tête de liste.
*/
void ajout_tete_v2(maillon_int** p_p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = *p_p_tete;
    *p_p_tete = p_nv_elt;
}

/** 
Parcourt et affiche les éléments de la liste.
@param p_tete Pointeur sur l'élément de tête de la liste.
@return Void.
@precondition Aucune.
@postcondition Les éléments de la liste sont affichés.
*/
void parcourir(maillon_int* p_tete)
{
    if (p_tete == NULL)
        printf("liste vide");
    else
        while (p_tete != NULL) {
            printf("%d--", p_tete->val);
            p_tete = p_tete->p_suiv;
        }
    putchar('\n');
}

/** 
Insère un nouvel élément dans la liste suivant l'ordre croissant des premiers éléments (version 1).
@param p_tete Pointeur sur l'élément de tête de la liste.
@param p_nv_elt Pointeur vers le nouvel élément à insérer.
@return Nouveau pointeur sur l'élément de tête de la liste.
@precondition La liste doit être triée par ordre croissant.
@postcondition Le nouvel élément est inséré dans la liste.
*/
maillon_int* inserer1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    maillon_int* n, * prec;
    
    if (p_tete == NULL || p_nv_elt->val <= p_tete->val) {  
        p_nv_elt->p_suiv = p_tete;
        p_tete = p_nv_elt;
    }
    else {  
        n = prec = p_tete;
        while (n != NULL && p_nv_elt->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        p_nv_elt->p_suiv = n;
        prec->p_suiv = p_nv_elt;
    }
    return p_tete;
}

/** 
Insère un nouvel élément dans la liste suivant l'ordre croissant des premiers éléments (version 2).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@param e Pointeur vers le nouvel élément à insérer.
@return Void.
@precondition La liste doit être triée par ordre croissant.
@postcondition Le nouvel élément est inséré dans la liste.
*/
void inserer2(maillon_int** prem, maillon_int* e)
{
    maillon_int* n, * prec;
    if (*prem == NULL || e->val <= (*prem)->val){ 
        e->p_suiv = *prem;
        *prem = e;
    }
    else {  
        n = prec = *prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        e->p_suiv = n;
        prec->p_suiv = e;
    }
}

/** 
Supprime l'élément de tête de la liste (version pointeur direct).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@return Void.
@precondition La liste ne doit pas être vide.
@postcondition L'élément de tête est supprimé de la liste.
*/
void supprimer_debut(maillon_int** prem)
{
    maillon_int* n;
    if (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

/** 
Supprime tous les maillons d'une valeur donnée (version 1).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@param val Valeur à supprimer.
@return Nouveau pointeur sur l'élément de tête de la liste.
@precondition Aucune.
@postcondition Tous les maillons contenant la valeur donnée sont supprimés de la liste.
*/
maillon_int* critere_supp_un1(maillon_int* prem, int val)
{
    maillon_int* e = prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
    return prem;

}

/** 
Supprime tous les maillons d'une valeur donnée (version 2).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@param val Valeur à supprimer.
@return Void.
@precondition Aucune.
@postcondition Tous les maillons contenant la valeur donnée sont supprimés de la liste.
*/
void critere_supp_un2(maillon_int** prem, int val)
{
    maillon_int* e = *prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                *prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
}

/** 
Détruit tous les maillons de la liste (version 1).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@return Void.
@precondition Aucune.
@postcondition Tous les maillons de la liste sont libérés de la mémoire.
*/
void detruire_liste(maillon_int** prem)
{
    maillon_int* n;
    while (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

/** 
Détruit tous les maillons de la liste (version 2).
@param prem Pointeur sur le pointeur de l'élément de tête de la liste.
@return Void.
@precondition Aucune.
@postcondition Tous les maillons de la liste sont libérés de la mémoire.
*/
void detruire_liste2(maillon_int** prem)
{
    while (*prem != NULL)
        supprimer_debut(prem);
    
}

/* Permet la sérialisation format binaire dans le fichier
"saveliste.bin" de la liste d'entier (maillon_int) dont
le pointeur sur le premier élément est passé en paramètre
@input : maillon_int * prem, pointeur sur l'élément de tête de la liste à sérialiser
@output : void
@precondition : le répertoire courant et le processus père permettent l'écriture 
                le pointeur prem, est soit NULL (aucune action) soit pointe sur
                le premier élément d'une liste d'entiers
@postcondition : le fichier saveliste.bin contient les éléments de la liste 
                dont le premier élément est pointé par prem. 
                Nota : il n'y a pas de libération de la mémoire occupée par la 
                liste. Il faut donc la détruire avant d'éventuellement la recharger.
*/
void sauver_liste(maillon_int* prem)
{
    //ouvrir un fichier binaire en écriture : suffixe b
    FILE* f=fopen("saveliste.bin", "wb");
    printf("Ouvertude du fichier %p\n",f);
    // si liste non vide
    if (prem != NULL) {
        if (f==NULL)
            fprintf(stderr,"erreur création fichier :%i\n",errno);
        else // parcourir la liste jusque fin
            while (prem != NULL) {
                // écrire chaque maillon en binaire
                if (1 !=fwrite(prem, sizeof(maillon_int), 1, f))
                    fprintf(stderr,"Erreur d'écriture du maillon %p\n",prem);
                else 
                // passer au maillon suivant
                prem = prem->p_suiv;
            }
            fclose(f);	// fermer le fichier
    }
    else
        fprintf(stderr,"pas de sauvegarde pour une liste vide\n");
}

/** 
Charge une liste depuis le fichier "saveliste.bin".
@return Pointeur sur l'élément de tête de la liste chargée.
@precondition Le fichier "saveliste.bin" doit exister et être accessible en lecture.
@postcondition Si le fichier existe, la liste chargée contient les éléments lus à partir du fichier.
                Sinon, aucun changement n'est apporté à la liste.
*/
maillon_int* load_liste()
{
    FILE* f;
    maillon_int* prem = NULL, * p, e;
    if ((f= fopen("saveliste.bin", "rb")) != NULL) {
        prem = malloc(sizeof(maillon_int));
        fread(prem, sizeof(maillon_int), 1, f);
        p = prem;
        while (fread(&e, sizeof(maillon_int), 1, f)) {
            p->p_suiv = malloc(sizeof(maillon_int));
            p = p->p_suiv;
            *p = e;
            p->p_suiv = NULL;
        }
        fclose(f);
    }
    else
        printf("erreur ou fichier inexistant");
    return prem;
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