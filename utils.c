#include "utils.h"
#include <stdio.h>

static char opcoes_menu[NUM_OPCOES][21]={"Inserir registro","Editar registro","Excluir registro","Visualizar registro","Sair"};

void print_menu()
/*< Função para imprimir o menu do sistema >*/
{
	int i;

	for(i=0;i<NUM_OPCOES;i++)
		printf("%d) %s\n",i+1,opcoes_menu[i]);
}

int conta_linhas(FILE *fp){
        char linha[30];
        int count=0;
        while(fscanf(fp,"%[^\n]%*c",linha)==1){
                count++;
        }
        rewind(fp);
        return count;
}
