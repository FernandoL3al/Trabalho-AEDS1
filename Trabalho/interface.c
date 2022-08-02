#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "interface.h"


//                          lINHA COLUNA HVRS
//=====================================================================================================
void Gotoxy(int linha, int coluna){
    COORD c;
    c.X = linha; c.Y = coluna;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//                          CAIXA HVRS
//=====================================================================================================
void Caixa(int x, int y, int largura, int altura, int tipo){
    int i, j;
    unsigned char C[][6] = {{218, 196, 191, 179, 192, 217},
                            {201, 205, 187, 186, 200, 188}};
    Gotoxy(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][2]);
    for(j = 0; j < altura; j++){
        Gotoxy(x, y + j + 1); printf("%c", C[tipo][3]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][3]);
    }
    Gotoxy(x, y + j + 1); printf("%c", C[tipo][4]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][5]);
}


//                          CORES LETRAS/FUNDO HVRS
//=====================================================================================================
void Cores(int fundo, int letras){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + (fundo << 4));
}


//                          MENU HVRS(EDITED, TEMAS)
//=====================================================================================================
int Menu(int x[], int y[], char Opcoes[][20], int n, Tema t){
    int i, Opcao = 0, tecla;
    TipoCursor(0);
    Cores(t.fundo, t.letra);
    for(i = 0; i < n; i++){
        Gotoxy(x[i], y[i]); printf("%s", Opcoes[i]);
    }
    do{
        Cores(t.letra, t.fundo);
        Gotoxy(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        tecla = GetTecla();
        Cores(t.fundo, t.letra);
        Gotoxy(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        if(tecla == TEC_ESQ) Opcao--;
        if(tecla == TEC_DIR) Opcao++;
        if(tecla == TEC_CIMA) Opcao--;
        if(tecla == TEC_BAIXO) Opcao++;

        if(n == 9 && tecla == TEC_EASTER_G) return 9; // my secret button
        
        if(tecla == TEC_ENTER){
                TipoCursor(1);
                return Opcao;
        }
        if(Opcao < 0) Opcao = n -1;
        if(Opcao >= n) Opcao = 0;
    }while(tecla != TEC_ESC);
    TipoCursor(1);
    return -1;
}


//                          lINHA COLUNA HVRS
//=====================================================================================================
int GetTecla(){
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}


//                          lINHA COLUNA HVRS
//=====================================================================================================
void TipoCursor(int cursor){
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    if(cursor == 0)
        CURSOR.bVisible = FALSE;
    else
        CURSOR.bVisible = TRUE;
    result = SetConsoleCursorInfo(myconsole, &CURSOR);
}


//          CARREGADOR E CRIADOR DE ARQUIVO TEMAS.TXT
//=====================================================================================================
void TemaLoad(FILE *arquivo, Tema vetor[]){  
    arquivo = fopen("temas.txt", "rb");

    if(arquivo == NULL) {                          //backup temas.txt
        arquivo = fopen("temas.txt", "w+b"); 
        Tema Temas1[] = {{ .nome = "Night Mode", .letra = 8, .fundo = 0},
                    { .nome = "Bulbasaur", .letra = 0 , .fundo = 2},
                    { .nome = "Squirtle", .letra = 0 , .fundo = 3},
                    { .nome = "Charmander", .letra = 0 , .fundo = 4},
                    { .nome = "Ekans", .letra = 0 , .fundo = 5},
                    { .nome = "Pikachu", .letra = 0 , .fundo = 6},
                    { .nome = "Lapras", .letra = 0 , .fundo = 11},
                    { .nome = "Chansey", .letra = 0 , .fundo = 12},
                    { .nome = "Matrix", .letra = 10 , .fundo = 0},
                    { .nome = "Bozo", .letra = 6, .fundo = 2},
                    { .nome = "Molusco", .letra = 15, .fundo = 4}};
        fwrite(Temas1, sizeof(Tema), 11, arquivo);
    }

    fseek(arquivo, 0, SEEK_SET);
    for(int b = 0 ; b < 11; b++){
        fread(&vetor[b], sizeof(Tema), 1, arquivo);
    }
    fclose(arquivo);
}


//                              ????? ENIGMA ??????
//=====================================================================================================
 int EseG(Tema t){ 
        char code; int i, j;
        Caixa(19, 5 , 79, 14, 1);
        Cores(15, 0);
        for(i = 6; i < 20; i++){
            for(j = 20; j < 98; j++ ){
                Gotoxy(j, i); printf("?");
            }
        }
        Caixa(57, 11, 2, 1, 1); Gotoxy(58, 12); scanf("%c", &code);
        if(code == 'B') return 9;
        else if(code == 'L')  return 10;
        else {
            Cores(0, 15);
            Caixa(19, 5 , 79, 14, 1);
            Caixa(44, 11, 27, 1, 1);
            Gotoxy(45, 12); printf("Nada de Easter Egg pra voc%c", 136);
            Gotoxy(34, 28); system("pause");
            return 2;
        }
}


//                              CRIPTOGRAFIA SEM USO
//=====================================================================================================
char *EncDec(char palavra[], int num){ // Funcao de Encriptar/Decriptar string ... necessita passar string por referencia 
    int i, tam = strlen(palavra);
    //Encriptar
    if(num == 1){   
        for(i = 0; i < tam; i++){
            if(palavra[i] >= 'D' && palavra[i] <= 'W' || palavra[i] >= 'd' && palavra[i] <= 'w' ) palavra[i] += 3;
        }
    }
    //Decriptar
    if(num == 2){
        for(i = 0; i < tam; i++){
                if(palavra[i] >= 'D' && palavra[i] <= 'W' || palavra[i] >= 'd' && palavra[i] <= 'w' ) palavra[i] -= 3;
                if(palavra[i] == '@') palavra[i] = ' ';
        }
    }
    return palavra;
}


//                          TELA INICIAL LAYOUT
//=====================================================================================================
void Inicio(Tema t, int num){

    int cdf = t.letra;
    int fundo = t.fundo;

    Cores(fundo, cdf); Caixa(0, 0, 118, 28, 1);
    Cores(fundo, cdf); Caixa(3, 2, 112, 24, 1 );
    Cores(fundo, cdf); Caixa(24, 1, 68, 1, 0);
    Cores(fundo, cdf);
    Gotoxy(32, 2);
    Cores(cdf, fundo);
    printf("                       LFA jobs                      ");
    Cores(fundo, cdf);

    Caixa(10, 8, 98, 8, 1); Cores(cdf, fundo); Caixa(12, 9, 94, 6, 0); Cores(cdf,fundo); Caixa(14, 11,90, 2,0);
    Cores(fundo, cdf); 
    Caixa(19, 5 , 79, 14, 1);
    Caixa(21, 6, 75, 12, 0);

    if(num == 0){
        Cores(/*0,6*/cdf, fundo);
        Gotoxy(22, 7); printf("UUUUUUUUUUUUUUUUU   / 00           00000111    0       \\  UUUUUUUUUUUUUUUUU"); Cores(/*0,12*/cdf, fundo);
        Gotoxy(22, 8); printf("     uuuuuuuuuu     | 001        000001000    111      |    uuuuuuuuuu     "); Cores(/*0,4*/cdf, fundo);
        Gotoxy(22, 9); printf(" *    UUUUUUUUU     | 010        001         100 00    |    UUUUUUUUU    * "); Cores(/*0,13*/cdf, fundo);
        Gotoxy(22,10); printf("~~  *   uuuuuuuu    | 011        000001010  100   01   |   uuuuuuuu   *  ~~"); Cores(/*0,5*/cdf, fundo);
        Gotoxy(22,11); printf("~~~~  *     UUUUUU  | 100        011       0000010010  | UUUUUU     *  ~~~~"); Cores(/*0,1*/cdf, fundo);
        Gotoxy(22,12); printf("~~~~~~~~~~ *   uuuuu| 000000101  100      100      011 |uuuuu  *  ~~~~~~~~~"); Cores(/*0,9*/cdf, fundo);
        Gotoxy(22,13); printf("~~~~~~~~~~~~~~  *   u 0000000110 101     100        100u   *  ~~~~~~~~~~~~~"); Cores(/*0,3*/cdf, fundo);
        Gotoxy(22,14); printf("~~~~~~~~~~~~~~~~~~~ |     jj   oooo   bbbbb   ssssss   | ~~~~~~~~~~~~~~~~~~"); Cores(/*0,11*/cdf, fundo);
        Gotoxy(22,15); printf("------------------- |     jj ooo  ooo bb  bb sss       | ------------------"); Cores(/*0,2*/cdf, fundo);
        Gotoxy(22,16); printf("------------------- |     jj oo    oo bbbbb    sssss   | ------------------"); Cores(/*0,10*/cdf, fundo);
        Gotoxy(22,18); printf("--------------------\\  jjjj    oooo   bbbbb   ssssss   /----- --------------"); Cores(/*0,15*/cdf, fundo);
        Gotoxy(22,17); printf("------------------- | jj  jj ooo  ooo bb  bb      sss  | ------------------"); Cores(/*0,14*/cdf, fundo);
    }
    if(num == 1){
        Gotoxy(22, 7); Cores(2, 6);printf("                              ");Cores(6,2);printf("2222222222222222");Cores(2,6);printf("                             "); Cores(2, 6);
        Gotoxy(22, 8); printf("                        ");Cores(6,2);printf("222222");Cores(1,15);printf("2222222222222222");Cores(6,2);printf("222222");Cores(2,6);printf("                       "); Cores(2, 6);
        Gotoxy(22, 9); printf("                   ");Cores(6,2);printf("2222222");Cores(1,15);printf("22222222222222222222222");;Cores(6,2);printf("2222222");Cores(2,6);printf("                   "); Cores(2, 6);
        Gotoxy(22,10); printf("               ");Cores(6,2);printf("222222222");Cores(1,15);printf("222222222222222222222222222");Cores(6,2);printf("222222222");Cores(2,6);printf("               "); Cores(2, 6);
        Gotoxy(22,11); printf("          ");Cores(6,2);printf("222222222222");Cores(1,15);printf("22222");Cores(15,2);printf("22222222222222222222");Cores(1,15);printf("222222");Cores(6,2);printf("222222222222");Cores(2,6);printf("          "); Cores(2, 6);
        Gotoxy(22,12); printf("      ");Cores(6,2);printf("222222222222222");Cores(1,15);printf("2");Cores(15,2);printf("222222222222222222222222222222");Cores(1,15);printf("2");Cores(6,2);printf("2222222222222222");Cores(2,6);printf("      "); Cores(2, 6);
        Gotoxy(22,13); printf("   ");Cores(6,2);printf("222222222222222222");Cores(15,2);printf("22222222");Cores(1,15);printf("222222222222222");Cores(15,2);printf("222222222");Cores(6,2);printf("2222222222222222222");Cores(2,6);printf("   "); Cores(2, 6);
        Gotoxy(22,14); printf("      ");Cores(6,2);printf("222222222222222");Cores(1,15);printf("22222222222222222222222222222222");Cores(6,2);printf("2222222222222222");Cores(2,6);printf("      "); Cores(2, 6);
        Gotoxy(22,15); printf("          ");Cores(6,2);printf("2222222222222");Cores(1,15);printf("222222222222222222222222222222");Cores(6,2);printf("2222222222222");Cores(2,6);printf("         "); Cores(2, 6);
        Gotoxy(22,16); printf("                 ");Cores(6,2);printf("22222222");Cores(1,15);printf("22222222222222222222222222");Cores(6,2);printf("222222222222");Cores(2,6);printf("            "); Cores(2, 6);
        Gotoxy(22,17); printf("                        ");Cores(6,2);printf("22222");Cores(1,15);printf("2222222222222222222");Cores(6,2);printf("2222222");Cores(2,6);printf("                    "); Cores(2, 6);
        Gotoxy(22,18); printf("                             ");Cores(6,2);printf("2222222222222222222");Cores(2,6);printf("                           "); Cores(2, 6);

        Gotoxy(4, 28); printf("     Meus parab%cns , voc%c encontrou nosso easter egg!!! ...     ", 130, 136);
    }

    if(num == 2){
        Gotoxy(22, 7); printf("                                    ");Cores(4,15);printf("131313");Cores(15,4);printf("                                 "); Cores(cdf/*LIGHT_RED*/, fundo);
        Gotoxy(22, 8); printf("                                   ");Cores(4,15);printf("13131313");Cores(15,4);printf("                                "); Cores(cdf/*RED*/, fundo);
        Gotoxy(22, 9); printf("                                  ");Cores(4,15);printf("3131313131");Cores(15,4);printf("                               "); Cores(cdf/*LIGHT_MAGENTA*/, fundo);
        Gotoxy(22,10); printf("             ");Cores(4,15);printf("13131313131313131313131313131313131313131313131313");Cores(15,4);printf("            "); Cores(cdf/*MAGENTA*/, fundo);
        Gotoxy(22,11); printf("                  ");Cores(4,15);printf("1313131313");Cores(15,4);printf("         ");Cores(4,15);printf("313");Cores(15,4);printf("          ");Cores(4,15);printf("1313131313");Cores(15,4);printf("               "); Cores(cdf/*BLUE*/, fundo);
        Gotoxy(22,12); printf("                      ");Cores(4,15);printf("131313");Cores(15,4);printf(" ");Cores(4,15);printf("31313131");Cores(15,4);printf(" ");Cores(4,15);printf("1313131");Cores(15,4);printf(" ");Cores(4,15);printf("1313131313");Cores(15,4);printf("                   "); Cores(cdf/*LIGHT_BLUE*/, fundo);
        Gotoxy(22,13); printf("                          ");Cores(4,15);printf("13");Cores(15,4);printf(" ");Cores(4,15);printf("31313131");Cores(15,4);printf(" ");Cores(4,15);printf("1313131");Cores(15,4);printf(" ");Cores(4,15);printf("131313");Cores(15,4);printf("                       "); Cores(cdf/*CYAN*/, fundo);
        Gotoxy(22,14); printf("                          ");Cores(4,15);printf("13");Cores(15,4);printf("        ");Cores(4,15);printf("131313131");Cores(15,4);printf(" ");Cores(4,15);printf("131313");Cores(15,4);printf("                       "); Cores(cdf/*LIGHT_CYAN*/, fundo);
        Gotoxy(22,15); printf("                        ");Cores(4,15);printf("1313");Cores(15,4);printf(" ");Cores(4,15);printf("3131313131313131");Cores(15,4);printf(" ");Cores(4,15);printf("13131313");Cores(15,4);printf("                     "); Cores(cdf/*GREEN*/, fundo);
        Gotoxy(22,16); printf("                      ");Cores(4,15);printf("313131");Cores(15,4);printf(" ");Cores(4,15);printf("1313131313131333");Cores(15,4);printf(" ");Cores(4,15);printf("3131313131");Cores(15,4);printf("                   "); Cores(cdf/*LIGHT_GREEN*/, fundo);
        Gotoxy(22,17); printf("                    ");Cores(4,15);printf("131313131313");Cores(15,4);printf("             ");Cores(4,15);printf("3131313131313");Cores(15,4);printf("                 "); Cores(cdf/*YELLOW*/, fundo);
        Gotoxy(22,18); printf("                  ");Cores(4,15);printf("13131313");Cores(15,4);printf("                         ");Cores(4,15);printf("131313131");Cores(15,4);printf("               "); Cores(cdf/*WHITE*/, fundo);
        
        Gotoxy(4, 28); printf("     Meus parab%cns , voc%c encontrou nosso easter egg!!! ...     ", 130, 136);
    }
    Cores(fundo, cdf);
    Gotoxy(42,22); printf("---- TRABALHO AEDS 1%c PER%cODO ----", 248, 214);

    Cores(fundo, cdf);
    Caixa(24, 24, 68, 1, 0);
    Cores(cdf, fundo);
    Gotoxy(34, 25); printf("               Fernando Leal & Arthur              ");
    Cores(cdf, fundo);
    Gotoxy(90, 28); printf("   copyright %c LFA 2022   ", 184);
    
}












