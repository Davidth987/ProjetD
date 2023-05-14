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

void negatif(const GrandNombre* original, GrandNombre* resultat) {
    resultat->taille = original->taille;
    resultat->positif = !(original->positif);
    resultat->digits = malloc(resultat->taille * sizeof(int));
    if(resultat->digits == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour resultat->digits.\n");
        return;
    }
    for (int i = 0; i < original->taille; i++) {
        resultat->digits[i] = original->digits[i];
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
    GrandNombre neg;
    if (gn1->positif == gn2->positif) {
        // Same sign, proceed as before.
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
        // Different signs, need to subtract.
        if (inferieur_a(gn1, gn2)) {
            negatif(gn1, &neg);
            soustraction_grand_nombre(gn2, &neg, resultat);
        } else {
            negatif(gn2, &neg);
            soustraction_grand_nombre(gn1, &neg, resultat);
        }
        liberer_grand_nombre(&neg);
    }
}

void soustraction_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat)
{
    GrandNombre neg;
    if (gn1->positif == gn2->positif) {
        // Same sign, proceed as before.
        if (inferieur_a(gn1, gn2)) {
            soustraction_grand_nombre(gn2, gn1, resultat);
            resultat->positif = !(gn1->positif);
        } else {
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

            resultat->positif = gn1->positif;
        }
    } else {
        // Different signs, need to add.
        negatif(gn2, &neg);
        additionner_grand_nombre(gn1, &neg, resultat);
        liberer_grand_nombre(&neg);
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
    GrandNombre inv_gn1, inv_gn2;
    inverser_grand_nombre(gn1, &inv_gn1);
    inverser_grand_nombre(gn2, &inv_gn2);

    if (inv_gn1.taille != inv_gn2.taille) {
        return 0;
    }

    for (int i = inv_gn1.taille - 1; i >= 0; i--) {
        if (inv_gn1.digits[i] != inv_gn2.digits[i]) {
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
    GrandNombre inv_gn1, inv_gn2;
    inverser_grand_nombre(gn1, &inv_gn1);
    inverser_grand_nombre(gn2, &inv_gn2);

    if (inv_gn1.taille != inv_gn2.taille) {
        return inv_gn1.taille < inv_gn2.taille;
    }

    for (int i = inv_gn1.taille - 1; i >= 0; i--) {
        if (inv_gn1.digits[i] != inv_gn2.digits[i]) {
            return inv_gn1.digits[i] < inv_gn2.digits[i];
        }
    }

    return 0;
}

int inferieur_ou_egal_a(const GrandNombre* gn1, const GrandNombre* gn2)
{
    return inferieur_a(gn1, gn2) || egal_a(gn1, gn2);
}