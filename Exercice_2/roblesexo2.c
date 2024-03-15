#include <stdio.h>
#include <stdlib.h>

// Définition de la structure de la pile (stack)
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Fonction pour tester si la pile est vide
int isStackEmpty(StackNode* top) {
    return top == NULL;
}

// Fonction pour ajouter un élément au sommet de la pile
void push(StackNode** top, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    newNode->data = data;      // Assigner la donnée au nouveau nœud
    newNode->next = *top;      // Mettre l'ancien sommet de la pile comme suivant du nouveau nœud
    *top = newNode;            // Mettre à jour le sommet de la pile avec le nouveau nœud
}

// Fonction pour récupérer la valeur du sommet de la pile sans le retirer
int peek(StackNode* top) {
    if (isStackEmpty(top)) {
        printf("La pile est vide\n");
        return 0; 
    }
    return top->data;
}

// Fonction pour retirer l'élément du sommet de la pile et le retourner
int pop(StackNode** top) {
    if (isStackEmpty(*top)) {
        printf("La pile est vide, impossible de dépiler\n");
        return 0; 
    }
    StackNode* temp = *top;    // Conserver le sommet actuel de la pile
    int poppedData = temp->data; // Conserver les données pour les retourner
    *top = (*top)->next;       // Mettre à jour le sommet de la pile
    free(temp);                // Libérer la mémoire de l'ancien sommet
    return poppedData;
}

// Fonction pour renverser et afficher une liste d'entiers en utilisant une pile
void reverseAndPrintList(int *list, int length) {
    StackNode* stack = NULL;  // Initialiser une pile vide

    // Empiler tous les éléments de la liste
    for (int i = 0; i < length; i++) {
        push(&stack, list[i]);
    }

    // Dépiler et afficher les éléments, ce qui les affichera dans l'ordre inverse
    printf("Liste renversée: ");
    while (!isStackEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

}

int main() {
    int list[] = {1, 2, 3, 4, 5};  
    int length = sizeof(list) / sizeof(list[0]);  // Calculer la longueur de la liste

    reverseAndPrintList(list, length);  // Inverser et afficher la liste

    return 0;
}
