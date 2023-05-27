#include "utility.cpp"
#include <cuda_runtime.h>

__global__ void matrixMultiply(float* A, float* B, float* C, int rowsA, int colsA, int colsB) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rowsA && col < colsB) {
        float sum = 0.0f;
        for (int k = 0; k < colsA; k++) {
            sum += A[row * colsA + k] * B[k * colsB + col];
        }
        C[row * colsB + col] = sum;
    }
}

void matrixMultiplicationGPU(float* A, float* B, float* C, int rowsA, int colsA, int colsB) {
    float* d_A;
    float* d_B;
    float* d_C;
    size_t sizeA = rowsA * colsA * sizeof(float);
    size_t sizeB = colsA * colsB * sizeof(float);
    size_t sizeC = rowsA * colsB * sizeof(float);

    cudaMalloc((void**)&d_A, sizeA);
    cudaMalloc((void**)&d_B, sizeB);
    cudaMalloc((void**)&d_C, sizeC);

    cudaMemcpy(d_A, A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeB, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((colsB + threadsPerBlock.x - 1) / threadsPerBlock.x, (rowsA + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrixMultiply<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, rowsA, colsA, colsB);

    cudaMemcpy(C, d_C, sizeC, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

matrix multiply(matrix_a, matrxi_b) {
    if(device == "CUDA") {
        int rowsA = matrix_a.get_size_x();
        int colsA = matrix_a.get_size_y();
        int colsB = matrix_b.get_size_y();

        float *A = matrix_a.convert();
        float *B = matrix_b.convert();

        float C = new float[rowsA * colsB];

        matrixMultiplicationGPU(A, B, C, rowsA, colsA, colsB);
    }
    return C;
}