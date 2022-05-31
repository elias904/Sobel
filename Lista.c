#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int PosicaoMenor(float *Lista)
{
    // Retorna a posição do menor termo da linha passada;
    int x;
    float Menor = Lista[0];

    for (x = 1; Lista[x] != '\0'; x++)
    {
        if (Lista[x] < Menor)
            Menor = Lista[x];
    }
    return RetornaPosicao(Menor, Lista);
}

int RetornaPosicao(float P, float *Lista)
{
    int i = 0;
    while (Lista[i] != P)
        i++;

    return i;
}

void ImprimeListaIndices(int *List)
{
    int i = 0;
    while (List[i] != '\0')
        printf("[%d]", List[i]);
}