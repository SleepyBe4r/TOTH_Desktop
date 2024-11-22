#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#define CAPACIDADE_SALA 30
#define MAX_DISCIPLINA 30

/*Gerenciar alunos, gerenciar disciplinas, gerenciar
professores, gerenciar série, gerenciar turma, gerenciar sala, gerenciar ano letivo;
• Efetuar matrícula
• Definir de grade curricular
• Alocar turma.
• Gerenciar compra de material
• Controlar de estoque
• Efetuar baixa (uso de material)
• Relatórios gerais (ex: turmas, professores, etc). */

typedef struct {
	int dia, // dia ex: 02;
		mes, // mes ex: 07;
		ano; // ano ex: 2000;
}DATA;

typedef struct {
	int ano; // ano da serie ex: 1, 2, 3;
	char sala[50]; // identificação da sala ex: A, B, C;
	DATA ano_letivo; // ano letivo ex: 2022, 2023, 2024;
}SERIE;

typedef struct {
	int cod; // código da disciplina ex: 1, 2, 3;
	char nome[100];	// nome da disciplina ex: matematica, português, ciências;
}DISCIPLINA;

typedef struct {
	int faltas, // quantidade de faltas ex: 0, 1, 2;	
		bimestre; // indentificação do bimestre ex: 1, 2, 3;
	char cpf_aluno;
	float nota; // nota do aluno ex: 0, 2.5, 10;
	DISCIPLINA disc; // disciplina do professor ex: cód->1, nome->matematica;
	DATA ano; 
}HISTORICO_ESCOLAR;

typedef struct {
	char nome[100], // nome do aluno ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100], // email de contato ex: joao@gmail.com;
		sexo, // sexo do aluno ex: F, M;
	    CPF[20]; // CPF do aluno ex: 12345678912; 
	DATA niver; // aniversário do aluno ex: dia->02, mes->07, ano->2000;
	SERIE turma; // turma do aluno ex: ano->1, sala->B;	
}ALUNO;

typedef struct {
	int cod_material, // código do material retirado ex: 1, 2, 3;
		quantidade; // quantidade retirada ex: 0, 1, 2;	
	char motivo[100], // motivo da retirada do material ex: uso na sala, impressao de prova;	
		 cod_pessoa[20]; // código da pessoa que retirou ex: 12345678912;	
	DATA dt_retirada; // data da retirada do material ex: dia->02, mes->07, ano->2000;
}HISTORICO_RETIRADA;

typedef struct {
	int cod, // código do material ex: 1, 2, 3;
		estoque; // quantidade em estoque ex: 0, 1, 2;	
	char descricao[100]; // descrição do material ex: lapis, giz, papel A4;	
	DATA ultima_compra; // data da ultima compra do material ex: dia->02, mes->07, ano->2000;
}ESTOQUE;

typedef struct {
	char nome[100], // nome do professor ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100],// email de contato ex: joao@gmail.com;
		sexo,
	    CPF[20]; // CPF do professor ex: 12345678912;
	DATA niver; // aniversário do professor ex: dia->02, mes->07, ano->2000;
	SERIE turma[50]; // turma do professor ex: ano->1, sala->B;
	int cont_diciplina;	
	DISCIPLINA disc[MAX_DISCIPLINA]; // disciplina do professor ex: cód->1, nome->matematica;
}PROFESSOR;

// 1° paramêtro - menu: grava a opção escolhida;
// 2° paramêtro - op: opção do Menu que irá aparecer;
void mostrar_menu(int *menu, int op){
		
	system("cls");	
	switch (op) {
        case 1:
            printf("\n\nMenu de Gerenciamento de Alunos");
		    printf("\n1- Cadastrar Aluno"); // OK Cayo;
		    printf("\n2- Editar Aluno"); // OK Cayo;
		    printf("\n3- Excluir Aluno"); // OK Cayo;
		    printf("\n4- Lançar notas e Frequência"); // OK Cayo;
		    printf("\n5- Editar notas e Frequência"); // OK Cayo;	
		    printf("\n6- Excluir notas e Frequência"); // OK Cayo;
		    printf("\n7- Ordenar Alunos"); // OK Cayo;
		    printf("\n0- Retornar");
            break;
        case 2:
            printf("\n\nMenu de Gerenciamento de Disciplinas");
		    printf("\n1- Cadastrar Disciplina"); // OK Cayo;
		    printf("\n2- Editar Disciplina"); // OK Cayo;
		    printf("\n3- Excluir Disciplina"); // OK Cayo;
		    printf("\n4- Atribuir Disciplina ao Professor"); // OK Cayo;
		    printf("\n5- Retirar Disciplina do Professor"); // OK Cayo;
		    printf("\n0- Retornar");	
            break;
        case 3:
            printf("\n\nMenu de Gerenciamento de Professores");
		    printf("\n1- Cadastrar Professor"); // OK Cayo;
		    printf("\n2- Editar Professor"); // OK Cayo;
		    printf("\n3- Excluir Professor"); // OK Cayo;
		    printf("\n0- Retornar");	
            break;
        case 4:
            printf("\n\nMenu de Gerenciamento de Séries");
		    printf("\n1- Cadastrar Série"); // OK Cayo;
		    printf("\n2- Editar Série"); // OK Cayo;
		    printf("\n3- Excluir Série"); // OK Cayo;
		    printf("\n4- Atribuir à Série"); // OK Cayo;
		    printf("\n5- Retirar da Série"); // OK Cayo;
		    printf("\n0- Retornar");
            break;
        case 5:
            printf("\n\nMenu de Gerenciamento do Estoque");
		    printf("\n1- Cadastrar Material"); // OK Cayo;
		    printf("\n2- Editar Material"); // OK Cayo;
		    printf("\n3- Excluir Material"); // OK Cayo;
		    printf("\n4- Compra de Materiais"); // OK Cayo;
		    printf("\n5- Efetuar Baixa de Materiais"); // OK Cayo;				
		    printf("\n0- Retornar");
            break;
        case 6:
            printf("\n\nMenu de Relatorios Gerais");
		    printf("\n1- Listar Alunos"); // OK Cayo;
		    printf("\n2- Listar Histórico Acadêmico"); 
		    printf("\n3- Listar Alunos por Série"); 
			printf("\n4- Listar Disciplinas"); // OK Cayo;
		    printf("\n5- Listar Disciplinas do Professor"); // OK Cayo;
		    printf("\n6- Listar Professores"); // OK Cayo;
		    printf("\n9- Listar Séries"); // OK Cayo;
		    printf("\n10- Listar Inventário de Materiais"); // OK Cayo;
		    printf("\n11- Listar Baixas de Materiais"); 
		    printf("\n0- Retornar");
            break;        
        case 0:
            printf("\n\nMenu de Gerenciamento Escolar");
		    printf("\n1- Gerenciar Alunos");
		    printf("\n2- Gerenciar Disciplinas");
		    printf("\n3- Gerenciar Professores");
		    printf("\n4- Gerenciar Série");
			printf("\n5- Gerenciar Estoque");
		    printf("\n6- Relatórios Gerais");
		    printf("\n0- Sair do programa");	
        	break;
    }	
    
	printf("\n\nDigite uma opção para continuar: ");
	scanf("%d",&*menu);
}

// 1° paramêtro - fl: arquivo que será buscado;
// 2° paramêtro - id_d: indentificação em decimal que será usada para buscar;
// 3° paramêtro - id_s: indentificação em string que será usada para buscar;
// 4° paramêtro - op: opção que será usada para buscar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque;
int busca_posicao(FILE *fl, int id_d, char id_s[100], int op){
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	PROFESSOR professor;
	SERIE serie;
	ESTOQUE estoque;
	
	switch(op){
		case 1:
			rewind(fl);
			fread(&aluno,sizeof(ALUNO),1,fl);
			while(!feof(fl) && strcmp(id_s, aluno.CPF)){
				fread(&aluno,sizeof(ALUNO),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(ALUNO));
			} else{
				return -1;
			}
			break;
		case 2:
			rewind(fl);
			fread(&disciplina,sizeof(DISCIPLINA),1,fl);
			while(!feof(fl) && id_d != disciplina.cod){
				fread(&disciplina,sizeof(DISCIPLINA),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(DISCIPLINA));
			} else{
				return -1;
			}
			break;
		case 3:
			rewind(fl);
			fread(&professor,sizeof(PROFESSOR),1,fl);
			while(!feof(fl) && strcmp(id_s, professor.CPF)){
				fread(&professor,sizeof(PROFESSOR),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(PROFESSOR));
			} else{
				return -1;
			}
			break;
		case 4:
			rewind(fl);
			fread(&serie,sizeof(SERIE),1,fl);
			while(!feof(fl) && strcmp(id_s, serie.sala) && id_d != serie.ano){
				fread(&serie,sizeof(SERIE),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(SERIE));
			} else{
				return -1;
			}
			break;
		case 5:
			rewind(fl);
			fread(&estoque,sizeof(ESTOQUE),1,fl);
			while(!feof(fl) && id_d != estoque.cod){
				fread(&estoque,sizeof(ESTOQUE),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(ESTOQUE));
			} else{
				return -1;
			}
			break;
	}
}
				
// 1° paramêtro - op: opção que será usada para inserir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque;
void inserir(int op){
	FILE *fl;
	int pos,
		qnt;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	PROFESSOR professor;
	SERIE serie;
	ESTOQUE estoque;
		
	switch(op){
		case 1:			
			fl = fopen("aluno.bin","ab+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno: ");
					fflush(stdin);
					gets(aluno.CPF);
					pos = busca_posicao(fl, 0, aluno.CPF, 1);
					if(pos==-1)
					{
						printf("\n\nInforme o nome completo: ");
						fflush(stdin);
						gets(aluno.nome);
						
						printf("\n\nInforme o sexo do aluno (F/M): ");
						fflush(stdin);
						scanf("%c", &aluno.sexo);
						aluno.sexo = toupper(aluno.sexo);
						
						printf("\n\nInforme o telefone de contato: ");
						fflush(stdin);
						gets(aluno.telefone);
						
						printf("\n\nInforme o email de contato: ");
						fflush(stdin);
						gets(aluno.email);
						
						printf("\nInforme a data de aniversario dd mm aaaa: ");
						scanf("%d %d %d", &aluno.niver.dia, &aluno.niver.mes, &aluno.niver.ano);	
												
						fwrite(&aluno,sizeof(ALUNO),1,fl);
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&aluno,sizeof(ALUNO),1,fl);
						printf("\n\nId: %s (Aluno ja cadastrado!)",aluno.CPF);
					}
					printf("\n\nDeseja cadastrar outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 2:			
			fl = fopen("disciplina.bin","ab+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					qnt = ftell(fl)/sizeof(DISCIPLINA);
					if(qnt < MAX_DISCIPLINA){
						printf("\n\nInforme o código da disciplina: ");
						scanf("%d", &disciplina.cod);
						
						pos = busca_posicao(fl, disciplina.cod, "", 2);
						if(pos==-1)
						{
							printf("\n\nInforme o nome da disciplina: ");
							fflush(stdin);
							gets(disciplina.nome);
							
							fwrite(&disciplina,sizeof(DISCIPLINA),1,fl);
						}
						else 
						{
							fseek(fl,pos,0);
							fread(&disciplina,sizeof(DISCIPLINA),1,fl);
							printf("\n\nId: %d (Disciplina ja cadastrado!)",disciplina.cod);
							printf("\n\nDeseja cadastrar outra disciplina? (s)(n)");
						}						
					} else {
						printf("\n\nNão é possível cadastrar outra disciplina, pois o limite máximo já foi atingido.");
						system("cls");
						printf("\n\nDeseja continuar? (s)(n)");
					}
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 3:
			fl = fopen("professor.bin","ab+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					
					printf("\n\nInforme o CPF do professor: ");
					fflush(stdin);
					gets(professor.CPF);
					pos = busca_posicao(fl, 0, professor.CPF, 3);
					if(pos==-1)
					{
						printf("\n\nInforme o nome completo: ");
						fflush(stdin);
						gets(professor.nome);
						
						printf("\n\nInforme o sexo do professor (F/M): ");
						fflush(stdin);
						scanf("%c", &professor.sexo);
						professor.sexo = toupper(professor.sexo);
						
						printf("\n\nInforme o telefone de contato: ");
						fflush(stdin);
						gets(professor.telefone);
						
						printf("\n\nInforme o email de contato: ");
						fflush(stdin);
						gets(professor.email);
						
						printf("\nInforme a data de aniversario dd mm aaaa: ");
						scanf("%d %d %d", &professor.niver.dia, &professor.niver.mes, &professor.niver.ano);	
						
						professor.cont_diciplina = 0;
						
						fwrite(&professor,sizeof(PROFESSOR),1,fl);
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&professor,sizeof(PROFESSOR),1,fl);
						printf("\n\nId: %s (Professor ja cadastrado!)",professor.CPF);
					}
					printf("\n\nDeseja cadastrar outro professor? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 4:
			fl = fopen("serie.bin","ab+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					
					printf("\n\nInforme o ano da série: ");
					scanf("%d", &serie.ano);	
					
					printf("\n\nInforme o nome da sala: ");
					fflush(stdin);
					gets(serie.sala);
					pos = busca_posicao(fl, serie.ano, serie.sala, 4);
					if(pos==-1)
					{						
						printf("\nInforme a ano letivo aaaa: ");
						scanf("%d", &serie.ano_letivo.ano);	
						
						fwrite(&serie,sizeof(SERIE),1,fl);
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&serie,sizeof(SERIE),1,fl);
						printf("\n\nId: %d-%s (Série ja cadastrado!)",serie.ano,serie.sala);
					}
					printf("\n\nDeseja cadastrar outra série? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 5:
			fl = fopen("estoque.bin","ab+");
			if(fl == NULL) {
				printf("\n\nErro no arquivo!");
			} else {
				do{
					printf("\n\nInforme o Código do material: ");
					scanf("%d", &estoque.cod);
					
					pos = busca_posicao(fl, estoque.cod, "",5);
					if(pos == -1){
						printf("\n\nInforme a quantidade inicial do material: ");
						scanf("%d", &estoque.estoque);
						
						printf("\n\nInforme a descrição do material: ");
						fflush(stdin);
						gets(estoque.descricao);
						
						printf("\n\nInforme a data da ultima compra do material dd mm aaaa: ");
						scanf("%d %d %d", &estoque.ultima_compra.dia, &estoque.ultima_compra.mes, &estoque.ultima_compra.ano);
						
						fwrite(&estoque,sizeof(ESTOQUE),1,fl);
					} else {
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\nId: %d (Material ja cadastrado!)",estoque.cod);
					}
					printf("\n\nDeseja cadastrar outro material? (s)(n)");
				} while(toupper(getch()) == 'S');
			}
			fclose(fl);
			break;
	}
}

// 1° paramêtro - op: opção que será usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque;
void atualizar(int op){
	FILE *fl;	
	int pos,
		pos2;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	PROFESSOR professor;
	SERIE serie;
	ESTOQUE estoque;
	
	switch(op){
		case 1:			
			fl = fopen("aluno.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno à ser editado: ");
					fflush(stdin);
					gets(aluno.CPF);
					pos = busca_posicao( fl, 0, aluno.CPF, 1);
					if(pos==-1)
					{						
						printf("\n\n(Aluno não cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&aluno,sizeof(ALUNO),1,fl);
						printf("\n\n__________________");
						printf("\nNome: %s",aluno.nome);
						printf("\nFone: %s",aluno.telefone);
						printf("\nE-mail: %s",aluno.email);
						printf("\nSexo: %c",aluno.sexo);
						printf("\nCPF: %s",aluno.CPF);
						printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
						printf("\n__________________");
						printf("\n\n1 - Nome \n2 - Fone \n3 - E-mail \n4 - Sexo \n5 - CPF \n6 - Aniversário \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo Nome: ");
								fflush(stdin);
								gets(aluno.nome);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							case 2:
								printf("\n\nNovo telefone: ");
								fflush(stdin);
								gets(aluno.telefone);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							case 3:
								printf("\n\nNovo E-mail: ");
								fflush(stdin);
								gets(aluno.email);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							case 4:
								printf("\n\nNovo Sexo (F/M): ");
								fflush(stdin);
								scanf("%c",&aluno.sexo);
								aluno.sexo = toupper(aluno.sexo);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							case 5:
								printf("\n\nNovo CPF: ");
								fflush(stdin);
								gets(aluno.CPF);
								pos2 = busca_posicao( fl, 0, aluno.CPF, 1);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&aluno,sizeof(ALUNO),1,fl);	
								} else{
									printf("\n\nId: %s (Aluno ja cadastrado!)",aluno.CPF);
									op = 0;
								}																
								break;
							case 6:
								printf("\n\nNovo Aniversário dd mm aaaa: ");
								fflush(stdin);
								scanf("%d", &aluno.niver.dia, &aluno.niver.mes, &aluno.niver.ano);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							default:
								printf("\n\nOpção inválida!!");
								break;
						}						
						if(op >= 1 && op <= 6){
							printf("\n\nRegistro Atualizado!");
						}
					}
					printf("\n\nDeseja atualizar outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 2:			
			fl = fopen("disciplina.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o código da disciplina à ser editada: ");
					scanf("%d", &disciplina.cod);
					pos = busca_posicao( fl, disciplina.cod, "", 2);
					if(pos==-1)
					{						
						printf("\n\n(Disciplina não cadastrada!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&disciplina,sizeof(DISCIPLINA),1,fl);
						printf("\n\n__________________");
						printf("\n\nCód: %d",disciplina.cod);
						printf("\nNome: %s",disciplina.nome);
						printf("\n__________________");
						printf("\n\n1 - Cód \n2 - Nome \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo Código: ");
								scanf("%d", &disciplina.cod);
								fseek(fl,pos,0);
								fwrite(&disciplina,sizeof(DISCIPLINA),1,fl);
								pos2 = busca_posicao( fl, disciplina.cod, "", 1);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&disciplina,sizeof(DISCIPLINA),1,fl);	
								} else{
									printf("\n\nId: %d (Disciplina ja cadastrada!)",disciplina.cod);
									op = 0;
								}
								break;
							case 2:
								printf("\n\nNovo Nome: ");
								fflush(stdin);
								gets(aluno.nome);
								fseek(fl,pos,0);
								fwrite(&disciplina,sizeof(DISCIPLINA),1,fl);
								break;
							default:
								printf("\n\nOpção inválida!!");
								break;
						}						
						if(op >= 1 && op <= 6){
							printf("\n\nRegistro Atualizado!");
						}
					}
					printf("\n\nDeseja atualizar outra disciplina? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 3:			
			fl = fopen("professor.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do professor à ser editado: ");
					fflush(stdin);
					gets(professor.CPF);
					pos = busca_posicao( fl, 0, professor.CPF, 3);
					if(pos==-1)
					{						
						printf("\n\n(Professor não cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&professor,sizeof(PROFESSOR),1,fl);
						printf("\n\n__________________");
						printf("\nNome: %s",professor.nome);
						printf("\nFone: %s",professor.telefone);
						printf("\nE-mail: %s",professor.email);
						printf("\nSexo: %c",professor.sexo);
						printf("\nCPF: %s",professor.CPF);
						printf("\nAniversario: %d/%d/%d", professor.niver.dia, professor.niver.mes, professor.niver.ano);																		
						printf("\n__________________");
						printf("\n\n1 - Nome \n2 - Fone \n3 - E-mail \n4 - Sexo \n5 - CPF \n6 - Aniversário \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo Nome: ");
								fflush(stdin);
								gets(professor.nome);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							case 2:
								printf("\n\nNovo telefone: ");
								fflush(stdin);
								gets(professor.telefone);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							case 3:
								printf("\n\nNovo E-mail: ");
								fflush(stdin);
								gets(professor.email);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							case 4:
								printf("\n\nNovo Sexo (F/M): ");
								fflush(stdin);
								scanf("%c",&professor.sexo);
								professor.sexo = toupper(professor.sexo);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							case 5:
								printf("\n\nNovo CPF: ");
								fflush(stdin);
								gets(professor.CPF);
								pos2 = busca_posicao( fl, 0, professor.CPF, 1);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&professor,sizeof(PROFESSOR),1,fl);	
								} else{
									printf("\n\nId: %s (Professor ja cadastrado!)",professor.CPF);
									op = 0;
								}																
								break;
							case 6:
								printf("\n\nNovo Aniversário dd mm aaaa: ");
								fflush(stdin);
								scanf("%d", &professor.niver.dia, &professor.niver.mes, &professor.niver.ano);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							default:
								printf("\n\nOpção inválida!!");
								break;
						}						
						if(op >= 1 && op <= 6){
							printf("\n\nRegistro Atualizado!");
						}
					}
					printf("\n\nDeseja atualizar outro professor? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 4:
			fl = fopen("serie.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o ano da série à ser editada: ");
					scanf("%d", &serie.ano);	
					
					printf("\n\nInforme o nome da sala à ser editada: ");
					fflush(stdin);
					gets(serie.sala);
					pos = busca_posicao(fl, serie.ano, serie.sala, 4);
					if(pos==-1)
					{						
						printf("\n\n(Série não cadastrada!)");
					} else {
						fseek(fl,pos,0);
						fread(&serie,sizeof(SERIE),1,fl);
						printf("\n\n__________________");
						printf("\n\nAno: %d",serie.ano);
						printf("\nSala: %s",serie.sala);
						printf("\nAno letivo: %d",serie.ano_letivo.ano);
						printf("\n__________________");
						printf("\n\n1 - Ano \n2 - Sala \n3 - Ano Letivo \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo Ano: ");
								scanf("%d", &serie.ano);
								pos2 = busca_posicao( fl, serie.ano, serie.sala, 4);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&serie,sizeof(SERIE),1,fl);	
								} else {
									printf("\n\nId: %d-%s (Série ja cadastrado!)",serie.ano,serie.sala);
									op = 0;
								}
								break;
							case 2:
								printf("\n\nNova Sala: ");
								fflush(stdin);
								gets(serie.sala);
								pos2 = busca_posicao( fl, serie.ano, serie.sala, 4);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&serie,sizeof(SERIE),1,fl);	
								} else{
									printf("\n\nId: %d-%s (Série ja cadastrado!)",serie.ano,serie.sala);
									op = 0;
								}
								break;
							case 3:
								printf("\n\nNovo Ano Letivo: ");
								scanf("%d", &serie.ano_letivo);
								fseek(fl,pos,0);
								fwrite(&serie,sizeof(SERIE),1,fl);		
								break;
						}						
						if(op >= 1 && op <= 3){
							printf("\n\nRegistro Atualizado!");
						}
					}
					printf("\n\nDeseja atualizar outra série? (s)(n)");
				}while(toupper(getche())=='S');		
			}
			fclose(fl);
			break;
		case 5:
			fl = fopen("estoque.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {
				do{
					printf("\n\ninforme o código do material á ser editado: ");
					scanf("%d", &estoque.cod);
					pos = busca_posicao(fl, estoque.cod, "",5);
					if(pos == -1){
						printf("\n\n(Material não cadastrado!)");
					} else {
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\n__________________");
						printf("\n\nCód: %d", estoque.cod);
						printf("\nQuantidade: %d", estoque.estoque);
						printf("\nDescrição: %s", estoque.descricao);
						printf("\nUltima Compra: %d/%d/%d", estoque.ultima_compra.dia, estoque.ultima_compra.mes, estoque.ultima_compra.ano);
						printf("\n__________________");
						printf("\n\n1 - Cód \n2 - Quantidade \n3 - Descrição \n4 - Ultima Compra \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo Cód: ");
								scanf("%d", &estoque.cod);
								pos2 = busca_posicao( fl, estoque.cod, "", 5);
								if(pos2==-1) {
									fseek(fl,pos,0);
									fwrite(&estoque,sizeof(ESTOQUE),1,fl);	
								} else {
									printf("\n\nId: %d (Material ja cadastrado!)", estoque.cod);
									op = 0;
								}
								break;
							case 2:
								printf("\n\nNova Quantidade: ");
								scanf("%d", &estoque.estoque);
								fseek(fl,pos,0);
								fwrite(&estoque,sizeof(ESTOQUE),1,fl);		
								break;
							case 3:
								printf("\n\nNova Descrição: ");
								fflush(stdin);
								gets(estoque.descricao);
								fseek(fl,pos,0);
								fwrite(&estoque,sizeof(ESTOQUE),1,fl);		
								break;
							case 4:
								printf("\n\nNova Ultima Compra dd mm aaaa: ");
								scanf("%d %d %d", &estoque.ultima_compra.dia, &estoque.ultima_compra.mes, &estoque.ultima_compra.ano);
								fseek(fl,pos,0);
								fwrite(&estoque,sizeof(ESTOQUE),1,fl);		
								break;
						}						
						if(op >= 1 && op <= 4){
							printf("\n\nRegistro Atualizado!");
						}
					}
					printf("\n\nDeseja atualizar outro material? (s)(n)");
				} while(toupper(getch()) == 'S');
			}
			fclose(fl);
			break;
	}
}

// 1° paramêtro - op: opção que será usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque;
void excluir(int op){
	FILE *fl;
	int pos,
		cod,
		ano;
	char cpf[20],
		 sala[50];
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	PROFESSOR professor;
	SERIE serie;
	ESTOQUE estoque;
	
	switch(op){
		case 1:
			fl = fopen("aluno.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno à ser excluido: ");
					fflush(stdin);
					gets(cpf);
					pos = busca_posicao(fl,0,cpf,1);
					if(pos==-1)
					{						
						printf("\n\n(Aluno não cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&aluno,sizeof(ALUNO),1,fl);
						printf("\n\n__________________");
						printf("\nNome: %s",aluno.nome);
						printf("\nFone: %s",aluno.telefone);
						printf("\nE-mail: %s",aluno.email);
						printf("\nSexo: %c",aluno.sexo);
						printf("\nCPF: %s",aluno.CPF);
						printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
						printf("\n__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&aluno,sizeof(ALUNO),1,fl);
							while(!feof(fl)){
								if(strcmp(aluno.CPF, cpf) != 0){
									fwrite(&aluno,sizeof(ALUNO),1,temp);						
								}
								fread(&aluno,sizeof(ALUNO),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("aluno.bin");
							rename("auxiliar.bin","aluno.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("\n\nDeseja excluir outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 2:
			fl = fopen("disciplina.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o código da disciplina à ser excluida: ");					
					scanf("%d", &cod);
					pos = busca_posicao(fl, disciplina.cod, "", 2);
					if(pos==-1)
					{						
						printf("\n\n(Disciplina não cadastrada!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&disciplina,sizeof(DISCIPLINA),1,fl);
						printf("\n\n__________________");
						printf("\n\nCód: %d",disciplina.cod);
						printf("\nNome: %s",disciplina.nome);
						printf("\n__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&disciplina,sizeof(DISCIPLINA),1,fl);
							while(!feof(fl)){
								if(disciplina.cod != cod ){
									fwrite(&disciplina,sizeof(DISCIPLINA),1,temp);						
								}
								fread(&disciplina,sizeof(DISCIPLINA),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("disciplina.bin");
							rename("auxiliar.bin","disciplina.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("\n\nDeseja excluir outra disciplina? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 3:
			fl = fopen("professor.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {	
				do{				
					printf("\n\nInforme o CPF do professor à ser excluido: ");
					fflush(stdin);
					gets(cpf);
					pos = busca_posicao(fl,0,cpf,3);
					if(pos==-1)
					{						
						printf("\n\n(Professor não cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&professor,sizeof(PROFESSOR),1,fl);
						printf("\n\n__________________");
						printf("\nNome: %s",professor.nome);
						printf("\nFone: %s",professor.telefone);
						printf("\nE-mail: %s",professor.email);
						printf("\nSexo: %c",professor.sexo);
						printf("\nCPF: %s",professor.CPF);
						printf("\nAniversario: %d/%d/%d", professor.niver.dia, professor.niver.mes, professor.niver.ano);																		
						printf("\n__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&professor,sizeof(PROFESSOR),1,fl);
							while(!feof(fl)){
								if(strcmp(professor.CPF, cpf) != 0){
									fwrite(&professor,sizeof(PROFESSOR),1,temp);						
								}
								fread(&professor,sizeof(PROFESSOR),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("professor.bin");
							rename("auxiliar.bin","professor.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("\n\nDeseja excluir outro professor? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
		case 4:
			fl = fopen("serie.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o ano da série à ser excluida: ");
					scanf("%d", &ano);	
					
					printf("\n\nInforme o nome da sala à ser excluida: ");
					fflush(stdin);
					gets(sala);
					pos = busca_posicao(fl, serie.ano, serie.sala, 4);
					if(pos==-1)
					{						
						printf("\n\n(Série não cadastrada!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&serie,sizeof(SERIE),1,fl);
						printf("\n\n__________________");
						printf("\n\nAno: %d",serie.ano);
						printf("\nSala: %s",serie.sala);
						printf("\nAno letivo: %d",serie.ano_letivo.ano);
						printf("\n__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&serie,sizeof(SERIE),1,fl);
							while(!feof(fl)){
								if(serie.ano != ano && strcmp(serie.sala, sala) != 0){
									fwrite(&serie,sizeof(SERIE),1,temp);						
								}
								fread(&serie,sizeof(SERIE),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("serie.bin");
							rename("auxiliar.bin","serie.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("\n\nDeseja excluir outra Série? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;		
		case 5:
			fl = fopen("estoque.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o código do material à ser excluido: ");
					scanf("%d", &cod);	
					
					pos = busca_posicao(fl, cod, "", 5);
					if(pos==-1)
					{						
						printf("\n\n(Material não cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\n__________________");
						printf("\n\nCód: %d", estoque.cod);
						printf("\nQuantidade: %d", estoque.estoque);
						printf("\nDescrição: %s", estoque.descricao);
						printf("\nUltima Compra: %d/%d/%d", estoque.ultima_compra.dia, estoque.ultima_compra.mes, estoque.ultima_compra.ano);
						printf("\n__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&estoque,sizeof(ESTOQUE),1,fl);
							while(!feof(fl)){
								if(estoque.cod != cod){
									fwrite(&estoque,sizeof(ESTOQUE),1,temp);						
								}
								fread(&serie,sizeof(ESTOQUE),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("estoque.bin");
							rename("auxiliar.bin","estoque.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("\n\nDeseja excluir outro Material? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

// 1° paramêtro - op: opção que será usada para mostrar, ;
void mostrar(int op){
	FILE *fl;
	int pos,
		i;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	PROFESSOR professor;
	SERIE serie;
	ESTOQUE estoque;
	
	switch(op){
		case 1:
			fl = fopen("aluno.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\n__________________");
				while(fread(&aluno,sizeof(ALUNO),1,fl)==1)
				{					
					printf("\n\nNome: %s",aluno.nome);
					printf("\nFone: %s",aluno.telefone);
					printf("\nE-mail: %s",aluno.email);
					printf("\nSexo: %c",aluno.sexo);
					printf("\nCPF: %s",aluno.CPF);
					printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
					printf("\n__________________");
					printf("\n\n");
				}				
			}	
			fclose(fl);
			system("pause");
			break;
		case 4:
			fl = fopen("disciplina.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\n__________________");
				while(fread(&disciplina,sizeof(DISCIPLINA),1,fl)==1)
				{										
					printf("\n\nCód: %d",disciplina.cod);
					printf("\nNome: %s",disciplina.nome);
					printf("\n__________________");
					printf("\n\n");
				}
				
			}	
			fclose(fl);
			system("pause");
			break;
		case 5:
			fl = fopen("professor.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\nInforme o CPF do professor: ");
				fflush(stdin);
				gets(professor.CPF);
				
				pos = busca_posicao(pos,0,professor.CPF,3);
				if(pos == -1){
					printf("\n\n()Professor não cadastrado!)");
				} else{	
					fseek(fl,pos,0);
					fread(&professor,sizeof(PROFESSOR),1,fl);
					printf("\n\n__________________");
					printf("\n\nNome: %s",professor.nome);
					printf("\nCPF: %s",professor.CPF);
					printf("\n__________________");
					printf("\n\n");
					for(i = 0; i < professor.cont_diciplina;i++){
						printf("\n\nCód: %d", professor.disc[i].cod);
						printf("\nNome: %s", professor.disc[i].nome);
						printf("\n__________________");
						printf("\n\n");
					}
				}
			}	
			fclose(fl);
			system("pause");
			break;
		case 6:
			fl = fopen("professor.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\n__________________");
				while(fread(&professor,sizeof(PROFESSOR),1,fl)==1)
				{					
					printf("\n\nNome: %s",professor.nome);
					printf("\nFone: %s",professor.telefone);
					printf("\nE-mail: %s",professor.email);
					printf("\nSexo: %c",professor.sexo);
					printf("\nCPF: %s",professor.CPF);
					printf("\nAniversario: %d/%d/%d", professor.niver.dia, professor.niver.mes, professor.niver.ano);																		
					printf("\n__________________");
					printf("\n\n");
				}				
			}	
			fclose(fl);
			system("pause");
			break;
		case 9:
			fl = fopen("serie.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\n__________________");
				while(fread(&serie,sizeof(SERIE),1,fl)==1)
				{										
					printf("\n\nAno: %d",serie.ano);
					printf("\nSala: %s",serie.sala);
					printf("\nAno letivo: %d",serie.ano_letivo.ano);
					printf("\n__________________");
					printf("\n\n");
				}				
			}	
			fclose(fl);
			system("pause");
			break;
		case 10:
			fl = fopen("estoque.bin","rb");
			if (fl==NULL) {
				printf("Erro no arquivo!");
			} else {
				printf("\n\n__________________");
				while(fread(&estoque,sizeof(ESTOQUE),1,fl)==1)
				{										
					printf("\n\nCód: %d", estoque.cod);
					printf("\nQuantidade: %d", estoque.estoque);
					printf("\nDescrição: %s", estoque.descricao);
					printf("\nUltima Compra: %d/%d/%d", estoque.ultima_compra.dia, estoque.ultima_compra.mes, estoque.ultima_compra.ano);
					printf("\n__________________");
					printf("\n\n");
				}				
			}	
			fclose(fl);
			system("pause");
			break;
	}
}

void troca(ALUNO *a,ALUNO *b) {
	ALUNO t;
	t = *a;
	*a = *b;
	*b = t;
}

int particao(ALUNO arr[], int inicio, int fim){
	// Escolhe o pivô
    ALUNO pivo = arr[fim];
    
    // indica o indice do menor elemento
    // a posição correta do pivô até agora
    int j,
		i = inicio - 1;

    // Percorre arr[inicio..fim] e move todos os menores
    // elementos para o lado esquerdo. Elementos ds inicio para
    // i são menores após cada interação
    for (j = inicio; j <= fim - 1; j++) {
        if (strcmp(arr[j].nome, pivo.nome) <= 0) {
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    
    // Move o pivô para depois dos menores elementos e
    // retprna a sua posição
    troca(&arr[i + 1], &arr[fim]);  
    return i + 1;
}

int mediano_de_tres(ALUNO arr[], int inicio, int fim) {
    int meio = inicio + (fim - inicio) / 2;
    if (strcmp(arr[inicio].nome, arr[meio].nome) < 0) troca(&arr[inicio], &arr[meio]);
    if (strcmp(arr[inicio].nome, arr[fim].nome) < 0) troca(&arr[inicio], &arr[fim]);
    if (strcmp(arr[meio].nome, arr[fim].nome) < 0) troca(&arr[meio], &arr[fim]);
    return meio;  // Retorna o índice do mediano
}

void quickSort(ALUNO arr[], int inicio, int fim){	
	if (inicio < fim) {
        int pivotIdx = mediano_de_tres(arr, inicio, fim);  // Pivô mediano de três
        troca(&arr[pivotIdx], &arr[fim]);  // Coloca o pivô na última posição
        int pi = particao(arr, inicio, fim);
        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
}

void ordenar_aluno(){
	FILE *fl;		
	int i,
		qnt;
	fl = fopen("aluno.bin", "rb+");
	if(fl == NULL){
		printf("\n\nErro no arquivo");
	} else {		
		fseek(fl,0,2);
		qnt = ftell(fl)/sizeof(ALUNO);
		ALUNO ctt[qnt];
		rewind(fl);
		for (i = 0; i < qnt; i++) {
	        fread(&ctt[i], sizeof(ALUNO),1,fl);
	    }	
	    quickSort(ctt,0,qnt-1);
		rewind(fl);			
		for (i = 0; i < qnt; i++) {	        
	        fwrite(&ctt[i], sizeof(ALUNO),1,fl);
	    }	
	    system("cls");
		printf("\n\nArquivo ordenado com sucesso!\n");
		system("pause");
	}
	fclose(fl);
}

void compra_material(){
	FILE *fl;
		 
	int pos,
		qnt;
	ESTOQUE estoque;
	
	fl = fopen("estoque.bin","rb+");
	if(fl == NULL) {
		printf("\n\nErro no arquivo!");
	} else {
		do{
			printf("\n\nInforme o Código do material à dar entrada: ");
			scanf("%d", &estoque.cod);
			
			pos = busca_posicao(fl, estoque.cod, "",5);
			if(pos == -1){
				printf("\n\n(Material não cadastrado!)");
			} else {	
				fseek(fl,pos,0);
				fread(&estoque,sizeof(ESTOQUE),1,fl);
				printf("\n\nInforme a quantidade à adicionar: ");
				scanf("%d", &qnt);
				
				printf("\n\nInforme a data da compra do material dd mm aaaa: ");
				scanf("%d %d %d", &estoque.ultima_compra.dia, &estoque.ultima_compra.mes, &estoque.ultima_compra.ano);
				
				
				estoque.estoque = estoque.estoque + qnt;
				
				fseek(fl,pos,0);	
				fwrite(&estoque,sizeof(ESTOQUE),1,fl);
			}
			printf("\n\nDeseja dar entrada em outro material? (s)(n)");
		} while(toupper(getch()) == 'S');
	}
	fclose(fl);
}

void baixa_material(){
	FILE *fl_esto,
		 *fl_reti,
		 *fl_A,
		 *fl_P;
		 
	int pos,
		pos_A,
		pos_P;
	ESTOQUE estoque;
	HISTORICO_RETIRADA e_retirada; 
	
	fl_esto = fopen("estoque.bin","rb+");
	fl_A = fopen("aluno.bin","rb+");
	fl_P = fopen("professor.bin","rb+");
	fl_reti = fopen("estoque_retirada.bin","ab+");
	if(fl_esto == NULL || fl_A == NULL || fl_P == NULL || fl_reti == NULL) {
		printf("\n\nErro no arquivo!");
	} else {
		do{
			printf("\n\nInforme o Código do material à dar baixa: ");
			scanf("%d", &e_retirada.cod_material);
			
			pos = busca_posicao(fl_esto, e_retirada.cod_material, "",5);
			if(pos == -1){
				printf("\n\n(Material não cadastrado!)");
			} else {
				printf("\n\nInforme o CPF da pessoa à retirar o material: ");
				fflush(stdin);
				gets(e_retirada.cod_pessoa);
				
				pos_A = busca_posicao(fl_A, 0, e_retirada.cod_pessoa,1);
				pos_P = busca_posicao(fl_P, 0, e_retirada.cod_pessoa,3);
				
				if(pos_A == -1 && pos_P == -1){
					printf("\n\n(Aluno ou Professor não cadastrado!)");
				} else {
					printf("\n\nInforme a quantidade à retirar: ");
					scanf("%d", &e_retirada.quantidade);
					
					printf("\n\nInforme o motivo da retirada do material: ");
					fflush(stdin);
					gets(e_retirada.motivo);
					
					printf("\n\nInforme a data da retirada do material dd mm aaaa: ");
					scanf("%d %d %d", &e_retirada.dt_retirada.dia, &e_retirada.dt_retirada.mes, &e_retirada.dt_retirada.ano);
					
					fseek(fl_esto,pos,0);
					fread(&estoque,sizeof(ESTOQUE),1,fl_esto);
					
					fseek(fl_esto,pos,0);
					estoque.estoque = estoque.estoque - e_retirada.quantidade;
					
					if(estoque.estoque >= 0){
						fwrite(&estoque,sizeof(ESTOQUE),1,fl_esto);	
						fwrite(&e_retirada,sizeof(HISTORICO_RETIRADA),1,fl_reti);		
					} else {
						printf("\n\nNão há estoque o suficiente para fazer a retirada");
					}				
				}
			}
			printf("\n\nDeseja retirar outro material? (s)(n)");
		} while(toupper(getch()) == 'S');
	}
	fclose(fl_esto);
	fclose(fl_A);
	fclose(fl_P);
	fclose(fl_reti);
}

void atribuir_disciplina(){
	FILE *fl_Disc,
		 *fl_Prof;
	int pos_Disc,
		pos_Prof,
		cont,
		i,
		achou=0,
		menu;
	
	DISCIPLINA disciplina;
	PROFESSOR professor;
	
	fl_Disc = fopen("disciplina.bin","rb+");
	fl_Prof = fopen("professor.bin","rb+");
	if(fl_Prof == NULL){
		printf("\n\nErro no arquivo!");
	} else {
		printf("\n\nInforme o CPF do professor: ");
		fflush(stdin);
		gets(professor.CPF);
		
		pos_Prof = busca_posicao(fl_Prof,0,professor.CPF,3);
		if(pos_Prof == -1){
			printf("\n\n(Professor não cadastrado!)");
		} else{			
			do{
				fseek(fl_Prof,pos_Prof,0);
				fread(&professor,sizeof(PROFESSOR),1,fl_Prof);
				cont = professor.cont_diciplina;
				if(cont < MAX_DISCIPLINA) {
					
					printf("\n\nInforme o código da disciplina: ");
					scanf("%d", &disciplina.cod);
					
					pos_Disc = busca_posicao(fl_Disc, disciplina.cod, "", 2);
					if(pos_Disc==-1){
						printf("\n\n(Disciplina não cadastrada!)");
					}else{
						do{
							fseek(fl_Disc,pos_Disc,0);
							fread(&disciplina,sizeof(DISCIPLINA),1,fl_Disc);
							for(i = 0; i < cont;i++){
								if(professor.disc[i].cod == disciplina.cod){
									achou = 1;
								}
							}
							
							if(achou == 1){
								printf("\n\n(Disciplina já atribuida!)");
							}else{
								professor.disc[cont].cod = disciplina.cod;
								strcpy(professor.disc[cont].nome, disciplina.nome);
								
								professor.cont_diciplina++;
								fseek(fl_Prof,pos_Prof,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl_Prof);	
							}
							printf("\n\nDeseja atribuir outra disciplina? (s)(n)");
						} while(toupper(getch()) == 'S');	
					}
					printf("\n\nDeseja atribuir a outro professor? (s)(n)");
				} else {
					printf("\n\nNão é possível atribuir outra disciplina, pois o limite máximo já foi atingido.");
					system("cls");
					printf("\n\nDeseja continuar? (s)(n)");
					
				}
			} while(toupper(getch()) == 'S');	
		}
	}
	fclose(fl_Disc);
	fclose(fl_Prof);
}

void retirar_disciplina(){
	FILE *fl_Disc,
		 *fl_Prof;
	int pos_Disc,
		pos_Prof,
		cont,
		i,
		j = 0,
		menu;
	
	DISCIPLINA disciplina;
	PROFESSOR professor;
	
	fl_Disc = fopen("disciplina.bin","rb+");
	fl_Prof = fopen("professor.bin","rb+");
	if(fl_Prof == NULL){
		printf("\n\nErro no arquivo!");
	} else {
		printf("\n\nInforme o CPF do professor: ");
		fflush(stdin);
		gets(professor.CPF);
		
		pos_Prof = busca_posicao(fl_Prof,0,professor.CPF,3);
		if(pos_Prof == -1){
			printf("\n\n(Professor não cadastrado!)");
		} else{			
			do{
				fseek(fl_Prof,pos_Prof,0);
				fread(&professor,sizeof(PROFESSOR),1,fl_Prof);
				cont = professor.cont_diciplina;
				if(cont == 0) {
					
					printf("\n\nInforme o código da disciplina: ");
					scanf("%d", &disciplina.cod);
					
					pos_Disc = busca_posicao(fl_Disc, disciplina.cod, "", 2);
					if(pos_Disc==-1){
						printf("\n\n(Disciplina não cadastrada!)");
					}else{
						do{
							fseek(fl_Disc,pos_Disc,0);
							fread(&disciplina,sizeof(DISCIPLINA),1,fl_Disc);
							for(i = 0; i < cont;i++){
								if(professor.disc[i].cod != disciplina.cod){
									professor.disc[j].cod = professor.disc[i].cod;
									strcpy(professor.disc[j].nome, professor.disc[i].nome);
									j++;
								}
							}
							
							professor.cont_diciplina = j +1;
							fseek(fl_Prof,pos_Prof,0);
							fwrite(&professor,sizeof(PROFESSOR),1,fl_Prof);
							printf("\n\nDeseja retirar outra disciplina? (s)(n)");
						} while(toupper(getch()) == 'S');	
					}
					printf("\n\nDeseja retirar a outro professor? (s)(n)");
				} else {
					printf("\n\nNão é possível retirar uma disciplina, pois o não tem nenhuma atribuida.");
					system("cls");
					printf("\n\nDeseja continuar? (s)(n)");
					
				}
			} while(toupper(getch()) == 'S');	
		}
	}
	fclose(fl_Disc);
	fclose(fl_Prof);
}

void lancar_notas_frequencia(){	
	FILE *fl_Disc,
		 *fl_Aluno,
		 *fl_Hist;
	char cpf[20];
	int pos_Disc,
		pos_Aluno,
		pos_Hist,
		cont=0,
		i,
		achou=0,
		menu;
	
	DISCIPLINA disciplina;
	HISTORICO_ESCOLAR h_aluno;
	
	fl_Disc = fopen("disciplina.bin","rb+");
	fl_Aluno = fopen("aluno.bin","rb+");
	fl_Hist = fopen("historico_escolar.bin","rb+");
	
	int qnt = ftell(fl_Hist)/sizeof(HISTORICO_ESCOLAR);
	HISTORICO_ESCOLAR todo_hist[qnt];
	
	if(pos_Hist == NULL){
		printf("\n\nErro no arquivo!");
	} else {
		printf("\n\nInforme o CPF do aluno: ");
		fflush(stdin);
		gets(cpf);
		
		pos_Aluno = busca_posicao(fl_Aluno,0,cpf,1);
		if(pos_Aluno == -1){
			printf("\n\n(Aluno não cadastrado!)");
		} else{			
			do{
				while(fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist))
				{										
					if(strcmp(cpf, h_aluno.cpf_aluno)){
						todo_hist[cont].ano = h_aluno.ano;
						todo_hist[cont].bimestre = h_aluno.bimestre;
						strcpy(todo_hist[cont].cpf_aluno, h_aluno.cpf_aluno);
						todo_hist[cont].disc.cod = h_aluno.disc.cod;
						strcpy(todo_hist[cont].disc.nome, h_aluno.disc.nome);
						todo_hist[cont].faltas = h_aluno.faltas;
						todo_hist[cont].nota = h_aluno.nota;
						cont++;
					}
				}
				
				if(cont < MAX_DISCIPLINA * 4) {
					
					printf("\n\nInforme o código da disciplina: ");
					scanf("%d", &h_aluno.disc.cod);
					
					printf("\n\nInforme o bimestre: ");
					scanf("%d", h_aluno.bimestre);
					
					printf("\n\nInforme o ano da nota aaaa: ");
					scanf("%d", h_aluno.ano.ano);
								
					pos_Disc = busca_posicao(fl_Disc, h_aluno.disc.cod, "", 2);
					if(pos_Disc==-1){
						printf("\n\n(Disciplina não cadastrada!)");
					}else{
						do{
							for(i = 0; i < cont;i++){
								if(todo_hist[i].bimestre == h_aluno.bimestre &&
									todo_hist[i].disc.cod == h_aluno.disc.cod &&
									todo_hist[i].ano.ano == h_aluno.ano.ano){
									achou = 1;
								}
							}
							
							if(achou == 1){
								printf("\n\n(Disciplina já atribuida!)");
							}else{
								
								printf("\n\nInforme a quantidade de faltas: ");
								scanf("%d", h_aluno.faltas);
								
								printf("\n\nInforme a nota: ");
								scanf("%d", h_aluno.nota);
								
								h_aluno.disc.cod = disciplina.cod;
								strcpy(h_aluno.disc.nome, disciplina.nome);
								strcpy(h_aluno.cpf_aluno, cpf);
								
								
								fwrite(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);	
							}
							printf("\n\nDeseja lançar outra nota? (s)(n)");
						} while(toupper(getch()) == 'S');	
					}
					printf("\n\nDeseja lançar a outro aluno? (s)(n)");
				} else {
					printf("\n\nNão é possível lançar outra nota, pois o limite máximo já foi atingido.");
					system("cls");
					printf("\n\nDeseja continuar? (s)(n)");
					
				}
			} while(toupper(getch()) == 'S');	
		}
	}
	fclose(fl_Aluno);
	fclose(fl_Disc);
	fclose(fl_Hist);
}

void alterar_notas_frequencia(){	
	FILE *fl_Disc,
		 *fl_Aluno,
		 *fl_Hist;
		 
	int pos_Disc,
		pos_Aluno,
		pos_Hist,
		cont=0,
		op,
		i,
		achou=0,
		menu;
	
	DISCIPLINA disciplina;
	ALUNO aluno;	
	HISTORICO_ESCOLAR h_aluno;
	
	fl_Disc = fopen("disciplina.bin","rb+");
	fl_Aluno = fopen("aluno.bin","rb+");
	fl_Hist = fopen("historico_escolar.bin","rb+");	
	
	int qnt = ftell(fl_Hist)/sizeof(HISTORICO_ESCOLAR);
	HISTORICO_ESCOLAR todo_hist[qnt];
	
	if(pos_Hist == NULL){
		printf("\n\nErro no arquivo!");
	} else {
		printf("\n\nInforme o CPF do aluno: ");
		fflush(stdin);
		gets(aluno.CPF);
		
		pos_Aluno = busca_posicao(fl_Aluno,0,h_aluno.cpf_aluno,1);
		if(pos_Aluno == -1){
			printf("\n\n(Aluno não cadastrado!)");
		} else{			
			do{
				
				while(fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist))
				{
					if(strcmp(aluno.CPF, h_aluno.cpf_aluno)){
						printf("\n%d- %s, %d°bimestre, nota: %d, faltas: %d, ano:%d",
								cont+1, h_aluno.disc.nome, h_aluno.bimestre, h_aluno.nota,
								h_aluno.faltas, h_aluno.ano);
								
						todo_hist[cont].ano = h_aluno.ano;
						todo_hist[cont].bimestre = h_aluno.bimestre;
						strcpy(todo_hist[cont].cpf_aluno, h_aluno.cpf_aluno);
						todo_hist[cont].disc.cod = h_aluno.disc.cod;
						strcpy(todo_hist[cont].disc.nome, h_aluno.disc.nome);
						todo_hist[cont].faltas = h_aluno.faltas;
						todo_hist[cont].nota = h_aluno.nota;
						cont++;
					}
				}
				
				if(cont != 0) {					
					printf("\n\nInforme uma opção para ser alterada: ");
					scanf("%d", &op);
					
					if(op > 0 && op <= (cont)){
							op--;
							rewind(fl_Hist);
							while(strcmp(todo_hist[op].cpf_aluno, h_aluno.cpf_aluno) &&
									todo_hist[op].bimestre == h_aluno.bimestre &&
									todo_hist[op].disc.cod == h_aluno.disc.cod){
								fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
							}
							if(!feof(fl_Hist)){
								pos_Hist =(ftell(fl_Hist)-sizeof(HISTORICO_ESCOLAR));
							} else{
								pos_Hist = -1;
							}
					}
					if(pos_Hist==-1){
						printf("\n\n(Nota não cadastrada!)");
					}else{
						do{
							fseek(fl_Hist,pos_Hist,0);
							fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
							printf("\n\n__________________");
							printf("\n\nDisciplina: %s", h_aluno.disc.nome);
							printf("\nBimestre: %d", h_aluno.bimestre);
							printf("\nano: %s", h_aluno.ano);
							printf("\nNota: %d", h_aluno.nota);
							printf("\nFaltas: %d", h_aluno.faltas);
							printf("\n__________________");
							printf("\n\n1 - Nota \n2 - Faltas \nDeseja alterar: ");
							scanf("%d",&op);
							
							switch(op){								
								case 1:
									printf("\n\nNova Nota: ");
									scanf("%d", &h_aluno.nota);
									fseek(fl_Hist,pos_Hist,0);
									fwrite(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);		
									break;
								case 2:
									printf("\n\nNova quantidade de faltas: ");
									scanf("%d", &h_aluno.faltas);
									fseek(fl_Hist,pos_Hist,0);
									fwrite(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);		
									break;
							}						
							if(op >= 1 && op <= 2){
								printf("\n\nRegistro Atualizado!");
							}
							printf("\n\nDeseja excluir outra nota? (s)(n)");
						} while(toupper(getch()) == 'S');	
					}
					printf("\n\nDeseja lançar a outro aluno? (s)(n)");
				} else {
					printf("\n\nNão é possível excluir uma nota, pois o não tem nenhuma atribuida.");
					system("cls");
					printf("\n\nDeseja continuar? (s)(n)");
					
				}
			} while(toupper(getch()) == 'S');	
		}
	}
	fclose(fl_Aluno);
	fclose(fl_Disc);
	fclose(fl_Hist);
}

void excluir_notas_frequencia(){	
	FILE *fl_Disc,
		 *fl_Aluno,
		 *fl_Hist;
		 
	int pos_Disc,
		pos_Aluno,
		pos_Hist,
		cont=0,
		op,
		i,
		achou=0,
		menu;
	
	DISCIPLINA disciplina;
	ALUNO aluno;	
	HISTORICO_ESCOLAR h_aluno;
	
	fl_Disc = fopen("disciplina.bin","rb+");
	fl_Aluno = fopen("aluno.bin","rb+");
	fl_Hist = fopen("historico_escolar.bin","rb+");	
	
	int qnt = ftell(fl_Hist)/sizeof(HISTORICO_ESCOLAR);
	HISTORICO_ESCOLAR todo_hist[qnt];
	
	if(pos_Hist == NULL){
		printf("\n\nErro no arquivo!");
	} else {
		printf("\n\nInforme o CPF do aluno: ");
		fflush(stdin);
		gets(aluno.CPF);
		
		pos_Aluno = busca_posicao(fl_Aluno,0,h_aluno.cpf_aluno,1);
		if(pos_Aluno == -1){
			printf("\n\n(Aluno não cadastrado!)");
		} else{			
			do{
				
				while(fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist))
				{
					if(strcmp(aluno.CPF, h_aluno.cpf_aluno)){
						printf("\n%d- %s, %d°bimestre, nota: %d, faltas: %d, ano:%d",
								cont+1, h_aluno.disc.nome, h_aluno.bimestre, h_aluno.nota,
								h_aluno.faltas, h_aluno.ano);
								
						todo_hist[cont].ano = h_aluno.ano;
						todo_hist[cont].bimestre = h_aluno.bimestre;
						strcpy(todo_hist[cont].cpf_aluno, h_aluno.cpf_aluno);
						todo_hist[cont].disc.cod = h_aluno.disc.cod;
						strcpy(todo_hist[cont].disc.nome, h_aluno.disc.nome);
						todo_hist[cont].faltas = h_aluno.faltas;
						todo_hist[cont].nota = h_aluno.nota;
						cont++;
					}
				}
				
				if(cont != 0) {					
					printf("\n\nInforme uma opção para ser excluida: ");
					scanf("%d", &op);
					
					if(op > 0 && op <= (cont)){
							op--;
							rewind(fl_Hist);
							while(strcmp(todo_hist[op].cpf_aluno, h_aluno.cpf_aluno) &&
									todo_hist[op].bimestre == h_aluno.bimestre &&
									todo_hist[op].disc.cod == h_aluno.disc.cod){
								fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
							}
							if(!feof(fl_Hist)){
								pos_Hist =(ftell(fl_Hist)-sizeof(HISTORICO_ESCOLAR));
							} else{
								pos_Hist = -1;
							}
					}
					if(pos_Hist==-1){
						printf("\n\n(Nota não cadastrada!)");
					}else{
						do{
							fseek(fl_Hist,pos_Hist,0);
							fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
							printf("\n\n__________________");
							printf("\n\nDisciplina: %s", h_aluno.disc.nome);
							printf("\nBimestre: %d", h_aluno.bimestre);
							printf("\nano: %s", h_aluno.ano);
							printf("\nNota: %d", h_aluno.nota);
							printf("\nFaltas: %d", h_aluno.faltas);
							printf("\n__________________");
							printf("\n\nDeseja excluir? (s/n)");
							if(toupper(getch()) == 'S'){
								FILE *temp;
								temp = fopen("auxiliar.bin","wb");
								rewind(fl_Hist);
								fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
								while(!feof(fl_Hist)){
									if(strcmp(todo_hist[op].cpf_aluno, h_aluno.cpf_aluno) &&
									   todo_hist[op].bimestre == h_aluno.bimestre &&
									   todo_hist[op].disc.cod == h_aluno.disc.cod){
										fwrite(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,temp);						
									}
									fread(&h_aluno,sizeof(HISTORICO_ESCOLAR),1,fl_Hist);
								}
								fclose(fl_Hist);
								fclose(temp);
								remove("historico_escolar.bin");
								rename("auxiliar.bin","historico_escolar.bin");
								system("cls");
								printf("\n\nArquivo excluido com sucesso!\n");
								system("pause");
							}		
							printf("\n\nDeseja excluir outra nota? (s)(n)");
						} while(toupper(getch()) == 'S');	
					}
					printf("\n\nDeseja lançar a outro aluno? (s)(n)");
				} else {
					printf("\n\nNão é possível excluir uma nota, pois o não tem nenhuma atribuida.");
					system("cls");
					printf("\n\nDeseja continuar? (s)(n)");
					
				}
			} while(toupper(getch()) == 'S');	
		}
	}
	fclose(fl_Aluno);
	fclose(fl_Disc);
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Aluno;
void gerenciar_alunos(int menu) { 
	switch(menu){ // Gerenciamento de Alunos;
		case 1: // 1- Cadastrar Aluno;
			inserir(1);
			break;
		case 2: // 2- Editar Aluno;
			atualizar(1);
			break;
		case 3: // 3- Excluir Aluno;
			excluir(1);
			break;
		case 4: // 4- Lançar notas e Frequência;
			lancar_notas_frequencia();
			break;
		case 5: // 5- Editar notas e Frequência;
			alterar_notas_frequencia();
			break;
		case 6: // 6- Excluir notas e Frequência;
			excluir_notas_frequencia();
			break;
		case 7: // 7- Ordenar Alunos;
			ordenar_aluno();
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Disciplinas;
void gerenciar_disciplinas(int menu) { 
	switch(menu){ // Gerenciamento de Disciplinas;
		case 1: // 1- Cadastrar Disciplina;
			inserir(2);
			break;
		case 2: // 2- Editar Disciplina;
			atualizar(2);
			break;
		case 3: // 3- Excluir Disciplina;
			excluir(2);
			break;
		case 4: // 4- Atribuir Disciplina;
			atribuir_disciplina();
			break;
		case 5: // 5- Retirar Disciplina;
			retirar_disciplina();
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Professores;
void gerenciar_professores(int menu) { 
	switch(menu){ // Gerenciamento de Professores;
		case 1: // 1- Cadastrar Professor;
			inserir(3);
			break;
		case 2: // 2- Editar Professor;
			atualizar(3);
			break;
		case 3: // 3- Excluir Professor;
			excluir(3);
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Séries;
void gerenciar_serie(int menu) { 
	switch(menu){ // Gerenciamento de Séries;
		case 1: // 1- Cadastrar Série;
			inserir(4);
			break;
		case 2: // 2- Editar Série;
			atualizar(4);
			break;
		case 3: // 3- Excluir Série;
			excluir(4);
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento do Estoque;
void gerenciar_estoque(int menu) { 
	switch(menu){ // Gerenciamento do Estoque;
		case 1: // 1- Cadastrar Material;
			inserir(5);
			break;
		case 2: // 2- Editar Material;
			atualizar(5);
			break;
		case 3: // 3- Excluir Material;
			excluir(5);
			break;
		case 4: // 4- Compra de Materiais;
			compra_material();
			break;
		case 5: // 5- Efetuar Baixa de Materiais;
			baixa_material();
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	  	
}

// 1° paramêtro - menu: seleciona a opção do menu de gerenciamento Relatorios Gerais;
void gerenciar_relatorios(int menu) { 
	switch(menu){
		case 1: // 1- Listar Alunos;
			mostrar(1);
			break;
		case 4: // 4- Listar Disciplinas;
			mostrar(4);
			break;
		case 5: // 5- Listar Disciplinas do Professor;
			mostrar(5);
			break;
		case 6: // 6- Listar Professores;
			mostrar(6);
			break;	
		case 9: // 9- Listar Séries;
			mostrar(9);
			break;	
		case 10: // 10- Listar Inventário de Materiais;
			mostrar(10);
			break;
	}	    	
}

main(){
	setlocale(LC_ALL ,"portuguese");
	
	int i,
		menu;
	
	mostrar_menu(&menu, 0);	
	while(menu != 0){
		switch(menu){
			case 1: // 1- Gerenciar Alunos;
				mostrar_menu(&menu, 1);				
				while(menu != 0){
					gerenciar_alunos(menu);
					mostrar_menu(&menu, 1);
				}
				break;
			case 2: // 2- Gerenciar Disciplinas;
				mostrar_menu(&menu, 2);				
				while(menu != 0){
					gerenciar_disciplinas(menu);
					mostrar_menu(&menu, 2);
				}
				break;
			case 3: // 3- Gerenciar Professores;
				mostrar_menu(&menu, 3);				
				while(menu != 0){
					gerenciar_professores(menu);
					mostrar_menu(&menu, 3);
				}
				break;
			case 4: // 4- Gerenciar Série;
				mostrar_menu(&menu, 4);				
				while(menu != 0){
					gerenciar_serie(menu);
					mostrar_menu(&menu, 4);
				}
				break;
			case 5: // 5- Gerenciar Estoque;
				mostrar_menu(&menu, 5);				
				while(menu != 0){
					gerenciar_estoque(menu);
					mostrar_menu(&menu, 5);
				}
				break;	
			case 6: // 6- Relatórios Gerais;
				mostrar_menu(&menu, 6);				
				while(menu != 0){
					gerenciar_relatorios(menu);
					mostrar_menu(&menu, 6);
				}
				break;
			case 0: // 0- Sair do programa;
				printf("\n\nSaindo...");
				break;
			default:
				printf("\n\nOpção inválida!!");
				system("pause");
				break;
		}		
		mostrar_menu(&menu, 0);	
	}
}

