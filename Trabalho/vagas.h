#ifndef VAGAS_H_INCLUDED
#define VAGAS_H_INCLUDED

//                  TIPO STRUCT VAGA
//==========================================================
typedef struct{
    char Empresa[51];
    char NomeVaga[51];
    char Area[51];
    double Salario;
    int Disponivel;
    char linked[51];
}Vaga;

void AplicarVaga(Tema t);

void AtivarVaga(FILE *arquivo, Tema t, int escolha, char *end_arquivo);

void DefaultVaga(FILE *arquivo);

void ReprintTela();

int CompareDados(char *nome, char *end_arquivo, Tema t, FILE *arquivo2);

void CriarVaga(Tema t, Vaga *C, FILE *arquivo, FILE *arquivo2);

void DefaultVaga(FILE *arquivo);

void ListarVagas(Vaga vetor[], int Quantidade, Tema t);

void PesquisarVaga(Tema t, char *end_arquivo, char *end_arquivo2);

int Autenticacao(Cliente z, FILE *arquivo, Tema t);

void Relatorio(Tema t);

void ObliteratorVagas(char *end_arquivo, char *pattern);  //realmente exclui registro


#endif // VAGAS_H_INCLUDED