#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define MAX_NOME 30
#define BANCO_DE_DADOS "pessoas.txt"

void inserir_registros(){

	char nome[MAX_NOME];
	FILE *fp;
	char salvar='n';

	fp = fopen(BANCO_DE_DADOS,"a");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		exit(1);
	}

	printf("Inserir novo registro na Agenda\n");
	printf("Digite o nome do usuário:\n");
	scanf(" %[^\n]",nome);
	if((strlen(nome))<=2){
		fprintf(stderr,"%s: Erro: O nome deve possuir mais de 2 caracteres!\n",__FILE__);
		return;
	}

	printf("O usuário a ser cadastrado:\n");
	printf("Nome: %s\n",nome);
	printf("Salvar (y/n)? "); scanf(" %c",&salvar);
	if(salvar=='y'){
		fseek(fp,0*sizeof(char),SEEK_END);
		fprintf(fp,"%s\n",nome);
		printf("Registro salvo com sucesso!\n");
	}else if(salvar=='n'){
		printf("Registro ignorado!\n");
	}else{
		fprintf(stderr,"%s: Erro: Opção inválida! (y/n)?",__FILE__);
		return;
	}

	fclose(fp);
}

void visualizar_registros(){
	FILE *fp;
	int i;
	int num_usuarios;
	char buffer[30];

	fp = fopen(BANCO_DE_DADOS,"r");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		exit(1);
	}

	num_usuarios=conta_linhas(fp);

	for(i=0;i<num_usuarios;i++){
		fscanf(fp,"%[^\n]%*c",buffer);
		printf("id=%d nome=%s\n",i,buffer);
	}

	fclose(fp);
}
