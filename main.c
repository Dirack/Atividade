#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "sistema.h"

int main(void){
	int opcao;

	iniciar_banco_de_dados();

	while(1){
		printf("Sistema de cadastro - Agenda\n");
		print_menu();
		scanf("%d%*c",&opcao);

		switch(opcao){
			case 1:	inserir_registros(); break;
			case 2:	editar_registros(); break;
			case 3:	excluir_registros(); break;
			case 4:	visualizar_registros(); break;
			case 5:	printf("Encerrar\n"); exit(0);
			default: printf("Opção inválida!\n");
		}
	}

}
