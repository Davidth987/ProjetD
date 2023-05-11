#include <stdio.h>
#include <stdbool.h>

#define TailleMax 1000

typedef struct {
    int digits [TailleMax];
    int taille;
    bool positif;
}GrandNombre;

void Affiche_grand_entier (const GrandNombre *a)
{
    if ( (a->positif) == true)
    {
        printf("+");
    }
    else {
        printf("-");
    }
    for (int i = 0; i < a->taille - 1; i++)
    {
        printf("%d",a->digits[i]);

    }
    printf("\n");
}


void additionner_grand_entier ( const GrandNombre *a, const GrandNombre *b, GrandNombre *resultat)
{

    int supTaille;
    if(a->taille > b->taille)
    {
        supTaille = a->taille;
    }
    else {
        supTaille = b->taille;
    }

    int retenu = 0;
    int somme;
    for (int i = 0; i < supTaille ; i++)
    {
        somme = a->digits[i] + b->digits[i] + retenu;
        retenu = somme / 10;
        resultat->digits[i]= somme%10;
    }
    resultat->taille = supTaille;
}


int main ()
{
    GrandNombre resultat;

    GrandNombre a = {{8,7,6,5,4},5,true};
    GrandNombre b = {{9,7,6,5,},4,true};
    Affiche_grand_entier(&a);
    additionner_grand_entier(&a,&b,&resultat);
    Affiche_grand_entier(&resultat);

}