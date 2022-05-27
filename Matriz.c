#include <stdio.h>
#include <stdlib.h>

float * CriaMatriz(int Linhas, int Colunas)
{
    float *Matriz= (float *)malloc(Linhas* Colunas * sizeof(float));
    for(int x = 0; x < Colunas; x++)
    {
        for(int y = 0; y < Linhas; y++)
        {
            Matriz[x * Colunas + y] = 0;
        }
    }

    return Matriz;
}

void ImprimeMatriz(float * Matriz, int Linhas, int Colunas)
{
    for(int x = 0; x < Colunas; x++)
    {
        for(int y = 0; y < Linhas; y++)
        {
            printf("\nBloco[%d]: %.2f\n", x * Linhas + y, Matriz[x * Linhas + y]);
        }
    }
}