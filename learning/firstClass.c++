#include "cuda_runtime.h"
#include <cuda.h>
#include "device_launch_parameters.h"
#include <stdio.h>

int *a, *b, *c; // variaveis globais
// kernel --> GPU
__global__ void vecSoma(int N, int *a, int *b, int *c)
{
    int i = threadIdx.x; // X pois um vetor somente tem uma dimensão
    while (i < N)
    {
        c[i] = a[i] + b[i];
        i += blockDim.x;
    }
}

// codigo --> cpu
int main()
{
    cudaDeviceReset();            // resetar cudacore
    int *d_a, int *d_b, int *c_b; // variaveis do lado da gpu
    int n = 256;
    int tamanho = n * sizeof(int); // vetor para locacao de memoria

    // maloc do abc memoria da cpu
    a = (int *)malloc(tamanho);
    b = (int *)malloc(tamanho);
    c = (int *)malloc(tamanho);

    // maloc da gpu
    cudaMaloc((void **), &d_a, tamanho);
    cudaMaloc((void **), &d_b, tamanho);
    cudaMaloc((void **), &d_c, tamanho);

    // iniciarlizar valores dos vetores a e b
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        b[i] = i;
    }

    // processo significa mover dados da cpu para gpu
    cudaMemcpy(d_a, a, tamanho, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, tamanho, cudaMemcpyHostToDevice);

    // processamento
    vecSoma<<<1, n>>>(n, d_a, d_b, d_c);
    cudaDeviceSyncronize();
    // fim processamento

    // saida de dados
    cudaMemcpy(c, d_c, tamanho, cudaMemcpyDeviceToHost);
    for (int i = 0; i < n; i++)
        printf("%d", c[i]);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
//___>>> Device representação da GPU
//___>>> Host representação da CPU