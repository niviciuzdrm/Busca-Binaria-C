#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c = 0;
    int achei = 0;
    char procurado[8] = "22755170";
    

    f = fopen("cep_ordenado.dat","r");
    fseek(f,0,SEEK_END);
    int tamarq = ftell(f);
    int qtdreg = tamarq / sizeof(Endereco);
    int inicio = 0;
    int fim = qtdreg - 1;

    while(inicio <= fim && !achei){

        c++; 
        int meio = (inicio + fim) / 2;
        fseek(f, meio*sizeof(Endereco), SEEK_SET);
        qt = fread(&e,sizeof(Endereco),1,f);

        if(strncmp(e.cep, procurado, 8) == 0){
            printf("Achei: %.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            achei = 1;
        } else if(strncmp(procurado, e.cep, 8) > 0){
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if(!achei){
        printf("O CEP %s não esta na lista", procurado);
    }
    printf("%d\n", c);
    return 0;
}