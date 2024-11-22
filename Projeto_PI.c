#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#define CAPACIDADE_SALA 30
#define MAX_DISCIPLINA 30

/*Gerenciar alunos, gerenciar disciplinas, gerenciar
professores, gerenciar s�rie, gerenciar turma, gerenciar sala, gerenciar ano letivo;
� Efetuar matr�cula
� Definir de grade curricular
� Alocar turma.
� Gerenciar compra de material
� Controlar de estoque
� Efetuar baixa (uso de material)
� Relat�rios gerais (ex: turmas, professores, etc). */

typedef struct {
	int dia, // dia ex: 02;
		mes, // mes ex: 07;
		ano; // ano ex: 2000;
}DATA;

typedef struct {
	int ano; // ano da serie ex: 1, 2, 3;
	char sala[50]; // identifica��o da sala ex: A, B, C;
	DATA ano_letivo; // ano letivo ex: 2022, 2023, 2024;
}SERIE;

typedef struct {
	int cod; // c�digo da disciplina ex: 1, 2, 3;
	char nome[100];	// nome da disciplina ex: matematica, portugu�s, ci�ncias;
}DISCIPLINA;

typedef struct {
	int cod_disc, // c�digo da disciplina ex: 1, 2, 3;
		faltas, // quantidade de faltas ex: 0, 1, 2;	
		bimestre; // indentifica��o do bimestre ex: 1, 2, 3;
	float nota; // nota do aluno ex: 0, 2.5, 10; 
}HISTORICO_ESCOLAR;

typedef struct {
	char nome[100], // nome do aluno ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100], // email de contato ex: joao@gmail.com;
		sexo, // sexo do aluno ex: F, M;
	    CPF[20]; // CPF do aluno ex: 12345678912; 
	DATA niver; // anivers�rio do aluno ex: dia->02, mes->07, ano->2000;
	SERIE turma; // turma do aluno ex: ano->1, sala->B;
	HISTORICO_ESCOLAR hist_esco[MAX_DISCIPLINA * 4];	
}ALUNO;

typedef struct {
	int cod_material, // c�digo do material retirado ex: 1, 2, 3;
		quantidade, // quantidade retirada ex: 0, 1, 2;	
		cod_pessoa; // c�digo da pessoa que retirou ex: 12345678912;	
	char motivo[250]; // motivo da retirada do material ex: uso na sala, impressao de prova;	
	DATA dt_retirada; // data da retirada do material ex: dia->02, mes->07, ano->2000;
}HISTORICO_RETIRADA;

typedef struct {
	int cod, // c�digo do material ex: 1, 2, 3;
		estoque; // quantidade em estoque ex: 0, 1, 2;	
	char descricao[250]; // descri��o do material ex: lapis, giz, papel A4;	
	DATA ultima_compra; // data da ultima compra do material ex: dia->02, mes->07, ano->2000;
}ESTOQUE;

typedef struct {
	char nome[100], // nome do professor ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100],// email de contato ex: joao@gmail.com;
		sexo,
	    CPF[20]; // CPF do professor ex: 12345678912;
	DATA niver; // anivers�rio do professor ex: dia->02, mes->07, ano->2000;
	SERIE turma[50]; // turma do professor ex: ano->1, sala->B;
	DISCIPLINA disc[MAX_DISCIPLINA]; // disciplina do professor ex: c�d->1, nome->matematica;
}PROFESSOR;

// 1� param�tro - menu: grava a op��o escolhida;
// 2� param�tro - op: op��o do Menu que ir� aparecer;
void mostrar_menu(int *menu, int op){
		
	system("cls");	
	switch (op) {
        case 1:
            printf("\n\nMenu de Gerenciamento de Alunos");
		    printf("\n1- Cadastrar Aluno");
		    printf("\n2- Editar Aluno");
		    printf("\n3- Excluir Aluno");
		    printf("\n4- Lan�ar notas e Frequ�ncia");
		    printf("\n0- Retornar");
            break;
        case 2:
            printf("\n\nMenu de Gerenciamento de Disciplinas");
		    printf("\n1- Cadastrar Disciplina");
		    printf("\n2- Editar Disciplina");
		    printf("\n3- Excluir Disciplina");
		    printf("\n4- Atribuir Disciplina");
		    printf("\n5- Retirar Disciplina");
		    printf("\n0- Retornar");	
            break;
        case 3:
            printf("\n\nMenu de Gerenciamento de Professores");
		    printf("\n1- Cadastrar Professor");
		    printf("\n2- Editar Professor");
		    printf("\n3- Excluir Professor");		    
		    printf("\n0- Retornar");	
            break;
        case 4:
            printf("\n\nMenu de Gerenciamento de S�ries");
		    printf("\n1- Cadastrar S�rie");
		    printf("\n2- Editar S�rie");
		    printf("\n3- Excluir S�rie");
		    printf("\n0- Retornar");
            break;
        case 5:
            printf("\n\nMenu de Gerenciamento do Estoque");
		    printf("\n1- Cadastrar Material");
		    printf("\n2- Editar Material");
		    printf("\n3- Excluir Material");
		    printf("\n4- Compra de Materiais");
		    printf("\n5- Efetuar Baixa de Materiais");					
		    printf("\n0- Retornar");
            break;
        case 6:
            printf("\n\nMenu de Relatorios Gerais");
		    printf("\n1- Listar Alunos"); 
		    printf("\n2- Listar Hist�rico Acad�mico"); 
		    printf("\n3- Listar Alunos por S�rie"); 
			printf("\n4- Listar Disciplinas"); 
		    printf("\n5- Listar Disciplinas por Turma"); 
		    printf("\n6- Listar Professores"); 
		    printf("\n7- Listar Disciplinas Ministradas por Professor"); 
		    printf("\n8- Listar Hor�rios dos Professores"); 
		    printf("\n9- Listar S�ries"); 
		    printf("\n10- Listar Hor�rio das Turmas"); 
		    printf("\n11- Listar Uso de Salas"); 
		    printf("\n12- Listar Capacidade das Salas"); 
		    printf("\n13- Listar Calend�rio Escolar"); 
		    printf("\n14- Listar Resumo de Atividades"); 
		    printf("\n15- Listar Invent�rio de Materiais"); 
		    printf("\n16- Listar Compra de Materiais"); 
		    printf("\n17- Listar Baixas de Materiais"); 
		    printf("\n0- Retornar");
            break;        
        case 0:
            printf("\n\nMenu de Gerenciamento Escolar");
		    printf("\n1- Gerenciar Alunos");
		    printf("\n2- Gerenciar Disciplinas");
		    printf("\n3- Gerenciar Professores");
		    printf("\n4- Gerenciar S�rie");
			printf("\n5- Gerenciar Estoque");
		    printf("\n6- Relat�rios Gerais");
		    printf("\n0- Sair do programa");	
        	break;
    }	
    
	printf("\n\nDigite uma op��o para continuar: ");
	scanf("%d",&*menu);
}

// 1� param�tro - fl: arquivo que ser� buscado;
// 2� param�tro - id_d: indentifica��o em decimal que ser� usada para buscar;
// 3� param�tro - id_s: indentifica��o em string que ser� usada para buscar;
// 4� param�tro - op: op��o que ser� usada para buscar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque;
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
				
// 1� param�tro - op: op��o que ser� usada para inserir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque;
void inserir(int op){
	FILE *fl;
	int pos;
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
					printf("\n\nInforme o c�digo da disciplina: ");
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
					}
					printf("\n\nDeseja cadastrar outra disciplina? (s)(n)");
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
					
					printf("\n\nInforme o ano da s�rie: ");
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
						printf("\n\nId: %d-%s (S�rie ja cadastrado!)",serie.ano,serie.sala);
					}
					printf("\n\nDeseja cadastrar outra s�rie? (s)(n)");
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
					printf("\n\nInforme o C�digo do material: ");
					scanf("%d", &estoque.cod);
					
					pos = busca_posicao(fl, estoque.cod, "",5);
					if(pos == -1){
						printf("\n\nInforme a quantidade inicial do material: ");
						scanf("%d", &estoque.estoque);
						
						printf("\n\nInforme a descri��o do material: ");
						fflush(stdin);
						gets(estoque.descricao);
						
						printf("\n\nInforme a data da ultima compra do material dd mm aaaa: ");
						scanf("%d %d %d", &estoque.ultima_compra.dia, &estoque.ultima_compra.mes, &estoque.ultima_compra.ano);
						
						fwrite(&estoque,sizeof(ESTOQUE),1,fl);
					} else {
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\nId: %d (Material ja cadastrado!)",estoque.ano);
					}
					printf("\n\nDeseja cadastrar outro material? (s)(n)");
				} while(toupper(getch()) == 'S');
			}
			break;
	}
}

// 1� param�tro - op: op��o que ser� usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque;
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
					printf("\n\nInforme o CPF do aluno � ser editado: ");
					fflush(stdin);
					gets(aluno.CPF);
					pos = busca_posicao( fl, 0, aluno.CPF, 1);
					if(pos==-1)
					{						
						printf("\n\n(Aluno n�o cadastrado!)");
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
						printf("\n\n1 - Nome \n2 - Fone \n3 - E-mail \n4 - Sexo \n5 - CPF \n6 - Anivers�rio \nDeseja alterar: ");
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
								printf("\n\nNovo Anivers�rio dd mm aaaa: ");
								fflush(stdin);
								scanf("%d", &aluno.niver.dia, &aluno.niver.mes, &aluno.niver.ano);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							default:
								printf("\n\nOp��o inv�lida!!");
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
					printf("\n\nInforme o c�digo da disciplina � ser editada: ");
					scanf("%d", &disciplina.cod);
					pos = busca_posicao( fl, disciplina.cod, "", 2);
					if(pos==-1)
					{						
						printf("\n\n(Disciplina n�o cadastrada!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&disciplina,sizeof(DISCIPLINA),1,fl);
						printf("\n\n__________________");
						printf("\n\nC�d: %d",disciplina.cod);
						printf("\nNome: %s",disciplina.nome);
						printf("\n__________________");
						printf("\n\n1 - C�d \n2 - Nome \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo C�digo: ");
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
								printf("\n\nOp��o inv�lida!!");
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
					printf("\n\nInforme o CPF do professor � ser editado: ");
					fflush(stdin);
					gets(professor.CPF);
					pos = busca_posicao( fl, 0, professor.CPF, 3);
					if(pos==-1)
					{						
						printf("\n\n(Professor n�o cadastrado!)");
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
						printf("\n\n1 - Nome \n2 - Fone \n3 - E-mail \n4 - Sexo \n5 - CPF \n6 - Anivers�rio \nDeseja alterar: ");
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
								printf("\n\nNovo Anivers�rio dd mm aaaa: ");
								fflush(stdin);
								scanf("%d", &professor.niver.dia, &professor.niver.mes, &professor.niver.ano);
								fseek(fl,pos,0);
								fwrite(&professor,sizeof(PROFESSOR),1,fl);
								break;
							default:
								printf("\n\nOp��o inv�lida!!");
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
					printf("\n\nInforme o ano da s�rie � ser editada: ");
					scanf("%d", &serie.ano);	
					
					printf("\n\nInforme o nome da sala � ser editada: ");
					fflush(stdin);
					gets(serie.sala);
					pos = busca_posicao(fl, serie.ano, serie.sala, 4);
					if(pos==-1)
					{						
						printf("\n\n(S�rie n�o cadastrada!)");
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
									printf("\n\nId: %d-%s (S�rie ja cadastrado!)",serie.ano,serie.sala);
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
									printf("\n\nId: %d-%s (S�rie ja cadastrado!)",serie.ano,serie.sala);
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
					printf("\n\nDeseja atualizar outra s�rie? (s)(n)");
				}while(toupper(getche())=='S');		
			}
			break;
		case 5:
			fl = fopen("estoque.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {
				do{
					printf("\n\ninforme o c�digo do material � ser editado");
					scanf("%d", &estoque.cod);
					pos = busca_posicao(fl, estoque.cod, "",5);
					if(pos == -1){
						printf("\n\n(Material n�o cadastrado!)");
					} else {
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\n__________________");
						printf("\n\nC�d: %d", estoque.cod);
						printf("\nQuantidade: %d", estoque.estoque);
						printf("\nDescri��o: %s", estoque.descricao);
						printf("\nUltima Compra: %d/%d/%d", estoque.ultima_compra.dia, estoque.ultima_compra.mes, estoque.ultima_compra.ano);
						printf("\n__________________");
						printf("\n\n1 - C�d \n2 - Quantidade \n3 - Descri��o \n4 - Ultima Compra \nDeseja alterar: ");
						scanf("%d",&op);
						
						switch(op){
							case 1:
								printf("\n\nNovo C�d: ");
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
								printf("\n\nNova Descri��o: ");
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
				} while(toupper(getch()) != 'S');
			}
			break;
	}
}

// 1� param�tro - op: op��o que ser� usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque;
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
					printf("\n\nInforme o CPF do aluno � ser excluido: ");
					fflush(stdin);
					gets(cpf);
					pos = busca_posicao(fl,0,cpf,1);
					if(pos==-1)
					{						
						printf("\n\n(Aluno n�o cadastrado!)");
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
									fwrite(&aluno,sizeof(ALUNO),1,fl);						
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
					printf("\n\nInforme o c�digo da disciplina � ser excluida: ");					
					scanf("%d", &cod);
					pos = busca_posicao(fl, disciplina.cod, "", 2);
					if(pos==-1)
					{						
						printf("\n\n(Disciplina n�o cadastrada!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&disciplina,sizeof(DISCIPLINA),1,fl);
						printf("\n\n__________________");
						printf("\n\nC�d: %d",disciplina.cod);
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
									fwrite(&disciplina,sizeof(DISCIPLINA),1,fl);						
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
					printf("\n\nInforme o CPF do professor � ser excluido: ");
					fflush(stdin);
					gets(cpf);
					pos = busca_posicao(fl,0,cpf,3);
					if(pos==-1)
					{						
						printf("\n\n(Professor n�o cadastrado!)");
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
									fwrite(&professor,sizeof(PROFESSOR),1,fl);						
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
			break;
		case 4:
			fl = fopen("serie.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o ano da s�rie � ser excluida: ");
					scanf("%d", &ano);	
					
					printf("\n\nInforme o nome da sala � ser excluida: ");
					fflush(stdin);
					gets(sala);
					pos = busca_posicao(fl, serie.ano, serie.sala, 4);
					if(pos==-1)
					{						
						printf("\n\n(S�rie n�o cadastrada!)");
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
									fwrite(&serie,sizeof(SERIE),1,fl);						
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
					printf("\n\nDeseja excluir outra S�rie? (s)(n)");
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
					printf("\n\nInforme o c�digo do material � ser excluido: ");
					scanf("%d", &cod);	
					
					pos = busca_posicao(fl, cod, "", 5);
					if(pos==-1)
					{						
						printf("\n\n(Material n�o cadastrado!)");
					}
					else 
					{
						fseek(fl,pos,0);
						fread(&estoque,sizeof(ESTOQUE),1,fl);
						printf("\n\n__________________");
						printf("\n\nC�d: %d", estoque.cod);
						printf("\nQuantidade: %d", estoque.estoque);
						printf("\nDescri��o: %s", estoque.descricao);
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
									fwrite(&estoque,sizeof(ESTOQUE),1,fl);						
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

// 1� param�tro - op: op��o que ser� usada para mostrar, ;
void mostrar(int op){
	FILE *fl;
	int pos;
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
					printf("\n\nC�d: %d",disciplina.cod);
					printf("\nNome: %s",disciplina.nome);
					printf("\n__________________");
					printf("\n\n");
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
	}
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento de Aluno;
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
		case 4: // 4- Lan�ar notas e Frequ�ncia;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento de Disciplinas;
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
			
			break;
		case 5: // 5- Retirar Disciplina;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento de Professores;
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
		case 4: // 4- Lan�ar notas e Frequ�ncia;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento de S�ries;
void gerenciar_serie(int menu) { 
	switch(menu){ // Gerenciamento de S�ries;
		case 1: // 1- Cadastrar S�rie;
			inserir(4);
			break;
		case 2: // 2- Editar S�rie;
			atualizar(4);
			break;
		case 3: // 3- Excluir S�rie;
			excluir(4);
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento do Estoque;
void gerenciar_estoque(int menu) { 
	switch(menu){ // Gerenciamento do Estoque;
		case 1: // 1- Compra de Materiais;
			inserir(5);
			break;
		case 2: // 2- Controle do Estoque;
			atualizar(5);
			break;
		case 3: // 3- Planejamento de Reposi��es;
			excluir(5);
			break;
		case 4: // 4- Efetuar Baixa de Materiais;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do menu de gerenciamento Relatorios Gerais;
void gerenciar_relatorios(int menu) { 
	switch(menu){
		case 1: // 1- Listar Alunos;
			mostrar(1);
			break;
		case 4: // 4- Listar Disciplinas;
			mostrar(4);
			break;
		case 6: // 6- Listar Professores;
			mostrar(6);
			break;	
		case 9: // 9- Listar S�ries;
			mostrar(9);
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
			case 4: // 4- Gerenciar S�rie;
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
			case 6: // 6- Relat�rios Gerais;
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
				printf("\n\nOp��o inv�lida!!");
				system("pause");
				break;
		}		
		mostrar_menu(&menu, 0);	
	}
}

