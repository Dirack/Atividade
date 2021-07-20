#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define MAX_NOME 30
#define MAX_EMAIL 30
#define MAX_TELEFONE 12
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

static int usuario_valido(char nome[MAX_NOME], char *email, char *telefone){

	int i;

	printf("%s %s %s\n",nome,email,telefone);
	if(strlen(nome)<=2) return 0;

	if(strlen(email)<10) return 0;

	if(strlen(telefone)<10) return 0;

	for(i=0;i<strlen(telefone);i++)
		if(((int)telefone[i]) < 48 || ((int)telefone[i]) > 57) return 0;	
	return 1;
}

void inserir_registros(){

	char nome[MAX_NOME];
	char email[MAX_EMAIL];
	char telefone[MAX_TELEFONE];
	char salvar='n';
	char sexo='m';
	int i;

	fp = fopen(BANCO_DE_DADOS,"a");
	if(fp==NULL){
		fprintf(stderr,"%s: Falha ao abrir o arquivo %s\n",__FILE__,BANCO_DE_DADOS);
		return;
	}

	printf("Inserir novo registro na Agenda\n");
	printf("Digite o nome do usuário:\n");

	fgets(nome,MAX_NOME,stdin); nome[strcspn(nome, "\n")] = '\0';
	printf("Digite o email:\n");
	fgets(email,MAX_EMAIL,stdin); email[strcspn(email, "\n")] = '\0';
	printf("Digite o telefone:\n");
	fgets(telefone,MAX_TELEFONE,stdin); telefone[strcspn(telefone, "\n")] = '\0';
	printf("Escolha o Sexo do usuário (m/f)?");
	scanf(" %c%*c",&sexo);
	
	if(sexo!='m' && sexo != 'f'){
		fprintf(stderr,"%s: Erro: Opção inválida! (m/f)?",__FILE__);
		return;
	}

	if(strlen(nome)<=2){
		fprintf(stderr,"%s: Erro: Registro inválido!\nO nome deve possuir mais de 2 caracteres!\n",__FILE__);
		return;
	}else if(strlen(email)<10){
		fprintf(stderr,"%s: Erro: Registro inválido!\nO email deve possuir mais de 10 caracteres\n",__FILE__);
		return;
	}else if(strlen(telefone)<10){
		fprintf(stderr,"%s: Erro: Registro inválido!\nO telefone deve possuir de 10 a 11 caracteres\n",__FILE__);
		return;
	}else{
		for(i=0;i<strlen(telefone);i++){
			printf("%d ",telefone[i]);
			if(((int)telefone[i])<48 || ((int) telefone[i])>57){
				fprintf(stderr,"%s: Erro: Registro inválido!\nO telefone deve possuir apenas caracteres numéricos\n",__FILE__);
			       	return;
			}
		}
		printf("O usuário a ser cadastrado:\n");
		printf("Nome: %s\n",nome);
		printf("Email: %s\n",email);
		printf("Telefone: %s\n",telefone);
	}
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
		if(!(strlen(novo)>2)){
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
