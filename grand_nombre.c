#include "tete.h"

#include "grand_nombre.h"

void inverser_grand_nombre(const GrandNombre* original, GrandNombre* inverse) {
    inverse->taille = original->taille;
    inverse->positif = original->positif;
    inverse->digits = malloc(inverse->taille * sizeof(int));
    if(inverse->digits == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour inverse->digits.\n");
        return;
    }
    for (int i = 0; i < original->taille; i++) {
        inverse->digits[i] = original->digits[original->taille - 1 - i];
    }
}


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

    resultat->digits = malloc((taille_max + 1) * sizeof(int));
    if(resultat->digits == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour resultat->digits.\n");
        return;
    }

    for (int i = 0; i < taille_max; i++) {
        int digit1 = i < gn1->taille ? gn1->digits[i] : 0;
        int digit2 = i < gn2->taille ? gn2->digits[i] : 0;
        somme = digit1 + digit2 + retenue;
        retenue = somme / 10;
        resultat->digits[i] = somme % 10;
    }

    if (retenue > 0) {
        resultat->digits[taille_max] = retenue;
        resultat->taille = taille_max + 1;
    } else {
        resultat->taille = taille_max;
    }
}


void soustraction_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    if (gn1->taille < gn2->taille) {
        printf("Erreur: Le premier nombre doit être plus grand ou égal au second.\n");
        return;
    }

    resultat->digits = malloc(gn1->taille * sizeof(int));
    if(resultat->digits == NULL) {
        printf("Erreur de mémoire\n");
        return;
    }

    int retenue = 0;
    int difference = 0;

    for (int i = 0; i < gn1->taille; i++) {
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
}


void multiplier_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    int taille_resultat = gn1->taille + gn2->taille;

    resultat->digits = calloc(taille_resultat, sizeof(int));
    if(resultat->digits == NULL) {
        printf("Erreur de mémoire\n");
        return;
    }

    for (int i = 0; i < gn1->taille; i++) {
        for (int j = 0; j < gn2->taille; j++) {
            resultat->digits[i+j] += gn1->digits[i] * gn2->digits[j];
        }
    }

    for (int k = 0; k < taille_resultat - 1; k++) {
        resultat->digits[k+1] += resultat->digits[k] / 10;
        resultat->digits[k] %= 10;
    }

    resultat->taille = taille_resultat;
    while (resultat->taille > 0 && resultat->digits[resultat->taille - 1] == 0) {
        resultat->taille--;
    }

    resultat->positif = gn1->positif == gn2->positif;
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
