#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "grand_nombre.h"
#include "initialisation.h"

int main()
{
    // Initialisation
    GrandNombre a = { 0 };
    initialiser_a(&a);

    GrandNombre b = { 0 };
    initialiser_b(&b);

    // Addition
    GrandNombre resultat = { 0 };
    resultat.digits = malloc((a.taille > b.taille ? a.taille : b.taille + 1) * sizeof(int)); // Allocate memory for addition
    additionner_grand_nombre(&a, &b, &resultat);
    printf("Resultat de l'addition : ");
    afficher_grand_nombre(&resultat);

    // Subtraction
    GrandNombre resultat2 = { 0 };
    resultat2.digits = malloc(a.taille * sizeof(int)); // Allocate memory for subtraction
    soustraction_grand_nombre(&a, &b, &resultat2);
    printf("Resultat de la soustraction : ");
    afficher_grand_nombre(&resultat2);

    // Multiplication
    GrandNombre resultat3 = { 0 };
    resultat3.digits = malloc((a.taille + b.taille) * sizeof(int)); // Allocate memory for multiplication
    multiplier_grand_nombre(&a, &b, &resultat3);
    printf("Resultat de la multiplication : ");
    afficher_grand_nombre(&resultat3);

    // Comparisons
    printf("A et B égal ? %d\n", egal_a(&a, &b));
    printf("A et B different ? %d\n", different_de(&a, &b));
    printf("A inférieur de B ? %d\n", inferieur_a(&a, &b));
    printf("A inférieur ou égal de B ? %d\n", inferieur_ou_egal_a(&a, &b));

    // Free memory
    liberer_grand_nombre(&a);
    liberer_grand_nombre(&b);
    liberer_grand_nombre(&resultat);
    liberer_grand_nombre(&resultat2);
    liberer_grand_nombre(&resultat3);

    return 0;
}
