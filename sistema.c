#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define MAX_NOME 30
#define MAX_USUARIOS 100
#define BANCO_DE_DADOS "pessoas.txt"

FILE *fp;
int num_usuarios;

void iniciar_banco_de_dados(){
	fp=fopen(BANCO_DE_DADOS,"r");
	if(NULL==fp){
		fprintf(stderr,"%s: Arquivo de banco de dados %s não encontrado!\n",__FILE__,BANCO_DE_DADOS);
		exit(1);
	}
	num_usuarios=conta_linhas(fp);
	fclose(fp);
}

static int nome_valido(const char *nome){
	return (strlen(nome)>=2);
}

void inserir_registros(){

	char nome[MAX_NOME];
	char salvar='n';

	fp = fopen(BANCO_DE_DADOS,"a");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		return;
	}

	printf("Inserir novo registro na Agenda\n");
	printf("Digite o nome do usuário:\n");
	scanf(" %[^\n]",nome);
	
	if(!nome_valido(nome)){
		fprintf(stderr,"%s: Erro: O nome deve possuir mais de 2 caracteres!\n",__FILE__);
		return;
	}

	printf("O usuário a ser cadastrado:\n");
	printf("Nome: %s\n",nome);
	printf("Salvar (y/n)? "); scanf(" %c",&salvar);

	if(salvar=='y'){
		fprintf(fp,"%-29s\n",nome);
		num_usuarios++;
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
	int i;
	char buffer[30];
	int id, opcao;

	fp = fopen(BANCO_DE_DADOS,"r");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		exit(1);
	}

	printf("1 - Visualizar por id\n2 - Visualizar todos os usuários\n");
	scanf(" %d",&opcao);

	if(opcao==2){
		printf("Lista de usuários\n");
		for(i=0;i<num_usuarios;i++){
			fscanf(fp,"%[^\n]%*c",buffer);
			printf("id=%d nome=%29s\n",i,buffer);
		}
	}else if(opcao==1){
		printf("Qual o id? ");
		scanf(" %d",&id);
		if(id>=num_usuarios || id < 0){
			printf("Não há nenhum usuário cadastrado com o id=%d\n",id);
			return;
		}

		fseek(fp,id*MAX_NOME*sizeof(char),SEEK_SET);
		fscanf(fp,"%[^\n]%*c",buffer);
		printf("id=%d nome=%s\n",id,buffer);
	}else{
		printf("Opção inválida! (y/n)?\n");
	}

	fclose(fp);
}

void excluir_registros(){
	int id;
	int i;
	char excluir='n';
	char nome[MAX_NOME];
	char usuarios[MAX_USUARIOS][MAX_NOME];
	fp=fopen(BANCO_DE_DADOS,"r");

	num_usuarios=conta_linhas(fp);
	printf("Forneça o id de usuário: "); scanf(" %d",&id);
	if(id>=num_usuarios){
		fprintf(stderr,"%s: Erro: Usuário id=%d não encontrado!\n",__FILE__,id);
		return;
	}else{
		for(i=0;i<num_usuarios;i++)	
			fscanf(fp,"%[^\n]%*c",usuarios[i]);
		fclose(fp);
	}

	printf("O usuário a ser excluído:\n");
	printf("Nome: %s\n",usuarios[id]);
	printf("Excluir (y/n)? "); scanf(" %c",&excluir);
	if(excluir=='y'){
		fp=fopen(BANCO_DE_DADOS,"w");
		for(i=0;i<num_usuarios;i++){
			if(i==id) continue;
			fprintf(fp,"%s\n",usuarios[i]);
		}
		num_usuarios--;
		fclose(fp);
		printf("Registro excluído com sucesso!\n");
	}else if(excluir=='n'){
		printf("Registro ignorado!\n");
	}else{
		fprintf(stderr,"%s: Erro: Opção inválida! (y/n)?",__FILE__);
		return;
	}
}

void editar_registros(){
	int id;
	int i;
	char editar='n';
	char novo[MAX_NOME];
	char usuarios[MAX_USUARIOS][MAX_NOME];
	fp=fopen(BANCO_DE_DADOS,"r");

	num_usuarios=conta_linhas(fp);
	printf("Forneça o id de usuário: "); scanf(" %d",&id);
	if(id>=num_usuarios){
		fprintf(stderr,"%s: Erro: Usuário id=%d não encontrado!\n",__FILE__,id);
		return;
	}else{
		for(i=0;i<num_usuarios;i++)	
			fscanf(fp,"%[^\n]%*c",usuarios[i]);
		fclose(fp);
	}

	printf("O usuário a ser editado:\n");
	printf("Nome: %s\n",usuarios[id]);
	printf("Editar (y/n)? "); scanf(" %c",&editar);
	if(editar=='y'){
		fp=fopen(BANCO_DE_DADOS,"w");
		printf("Digite o novo nome do usuário:\n");
		scanf(" %[^\n]",novo);
		if(!nome_valido){
			fprintf(stderr,"%s: Erro: O nome deve possuir mais de 2 caracteres!\n",__FILE__);
			return;
		}

		for(i=0;i<num_usuarios;i++){
			if(i==id){
				fprintf(fp,"%-29s\n",novo);
				continue;
			}
			fprintf(fp,"%s\n",usuarios[i]);
		}
		fclose(fp);
		printf("Registro editado com sucesso!\n");
	}else if(editar=='n'){
		printf("Registro ignorado!\n");
	}else{
		fprintf(stderr,"%s: Erro: Opção inválida! (y/n)?",__FILE__);
		return;
	}

}
