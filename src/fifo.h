#ifndef FIFO
#define FIFO

//Structure d'un noeud de la file
typedef struct Noeud {
    int numero_restau;
    int numero_commande;
    int total_commande;
    struct Noeud *suivant;
} Noeud;

//structure de la file
typedef struct {
    Noeud *debut;
    Noeud *fin;
    unsigned int id_suivant;
} Queue;

void initqueue(Queue *q);

int isEmpty(Queue *q);

void enqueue(Queue *q, int valeur_numero_restau, float valeur_total_commande);

Noeud dequeue(Queue *q);

void displayQueue(Queue *q);

#endif