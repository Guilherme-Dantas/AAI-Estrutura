typedef struct Dependente
{
    char nome[50];
    int codigo;
    char dataDeNascimento[10];
    char tipo[1]
} Dependente;

typedef struct Cliente
{
    char nome[50];
    int codigo;
    int idade;
    char dataDeNascimento[10];
    char tipoDeCartao[1];
    float limiteEmprestimo;
    int quantidadeDeDependentes;
    Dependente *estruturaDependentes;

} Cliente;

void cadastrarNome(char *nome);
char* cadastrarNascimento();
char cadastrarTipo();
void subMenuA();
void subMenuB();
void subMenuC();
void cadastrarLimite(float *limite, int *idade);
void cadastrarQtdDependente(Cliente *Cliente);
int compararIdade(int idade);
int calcularIdade();
int verificaData(char *data);


#define RAND rand() % 1000
#define RAND_INCREMENTAL(a) (a+1)
#define MAX_DEPENDETES (2)
#define MAX_IDADE (100)
#define MIN_IDADE_CLIENTE (18)
#define MIN_IDADE_DEPENDENTE (0)