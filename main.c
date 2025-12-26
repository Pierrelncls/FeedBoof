#include <stdio.h>

struct MenuItem
{
    char type[10];
    char nom[100];
    float prix;
    int stock;
};

struct Restaurant
{
    char nom[100];
    int count;
    struct MenuItem items[15];


};

struct Noeuds
{
    char nom[100];
    int ncommande;
    int total;
    struct MenuItem *next;
};


int main() {
    printf("Bidule lorem ipsum dolor sit amet\n");







    
    return 0;
}
