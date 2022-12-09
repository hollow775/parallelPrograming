
#include <stdio.h>
#include <cstdlib>

int *vector, *arrayEvenOdd; // variaveis globais
// kernel --> GPU
// codigo --> cpu
int main()
{                                   // resetar cudacore
    int *d_vector, *d_arrayEvenOdd; // variaveis do lado da gpu
    int n = 6000;
    int tamanho = n * sizeof(int); // vetor para locacao de memoria

    // maloc do abc memoria da cpu
    vector = (int *)malloc(tamanho);
    arrayEvenOdd = (int *)malloc(tamanho);

    for (int i = 0; i < n; i++)
    {
        vector[i] = (rand() % 990) + 10;
        arrayEvenOdd[i] = vector[i] % 2;
    }
    // processamento
    // vecSoma<<<6, 1024>>>(n, d_vector, d_arrayEvenOdd);

    for (int i = 0; i < n; i++)
    {
        printf("%d == %d\n", vector[i], arrayEvenOdd[i]);
    }

    return 0;
}

//___>>> Device representação da GPU
//___>>> Host representação da CPU