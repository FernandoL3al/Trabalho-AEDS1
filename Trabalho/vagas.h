#ifndef VAGAS_H_INCLUDED
#define VAGAS_H_INCLUDED

//                  TIPO STRUCT VAGA
//==========================================================
typedef struct{
    char Empresa[51];
    char NomeVaga[51];
    char Area[51];
    double Salario;
}Vaga;

int CompareDados(char *nome, char *end_arquivo);

//void AtivarVaga(FILE *arquivo, Tema t, int escolha);
void AtivarVaga(FILE *arquivo, Tema t, int escolha, char *end_arquivo);


Vaga CriarVaga(Tema t);

void DefaultVaga(FILE *arquivo);

void ListarVagas(Vaga vetor[], int Quantidade, Tema t);

//void PesquisarVaga(Vaga vetor[], Tema t, FILE *arquivo);
void PesquisarVaga(Tema t, char *end_arquivo);


void ObliteratorVagas(char *end_arquivo, char *pattern);  //realmente exclui registro


#endif // VAGAS_H_INCLUDED