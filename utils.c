#include "utils.h"
#include <stdio.h>

static char opcoes_menu[NUM_OPCOES][11]={"Inserir","Editar","Excluir","Visualizar","Sair"};

void print_menu()
/*< Função para imprimir o menu do sistema >*/
{
	int i;

	for(i=0;i<NUM_OPCOES;i++)
		printf("%d) %s\n",i,opcoes_menu[i]);
}

