typedef struct Dependente dependente;
struct Dependente
{
    char nome[50];
    int codigo;
    char dataDeNascimento[11];
    int idade;
    char tipo;
    dependente *anterior;
    dependente *proximo;
} Dependente;

typedef struct Cliente cliente;
struct Cliente
{
    char nome[50];
    int codigo;
    char dataDeNascimento[11];
    int idade;
    char tipoDeCartao;
    float limiteEmprestimo;
    int quantidadeDeDependentes;
    cliente *proximo;
    dependente *listaDependentes;

} Cliente;

void cadastrarNome(char *nome);
char *cadastrarNascimento(char *dataNascStruct, char *dataAtual);
void cadastrarTipoCartao(cliente *cliente);
void cadastrarTipoDependente(dependente *dependente);
cliente *subMenuA(cliente *listaCliente, char *dataAtual);
cliente *subMenuB(cliente *listaCliente);
void subMenuC();
void cadastrarLimite(float *limite, int idade);
void cadastrarQtdDependente(cliente *cliente);
int calcularIdade();
int verificaData(char *data);
cliente *cadastrarCliente(cliente *inicioLista, char *dtAtual);
dependente *cadastrarDependentes(dependente *fimLista, cliente *cliente, char *dtAtual);
cliente *buscarCliente(cliente *atual, int codigoProcurar, cliente **anterior);
int buscarCodigo();
void exibirTodosClientes(cliente *listaCliente, int count, float limiteTotal);
void exibirClienteEspecifico(cliente *listaCliente, int codigo);
void exibirDependentes(dependente *listaDependente);
void printarValoresCliente(cliente *cliente);
void printarClientePorCartao(cliente *listaCliente, char tipo);
void removerCliente(cliente *excluir, cliente *anterior, cliente **inicioLista);
char recebeTipoCartao();
void removerDependentePorCliente(dependente *excluir, dependente **inicioLista, dependente **ultimoRegistro);
dependente *procurarUltimo(dependente *listaDependente);
void removerDependente(cliente *clienteReferencia);

#define RAND rand() % 1000
#define RAND_INCREMENTAL(a) (a + 1)
#define MAX_DEPENDETES (2)
#define MAX_IDADE (100)
#define MIN_IDADE_CLIENTE (18)
#define MIN_IDADE_DEPENDENTE (0)
