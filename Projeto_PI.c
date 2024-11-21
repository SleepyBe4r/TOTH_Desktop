#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#define CAPACIDADE_SALA 30
#define MAX_DISCIPLINA 15

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
	char sala; // identificação da sala ex: A, B, C;
	DATA ano_letivo; // ano letivo ex: 2022, 2023, 2024;
}SERIE;

typedef struct {
	int cod; // código da disciplina ex: 1, 2, 3;
	char nome[100];	// nome da disciplina ex: matematica, português, ciências;
}DISCIPLINA;

typedef struct {
	int cod_disc, // código da disciplina ex: 1, 2, 3;
		faltas, // quantidade de faltas ex: 0, 1, 2;	
		bimestre; // indentificação do bimestre ex: 1, 2, 3;
	float nota; // nota do aluno ex: 0, 2.5, 10; 
}HISTORICO_ESCOLAR;

typedef struct {
	char nome[100], // nome do aluno ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100], // email de contato ex: joao@gmail.com;
		sexo, // sexo do aluno ex: F, M;
	    CPF[20]; // CPF do aluno ex: 12345678912; 
	DATA niver; // aniversário do aluno ex: dia->02, mes->07, ano->2000;
	SERIE turma; // turma do aluno ex: ano->1, sala->B;
	HISTORICO_ESCOLAR hist_esco[MAX_DISCIPLINA * 4];	
}ALUNO;

typedef struct {
	int cod_material, // código do material retirado ex: 1, 2, 3;
		quantidade, // quantidade retirada ex: 0, 1, 2;	
		cod_pessoa; // código da pessoa que retirou ex: 12345678912;	
	char motivo[100]; // motivo da retirada do material ex: uso na sala, impressao de prova;	
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
	DISCIPLINA disc[MAX_DISCIPLINA]; // disciplina do professor ex: cód->1, nome->matematica;
}PROFESSOR;

// 1° paramêtro - menu: grava a opção escolhida;
// 2° paramêtro - op: opção do Menu que irá aparecer;
void mostrar_menu(int *menu, int op){
		
	system("cls");	
	switch (op) {
        case 1:
            printf("\n\nMenu de Gerenciamento de Alunos");
		    printf("\n1- Cadastrar Aluno");
		    printf("\n2- Editar Aluno");
		    printf("\n3- Excluir Aluno");
		    printf("\n4- Lançar notas e Frequência");
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
            printf("\n\nMenu de Gerenciamento de Séries");
		    printf("\n1- Cadastrar Série");
		    printf("\n2- Editar Série");
		    printf("\n3- Excluir Série");
		    printf("\n0- Retornar");
            break;
        case 5:
            printf("\n\nMenu de Gerenciamento do Estoque");
		    printf("\n1- Compra de Materiais");
		    printf("\n2- Controle do Estoque");
		    printf("\n3- Planejamento de Reposições");
		    printf("\n4- Efetuar Baixa de Materiais");					
		    printf("\n0- Retornar");
            break;
        case 6:
            printf("\n\nMenu de Relatorios Gerais");
		    printf("\n1- Listar Alunos"); 
		    printf("\n2- Listar Histórico Acadêmico"); 
		    printf("\n3- Listar Alunos por Série"); 
			printf("\n4- Listar Disciplinas"); 
		    printf("\n5- Listar Disciplinas por Turma"); 
		    printf("\n6- Listar Professores"); 
		    printf("\n7- Listar Disciplinas Ministradas por Professor"); 
		    printf("\n8- Listar Horários dos Professores"); 
		    printf("\n9- Listar Turmas por Série"); 
		    printf("\n10- Listar Horário das Turmas"); 
		    printf("\n11- Listar Uso de Salas"); 
		    printf("\n12- Listar Capacidade das Salas"); 
		    printf("\n13- Listar Calendário Escolar"); 
		    printf("\n14- Listar Resumo de Atividades"); 
		    printf("\n15- Listar Inventário de Materiais"); 
		    printf("\n16- Listar Compra de Materiais"); 
		    printf("\n17- Listar Baixas de Materiais"); 
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
// 4° paramêtro - op: opção que será usada para buscar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque, 6==Historico escolar;
int busca_posicao(FILE *fl, int id_d, char id_s[100], int op){
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
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
	}
}
				
// 1° paramêtro - op: opção que será usada para inserir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque, 6==Historico escolar;
void inserir(int op){
	FILE *fl;
	int pos;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
		
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
					}
					printf("\n\nDeseja cadastrar outra disciplina? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

// 1° paramêtro - op: opção que será usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque, 6==Historico escolar;
void atualizar(int op){
	FILE *fl;	
	int pos;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	
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
								int pos2 = busca_posicao( fl, 0, aluno.CPF, 1);
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
								int pos2 = busca_posicao( fl, disciplina.cod, "", 1);
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
					printf("\n\nDeseja cadastrar outra disciplina? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

// 1° paramêtro - op: opção que será usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque, 6==Historico escolar;
void excluir(int op){
	FILE *fl;
	int pos,
		cod;
	char cpf[20];
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	
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
			
	}
}

// 1° paramêtro - op: opção que será usada para mostrar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==Série, 5==Estoque, 6==Historico escolar;
void mostrar(int op){
	FILE *fl;
	int pos;
	// structs;
	ALUNO aluno;
	DISCIPLINA disciplina;
	
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
	}
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
			
			break;
		case 5: // 5- Retirar Disciplina;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Professores;
void gerenciar_professores(int menu) { 
	switch(menu){ // Gerenciamento de Professores;
		case 1: // 1- Cadastrar Professor;
			
			break;
		case 2: // 2- Editar Professor;
			
			break;
		case 3: // 3- Excluir Professor;
			
			break;
		case 4: // 4- Lançar notas e Frequência;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento de Séries;
void gerenciar_serie(int menu) { 
	switch(menu){ // Gerenciamento de Séries;
		case 1: // 1- Cadastrar Série;
			
			break;
		case 2: // 2- Editar Série;
			
			break;
		case 3: // 3- Excluir Série;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1° paramêtro - menu: seleciona a opção do Menu de Gerenciamento do Estoque;
void gerenciar_estoque(int menu) { 
	switch(menu){ // Gerenciamento do Estoque;
		case 1: // 1- Compra de Materiais;
			
			break;
		case 2: // 2- Controle do Estoque;
			
			break;
		case 3: // 3- Planejamento de Reposições;
			
			break;
		case 4: // 4- Efetuar Baixa de Materiais;
			
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

