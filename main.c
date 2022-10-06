#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

typedef struct Canva{
    int frame[20][80];
}Canva;

void initializeCanva(Canva* canva);
void generateCanva(Canva* canva, long type,int* numb); //type 1 (*) type 2(+) type 3(x) type 4(random * + x) type 5(random emoji in diagonal lines)
void printCanva(Canva* canva); //
void generatecros(Canva* canva, int randomx, int randomy, const int* numb);
void generateX(Canva* canva, int randomx, int randomy, const int* numb);
void generatedot(Canva* canva, int randomx, int randomy, const int* numb);
void geratransversal(Canva* canva, int randomx, int randomy, const int* numb);

int main(){
    long type;
    int* numb;
    char type_char[CHAR_MAX];
    char *type_point;
    Canva canva;
    //printa menu
    printf("""PROGRAMA GERADOR DE OBRA DE ARTE:\n"
           "=================================\n"
           "Escolha o tipo de figura basica a ser usada para criar a obra:\n"
           " 1 - asterisco simples.\n"
           " 2 - simbolo de soma com asteriscos.\n"
           " 3 - letra X com asteriscos.\n"
           " 4 - figuras aleatorias\n "
           "5 - diagonais em toda tela (maximo de 99 diagonais) \n"
           "Digite o tipo de figura basica desejada: """);
    //pega os numeros
    scanf("%s",type_char);
    type = strtol(type_char,&type_point,10);

    printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
    scanf("%d",numb);

    //gera o canva
    initializeCanva(&canva);
    generateCanva(&canva,type,numb);
    printCanva(&canva);
    //imprime a resposta
    return 0;
}


void generateCanva(Canva* canva, long type,int* numb){
    int randomx,randomy;
    int numb1;
    int numb2;
    srand(time(0));


    //check the numb value
    if(*numb<=0){
        *numb =rand() % 100;
    } else if(*numb>=100){
        *numb = 100;
    }

    numb1 =*numb- rand()%*numb;

    numb2 =*numb- rand()%*numb;


    //canva->frame[0][0]=0;
    switch (type) {
        case 1:
            generatedot(canva, randomx, randomy, numb);
            break;
        case 2:
            generatecros(canva, randomx, randomy, numb);
            break;
        case 3:
            generateX(canva, randomx, randomy, numb);
            break;
        case 4:
            if (numb1>=numb2){
                *numb=*numb-numb1;
                numb1=numb1-numb2;

                generatedot(canva, randomx, randomy, &numb1);
                generateX(canva, randomx, randomy, &numb2);
                generatecros(canva, randomx, randomy, numb);
            } else{ if(numb2>numb1){
                    *numb=*numb-numb2;
                    numb2=numb2-numb1;

                    generatedot(canva, randomx, randomy, &numb1);
                    generateX(canva, randomx, randomy, &numb2);
                    generatecros(canva, randomx, randomy, numb);
                }}
            break;
        case 5:
            if(*numb==100){*numb=99;}
            geratransversal(canva, randomx, randomy, numb);
            break;
        default:
            printf("ERROR: Invalid Type");
            break;
    }
}

void initializeCanva(Canva* canva){
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 80; ++j) {
            canva->frame[i][j]=0;
        }
    }
}

void printCanva(Canva* canva){
    printf("\n----------------------------------------------------------------------------------\n");
    for (int i = 0; i <= 19; ++i) {
        printf("-");
        for (int j = 0; j <= 79; ++j) {
            if (canva->frame[i][j] == 1){
                printf("*");
            } else if(canva->frame[i][j]!=1){
                printf(" ");
            }
        }
        printf("-\n");
    }
    printf("----------------------------------------------------------------------------------");
}
void generatedot(Canva* canva, int randomx, int randomy, const int* numb){
    for (int i = 0; i < *numb; ++i) {
        randomx = rand() % 79;
        randomy = rand() % 19;
        //r = (rand() % (max + 1 - min)) + min
        if (canva->frame[randomy][randomx]==0){
            canva->frame[randomy][randomx]=1;
        } else {
            --i;
        }
    }}
void generatecros(Canva* canva, int randomx, int randomy, const int* numb){
    for (int i = 0; i < *numb; ++i) {
        randomx = rand() % 78;
        randomy = rand() % 18;
        if (19 >= (randomy - 1) < 1 || 19 >= (randomy + 1) < 1 || 79 >= (randomx - 1) < 1 || 79 >= (randomx +1) < 1) {
            --i;
        } else {
            //r = (rand() % (max + 1 - min)) + min
            if (canva->frame[randomy][randomx] == 0 && canva->frame[randomy-1][randomx] == 0&& canva->frame[randomy+1][randomx] == 0&&canva->frame[randomy][randomx+1] == 0 && canva->frame[randomy][randomx-1] == 0) {
                canva->frame[randomy][randomx] = 1;
                canva->frame[randomy-1][randomx] = 1;
                canva->frame[randomy][randomx-1] = 1;
                canva->frame[randomy+1][randomx] = 1;
                canva->frame[randomy][randomx+1] = 1;
            }
        }
    }
}
void generateX(Canva* canva, int randomx, int randomy, const int* numb){
    for (int i = 0; i < *numb; ++i) {
        randomx = rand() % 78;
        randomy = rand() % 18;
        if (18 >= randomy - 1 < 1 || 18 >= randomy + 1 < 1 || 78 >= randomx - 1 < 1 || 78 >= randomx < 1) {
            --i;
        } else {
            //r = (rand() % (max + 1 - min)) + min
            if (canva->frame[randomy][randomx] == 0 && canva->frame[randomy-1][randomx+1] == 0&& canva->frame[randomy+1][randomx+1] == 0&&canva->frame[randomy+1][randomx-1] == 0 && canva->frame[randomy-1][randomx-1] == 0) {
                canva->frame[randomy][randomx] = 1;
                canva->frame[randomy-1][randomx+1] = 1;
                canva->frame[randomy+1][randomx-1] = 1;
                canva->frame[randomy+1][randomx+1] = 1;
                canva->frame[randomy-1][randomx-1] = 1;
            }
        }
    }
}

void geratransversal(Canva* canva, int randomx, int randomy, const int* numb){
    for (int i = 0; i < *numb; ++i) {
        randomx = rand() % 78;
        randomy = rand() % 18;
        int bufferx=randomx,buffery=randomy;
        if (canva->frame[randomy][randomx]==0){
            while(0 <= buffery && bufferx <= 79) {
                canva->frame[buffery][bufferx]=1;
                buffery--;
                bufferx++;
            }
            bufferx=randomx-1;
            buffery=randomy+1;
            while(bufferx >= 0&&buffery < 20) {
                canva->frame[buffery][bufferx]=1;
                buffery++;
                bufferx--;
            }
        } else {
            --i;
        }
    }
}