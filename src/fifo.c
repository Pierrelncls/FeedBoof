#include <stdio.h>
#include <stdlib.h>
#include "fifo.h" 


//Initialiser une file d'attente (vide)
void initqueue(Queue *q) {
    q->debut = NULL;
    q->fin = NULL;
    q->id_suivant = 1;
}


int isEmpty(Queue *q) {
    return q->debut == NULL;
}

void enqueue(Queue *q,  int valeur_numero_restau, float valeur_total_commande) {
    Noeud *nv_noeud = malloc(sizeof(Noeud));
    if (nv_noeud == NULL) {
        printf("erreur Bidule\n");
        return;
    }
    nv_noeud->numero_restau = valeur_numero_restau;
    nv_noeud->numero_commande = q->id_suivant++;
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
        printf("Erreur: la file est vide\n");
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