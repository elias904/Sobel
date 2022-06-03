#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Dinamica.h"
#include "Matriz.h"
#include "Lista.h"
#include "imagem.h"

void main()
{

    Imagem ImagemEntrada;

    float pixel_x;
    float pixel_y;

    char *Entrada = "bird.ppm";

    ImagemEntrada = lerArquivoPPM(Entrada);

    int Linhas = ImagemEntrada.altura;
    int Colunas = ImagemEntrada.largura;

    // Cria a matriz de intensidade luminosa
    float *MatrizIL = CriaMatriz(Linhas, Colunas);

    float *MatrizTeste = CriaMatriz(Linhas + 1, Colunas + 2);

    // Coloca os valores dentro da matriz de intensidade luminosa
    for (int i = 0; i < Linhas; i++)
    {
        for (int j = 0; j < Colunas; j++)
        {
            float Valor = 0.3 * ImagemEntrada.RGB[i][j].R + 0.59 * ImagemEntrada.RGB[i][j].G + 0.11 * ImagemEntrada.RGB[i][j].B;
            ImagemEntrada.RGB[i][j].Indice = i * Linhas + j;
            MatrizIL[i * Linhas + j] = Valor;
        }
    }


    /*Cria matriz extendida para poder aplicar o filtro de Sobel corretamente. Ou seja,
   extendemos a Matriz de Intensidade Luminosa
   */
    int LinhasExtend = Linhas + 2;
    int ColunasExtend = Colunas + 1;
    float *MatrizExtendida = CriaMatriz(LinhasExtend, ColunasExtend);

    //Indice para percorrer a matriz Luminosa
    int indice = 0;

    printf("Matriz: %d x %d\n", LinhasExtend, ColunasExtend);
    // Preenchendo a MatrizExtend com a MatrizDeIntensidadeLuminosa
    for (int x = 1; x < LinhasExtend - 1; x++)
    {
        for (int y = 1; y < ColunasExtend - 1; y++)
        {
            MatrizExtendida[x * ColunasExtend + y] = MatrizIL[indice];
            indice++;
        }
    }

    //Até aqui: REVISADO

    //Liberando memoria da Matriz de Intensidade Luminosa
    free(MatrizIL);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Duplicando os valores de linhas e colunas.

    // Fazendo a Linha 0 duplicar os elementos da linha 1(Excluindo as kinas da esquerda, superiro e inferiors);
    int x = 0;
    while (x == 0)
    {
        for (int y = 1; y < ColunasExtend - 1; y++)
        {
            MatrizExtendida[x * ColunasExtend + y] = MatrizExtendida[1 * ColunasExtend + y];
        }
        x++;
    }

    //Até aqui: REVISADO

    // Fazendo a linha da esquerda duplicar(Excluindo as Kinas da esquerda, superior e inferior)
    for (int x = 1; x < LinhasExtend - 1; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            MatrizExtendida[x * ColunasExtend + y] = MatrizExtendida[x * ColunasExtend + 1];
        }
    }

    //Até aqui: REVISADO

    // Duplica a ultima linha
    for (int j = 1; j < ColunasExtend - 1; j++)
    {
        MatrizExtendida[(LinhasExtend - 1) * LinhasExtend + j] = MatrizExtendida[(LinhasExtend - 2) * LinhasExtend + j];
    }

    //Até aqui: REVISADO

    //Duplica linha da direita
    for (int x = 2; x < LinhasExtend; x++)
    {
        MatrizExtendida[x * ColunasExtend - 1] = MatrizExtendida[x * ColunasExtend - 2];
    }

    //Até aqui: REVISADO

    // Resolvendo o Problema das 4 quinas;
    MatrizExtendida[0] = MatrizExtendida[ColunasExtend + 1]; // Superior(Esquerda)

    MatrizExtendida[ColunasExtend - 1] = MatrizExtendida[ColunasExtend + ColunasExtend - 2]; // Superior(Direita)

    MatrizExtendida[(LinhasExtend - 1) * ColunasExtend] = MatrizExtendida[(LinhasExtend - 2) * ColunasExtend + 1]; // Inferior Esquerda

    MatrizExtendida[LinhasExtend * ColunasExtend - 1] = MatrizExtendida[(LinhasExtend - 1) * ColunasExtend - 2]; // Inferior Direita

    /////////////////////////////////////////////////////////////////////////////////////////

    //Até aqui: REVISADO

    // Criamos a matriz para receber os valores do gradiente.
    float *MatrizWPesos = CriaMatriz(Linhas, Colunas);

    float sobel_x[3][3] =
        {{-1, 0, 1},
         {-2, 0, 2},
         {-1, 0, 1}};

    float sobel_y[3][3] =
        {{-1, -2, -1},
         {0, 0, 0},
         {1, 2, 1}};

    int idx = 0;

    for (int x = 1; x < LinhasExtend - 1; x++)
    {
        for (int y = 1; y < ColunasExtend - 1; y++)
        {

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    pixel_x += sobel_x[i][j] * MatrizExtendida[LinhasExtend * (y - 1 + i) + (x - 1 + j)];
                    pixel_y += sobel_y[i][j] * MatrizExtendida[LinhasExtend * (y - 1 + i) + (x - 1 + j)];
                }
            }
            float e = (float)sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));
            // printf("\nValor e = %.2f\n",e);

            MatrizWPesos[idx] = e;
            idx++;
        }
    }

    //Até aqui: REVISADO

    //Liberando o espaço da Matriz de Intensidade Luminosa Extendida
    free(MatrizExtendida);

    // ImprimeMatriz(MatrizWPesos, Linhas, Colunas);
    float *MatrizDinamica = CriaMatriz(Linhas, Colunas);

    // Parei aqui, agora so falta achar o menor caminho e depois fazer funções retira linhas e retira coluna

    // Produzindo a MatrizDinamica, pesos devidamente somados ao longo das colunas para poder encontrar o melhor caminho
    for (int x = 0; x < Linhas; x++)
    {
        for (int y = 0; y < Colunas; y++)
        {
            if (x * Linhas == 0)
            {
                // Copiando a primeira linha da MatrizWPesos para a matriz Dinamica.
                MatrizDinamica[x * Linhas + y] = MatrizWPesos[x * Linhas + y];
            }
            else
            {
                if (y == 0) // Borda Esquerda
                {

                    float A = 0;
                    A = MatrizWPesos[(x - 1) * Linhas + y];
                    float B = 0;
                    B = MatrizWPesos[(x - 1) * Linhas + y + 1];
                    MatrizDinamica[x * Linhas + y] = MatrizWPesos[x * Linhas + y] + ValorDinamicoBorda(A, B);

                    // printf("\nIndice: %d", x * Linhas + y);
                    // printf("\nCaminhos Anteriores: %d, %d\n", (x - 1) * Linhas + y, (x - 1) * Linhas + y + 1);
                }
                else if (y == Linhas - 1) // Borda Direita
                {
                    float C = 0;
                    C = MatrizWPesos[(x - 1) * Linhas + (Colunas - 1)];
                    float D = 0;
                    D = MatrizWPesos[(x - 1) * Linhas + (Colunas - 2)];
                    MatrizDinamica[x * Linhas + (Colunas - 1)] = MatrizWPesos[x * Linhas + (Colunas - 1)] + ValorDinamicoBorda(C, D);

                    // printf("\nIndice: %d", x * Linhas + (Colunas - 1));
                    // printf("\nCaminhos Anteriores: %d, %d\n", (x - 1) * Linhas + (Colunas - 1), (x - 1) * Linhas + (Colunas - 2));
                }
                else // Meio
                {

                    float E = 0;
                    E = MatrizWPesos[(x - 1) * Linhas + (y - 1)];
                    float F = 0;
                    F = MatrizWPesos[(x - 1) * Linhas + y];
                    float G = 0;
                    G = MatrizWPesos[(x - 1) * Linhas + (y + 1)];

                    MatrizDinamica[x * Linhas + y] = MatrizWPesos[x * Linhas + y] + ValorDinamicoMid(E, F, G);

                    // printf("\nIndice: %d", x * Linhas + y);
                    // printf("\nCaminhos Anteriores: %d, %d e %d\n", (x - 1) * Linhas + (y - 1), (x - 1) * Linhas + y, (x - 1) * Linhas + (y + 1));
                }
            }
        }
    }

    //Liberando a memoria da Matriz com as "Importâncias" de cada pixel
    free(MatrizWPesos);

    int k = 0;
    float *List = malloc(Colunas * sizeof(float));
    int y = 0;
    while (k == 0)
    {

        for (y = 0; y < Linhas; y++)
        {
            List[y] = MatrizDinamica[y];
        }

        k++;
    }
    int PosMenorNmr = PosicaoMenor(List, Colunas);
    int *Lista = (int *)malloc(Linhas * sizeof(int));
    PosicaoDosMenoresCaminhos(MatrizDinamica, PosMenorNmr, Linhas, Colunas, Lista);
    //ImprimeListaIndices(Lista, Linhas);

    RemoveCaminho(ImagemEntrada, Lista, Linhas, Colunas);

    //MatrizTransposta(MatrizDinamica, Linhas, Colunas);
    //Fazer transposta da Matriz
}