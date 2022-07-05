#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

typedef struct{
    int Registro;
    char Nome[51];
    char Cargo[30];
} Funcionario;

void ListarFuncionarios(Funcionario Funcionarios[], int Quantidade);
int CarregarFuncionarios(char Texto[][20]);
void InserirFuncionario(int Registro, char Nome[], char Cargo[]);
void AtivarFuncionario();

#endif // FUNCIONARIO_H_INCLUDED