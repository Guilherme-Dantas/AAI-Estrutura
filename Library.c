#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"

void menu()
{

    /*
        VERIFICAÇÕES A FAZER
            1- REFATORAR DATA
            2- VERIFICAR SE A DATA ESTÁ COMPORTANDO CORRETAMENTE O TAMANHO INSERIDO
            3- VALIDAÇÕES NO INSERT DA DATA PARA IMPEDIR NASCIMENTOS NO FUTURO
            4- CALCULAR MEDIA DE LIMITE NA LISTA
    */
    cliente *listaCliente = NULL;

    char opcao;
    do
    {
        printf("\n========================= Menu Principal =======================\n");
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
            listaCliente = subMenuA(listaCliente);
            break;
        case 'B':
            subMenuB();
            break;
        case 'C':
            subMenuC(listaCliente);
            break;
        }

    } while (opcao != 'D');
}

cliente *subMenuA(cliente *listaCliente)

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
        listaCliente = cadastrarCliente(listaCliente);
        break;
    case 2:;
        int codigo = 0;
        cliente *clienteEncontrado;
        //dependente *listaDependentes = NULL;
        dependente *ultimoListaDependentes = NULL;

        do
        {
            codigo = procurarCodigo();
            clienteEncontrado = buscarRegistro(listaCliente, codigo);

            if (clienteEncontrado == NULL)
            {
                printf("\nCliente com o codigo %i nao foi encontrado. Insira novamente!", codigo);
            }
        } while (clienteEncontrado == NULL);
        cadastrarQtdDependente(clienteEncontrado);

        int i;
        for (i = 0; i < clienteEncontrado->quantidadeDeDependentes; i++)
        {
            ultimoListaDependentes = cadastrarDependentes(ultimoListaDependentes, clienteEncontrado);
            clienteEncontrado->listaDependentes = ultimoListaDependentes;
        }

        break;
    default:
        break;
    }

    return listaCliente;
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

void subMenuC(cliente *listaCliente)
{
    int opcaoNum = 0;
    do
    {
        printf("1 - Listar todos os dados de clientes cadastrados e exibir media dos limites\n");
        printf("2 - Listar todos os dados de um cliente por codigo\n");
        printf("3 - Listar clientes por tipo de cartao\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum < 1 || opcaoNum > 3)
        {
            printf(">>As opcoes tem que ser 1, 2 ou 3\n");
        }
    } while (opcaoNum < 1 || opcaoNum > 3);

    switch (opcaoNum)
    {
    case 1:;
        exibirTodosClientes(listaCliente, 0, 0);
        break;
    case 2:;
        exibirClienteEspecifico(listaCliente, procurarCodigo());
        break;
    case 3:;
    	printarClientePorCartao(listaCliente, recebeTipoCartao());
    	break;
    default:
        break;
    }
}

void cadastrarNome(char *nome)
{
    strcpy(nome, "");
    do
    {
        fflush(stdin);
        printf("\n\nDigite o seu nome: ");
        scanf(" %[^\n]", nome);
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

void cadastrarTipoCartao(cliente *cliente)
{
   char tipo =  recebeTipoCartao();

    if (tipo == 'N')
    {
        cliente->limiteEmprestimo *= 1.05;
    }
    else if (tipo == 'I')
    {
        cliente->limiteEmprestimo *= 1.20;
    }

    cliente->tipoDeCartao = tipo;
}

void cadastrarQtdDependente(cliente *cliente)
{
    int quantidade = 0;
    do
    {
        fflush(stdin);
        printf("\nDigite a quantidade de dependetes do cliente %s:", cliente->nome);
        scanf("%i", &quantidade);

        if (quantidade < 0 || quantidade > MAX_DEPENDETES)
        {
            printf("\nA quantidade de dependentes deve ser entre 0 e 2");
        }
    } while (quantidade < 0 || quantidade > MAX_DEPENDETES);

    cliente->quantidadeDeDependentes = quantidade;
}

void cadastrarTipoDependente(dependente *dependente)
{
    char tipoDependente = NULL;
    do
    {
        fflush(stdin);
        printf("\nInsira o tipo de dependente: ");
        scanf("%c", &tipoDependente);
        tipoDependente = toupper(tipoDependente);
        if (tipoDependente != 'C' && tipoDependente != 'F' && tipoDependente != 'E')
        {
            printf("\nInsira um valor dentre os possiveis: C, E ou F");
        }
    } while (tipoDependente != 'C' && tipoDependente != 'F' && tipoDependente != 'E');

    dependente->tipo = tipoDependente;
}

char *cadastrarNascimento(char *dataNascStruct, int minIdade)
{
    char dtNas[11];
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
    char dtAtual[11], anoAtualC[4], mesAtualC[2], diaAtualC[2];
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

dependente *cadastrarDependentes(dependente *fimLista, cliente *cliente)
{

    dependente *novoDependente = (dependente *)malloc(sizeof(dependente));
    cadastrarNome(novoDependente->nome);
    cadastrarNascimento(novoDependente->dataDeNascimento, MIN_IDADE_DEPENDENTE);
    cadastrarTipoDependente(novoDependente);
    if (fimLista == NULL)
    {
        novoDependente->codigo = RAND_INCREMENTAL(cliente->codigo);
    }
    else
    {
        novoDependente->codigo = RAND_INCREMENTAL(fimLista->codigo);
    }

    novoDependente->proximo = NULL;
    novoDependente->anterior = fimLista;

    if (fimLista != NULL)
    {
        fimLista->proximo = novoDependente;
    }

    return novoDependente;
}

cliente *cadastrarCliente(cliente *inicioLista)
{
    cliente *clienteNovo = (cliente *)malloc(sizeof(cliente));
    cadastrarNome(clienteNovo->nome);
    cadastrarNascimento(clienteNovo->dataDeNascimento, MIN_IDADE_CLIENTE);
    cadastrarLimite(&clienteNovo->limiteEmprestimo, calcularIdade(clienteNovo->dataDeNascimento));
    cadastrarTipoCartao(clienteNovo);
    clienteNovo->codigo = RAND;
    clienteNovo->proximo = inicioLista;
    clienteNovo->quantidadeDeDependentes = 0;

    return clienteNovo;
}

//REFATORAR FUNÇÃO - PRIORIDADE
cliente *buscarRegistro(cliente *atual, int cod)
{
    cliente *anterior = NULL;
    while (atual != NULL)
    { //Enquanto este ponteiro apontar para algum registro continua.
        if (atual->codigo == cod)
        { //Encontrei o registro.
            return atual;
        }
        else
        {                           //Não encontrei o registro.
            (anterior) = atual;     //Guarda o registro atual como anterior.
            atual = atual->proximo; //O atual aponta para o próximo, ainda na busca do registro.
        }
    }
    return NULL; //Se chegar aqui é porque o registro não existe na lista.
}

// TROCAR NOME DA FUNÇÃO
int procurarCodigo()
{
    int valor;
    do
    {
        printf("\nDigite o codigo a ser procurado: ");
        scanf("%i", &valor);
        if (valor < 0)
        {
            printf("\nInvalido.");
        }
    } while (valor < 0);
    return valor;
}

void exibirTodosClientes(cliente *listaCliente, int count, float limiteTotal)
{
    if (listaCliente != NULL)
    {
        printarValoresCliente(listaCliente);
        exibirTodosClientes(listaCliente->proximo, ++count, limiteTotal += listaCliente->limiteEmprestimo);
    }else{
    	float mediaLimite = limiteTotal/count;
    	printf("\n-------------------------MEDIA--------------------------------------");
    	printf("\nMedia dos limites: %.2f \n", mediaLimite);
	}
}

void exibirClienteEspecifico(cliente *listaCliente, int codigo)
{
    cliente *clienteEncontrado = buscarRegistro(listaCliente, codigo);
    if (clienteEncontrado != NULL)
    {
        printarValoresCliente(clienteEncontrado);
    }
    else
    {
        printf("\nNenhum cliente com esse codigo foi encontrado!\n");
    }
}

void exibirDependentes(dependente *listaDependente)
{
    if (listaDependente != NULL)
    {
        printf("\nDados do Dependente: %s", listaDependente->nome);
        printf("\nCodigo: %i", listaDependente->codigo);
        printf("\nData de Nascimento: %s", listaDependente->dataDeNascimento);
        printf("\nTipo de Dependente: %c", listaDependente->tipo);

        exibirDependentes(listaDependente->anterior);
    }
}

void printarValoresCliente(cliente *cliente)
{
    printf("\n================================================================");
    printf("\nDados do cliente %s", cliente->nome);
    printf("\nCodigo: %i", cliente->codigo);
    printf("\nData de Nascimento: %s", cliente->dataDeNascimento);
    printf("\nTipo de Cartao: %c", cliente->tipoDeCartao);
    printf("\nLimite de Emprestimo: %.2f", cliente->limiteEmprestimo);
    printf("\nQuantidade de Dependentes: %i", cliente->quantidadeDeDependentes);
    if (cliente->quantidadeDeDependentes > 0)
    {
        exibirDependentes(cliente->listaDependentes);
    }
}

char recebeTipoCartao()
{
	 char tipo;
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
     return tipo;
}

void printarClientePorCartao(cliente *listaCliente, char tipo)
{
     if(listaCliente != NULL){
     	if(listaCliente->tipoDeCartao == tipo){
     		printarValoresCliente(listaCliente);
		 }
		 printarClientePorCartao(listaCliente->proximo,tipo);
	 }
	 
}


