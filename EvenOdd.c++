#include "cuda_runtime.h"
#include <cuda.h>
#include "device_launch_parameters.h"
#include <stdio.h>
#include <curand_kernel.h>

int *vector, *arrayEvenOdd; // variaveis globais
// kernel --> GPU
__global__ void evenOdd(int N, int *vector, int *arrayEvenOdd)
{
    int i = threadIdx.x; // X pois um vetor somente tem uma dimensão

    while (i < N)
    {
        curandState* state;
        //curand_init(1, i, 0, &state);
        vector[i] = curand(&state);
        arrayEvenOdd[i] = vector[i] % 2;
        i += blockDim.x;
    }
}

// codigo --> cpu
int main()
{
    cudaDeviceReset();              // resetar cudacore
    int *d_vector, *d_arrayEvenOdd; // variaveis do lado da gpu
    int n = 6000;
    int tamanho = n * sizeof(int); // vetor para locacao de memoria

    // maloc do abc memoria da cpu
    vector = (int *)malloc(tamanho);
    arrayEvenOdd = (int *)malloc(tamanho);

    // maloc da gpu
    cudaMalloc((void **)&d_vector, tamanho);
    cudaMalloc((void **)&d_arrayEvenOdd, tamanho);

    // processo significa mover dados da cpu para gpu
    cudaMemcpy(d_vector, vector, tamanho, cudaMemcpyHostToDevice);
    cudaMemcpy(d_arrayEvenOdd, arrayEvenOdd, tamanho, cudaMemcpyHostToDevice);
    // processamento
    evenOdd<<<6, 1024>>>(n, d_vector, d_arrayEvenOdd);
    cudaDeviceSynchronize();
    // fim processamento

    // saida de dados
    cudaMemcpy(vector, d_vector, tamanho, cudaMemcpyDeviceToHost);
    cudaMemcpy(arrayEvenOdd, d_arrayEvenOdd, tamanho, cudaMemcpyDeviceToHost);

    for (int i = 0; i < n; i++)
        printf("%d == %d\n", vector[i], arrayEvenOdd[i]);

    cudaFree(d_vector);
    cudaFree(d_arrayEvenOdd);

    return 0;
}

//___>>> Device representação da GPU
//___>>> Host representação da CPU