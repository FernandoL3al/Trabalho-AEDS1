#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

typedef struct{
    int Codigo;
    char Nome[51];
    char Telefone[21];
    double Limite;
} Cliente;

void MostrarTelaCliente(int z);   //  Protótipo ou assinatura função
Cliente DigitarCliente();
void MostrarCliente(Cliente C, int z);
void LimparCliente(int z);
void ListarClientes(Cliente Clientes[], int Quantidade, int z);
void PesquisarCliente(Cliente Clientes[], int Quantidade);
void AtivarCliente(int z);

void InserirCliente(int Codigo, char Nome[], char Telefone[], double Limite);
int CarregarClientes(char Texto[][20]);


#endif // CADASTRO_H_INCLUDED