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
			case 2:	printf("escolheu 2\n"); break;
			case 3:	printf("escolheu 3\n"); break;
			case 4:	printf("escolheu 4\n"); break;
			case 5:	printf("escolheu 5\n"); break;
			default: printf("Opção inválida!\n");
		}
		if(opcao==5) break;
	}
}
