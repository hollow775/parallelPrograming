#include "cuda.runtime.h"
#include "device_launch_parameters.h"

__global__ void GrayScale_CUDA(unsigned char *Image, int canais);

void Image_GrayScale_Cuda(unsigned char *Input_Image, int altura, int largura, int canais)
{
    unsigned char *Dev_Input_Image = NULL;
    cudaMalloc((void **)&Dev_Input_Image, altura * largura * canais);
    cudaMemcpy(Dev_Input_Image, Input_Image, altura * largura * canais, cudaMemcpyHostToDevice);
    dim3 Grid_Image(largura, altura);
    GrayScale_CUDA<<<Grid_Image, 1>>>(Dev_Input_Image, canais);
    cudaMemcpy(Input_Image, Dev_Input_Image, altura * largura * canais, cudaMemcpyDeviceToHost);
    cudaFree(Dev_Input_Image);
}

__global__ void GrayScale_CUDA(unsigned char *Image, int canais)
{
    int x = blockIdx.x;
    int y = blockIdx.y;
    int idx = (x + y * gridDim.x) * canais;

    float b = Imagem[idx + 0] float g = Imagem[idx + 1] float r = Imagem[idx + 2]

        for (int i = 0; i < canais; i++)
    {
        Imagem[idx + i] = b * 0.299f + g * 0.587f + r * 0.144f;
    }
}