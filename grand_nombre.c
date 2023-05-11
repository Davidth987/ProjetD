#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grand_nombre.h"


void liberer_grand_nombre(GrandNombre *nombre) {
    if (nombre->digits != NULL) {
        free(nombre->digits);
        nombre->digits = NULL;
    }
}

void afficher_grand_nombre(const GrandNombre* gn)
{
    if (gn->positif) {
        printf("+");
    } else {
        printf("-");
    }

    for (int i = 0; i < gn->taille; i++) {
        printf("%d", gn->digits[i]);
    }

    printf("\n");
}

void additionner_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    int taille_max = (gn1->taille > gn2->taille) ? gn1->taille : gn2->taille;
    int retenue = 0;
    int somme = 0;

    for (int i = 0; i < taille_max; i++) {
        somme = gn1->digits[i] + gn2->digits[i] + retenue;
        retenue = somme / 10;
        resultat->digits[i] = somme % 10;
    }

    if (retenue > 0) {
        resultat->digits[taille_max] = retenue;
        resultat->taille = taille_max + 1;
    } else {
        resultat->taille = taille_max;
    }

    resultat->positif = true;
}

void soustraction_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    int retenue = 0;
    int difference = 0;

    for (int i = gn1->taille - 1; i >= 0; i--) {
        difference = gn1->digits[i] - (i < gn2->taille ? gn2->digits[i] : 0) - retenue;

        if (difference < 0) {
            difference += 10;
            retenue = 1;
        } else {
            retenue = 0;
        }

        resultat->digits[i] = difference;
    }

    resultat->taille = gn1->taille;
    while (resultat->taille > 0 && resultat->digits[resultat->taille - 1] == 0) {
        resultat->taille--;
    }

    resultat->positif = (resultat->taille != 0 || resultat->digits[0] != 0);
}

int egal_a(const GrandNombre* gn1, const GrandNombre* gn2)
{
    if (gn1->taille != gn2->taille) {
        return 0;
    }

    for (int i = gn1->taille - 1; i >= 0; i--) {
        if (gn1->digits[i] != gn2->digits[i]) {
            return 0;
        }
    }

    return 1;
}

int different_de(const GrandNombre* gn1, const GrandNombre* gn2)
{
    return !egal_a(gn1, gn2);
}

int inferieur_a(const GrandNombre* gn1, const GrandNombre* gn2)
{
    if (gn1->taille != gn2->taille) {
        return gn1->taille < gn2->taille;
    }

    for (int i = gn1->taille - 1; i >= 0; i--) {
        if (gn1->digits[i] != gn2->digits[i]) {
            return gn1->digits[i] < gn2->digits[i];
        }
    }

    return 0;
}

int inferieur_ou_egal_a(const GrandNombre* gn1, const GrandNombre* gn2)
{
    return inferieur_a(gn1, gn2) || egal_a(gn1, gn2);
}

