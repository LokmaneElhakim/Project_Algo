











#include <stdio.h>
#include <time.h>
#include <math.h>

int compteur = 0;

//  VERSION RECURSIVE
void hanoiRecursif(int n, char source, char dest, char aux, int afficher) {
    if (n == 1) {
        compteur++;
        if (afficher)
            printf("Deplacer disque 1 de %c vers %c\n", source, dest);
        return;
    }

    // Deplacer n-1 disques
    hanoiRecursif(n - 1, source, aux, dest, afficher);

    // Deplacer le disque principal
    compteur++;
    if (afficher)
        printf("Deplacer disque %d de %c vers %c\n", n, source, dest);

    // Deplacer n-1 disques
    hanoiRecursif(n - 1, aux, dest, source, afficher);
}

//  VERSION ITERATIVE
void hanoiIteratif(int n, char source, char dest, char aux, int afficher) {
    long long total = (1LL << n) - 1; // 2^n - 1

    char A = source, B, C;

    // Pour n pair, ordre des mouvements change
    if (n % 2 == 0) {
        B = aux;
        C = dest;
    } else {
        B = dest;
        C = aux;
    }

    for (long long i = 1; i <= total; i++) {
        compteur++;

        if (afficher) {
            if (i % 3 == 1)      printf("Deplacer de %c vers %c\n", A, B);
            else if (i % 3 == 2) printf("Deplacer de %c vers %c\n", A, C);
            else                 printf("Deplacer de %c vers %c\n", B, C);
        }
    }
}


int main() {


    int n;
    printf("Entrez le nombre de disques n : ");
    scanf("%d", &n);

    if (n < 1) {
        printf("n doit etre >= 1\n");
        return 1;
    }

    int afficher = (n <= 20); // Affichage seulement pour n <= 20

    long long theorique = (1LL << n) - 1;

    printf("\n");

    //  VERSION RECURSIVE
    printf("=== VERSION RECURSIVE ===\n");
    compteur = 0;
    clock_t debut = clock();
    hanoiRecursif(n, 'A', 'C', 'B', afficher);
    clock_t fin = clock();
    double temps_rec = ((double)(fin - debut) / CLOCKS_PER_SEC) * 1000.0;

    printf("Nombre de mouvements        : %d\n", compteur);
    printf("Nombre theorique (2^n - 1)  : %lld\n", theorique);
    printf("Temps d execution           : %.3f ms\n", temps_rec);
    if (compteur == theorique) printf("CORRECT (optimal)\n");
    if (n >= 33) printf("Attention : risque de stack overflow a partir de n environ 33.\n");

    //VERSION ITERATIVE
    printf("\n=== VERSION ITERATIVE ===\n");
    compteur = 0;
    debut = clock();
    hanoiIteratif(n, 'A', 'C', 'B', afficher);
    fin = clock();
    double temps_it = ((double)(fin - debut) / CLOCKS_PER_SEC) * 1000.0;

    printf("Nombre de mouvements        : %d\n", compteur);
    printf("Nombre theorique (2^n - 1)  : %lld\n", theorique);
    printf("Temps d execution           : %.3f ms\n", temps_it);
    if (compteur == theorique) printf("CORRECT (optimal)\n");


    return 0;
}

