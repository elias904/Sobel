#include <stdio.h>
#include <stdlib.h>
#include "Dinamica.h"

float *CriaMatriz(int Linhas, int Colunas)
{
    float *Matriz = (float *)malloc(Linhas * Colunas * sizeof(float));
    for (int x = 0; x < Colunas; x++)
    {
        for (int y = 0; y < Linhas; y++)
        {
            Matriz[x * Colunas + y] = 0;
        }
    }

    return Matriz;
}

void ImprimeMatriz(float *Matriz, int Linhas, int Colunas)
{
    for (int x = 0; x < Colunas; x++)
    {
        for (int y = 0; y < Linhas; y++)
        {
            printf("\nBloco[%d]: %.2f\n", x * Linhas + y, Matriz[x * Linhas + y]);
        }
    }
}

//O problema dessa função está na atribuição dos valores de indices na lista de indices. Não está recebendo de forma correta. Ele só armazena o 1
void PosicaoDosMenoresCaminhos(float *Matriz, int Inicio, int Linhas, int Colunas, int **Lista)
{
    int indice = 0;
    int Atual = Inicio;
    *Lista[indice] = Atual;
    while (Linhas - 1) // Sempre faz cálculo
    {
        indice++;                                             // Acrescimo de cara pra já saber na segunda linha quem faz parte do caminho minimo
        if (Atual % Linhas != 0 && (Atual + 1) % Linhas != 0) // Identifica o Meio.
        {
            long A = Matriz[Atual + Linhas];
            long B = Matriz[Atual + Linhas + 1];
            long C = Matriz[Atual + Linhas - 1];
            long Temp = ValorDinamicoMid(A,B,C);
            if (Temp == A)
            {
                *Lista[indice] = Atual + Linhas;
                Atual = Atual + Linhas;
            }
            else if (Temp == B)
            {
                *Lista[indice] = Atual + Linhas + 1;
                Atual = Atual + Linhas + 1;
            }
            else
            {
                *Lista[indice] = Atual + Linhas - 1;
                Atual = Atual + Linhas - 1;
            }
        }
        else // Identifica as Bordas
        {
            if (Atual % Linhas == 0) // Borda Esquerda
            {
                long A = Matriz[Atual + Linhas];
                long B = Matriz[Atual + Linhas + 1];
                if (ValorDinamicoBorda(A, B) == A)
                {
                    *Lista[indice] = Atual + Linhas;
                    Atual = Atual + Linhas;
                }
                else
                {
                    *Lista[indice] = Atual + Linhas + 1;
                    Atual = Atual + Linhas + 1;
                }
            }
            else // Borda Direita
            {
                long A = Matriz[Atual + Linhas];
                long B = Matriz[Atual + Linhas - 1];
                if (ValorDinamicoBorda(A, B) == A)
                {
                    *Lista[indice] = Atual + Linhas;
                    Atual = Atual + Linhas;
                }
                else
                {
                    *Lista[indice] = Atual + Linhas - 1;
                    Atual = Atual + Linhas - 1;
                }
            }
        }
        Linhas--; // Quando tiver terminado de fazer isso com todas as linhas. Podemos sair.
    }
    Lista[Linhas] = '\0';
}

void TranspostaMatriz(float * Matriz,int Linhas, int Colunas)
{
    float Temp;
    for (int x = 0; x < Colunas; x++)
    {
        for (int y = 0; y < Linhas; y++)
        {
            printf("\nNormal: %d e Transposto: %d\n",x * Linhas + y, y * Linhas + x);
        }
    }

}