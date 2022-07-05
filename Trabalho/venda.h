#ifndef VENDA_H_INCLUDED
#define VENDA_H_INCLUDED
typedef struct{
    int Numero;
    char DataVenda[15];
    int CodCliente;
    int CodProduto;
    int Quantidade;
    double PrecoUnitario;
} Venda;

void MostrarTelaVenda();   //  Protótipo ou assinatura função
Venda DigitarVenda(int z);
void MostrarVenda(Venda P);
void LimparVenda();
void ListarVendas(Venda Venda[], int Quantidade);
void PesquisarVenda(Venda Venda[], int Quantidade);
void AtivarVenda(int z);

#endif // VENDA_H_INCLUDED
