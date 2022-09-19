/*
    Autor: Hígaro Veloso
    UNIP 09/2022
    Feito para a aula do Professor Giovanni
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

#define TAMANHO_MAXIMO 11
int pos = 0;
char cpf[TAMANHO_MAXIMO + 1];

void Prosseguir(); // Espera o usuário pressionar ENTER para prosseguir
int MenuInicial(); // Apresenta para o usuário as opções de uso do programa
void ObterCpf(); // Recebe o input de um número de cpf do usuário
int ValidarCpf(); // Verifica se o cpf é válido ou não e retorna um valor com base nisso
void ImprimirCpf(); // Da o output do cpf com pontos e traço
void GerarCpf(); // Cria uma quantidade X de cpf's
int SomarDigitos(int x); // Faz o calculo da multiplicação e soma dos dígitos do cpf

int main()
{

    setlocale(LC_ALL, "Portuguese");
    srand(time(0));
    //GeradorCPF();


    do{
        switch(MenuInicial())
        {
            case 0:
                exit(1);
                break;
            case 1:
                ObterCpf();
                if(!ValidarCpf())
                {
                    printf("\n\t** CPF Válido.\n");
                }
                else
                {
                    printf("\n\t** CPF Inválido.\n");
                }
                break;
            case 2:
                GerarCpf();
                break;
        }

        Prosseguir();
    }while(1);

    return 0;
}

void Prosseguir()
{
    // Espera o usuário pressionar ENTER para prosseguir
    printf("\nPressione ENTER para continuar.");

    char input;
    do{
        input = getch();
    } while(input != '\r');
    system("cls");
}

int MenuInicial()
{
    // Apresenta para o usuário as opções de uso do programa
    printf(" Escolha uma opção:\n");
    printf(" [1] - Testar validade de um cpf.\n");
    printf(" [2] - Gerar cpf's aleatoriamente.\n");
    printf(" [0] - Sair do programa.\n");
    printf(" -> ");

    char escolhaCh = 'n';

    while(1)
    {
        char aux = getch();

        if(aux >= '0' && aux <= '2' && pos == 0)
        {
            pos++;
            putchar(aux);
            escolhaCh = aux;
        }

        if(aux == '\b' && pos > 0)
        {
            pos--;
            escolhaCh = 'n';
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }

        if(aux == '\r' && pos > 0)
        {
            pos = 0;
            system("cls");
            return (int)(escolhaCh - '0');
        }
    }
}

void ObterCpf()
{
    // Recebe o input de um número de cpf do usuário
    /*
        Nas posições 3, 6 e 9 são colocadas as divisões do cpf.
        Nessas mesmas posições, ao apagar um caractere, o programa exclui duas vezes
        para apagar as divisões
     */
    printf("Entre um cpf: ");

    while(1)
    {
        char aux = getch();

        if(aux >= '0' && aux <= '9' && pos < TAMANHO_MAXIMO)
        {
            cpf[pos++] = aux;
            putchar(aux);
            if(pos == 3 || pos == 6)
            {
                putchar('.');
            }
            if(pos == 9)
            {
                putchar('-');
            }
        }

        if(aux == '\b' && pos > 0)
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            if(pos % 3 == 0)
            {
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
            pos--;
        }

        if(aux == '\r' && pos == 11)
        {
            cpf[pos] = '\0';
            pos = 0;
            break;
        }
    }
}

int SomarDigitos(int peso)
{
    // Faz o calculo da multiplicação e soma dos dígitos do cpf
    int sum = 0;
    for(int idx = 0; peso >= 2; idx++, peso--)
    {
        sum += cpf[idx] * peso;
    }
    return sum;
}

int ValidarCpf()
{
    // Verifica se o cpf é válido ou não e retorna um valor com base nisso
    for(int idx = 0; idx < 11; idx++)
    {
        cpf[idx] -= '0'; // "Transforma" os caracteres em números
    }

    int soma = SomarDigitos(10);

    if(soma * 10 % 11 % 10 != (int)cpf[9])
    {
        return 1;
    }

    soma = SomarDigitos(11);

    if(soma * 10 % 11 % 10 != (int)cpf[10])
    {
        return 1;
    }

    for(int idx = 0; idx < 11; idx++)
    {
        cpf[idx] += '0'; // "Transforma" os números em caracteres
    }
    return 0;
}

void ImprimirCpf()
{
    // Da o output do cpf com pontos e traço
    for(int idx = 0; idx < strlen(cpf); idx++)
    {
        printf("%c", cpf[idx]);
        if(idx == 2 || idx == 5)
        {
            printf(".");
        }
        if(idx == 8)
        {
            printf("-");
        }
    }
}

void GerarCpf()
{
    // Cria uma quantidade X de cpf's
    printf("Quantos CPF's devem ser gerados? (Min. 1 e Max. 9): ");

    char escolhaCh = 'n';

    while(1)
    {
        char aux = getch();

        if(aux >= '1' && aux <= '9' && pos == 0)
        {
            pos++;
            putchar(aux);
            escolhaCh = aux;
        }

        if(pos > 0 && aux == '\b')
        {
            pos--;
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }

        if(pos > 0 && aux == '\r')
        {
            pos = 0;
            escolhaCh -= '0';
            break;
        }
    }

    system("cls");
    printf(" %d Cpf's válidos:\n", escolhaCh);
    for(int repetir = 0; repetir != (int)escolhaCh; repetir++)
    {
        for(int idx = 0; idx < 9; idx++)
        {
            cpf[idx] = (rand() % 10) + 48;
            while(cpf[0] == '0')
            {
                cpf[0] = (rand() % 10) + 48; // Impede que o 1° número do cpf seja zero
            }
        }

        cpf[9] = (SomarDigitos(10) * 10 % 11 % 10) + '0';
        cpf[10] = (SomarDigitos(11) * 10 % 11 % 10) + '0';

        printf("\n %d° ", repetir + 1);
        ImprimirCpf();
    }
    printf("\n");
}
