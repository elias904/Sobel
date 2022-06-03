#ifndef MATRIZ_H_
#define MATRIZ_H_

#include "imagem.h"

float * CriaMatriz(int Linhas, int Colunas);
void ImprimeMatriz(float * Matriz, int Linhas, int Colunas);
void PosicaoDosMenoresCaminhos(float *Matriz, int Inicio, int Linhas, int Colunas, int * Lista);
void RemoveCaminho(Imagem ImagemEntrada, int *Lista, int Linhas, int Colunas);
void MatrizTransposta(float * Matriz, int Linhas, int Colunas);

#endif
