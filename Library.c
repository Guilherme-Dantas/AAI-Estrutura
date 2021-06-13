#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"

void menu()
{
    char opcao;
    do
    {
        printf("========================= Menu Principal =======================\n");
        do
        {
            printf("A - Inserir\nB - Excluir\nC - Relatorio\nD - Sair\nOpcao : ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            if (opcao > 'D')
            {
                printf(">>As opcoes tem que ser A, B, C ou D\n>>Digite novamente!\n");
            }
        } while (opcao > 'D');
        switch (opcao)
        {
        case 'A':
            subMenuA();
            break;
        case 'B':
            subMenuB();
            break;
        case 'C':
            subMenuC();
            break;
        }

    } while (opcao != 'D');
}

void subMenuA()
{
    int opcaoNum = 0;
    do
    {
        printf("1 - Efetuar inclusao de cliente\n2 - Efetuar inclusao de dependente\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum < 1 || opcaoNum > 2)
        {
            printf(">>As opcoes tem que ser 1 ou 2\n");
        }
    } while (opcaoNum < 1 || opcaoNum > 2);

    switch (opcaoNum)
    {
    case 1:;
        Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
        cadastrarNome(cliente->nome);
        cadastrarNascimento(cliente->dataDeNascimento, MIN_IDADE_CLIENTE);
        cadastrarLimite(&cliente->limiteEmprestimo, calcularIdade(cliente->dataDeNascimento));
        cadastrarTipo(*cliente);
        cliente->codigo = RAND;
        
        break;
    case 2:

        break;
    default:
        break;
    }
}
void subMenuB()
{
    int opcaoNum = 0;
    do
    {
        printf("1 - Efetuar exclusao de cliente\n2 - Efetuar exclusao de dependente\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum < 1 || opcaoNum > 2)
        {
            printf(">>As opcoes tem que ser 1 ou 2\n");
        }
    } while (opcaoNum < 1 || opcaoNum > 2);
}

void subMenuC()
{
    int opcaoNum = 0;
    do
    {
        printf("1 - Listar todos os dados de clientes cadastrados e exibir media dos limites\n");
        printf("2 - Listar todos os dados de um cliente por código\n");
        printf("3 - Listar clientes por tipo de cartao\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum < 1 || opcaoNum > 3)
        {
            printf(">>As opcoes tem que ser 1, 2 ou 3\n");
        }
    } while (opcaoNum < 1 || opcaoNum > 3);
}

void cadastrarNome(char *nome)
{
    strcpy(nome, "");
    do
    {
        fflush(stdin);
        printf("\n\nDigite o seu nome: ");
        scanf("%s", nome);
    } while (nome[0] == '\0');
}

void cadastrarLimite(float *limite, int idade)
{
    if (idade <= 40)
    {
        *limite = 10000;
    }
    else if (idade <= 60)
    {
        *limite = 15000;
    }
    else if (idade <= 75)
    {
        *limite = 5000;
    }
    else
    {
        *limite = 2500;
    }
}

void cadastrarTipo(Cliente cliente)
{
    char tipo = NULL;
    do
    {
        fflush(stdin);
        printf("\nInsira o tipo de cartao: ");
        scanf("%c", &tipo);
        tipo = toupper(tipo);
        if (tipo != 'U' && tipo != 'N' && tipo != 'I')
        {
            printf("\nInsira um valor dentre os possiveis: U, N ou I");
        }
    } while (tipo != 'U' && tipo != 'N' && tipo != 'I');

    if (tipo == 'N')
    {
        cliente.limiteEmprestimo *= 1.05;  
    }
    else if (tipo == 'I')
    {
        cliente.limiteEmprestimo *= 1.20;
    }

    cliente.tipoDeCartao = tipo;
}

void cadastrarQtdDependente(Cliente *cliente)
{
    int quantidade = 0;
    do
    {
        fflush(stdin);
        printf("\nDigite a quantidade de dependetes do cliente %s:", cliente->nome);
        scanf("%i", &quantidade);
    } while (quantidade < 0 || quantidade > MAX_DEPENDETES);

    cliente->quantidadeDeDependentes = quantidade;
}

void cadastrarTipoDependente(char *tipoDependente)
{
    char tipo = NULL;
    do
    {
        fflush(stdin);
        printf("\nInsira o tipo de dependente: ");
        scanf("%c", &tipo);
        tipo = toupper(tipo);
        if (tipo != 'C' && tipo != 'F' && tipo != 'E')
        {
            printf("\nInsira um valor dentre os possiveis: E, F ou E");
        }
    } while (tipo != 'C' && tipo != 'F' && tipo != 'E');

    *tipoDependente = tipo;
}

char *cadastrarNascimento(char *dataNascStruct, int minIdade)
{
    char dtNas[10];
    int idade = -1;
    int valida = -1;

    do
    {
        do
        {
            printf("\nInsira data de nascimento: ");
            scanf(" %[^\n]", dtNas); //Recebendo a data de nascimento
            valida = verificaData(dtNas);
        } while (valida == 0);

        idade = calcularIdade(dtNas);

        if (idade < minIdade || idade > MAX_IDADE)
        {
            printf("\nA idade dessa pessoa deve ser maior ou igual a %i e menor que %i.", minIdade, MAX_IDADE);
        }

    } while (idade < minIdade || idade > MAX_IDADE);

    strcpy(dataNascStruct, dtNas);
    return dtNas;
}

int calcularIdade(char *dataNascimento)
{
    int idade = 0;
    int valida = -1;
    //Variáveis do dia atual
    char dtAtual[10], anoAtualC[4], mesAtualC[2], diaAtualC[2];
    char anoNascStr[4], mesNascStr[2], diaNascStr[2];

    int anoAtual, mesAtual, diaAtual;
    int anoNasc, mesNasc, diaNasc;

    anoNasc = atoi(strncpy(anoNascStr, dataNascimento + 6, 10));
    mesNasc = atoi(strncpy(mesNascStr, dataNascimento + 3, 6));
    diaNasc = atoi(strncpy(diaNascStr, dataNascimento + 0, 3));

    do
    {
        do
        {
            printf("\nInsira data atual: ");
            scanf(" %[^\n]", dtAtual); //Recebendo a data atual
            valida = verificaData(dtAtual);
        } while (valida == 0);

        //Recortando a data de atual em  mes - dia e passando ano atual para int
        mesAtual = atoi(strncpy(mesAtualC, dtAtual + 3, 6)); //mes
        diaAtual = atoi(strncpy(diaAtualC, dtAtual + 0, 3)); //dia
        //Recortando os anos e passando para int
        anoAtual = atoi(strncpy(anoAtualC, dtAtual + 6, 10));
        


        if (anoAtual < anoNasc)
        {
            printf("\n>>O ano atual nao pode ser menor que o ano de nascimento");
        }

    } while (anoAtual < anoNasc);

    idade = anoAtual - anoNasc;
    //Verificando se a pessoa já fez aniversário ou não
    if (mesAtual < mesNasc || mesAtual == mesNasc && diaAtual < diaNasc)
    {
        idade--;
    }
    printf(" %i", idade);
    return idade;
}

int verificaData(char *data)
{
    char anoC[4], mesC[2], diaC[2];
    int ano, mes, dia;
    ano = atoi(strncpy(anoC, data + 6, 10)),
    mes = atoi(strncpy(mesC, data + 3, 6)),
    dia = atoi(strncpy(diaC, data + 0, 3));

    if (strlen(data) != 10)
    {
        printf("\n>>A data tem que ser no padrao DD/MM/AAAA, com 10 caracteres\n");
        return 0;
    }
    else if (data[2] != '/' || data[5] != '/')
    {
        printf("\n>>A data tem que ser no padrao DD/MM/AAAA, com / entre dia e mes, e mes e ano\n");
        return 0;
    }
    else if (ano > 2021)
    {
        printf("\n>>Ano nao pode ser maior que 2021\n");
        return 0;
    }
    else if (mes < 1 || mes > 12)
    {
        printf("\n>>Mes tem que ser entre 1 e 12\n");
        return 0;
    }
    else if (dia < 1 || dia > 31)
    {
        printf("\n>>Dia tem que ser de 1 a 31\n");
        return 0;
    }
    else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
    {
        printf("\n>>Dia tem que ser ate 30\n");
        return 0;
    }
    else
    {
        if (dia > 29 && (ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0))
        {
            printf("\n>>Dia tem que ser ate 29\n");
            return 0;
        }
        else if (dia > 28 && !(ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0))
        {
            printf("\n>>Dia tem que ser ate 28\n");
            return 0;
        }
    }
    return 1;
}

void cadastrarQtdDependente(Cliente *cliente){
    printf("\nDigite a quantidade de dependentes do cliente %s", )
}