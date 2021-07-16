#include <stdio.h>
#include <stdlib.h>
#define MAX_NOME 30
#define BANCO_DE_DADOS "pessoas.txt"

void inserir_registros(){

	char nome[MAX_NOME];
	FILE *fp;

	fp = fopen(BANCO_DE_DADOS,"w");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		exit(1);
	}

	printf("Inserir novo registro na Agenda\n");
	printf("Digite o nome do usuário:\n");
	scanf(" %[^\n]",nome);

	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s\n",nome);
	fclose(fp);
}
