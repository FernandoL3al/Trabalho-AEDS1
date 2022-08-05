#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "interface.h"
#include "login.h"
#include "cadastro.h"
#include "vagas.h"

/*
FILE *arquivo = fopen("logins.txt", "rb+");
    if(arquivo == NULL){
        arquivo = fopen("logins.txt", "wb+");
    }
*/


//                        CADASTRO SENHA
//==============================================================================
Login GetLogin(char vetor[]){
    Login C;
    char senha[2][31];
    strcpy(C.nome, vetor);
    while(1){
        system("cls");
        Caixa(24,18, 25, 1, 1);
        Gotoxy(26, 19); 
        printf("Digite uma senha: "); scanf("%s", senha[0]);
        Caixa(24,21, 25, 1, 1);
        Gotoxy(26, 22);
        printf("Confirme a senha: "); scanf("%s", senha[1]);
        if(strcmp(senha[0], senha[1]) == 0){
            strcpy(C.senha, senha[0]);
            Caixa(34, 23, 14, 1, 1 );
            Gotoxy(36, 24);
            printf("Senha salva\n");
            system("pause");
            return C;
        }
        else{ 
            Caixa(30, 23, 30, 1, 1 );
            Gotoxy(32, 24);
            printf("As senhas nao sao iguais!!!\n");
            Caixa(34, 23, 23, 1, 1 );
            Gotoxy(36, 24);
            printf("Deseja cancelar?(s)\n"); 
            if(getch() == 's'){
                Caixa(34, 23, 21, 1, 1 );
                Gotoxy(36, 24);
                printf("Entrada cancelada\n");
                system("pause");
                break;
            }
        }
    }
}


//                        AUTENTICACAO
//==============================================================================
void Autenticacao(){
    FILE *arquivo;
    int opcao = 1;
    Login z;
    char teste[31];
    arquivo = fopen("logins.txt", "rb");
    do{
        system("cls");
        Caixa(24,18, 25, 1, 1);
        Gotoxy(26, 19); printf("\nDigite a senha: "); scanf("%s", teste); printf("\n");
        fseek(arquivo, 0, SEEK_SET);
        while(fread(&z, sizeof(Login), 1, arquivo)){
            if(strcmp(teste, z.senha) == 0){
                Caixa(32, 23, 17, 1, 1 );
                Gotoxy(34, 24); printf("Acesso Liberado\n");
                system("pause");
                opcao = 0;
            }
            else {
                Caixa(32, 23, 17, 1, 1 );
                Gotoxy(34, 24); printf("ACESSO NEGADO!\n");
                system("pause");
                Caixa(34, 25, 14, 1, 1 );
                Gotoxy(36, 26);
                printf("Cancelar?(s)\n");
                if(getch() == 's') opcao = 0;
            }
        }
    }while(opcao != 0);
    fclose(arquivo);
}

