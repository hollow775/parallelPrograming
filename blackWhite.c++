#include "cuda_runtime.h"
#include <cuda.h>
#include "device_launch_parameters.h"
#include <stdio.h>
#include <curand_kernel.h>


// kernel --> GPU
__global__ void blackWhite(char* image, int channel)
{
    int x = blockIdx.x;
    int y = blockIdx.y;

    int pixel = (x + y * gridDim.x) * channels;

}
void InversedImage(char* inputImage, int altura, int largura, int channels){
    char* cpu_input_image = NULL;

    cudaMalloc ((void**)&inputImage, latura * largura * channels);
    cudaMempcy(cpu_input_image, inputImage, altura * largura * channels, cudaMemcpyHostToDevice);

    dim3 Grid_Image(altura, largura); 
    InversingImage<<<Grid_Image, 1>>>;

}

// codigo --> cpu
int main()
{
    return 0;
}
