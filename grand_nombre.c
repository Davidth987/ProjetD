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

void additionner_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat_addition) {
    // Créez des copies locales de gn1 et gn2
    GrandNombre gn1_bis = *gn1;
    GrandNombre gn2_bis = *gn2;

    // Assurez-vous que les deux nombres sont positifs
    if (!gn1_bis.positif) {
        gn1_bis.positif = true;
    }
    if (!gn2_bis.positif) {
        gn2_bis.positif = true;
    }

    // Trouver la taille maximale entre gn1 et gn2
    int taille_max = gn1_bis.taille > gn2_bis.taille ? gn1_bis.taille : gn2_bis.taille;

    // Initialiser le résultat avec la taille maximale
    resultat_addition->digits = malloc((taille_max + 1) * sizeof(int));
    resultat_addition->taille = taille_max;
    resultat_addition->positif = true;

    // Ajouter les chiffres de gn1 et gn2
    int retenue = 0;
    for (int i = 0; i < taille_max; i++) {
        int sum = retenue;
        if (i < gn1_bis.taille) {
            sum += gn1_bis.digits[i];
        }
        if (i < gn2_bis.taille) {
            sum += gn2_bis.digits[i];
        }
        resultat_addition->digits[i] = sum % 10;
        retenue = sum / 10;
    }
    if (retenue != 0) {
        resultat_addition->digits[taille_max] = retenue;
        resultat_addition->taille++;
    }
}


void soustraire_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat_soustraire) {
    // Créez une copie locale de gn1 et gn2
    GrandNombre gn1_bis = *gn1;
    GrandNombre gn2_bis = *gn2;

    // Assurez-vous que gn2 est positif
    if (!gn2_bis.positif) {
        gn2_bis.positif = true;
    }

    // Vérifiez que gn1 est plus grand que ou égal à gn2
    if (gn1_bis.taille < gn2_bis.taille || !gn1_bis.positif) {
        printf("Erreur: gn1 doit être plus grand que ou égal à gn2 et positif.\n");
        return;
    }

    // Initialiser le résultat avec la taille de gn1
    resultat_soustraire->digits = malloc(gn1_bis.taille * sizeof(int));
    resultat_soustraire->taille = gn1_bis.taille;
    resultat_soustraire->positif = true;

    // Soustraire les chiffres de gn2 à ceux de gn1
    int emprunt = 0;
    for (int i = 0; i < gn1_bis.taille; i++) {
        int diff = gn1_bis.digits[i] - emprunt;
        if (i < gn2_bis.taille) {
            diff -= gn2_bis.digits[i];
        }
        if (diff < 0) {
            diff += 10;
            emprunt = 1;
        } else {
            emprunt = 0;
        }
        resultat_soustraire->digits[i] = diff;
    }

    // Mettre à jour la taille du résultat pour éliminer les zéros non significatifs
    while (resultat_soustraire->taille > 1 && resultat_soustraire->digits[resultat_soustraire->taille - 1] == 0) {
        resultat_soustraire->taille--;
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