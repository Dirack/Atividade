#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "sistema.h"

int main(void){
	int opcao;

	while(1){
		printf("Sistema de cadastro - Agenda\n");
		print_menu();
		scanf("%d",&opcao);

		switch(opcao){
			case 1:	inserir_registros(); break;
			case 2:	editar_registros(); break;
			case 3:	excluir_registros(); break;
			case 4:	visualizar_registros(); break;
			case 5:	printf("Encerrar\n"); break;
			default: printf("Opção inválida!\n");
		}
		if(opcao==5) break;
	}

}
