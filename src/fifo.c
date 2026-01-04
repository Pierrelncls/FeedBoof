#include <stdio.h>
#include <stdlib.h>

//Structure d'un noeud
typedef struct Noeud {
    int numero_restau;
    int numero_commande;
    int total_commande;
    struct Noeud *suivant;
} Noeud;

//Structuure de la file d'attente
typedef struct {
    Noeud *debut;
    Noeud *fin;
} Queue;

//Initialiser une file d'attente (vide)
void initqueue(Queue *q) {
    q->debut = NULL;
    q->fin = NULL;
}


int isEmpty(Queue *q) {
    return q->debut == NULL;
}

void enqueue(Queue *q,  int valeur_numero_restau, int valeur_numero_commande, float valeur_total_commande) {
    Noeud *nv_noeud = malloc(sizeof(Noeud));
    if (nv_noeud == NULL) {
        printf("erreur Bidule\n");
        return;
    }
    nv_noeud->numero_restau = valeur_numero_restau;
    nv_noeud->numero_commande = valeur_numero_commande;
    nv_noeud->total_commande = valeur_total_commande;
    nv_noeud->suivant =NULL;

    if (isEmpty(q)) {
        q->debut = nv_noeud;
        q->fin = nv_noeud;
    } else {
        q->fin->suivant = nv_noeud;
        q->fin = nv_noeud;
    }

}

Noeud dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Bidule vide\n");
        Noeud empty = {0};
        return empty;
    }

    Noeud *temp = q->debut;
    Noeud data = *temp;
    data.suivant = NULL;

    q->debut=temp->suivant;

    if (q->debut == NULL) {
        q->fin = NULL;
    }

    free(temp);
    return data;
}

void displayQueue(Queue *q) {
    Noeud *courant = q->debut;
    while (courant != NULL) {
        printf("%d -> ", courant->numero_restau);
        printf("%d -> ", courant->numero_commande);
        printf("%d -> ", courant->total_commande);
        courant = courant->suivant;
    }
}