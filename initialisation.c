#include "tete.h"

#include "initialisation.h"
#include "grand_nombre.h"

void initialiser_a(GrandNombre *a)
{
    a->digits = malloc(5 * sizeof(int));
    a->taille = 5;
    a->positif = true;

    if (a->digits != NULL) {
        a->digits[0] = 4;
        a->digits[1] = 5;
        a->digits[2] = 6;
        a->digits[3] = 7;
        a->digits[4] = 8;
    } else {
        a->taille = 0;  // Mettre la taille à 0 pour indiquer une initialisation invalide
    }
}

void initialiser_b(GrandNombre *b)
{
    b->digits = malloc(4 * sizeof(int));
    b->taille = 4;
    b->positif = true;

    if (b->digits != NULL) {
        b->digits[0] = 5;
        b->digits[1] = 6;
        b->digits[2] = 7;
        b->digits[3] = 9;
    } else {
        b->taille = 0;  // Mettre la taille à 0 pour indiquer une initialisation invalide
    }
}
