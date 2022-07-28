#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#define TEC_ENTER 13
#define TEC_TAB 9
#define TEC_BACKSPACE 8
#define TEC_ESC 27
#define TEC_DIR 1077
#define TEC_ESQ 1075
#define TEC_BAIXO 1080
#define TEC_CIMA 1072
#define TEC_DEL 1083
#define TEC_END 1079
#define TEC_INSERT 1082
#define TEC_HOME 1071
#define TEC_PAGE_UP 1073
#define TEC_PAGE_DOWN 1081
#define TEC_EASTER_G 63

typedef struct{
       char nome[51];
       int letra;
       int fundo;
}Tema;


void Gotoxy(int linha, int coluna);
void Caixa(int x, int y, int largura, int altura, int tipo);
void Cores(int letras, int fundo);
int MenuCor(int z);

int Menu(int x[], int y[], char Opcoes[][20], int n, Tema t);
int GetTecla();
void TipoCursor(int cursor);

void Inicio(Tema t, int num);
int EseG(Tema t);

char En_DecriptarSTR(char string[101], int opcao);

#endif // INTERFACE_H_INCLUDED