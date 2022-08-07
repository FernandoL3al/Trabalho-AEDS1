#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "interface.h"
#include "cadastro.h"



//                OBLITERADOR DE REGISTROS
//========================================================================
void ObliteratorCliente(char *end_arquivo, int pattern){   //realmente exclui registro
    Cliente item;
    char new_name[30];
    FILE *arquivo = fopen(end_arquivo, "rb");
    FILE *arquivo_copia = fopen("temp.txt", "wb");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&item, sizeof(item), 1, arquivo)){
        if(item.Codigo == pattern) continue;
        fwrite(&item, sizeof(item), 1, arquivo_copia);
    }
    fclose(arquivo); fclose(arquivo_copia);
    strcpy(new_name, end_arquivo);
    remove(end_arquivo);
    rename("temp.txt", new_name);
}


//                          DIGITAR HVRS(EDITED)
//=====================================================================================================
Cliente DigitarCliente(Tema t, FILE *arquivo){
    Cliente C;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                       Cadastro de Cliente                       ");
    Gotoxy(22,  7); printf("C%cdigo:....................................................................", 162);
    Gotoxy(22,  11);printf("Nome:......................................................................"); 
    Gotoxy(22, 15); printf("Telefone:...................................................................");
    Gotoxy(35,  7); scanf("%d", &C.Codigo) ; Gotoxy(35, 11); scanf(" %[^\n]", C.Nome); Gotoxy(35, 15); scanf(" %[^\n]", C.Telefone);
    
    Gotoxy(35, 7); GetLogin(&C, arquivo, t); // funcao de criacao de senha
    
    return C;
}


//                          LISTAR HVRS(EDITED)
//=====================================================================================================
void ListarClientes(char *end_arquivo, Tema t){
    FILE *arquivo = fopen(end_arquivo, "rb");
    int Quantidade = 0;
    Cliente reg;
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                              Lista                              ");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&reg, sizeof(Cliente), 1, arquivo)){
        Gotoxy(27, 7 + Quantidade);
        printf("%8d %-42s %-14s", reg.Codigo,
              reg.Nome, reg.Telefone);
        Quantidade++;
    }
    Gotoxy(27,  5); printf("C%cdigo   Nome                                       Telefone        \n", 162);
    Gotoxy(27, 6); printf("-------- ------------------------------------------ -------------- \n");
    Gotoxy(27, 21); printf("                            %d Cadastros                                   \n", Quantidade);
    fclose(arquivo);                    
}


//                          PESQUISAR HVRS(EDITED, TEMAS)
//=====================================================================================================
void PesquisarCliente(Tema t, char *end_arquivo){
    FILE *arquivo = fopen(end_arquivo, "rb+");
    int Codigo; Cliente a;

    int x[] = {37,52,67}, y[] = {14,14,14}; char opcoes[][30] = {"     Alterar     ", "     Excluir      ", "       Sair        "}; int menu; //vars Menu de alterar

    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Pesquisa                           ");
    Gotoxy(46,  7); printf("    Digite o C%cdigo: ", 162); Gotoxy(67, 7); scanf("%d", &Codigo);
    while(fread(&a, sizeof(Cliente), 1, arquivo)){
        if(Codigo == a.Codigo){
            Gotoxy(27, 8); printf("C%cdigo   Nome                                       Telefone        \n", 162);
            Gotoxy(27, 9); printf("-------- ------------------------------------------ -------------- \n");
            Gotoxy(27, 10);
            printf("%8d %-42s %-14s", a.Codigo,
                 a.Nome, a.Telefone);
            Gotoxy(39, 12); Cores(t.fundo, t.letra); printf("     Deseja excluir ou alterar registro?     ");
            Caixa(36,13,49,1,1);
            menu = Menu(x, y, opcoes, 3, t);
            //             ALTERAR
            //=========================================
            if(menu == 0){         //alterar
                if(Autenticacao(a, arquivo, t) == 1){
                    a = DigitarCliente(t, arquivo);
                    fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
                    fwrite(&a, sizeof(Cliente), 1, arquivo);
                    fclose(arquivo);
                }
                fclose(arquivo);
                return;
            }
            //             EXCLUIR
            //=========================================
            if(menu == 1){         //excluir
                if(Autenticacao(a, arquivo, t) == 1){
                    fclose(arquivo);     // esse fclose e para fechar o anterior antes de reabrir em Obliterador
                    ObliteratorCliente(end_arquivo, Codigo);
                    return;
                }
            }
            if(menu == 2){
                return;
            }
        }
    }               
    Caixa(44, 14 , 30 , 1, 1);
    Gotoxy(46, 15);
    printf("   Cliente n%co Cadastrado   \n", 198);
    Sleep(1000);
}

//                          ATIVAR CLIENTE HVRS(EDITED, TEMAS)
//=====================================================================================================
void AtivarCliente(Tema t,FILE *arquivo, char *end_arquivo){
    int Opcao;
    int x[] = {32,53,71};
    int y[] = {24,24,24};
    char sla[][30] = {"      Novo      ", "   Pesquisar   ", "       Sair        "};
    Cliente a;
    do{
        system("cls");
        ListarClientes(end_arquivo, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0); 
        Opcao = Menu(x, y, sla, 3, t);
        if(Opcao == 0){        //Novo
            arquivo = fopen(end_arquivo,"ab");
            a = DigitarCliente(t , arquivo);
            fwrite(&a, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);
        }
        if(Opcao == 1){    //Pesquisar
            PesquisarCliente( t, end_arquivo);
        }
    } while(Opcao != 2);
}


//                        CADASTRO SENHA
//==============================================================================
void GetLogin(Cliente *C, FILE *arquivo, Tema t){
    int i;
    char senha[2][31];
    while(1){
        Cores(t.fundo, t.letra); Caixa(43,16, 35, 9, 1);  // CAIXA MAIOR LIMPA TELA TBM
        Caixa(43,16, 35, 1, 1);

       //   ESCONDER DIGITACAO
        Gotoxy(45, 17); printf("Digite uma senha: ");
            i = 0;
            while(1){   // ESCONDER DIGITACAO
                senha[0][i] = getch();
                if(senha[0][i] == 13){ 
                    senha[0][i] = '\0'; // CRUCIAL , EU ESTAVA ESQUECENDO DE
                    break; //enter confirma
                }
                if(senha[0][i] == 8){        //backspace deleta
                    i--;
                    Gotoxy(64+i-1 , 17);
                    printf(" ");
                    Gotoxy(64+i-1 , 17);
                    continue;
                }
                printf("*");
                i++;
            }
        Caixa(43,18, 35, 1, 1);
        Gotoxy(45, 19);
        printf("Confirme a senha: "); //scanf("%s", senha2);
            i = 0;
            while(1){   // ESCONDER DIGITACAO
                senha[1][i] = getch();
                if(senha[1][i] == 13){ 
                    senha[1][i] = '\0'; // CRUCIAL , EU ESTAVA ESQUECENDO DE
                    break; //enter confirma
                }
                if(senha[1][i] == 8){        //backspace deleta
                    i--;
                    Gotoxy(64+i-1 , 19);
                    printf(" ");
                    Gotoxy(64+i-1 , 19);
                    continue;
                }
                printf("*");
                i++;
            }
        //   COMPARAR SENHAS
        if(strcmp(senha[0], senha[1]) == 0){
            strcpy(C->Senha, senha[0]);
            Caixa(55, 20, 13, 1, 1 );
            Gotoxy(56, 21); Cores(t.letra,2); printf(" SENHA SALVA "); Cores(t.letra, t.fundo);
            Sleep(1000);
            Cores(t.letra, t.fundo);
            return ;
        }
        else{ 
            Caixa(52, 20, 20, 1, 1 );
            Gotoxy(53, 21); Cores(t.letra,4); printf(" SENHAS DIFERENTES! "); Cores(t.fundo, t.letra);
            Caixa(52, 22, 15, 1, 1 );
            Gotoxy(54, 23); printf("Cancelar?(s)");
            if(getch() == 's'){
                Caixa(50, 24, 21, 1, 1 );
                Gotoxy(52, 25); printf("Entrada cancelada");
                Sleep(1000);
                fclose(arquivo);
                break;
            }
        }
    }
    Cores(t.letra, t.fundo);
}


//                        AUTENTICACAO
//==============================================================================
int Autenticacao(Cliente z, FILE *arquivo, Tema t){
    Cores(t.letra, t.letra); Caixa(21, 6, 76, 10, 1 ); // caixa pra limpar tela;
    int opcao = 1, i;
    char teste[31];
    do{
        Cores(t.fundo, t.letra); Caixa(43,9, 35, 1, 1);
        Gotoxy(45, 10); printf("Digite a senha: ");
        i = 0;
        while(1){   // ESCONDER DIGITACAO
            teste[i] = getch();
            if(teste[i] == 13){ 
                teste[i] = '\0'; // CRUCIAL , EU ESTAVA ESQUECENDO DE
                break; //enter confirma
            }
            if(teste[i] == 8){        //backspace deleta
                i--;
                Gotoxy(62+i-1 , 10);
                printf(" ");
                Gotoxy(62+i-1 , 10);
                continue;
            }
            printf("*");
            i++;
        }
        fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
        fread(&z, sizeof(Cliente), 1, arquivo);
        if(strcmp(teste, z.Senha) == 0){
            Caixa(52, 12, 17, 1, 1 );
            Gotoxy(53, 13); Cores(0,2); printf(" ACESSO LIBERADO ");Cores(t.letra, t.fundo);
            Sleep(1000);
            return 1;
        }
        else {
            Caixa(53, 12, 16, 1, 1 );
            Gotoxy(54, 13); Cores(0,4); printf(" ACESSO NEGADO! ");Cores(t.letra, t.fundo);
            Caixa(53, 15, 14, 1, 1 );
            Gotoxy(55, 16); printf("Cancelar?(s)");
            if(getch() == 's'){
                opcao = 0;
            }
        }
    }while(opcao != 0);
    return 0;
}

