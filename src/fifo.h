#ifndef FIFO
#define FIFO

typedef struct Noeud {
    int numero_restau;
    int numero_commande;
    int total_commande;
    struct Noeud *suivant;
} Noeud;

typedef struct {
    Noeud *debut;
    Noeud *fin;
} Queue;

void initqueue(Queue *q);

int isEmpty(Queue *q);

void enqueue(Queue *q, int numero_restau, int numero_commande, int total_commande);

int dequeue(Queue *q);

void displayQueue(Queue *q);

#endif