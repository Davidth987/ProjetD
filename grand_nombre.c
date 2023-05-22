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

void multiplier_grand_nombre_recursive(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat, int position) {

    if (position >= gn2->taille) {

        for (int i = 0; i < resultat->taille - 1; i++) {
            resultat->digits[i + 1] += resultat->digits[i] / 10;
            resultat->digits[i] %= 10;
        }

        while (resultat->taille > 1 && resultat->digits[resultat->taille - 1] == 0) {
            resultat->taille--;
        }

        resultat->positif = !(gn1->positif ^ gn2->positif);

        return;
    }

    for (int i = 0; i < gn1->taille; i++) {
        resultat->digits[i + position] += gn1->digits[i] * gn2->digits[position];
    }

    multiplier_grand_nombre_recursive(gn1, gn2, resultat, position + 1);
}

void multiplier_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat) {

    resultat->taille = gn1->taille + gn2->taille;
    resultat->digits = calloc(resultat->taille, sizeof(int));

    multiplier_grand_nombre_recursive(gn1, gn2, resultat, 0);
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

void decouper_grand_nombre(const GrandNombre* gn, GrandNombre* gn_high, GrandNombre* gn_low, int m) {
    gn_high->taille = gn->taille - m;
    gn_low->taille = m;
    gn_high->positif = gn->positif;
    gn_low->positif = gn->positif;

    gn_high->digits = malloc(gn_high->taille * sizeof(int));
    gn_low->digits = malloc(gn_low->taille * sizeof(int));

    for (int i = 0; i < gn->taille; i++) {
        if (i < m) {
            gn_low->digits[i] = gn->digits[i];
        } else {
            gn_high->digits[i - m] = gn->digits[i];
        }
    }
}

void multiplier_karatsuba_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat) {
    if (gn1->taille == 1 || gn2->taille == 1) {
        multiplier_grand_nombre(gn1, gn2, resultat);
        return;
    }

    int m = gn1->taille / 2;

    GrandNombre gn1_high, gn1_low, gn2_high, gn2_low;
    decouper_grand_nombre(gn1, &gn1_high, &gn1_low, m);
    decouper_grand_nombre(gn2, &gn2_high, &gn2_low, m);

    GrandNombre z, y, x, tmp1, tmp2, tmp3;
    multiplier_karatsuba_grand_nombre(&gn1_low, &gn2_low, &z);
    multiplier_karatsuba_grand_nombre(&gn1_high, &gn2_high, &y);

    GrandNombre gn1_tmp, gn2_tmp;
    additionner_grand_nombre(&gn1_low, &gn1_high, &gn1_tmp);
    additionner_grand_nombre(&gn2_low, &gn2_high, &gn2_tmp);
    multiplier_karatsuba_grand_nombre(&gn1_tmp, &gn2_tmp, &x);

    soustraire_grand_nombre(&x, &y, &tmp1);
    soustraire_grand_nombre(&tmp1, &z, &tmp2);

    y.digits = realloc(y.digits, (2 * m + y.taille) * sizeof(int));
    for (int i = y.taille - 1; i >= 0; --i) {
        y.digits[i + 2 * m] = y.digits[i];
    }
    for (int i = 0; i < 2 * m; i++) {
        y.digits[i] = 0;
    }
    y.taille += 2 * m;

    tmp2.digits = realloc(tmp2.digits, (m + tmp2.taille) * sizeof(int));
    for (int i = tmp2.taille - 1; i >= 0; --i) {
        tmp2.digits[i + m] = tmp2.digits[i];
    }
    for (int i = 0; i < m; i++) {
        tmp2.digits[i] = 0;
    }
    tmp2.taille += m;

    additionner_grand_nombre(&y, &z, &tmp3);
    additionner_grand_nombre(&tmp3, &tmp2, resultat);

    liberer_grand_nombre(&gn1_high);
    liberer_grand_nombre(&gn1_low);
    liberer_grand_nombre(&gn2_high);
    liberer_grand_nombre(&gn2_low);
    liberer_grand_nombre(&z);
    liberer_grand_nombre(&y);
    liberer_grand_nombre(&x);
    liberer_grand_nombre(&tmp1);
    liberer_grand_nombre(&tmp2);
    liberer_grand_nombre(&tmp3);
}
