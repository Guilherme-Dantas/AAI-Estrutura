typedef struct Dependente dependente;
struct Dependente
{
    char nome[50];
    int codigo;
    char dataDeNascimento[10];
    char tipo[1];
    dependente *anterior;
    dependente *proximo;
} Dependente;

typedef struct Cliente cliente;
struct Cliente
{
    char nome[50];
    int codigo;
    char dataDeNascimento[10];
    char tipoDeCartao;
    float limiteEmprestimo;
    int quantidadeDeDependentes;
    cliente *proximo;
    dependente *listaDependentes;

} Cliente;

void cadastrarNome(char *nome);
char* cadastrarNascimento(char *dataNascStruct, int minIdade);
void cadastrarTipo();
void subMenuA();
void subMenuB();
void subMenuC();
void cadastrarLimite(float *limite, int idade);
void cadastrarQtdDependente(cliente *cliente);
int calcularIdade();
int verificaData(char *data);
void imprimirLista(cliente *lista);
cliente* cadastrarCliente(cliente *listaCliente);


#define RAND rand() % 1000
#define RAND_INCREMENTAL(a) (a+1)
#define MAX_DEPENDETES (2)
#define MAX_IDADE (100)
#define MIN_IDADE_CLIENTE (18)
#define MIN_IDADE_DEPENDENTE (0)