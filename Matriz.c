#include <stdio.h>
#include <stdlib.h>
#include "Dinamica.h"
#include "Lista.h"
#include "imagem.h"

float *CriaMatriz(int Linhas, int Colunas)
{
    float *Matriz = (float *)malloc(Linhas * Colunas * sizeof(float));
    for (int x = 0; x < Linhas; x++)
    {
        for (int y = 0; y < Colunas; y++)
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

// O problema dessa função está na atribuição dos valores de indices na lista de indices. Não está recebendo de forma correta. Ele só armazena o 1
void PosicaoDosMenoresCaminhos(float *Matriz, int Inicio, int Linhas, int Colunas, int *Lista)
{
    int indice = 0;
    int E = Linhas;
    int Atual = Inicio;
    Lista[indice] = Atual;
    while (E - 1) // Sempre faz cálculo
    {
        indice++;                                             // Acrescimo de cara pra já saber na segunda linha quem faz parte do caminho minimo
        if (Atual % Linhas != 0 && (Atual + 1) % Linhas != 0) // Identifica o Meio.
        {
            long A = Matriz[Atual + Linhas];
            long B = Matriz[Atual + Linhas + 1];
            long C = Matriz[Atual + Linhas - 1];
            long Temp = ValorDinamicoMid(A, B, C);
            if (Temp == A)
            {
                Lista[indice] = Atual + Linhas;
                Atual = Atual + Linhas;
            }
            else if (Temp == B)
            {
                Lista[indice] = Atual + Linhas + 1;
                Atual = Atual + Linhas + 1;
            }
            else
            {
                Lista[indice] = Atual + Linhas - 1;
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
                    Lista[indice] = Atual + Linhas;
                    Atual = Atual + Linhas;
                }
                else
                {
                    Lista[indice] = Atual + Linhas + 1;
                    Atual = Atual + Linhas + 1;
                }
            }
            else // Borda Direita
            {
                long A = Matriz[Atual + Linhas];
                long B = Matriz[Atual + Linhas - 1];
                if (ValorDinamicoBorda(A, B) == A)
                {
                    Lista[indice] = Atual + Linhas;
                    Atual = Atual + Linhas;
                }
                else
                {
                    Lista[indice] = Atual + Linhas - 1;
                    Atual = Atual + Linhas - 1;
                }
            }
        }
        E--; // Quando tiver terminado de fazer isso com todas as linhas. Podemos sair.
    }
}

// Função que remove o caminho dado pela lista
void RemoveCaminho(Imagem ImagemEntrada, int *Lista, int Linhas, int Colunas)
{
    // Considere que sempre vou diminuir na largura, ele vai ter menor colunas
    int NLinhas = Linhas;
    int NColunas = Colunas - 1;

    // Criar uma nova matriz para ser a nova imagem
    Imagem ImagemSaida;

    ImagemSaida = criaImagem(ImagemEntrada.altura, ImagemEntrada.largura - 1);

    ImagemSaida.altura = ImagemEntrada.altura;
    ImagemSaida.largura = ImagemEntrada.largura - 1;

    int K = 0;
    int U = 0;

    // Observação: Estou sempre passando o mesmo tamanho de lista. Eu consigo otimizar retirando todo o elemento que eu acho de dentro da lista.
    // Diminuindo assim, o tempo de busca

    for (int i = 0; i < ImagemEntrada.altura; i++)
    {
        K = 0;//Zera quando pula pra proxima linha
        for (int j = 0; j < ImagemEntrada.largura; j++)
        {
            //Se Eu encontrar parte do meu menor caminho. Basta pular esse RGB e prosseguir com o proximo pixel.
            if (Achou(ImagemEntrada.RGB[i][j].Indice, Lista, NLinhas))
            {
                j++;
            }
            ImagemSaida.RGB[U][K].R = ImagemEntrada.RGB[i][j].R;
            ImagemSaida.RGB[U][K].G = ImagemEntrada.RGB[i][j].G;
            ImagemSaida.RGB[U][K].B = ImagemEntrada.RGB[i][j].B;
            K++;
        }
        U++;
    }
    imprimirImagem(ImagemSaida);
}

// Transposta de cada Matriz
void MatrizTransposta(float *Matriz, int Linhas, int Colunas)
{
    if (Linhas == Colunas)
    {
        // Para matrizes onde Colunas == Linhas
        float *MatrizT = CriaMatriz(Linhas, Colunas);
        for (int x = 0; x < Colunas; x++)
        {
            for (int y = 0; y < Linhas; y++)
            {
                int indice_1 = x * Colunas + y; // Normal
                int indice_2 = y * Linhas + x;  // Transposta

                MatrizT[indice_2] = Matriz[indice_1];
            }
        }
    }
    else
    {

        // Para matrizes onde Colunas != Linhas
        float *MatrizT = CriaMatriz(Linhas, Colunas);
        for (int x = 0; x < Colunas; x++)
        {
            for (int y = 0; y < Linhas; y++)
            {
                int indice_1 = x * Linhas + y;  // Normal
                int indice_2 = y * Colunas + x; // Transposta

                MatrizT[indice_2] = Matriz[indice_1];
            }
        }
    }
}
