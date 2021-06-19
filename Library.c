#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"

void menu()
{
    char dataAtaual[11] = "";
    int validaData = 0;
    do
    {
        printf("\nInsira data atual: ");
        scanf(" %[^\n]", dataAtaual);
        validaData = verificaData(dataAtaual);
    } while (validaData == 0);

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
            listaCliente = subMenuA(listaCliente, dataAtaual);
            break;
        case 'B':
            listaCliente = subMenuB(listaCliente);
            break;
        case 'C':
            subMenuC(listaCliente);
            break;
        }

    } while (opcao != 'D');
}

cliente *subMenuA(cliente *listaCliente, char *dataAtual)

{
    int opcaoNum = 0;
    do
    {
        //fflush(stdin);
        printf("1 - Efetuar inclusao de cliente\n2 - Efetuar inclusao de dependente\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum != 1 && opcaoNum != 2)
        {
            printf(">>As opcoes tem que ser 1 ou 2\n");
        }
    } while (opcaoNum != 1 && opcaoNum != 2);

    switch (opcaoNum)
    {
    case 1:;
        listaCliente = cadastrarCliente(listaCliente, dataAtual);
        break;
    case 2:;

        int codigo = 0;

        cliente *clienteEncontrado;
        dependente *inicioListaDependentes = NULL;
        dependente *ultimoListaDependentes = NULL;
        

        do
        {
            
            codigo = buscarCodigo("cliente");
            clienteEncontrado = buscarCliente(listaCliente, codigo, NULL);

            if (clienteEncontrado == NULL)
            {
                printf("\nCliente com o codigo %i nao foi encontrado. Insira novamente!", codigo);
            }
        } while (clienteEncontrado == NULL);

        cadastrarQtdDependente(clienteEncontrado);

        int i;
        for (i = 0; i < clienteEncontrado->quantidadeDeDependentes; i++)
        {
            ultimoListaDependentes = cadastrarDependentes(ultimoListaDependentes, clienteEncontrado, dataAtual);

            if (inicioListaDependentes == NULL)
            {
                inicioListaDependentes = ultimoListaDependentes;
            }

            clienteEncontrado->listaDependentes = inicioListaDependentes;
        }

        break;
    default:
        break;
    }

    return listaCliente;
}

cliente *subMenuB(cliente *listaCliente)
{

    cliente *clienteAnterior = NULL;

    int opcaoNum = 0;
    do
    {
        fflush(stdin);
        printf("1 - Efetuar exclusao de cliente\n2 - Efetuar exclusao de dependente\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum != 1 && opcaoNum != 2)
        {
            printf(">>As opcoes tem que ser 1 ou 2\n");
        }
    } while (opcaoNum != 1 && opcaoNum != 2);

    switch (opcaoNum)
    {
    case 1:;
        int codigo = buscarCodigo("cliente");
        cliente *clienteDeletar = buscarCliente(listaCliente, codigo, &clienteAnterior);
        if (clienteDeletar != NULL)
        {
            removerCliente(clienteDeletar, clienteAnterior, &listaCliente);
        }
        break;
    case 2:;
        codigo = buscarCodigo("cliente");
        cliente *clienteEncontrado = buscarCliente(listaCliente, codigo, &clienteAnterior);
        removerDependente(clienteEncontrado);
        break;

    default:
        break;
    }

    return listaCliente;
}

void subMenuC(cliente *listaCliente)
{
    int opcaoNum = 0;
    do
    {
        fflush(stdin);
        printf("1 - Listar todos os dados de clientes cadastrados e exibir media dos limites\n");
        printf("2 - Listar todos os dados de um cliente por codigo\n");
        printf("3 - Listar clientes por tipo de cartao\nOpcao : ");
        scanf(" %i", &opcaoNum);
        if (opcaoNum != 1 && opcaoNum != 2 && opcaoNum != 3)
        {
            printf(">>As opcoes tem que ser 1, 2 ou 3\n");
        }
    } while (opcaoNum != 1 && opcaoNum != 2 && opcaoNum != 3);

    if(listaCliente == NULL){
        printf("\nNao existe nenhum cliente cadastrado!");
        return;
    }

    switch (opcaoNum)
    {
    case 1:;
        exibirTodosClientes(listaCliente, 0, 0);
        break;
    case 2:;
        exibirClienteEspecifico(listaCliente, buscarCodigo("cliente"));
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
    } while (nome[0] == '\0' || strlen(nome) > 49);
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
    char tipo = recebeTipoCartao();

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

char *cadastrarNascimento(char *dataNascStruct, char *dataAtual)
{
    char dtNas[11];
    int valida = -1;

    do
    {
        fflush(stdin);
        printf("\nInsira data de nascimento: ");
        scanf(" %[^\n]", dtNas);
        valida = verificaData(dtNas);
    } while (valida == 0);

    strcpy(dataNascStruct, dtNas);
}

int calcularIdade(char *dataNascimento, char *dtAtual)
{
    int idade = 0;
    //Variáveis do dia atual
    char anoAtualC[4], mesAtualC[2], diaAtualC[2];
    char anoNascStr[4], mesNascStr[2], diaNascStr[2];

    int anoAtual, mesAtual, diaAtual;
    int anoNasc, mesNasc, diaNasc;

    anoNasc = atoi(strncpy(anoNascStr, dataNascimento + 6, 10)); //ano
    mesNasc = atoi(strncpy(mesNascStr, dataNascimento + 3, 6));  //mes
    diaNasc = atoi(strncpy(diaNascStr, dataNascimento + 0, 3));  //dia

    anoAtual = atoi(strncpy(anoAtualC, dtAtual + 6, 10)); // ano
    mesAtual = atoi(strncpy(mesAtualC, dtAtual + 3, 6));  //mes
    diaAtual = atoi(strncpy(diaAtualC, dtAtual + 0, 3));  //dia

    if (anoAtual < anoNasc)
    {
        printf("\n>>O ano atual nao pode ser menor que o ano de nascimento");
        return -1;
    }

    idade = anoAtual - anoNasc;
    //Verificando se a pessoa já fez aniversário ou não
    if (mesAtual < mesNasc || mesAtual == mesNasc && diaAtual < diaNasc)
    {
        idade--;
    }

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

dependente *cadastrarDependentes(dependente *fimLista, cliente *cliente, char *dtAtual)
{

    dependente *novoDependente = (dependente *)malloc(sizeof(dependente));
    int validacaoIdade = -1;
    cadastrarNome(novoDependente->nome);
    do
    {
        cadastrarNascimento(novoDependente->dataDeNascimento, dtAtual);
        novoDependente->idade = calcularIdade(novoDependente->dataDeNascimento, dtAtual);
        validacaoIdade = validaIdadeMinima(novoDependente->idade, MIN_IDADE_DEPENDENTE);

    } while (!validacaoIdade);

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

cliente *cadastrarCliente(cliente *inicioLista, char *dtAtual)
{
    cliente *clienteNovo = (cliente *)malloc(sizeof(cliente));
    int validacaoIdade = -1;
    cadastrarNome(clienteNovo->nome);

    do
    {
        cadastrarNascimento(clienteNovo->dataDeNascimento, dtAtual);
        clienteNovo->idade = calcularIdade(clienteNovo->dataDeNascimento, dtAtual);
        validacaoIdade = validaIdadeMinima(clienteNovo->idade, MIN_IDADE_CLIENTE);
    } while (!validacaoIdade);

    cadastrarLimite(&clienteNovo->limiteEmprestimo, clienteNovo->idade);
    cadastrarTipoCartao(clienteNovo);
    clienteNovo->codigo = RAND;
    clienteNovo->proximo = inicioLista;
    clienteNovo->quantidadeDeDependentes = 0;

    return clienteNovo;
}

cliente *buscarCliente(cliente *atual, int codigoProcurar, cliente **anterior)
{
    while (atual != NULL)
    {
        if (atual->codigo == codigoProcurar)
        {
            return atual;
        }
        else
        {
            (*anterior) = atual;
            atual = atual->proximo;
        }
    }
    return NULL;
}

dependente *buscarDependente(dependente *atual, int cod, dependente **anterior)
{
    dependente *dependenteAnterior = NULL;
    while (atual != NULL)
    {
        if (atual->codigo == cod)
        {
            if (dependenteAnterior != NULL)
            {
                *anterior = dependenteAnterior;
            }
            return atual;
        }
        else
        {
            (dependenteAnterior) = atual;
            atual = atual->proximo;
        }
    }
    return NULL;
}

int buscarCodigo(char *frase)
{
    int valor;
    do
    {
        fflush(stdin);
        printf("\nDigite o codigo do %s a ser buscado: ", frase);
        scanf("%i", &valor);
        if (valor < 0)
        {
            printf("\nCodigo deve ser maior que 0!");
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
    }
    else
    {
        float mediaLimite = limiteTotal / count;
        printf("\n-------------------------MEDIA--------------------------------------");
        printf("\nMedia dos limites: %.2f \n", mediaLimite);
    }
}

void exibirClienteEspecifico(cliente *listaCliente, int codigo)
{
    cliente *clienteEncontrado = buscarCliente(listaCliente, codigo, NULL);
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
        printf("\nIdade: %i", listaDependente->idade);
        printf("\nTipo de Dependente: %c", listaDependente->tipo);

        exibirDependentes(listaDependente->proximo);
    }
}

void printarValoresCliente(cliente *cliente)
{

    if (cliente != NULL)
    {
        printf("\n================================================================");
        printf("\nDados do cliente %s", cliente->nome);
        printf("\nCodigo: %i", cliente->codigo);
        printf("\nData de Nascimento: %s", cliente->dataDeNascimento);
        printf("\nIdade: %i", cliente->idade);
        printf("\nTipo de Cartao: %c", cliente->tipoDeCartao);
        printf("\nLimite de Emprestimo: %.2f", cliente->limiteEmprestimo);
        printf("\nQuantidade de Dependentes: %i", cliente->quantidadeDeDependentes);
        if (cliente->quantidadeDeDependentes > 0)
        {
            exibirDependentes(cliente->listaDependentes);
        }
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
    if (listaCliente != NULL)
    {
        if (listaCliente->tipoDeCartao == tipo)
        {
            printarValoresCliente(listaCliente);
        }
        printarClientePorCartao(listaCliente->proximo, tipo);
    }
}

void removerCliente(cliente *excluir, cliente *anterior, cliente **inicioLista)
{
    if (anterior == NULL)
    {
        (*inicioLista) = (*inicioLista)->proximo;
    }
    else if (excluir->proximo == NULL)
    {
        anterior->proximo = NULL;
    }
    else
    {
        anterior->proximo = excluir->proximo;
    }

    if (excluir->quantidadeDeDependentes != 0)
    {
        int i;
        for (i = 1; i <= excluir->quantidadeDeDependentes; i++)
        {
            dependente *dependenteEncontrado = buscarDependente(excluir->listaDependentes, excluir->listaDependentes->codigo, NULL);
            dependente *ultimoDependente = procurarUltimo(excluir->listaDependentes);
            removerDependentePorCliente(dependenteEncontrado, &excluir->listaDependentes, &ultimoDependente);
        }
    }

    free(excluir);
}

void removerDependente(cliente *clienteReferencia)
{
    int codigoDependente = buscarCodigo("dependente");
    dependente *dependenteEncontrado = buscarDependente(clienteReferencia->listaDependentes, codigoDependente, NULL);
    dependente *ultimoDependente = procurarUltimo(clienteReferencia->listaDependentes);
    removerDependentePorCliente(dependenteEncontrado, &clienteReferencia->listaDependentes, &ultimoDependente);
    clienteReferencia->quantidadeDeDependentes--;
}

void removerDependentePorCliente(dependente *excluir, dependente **inicioLista, dependente **ultimoRegistro)
{

    if (excluir->anterior == NULL)
    {                                             
        (*inicioLista) = (*inicioLista)->proximo; 
        if ((*inicioLista) != NULL)
        {                                    
            (*inicioLista)->anterior = NULL; 
        }
    }
    else
    { 
        excluir->anterior->proximo = excluir->proximo;
        if (excluir->proximo != NULL)
        {
            excluir->proximo->anterior = excluir->anterior;
        }
    }

    
    if ((*ultimoRegistro)->codigo == excluir->codigo)
    {
        (*ultimoRegistro) = excluir->anterior; 
    }

    free(excluir); 
}

dependente *procurarUltimo(dependente *listaDependente)
{
    dependente *atual = listaDependente;

    if (atual->proximo == NULL)
    {
        return atual;
    }

    atual = atual->proximo;
    return atual;
}

int validaIdadeMinima(int idade, int idadeMinima)
{

    if (idade < idadeMinima || idade > MAX_IDADE)
    {
        printf("\nA idade dessa pessoa deve ser maior ou igual a %i e menor que %i.", idadeMinima, MAX_IDADE);
        return 0;
    }

    return 1;
}
