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
    if(gn1->positif == gn2->positif) {
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

        resultat->positif = gn1->positif;
    } else {
        if(inferieur_a(gn1, gn2)) {
            soustraction_grand_nombre(gn2, gn1, resultat);
        } else {
            soustraction_grand_nombre(gn1, gn2, resultat);
        }
    }
}

void soustraction_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    if(gn1->positif != gn2->positif) {
        additionner_grand_nombre(gn1, gn2, resultat);
        resultat->positif = gn1->positif;
    } else {
        const GrandNombre* minuend = gn1;
        const GrandNombre* subtrahend = gn2;

        if (inferieur_a(gn1, gn2)) {
            minuend = gn2;
            subtrahend = gn1;
        }

        resultat->digits = malloc(minuend->taille * sizeof(int));
        if(resultat->digits == NULL) {
            printf("Erreur : Impossible d'allouer de la mémoire pour resultat->digits.\n");
            return;
        }

        int retenue = 0;
        int difference = 0;

        for (int i = 0; i < minuend->taille; i++) {
            difference = minuend->digits[i] - (i < subtrahend->taille ? subtrahend->digits[i] : 0) - retenue;

            if (difference < 0) {
                difference += 10;
                retenue = 1;
            } else {
                retenue = 0;
            }

            resultat->digits[i] = difference;
        }

        resultat->taille = minuend->taille;
        while (resultat->taille > 0 && resultat->digits[resultat->taille - 1] == 0) {
            resultat->taille--;
        }

        resultat->positif = (minuend == gn1);
    }
}

void multiplier_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    if (gn1->taille == 0 || gn2->taille == 0) {
        resultat->taille = 1;
        resultat->positif = true;
        resultat->digits = malloc(sizeof(int));
        if(resultat->digits == NULL) {
            printf("Erreur : Impossible d'allouer de la mémoire pour resultat->digits.\n");
            return;
        }
        resultat->digits[0] = 0;
        return;
    }

    resultat->taille = gn1->taille + gn2->taille;
    resultat->positif = gn1->positif == gn2->positif;
    resultat->digits = calloc(resultat->taille, sizeof(int));
    if(resultat->digits == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour resultat->digits.\n");
        return;
    }

    for (int i = 0; i < gn2->taille; i++) {
        for (int j = 0; j < gn1->taille; j++) {
            int produit = gn1->digits[j] * gn2->digits[i];
            int retenue = produit / 10;
            produit %= 10;

            resultat->digits[i+j] += produit;
            if (resultat->digits[i+j] >= 10) {
                resultat->digits[i+j+1] += resultat->digits[i+j] / 10;
                resultat->digits[i+j] %= 10;
            }

            resultat->digits[i+j+1] += retenue;
        }
    }

    while (resultat->taille > 0 && resultat->digits[resultat->taille - 1] == 0) {
        resultat->taille--;
    }

    if (resultat->taille == 0) {
        resultat->taille = 1; // Assumer un seul chiffre zéro pour représenter zéro
        resultat->positif = true;
    }
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