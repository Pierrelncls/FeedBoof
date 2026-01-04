#include <stdio.h>
#include <stdlib.h>

//Structure d'un noeud
typedef struct Commande {
    int numero_restau;
    int numero_commande;
    int total_commande;
    struct Commande *suivant;
} Commande;

//Structuure de la file d'attente
typedef struct {
    Commande *debut;
    Commande *fin;
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
    Commande *nv_noeud = malloc(sizeof(Commande));
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

Commande dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Bidule vide\n");
        Commande empty = {0};
        return empty;
    }

    Commande *temp = q->debut;
    Commande data = *temp;
    data.suivant = NULL;

    q->debut=temp->suivant;

    if (q->debut == NULL) {
        q->fin = NULL;
    }

    free(temp);
    return data;
}

void displayQueue(Queue *q) {
    Commande *courant = q->debut;
    while (courant != NULL) {
        printf("%d -> ", courant->numero_restau);
        printf("%d -> ", courant->numero_commande);
        printf("%d -> ", courant->total_commande);
        courant = courant->suivant;
    }
}