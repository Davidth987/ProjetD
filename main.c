#include "tete.h"
#include "grand_nombre.h"
#include "initialisation.h"

int main()
{
    // Initialisation
    GrandNombre a = { 0 };
    initialiser_a(&a);

    GrandNombre b = { 0 };
    initialiser_b(&b);

    // Inversement de A et B
    GrandNombre reverse_a = { 0 };
    inverser_grand_nombre(&a, &reverse_a);

    GrandNombre reverse_b = { 0 };
    inverser_grand_nombre(&b, &reverse_b);

    // Addition
    GrandNombre resultat_addition = { 0 };
    resultat_addition.digits = malloc(((a.taille > b.taille ? a.taille : b.taille) + 1) * sizeof(int));
    additionner_grand_nombre(&a, &b, &resultat_addition);

    // Subtraction
    GrandNombre resultat_soustraire = { 0 };
    resultat_soustraire.digits = malloc(a.taille * sizeof(int));
    soustraire_grand_nombre(&a, &b, &resultat_soustraire);

    // Multiplication
    GrandNombre resultat_multiplication = { 0 };
    resultat_multiplication.digits = malloc((a.taille + b.taille) * sizeof(int));
    multiplier_grand_nombre(&a, &b, &resultat_multiplication);

    // reverse résultat
    GrandNombre reverse_resultat_addition = { 0 };
    inverser_grand_nombre(&resultat_addition, &reverse_resultat_addition);

    GrandNombre reverse_resultat_soustraction = { 0 };
    inverser_grand_nombre(&resultat_soustraire, &reverse_resultat_soustraction);

    GrandNombre reverse_resultat_multiplication = { 0 };
    inverser_grand_nombre(&resultat_multiplication, &reverse_resultat_multiplication);

    // Print values and comparisons
    /*printf("Valeur de A : ");
    afficher_grand_nombre(&a);

    printf("Valeur de B : ");
    afficher_grand_nombre(&b);*/

    printf("Valeur de A inversée : ");
    afficher_grand_nombre(&reverse_a);

    printf("Valeur de B inversée : ");
    afficher_grand_nombre(&reverse_b);

    /*printf("Resultat de l'addition : ");
    afficher_grand_nombre(&resultat_addition);

    printf("Resultat de la soustraction : ");
    afficher_grand_nombre(&resultat_soustraction);

    printf("Resultat de la multiplication : ");
    afficher_grand_nombre(&resultat_multiplication);*/

    printf("Resultat de l'addition inversé : ");
    afficher_grand_nombre(&reverse_resultat_addition);

    printf("Resultat de la soustraction inversé : ");
    afficher_grand_nombre(&reverse_resultat_soustraction);

    printf("Resultat de la multiplication inversé : ");
    afficher_grand_nombre(&reverse_resultat_multiplication);

    printf("A et B égal ? %d\n", egal_a(&a, &b));
    printf("A et B different ? %d\n", different_de(&a, &b));
    printf("A inférieur de B ? %d\n", inferieur_a(&a, &b));
    printf("A inférieur ou égal de B ? %d\n", inferieur_ou_egal_a(&a, &b));

    // Free memory
    liberer_grand_nombre(&a);
    liberer_grand_nombre(&b);
    liberer_grand_nombre(&resultat_addition);
    liberer_grand_nombre(&resultat_soustraire);
    liberer_grand_nombre(&resultat_multiplication);
    liberer_grand_nombre(&reverse_a);
    liberer_grand_nombre(&reverse_b);
    liberer_grand_nombre(&reverse_resultat_addition);
    liberer_grand_nombre(&reverse_resultat_soustraction);
    liberer_grand_nombre(&reverse_resultat_multiplication);

    return 0;
}