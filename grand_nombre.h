#ifndef GRAND_NOMBRE_H
#define GRAND_NOMBRE_H

typedef struct GrandNombre {
    int *digits;
    int taille;
    int positif;
} GrandNombre;

void liberer_grand_nombre(GrandNombre *nombre);
void afficher_grand_nombre(const GrandNombre* gn);
void inverser_grand_nombre(const GrandNombre* original, GrandNombre* inverse);


void additionner_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat);
void soustraction_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat);
void multiplier_grand_nombre(const GrandNombre* gn1, const GrandNombre* gn2, GrandNombre* resultat);


int egal_a(const GrandNombre* gn1, const GrandNombre* gn2);
int different_de(const GrandNombre* gn1, const GrandNombre* gn2);
int inferieur_a(const GrandNombre* gn1, const GrandNombre* gn2);
int inferieur_ou_egal_a(const GrandNombre* gn1, const GrandNombre* gn2);


#endif