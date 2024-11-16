#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#define CAPACIDADE_SALA 30
#define MAX_DISCIPLINA 15

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
	char sala; // identifica��o da sala ex: A, B, C;
	DATA ano_letivo; // ano letivo ex: 2022, 2023, 2024;
}SERIE;

typedef struct {
	int cod; // c�digo da disciplina ex: 1, 2, 3;
	char nome[100];	// nome da disciplina ex: matematica, portugu�s, ci�ncias;
}DISCIPLINA;

typedef struct {
	int cod_disc[MAX_DISCIPLINA * 4], // c�digo da disciplina ex: 1, 2, 3;
		faltas[MAX_DISCIPLINA * 4], // quantidade de faltas ex: 0, 1, 2;	
		bimestre[MAX_DISCIPLINA * 4]; // indentifica��o do bimestre ex: 1, 2, 3;
	float nota[MAX_DISCIPLINA * 4]; // nota do aluno ex: 0, 2.5, 10; 
}HISTORICO_ESCOLAR;

typedef struct {
	char nome[100], // nome do aluno ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100], // email de contato ex: joao@gmail.com;
		sexo; // sexo do aluno ex: F, M;
	int CPF; // CPF do aluno ex: 12345678912;
	DATA niver; // anivers�rio do aluno ex: dia->02, mes->07, ano->2000;
	SERIE turma; // turma do aluno ex: ano->1, sala->B;
	HISTORICO_ESCOLAR hist_esco;
}ALUNO;

typedef struct {
	int cod_material, // c�digo do material retirado ex: 1, 2, 3;
		quantidade, // quantidade retirada ex: 0, 1, 2;	
		cod_pessoa; // c�digo da pessoa que retirou ex: 12345678912;	
	char motivo[100]; // motivo da retirada do material ex: uso na sala, impressao de prova;	
	DATA dt_retirada; // data da retirada do material ex: dia->02, mes->07, ano->2000;
}HISTORICO_RETIRADA;

typedef struct {
	int cod, // c�digo do material ex: 1, 2, 3;
		estoque; // quantidade em estoque ex: 0, 1, 2;	
	char descricao[100]; // descri��o do material ex: lapis, giz, papel A4;	
	DATA ultima_compra; // data da ultima compra do material ex: dia->02, mes->07, ano->2000;
}ESTOQUE;

typedef struct {
	char nome[100], // nome do professor ex: joao, maria, eduardo;
		telefone[15], // telefone de contato ex: (18) 12345-1234;
		email[100],// email de contato ex: joao@gmail.com;
		sexo;
	int CPF; // CPF do professor ex: 12345678912;
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
		    printf("\n0- Retornar\n");
            break;
        case 2:
            printf("\n\nMenu de Gerenciamento de Disciplinas");
		    printf("\n1- Cadastrar Disciplina");
		    printf("\n2- Editar Disciplina");
		    printf("\n3- Excluir Disciplina");
		    printf("\n4- Atribuir Disciplina");
		    printf("\n5- Retirar Disciplina");
		    printf("\n0- Sair\n");
            break;
        case 3:
            printf("\n\nMenu de Gerenciamento de Professores");
		    printf("\n1- Cadastrar Professor");
		    printf("\n2- Editar Professor");
		    printf("\n3- Excluir Professor");		    
		    printf("\n0- Retornar\n");	
            break;
        case 4:
            printf("\n\nMenu de Gerenciamento de S�ries");
		    printf("\n1- Cadastrar S�rie");
		    printf("\n2- Editar S�rie");
		    printf("\n3- Excluir S�rie");
		    printf("\n0- Retornar\n");	
            break;
        case 5:
            printf("\n\nMenu de Gerenciamento do Estoque");
		    printf("\n1- Compra de Materiais");
		    printf("\n2- Controle do Estoque");
		    printf("\n3- Planejamento de Reposi��es");
		    printf("\n4- Efetuar Baixa de Materiais");					
		    printf("\n0- Retornar\n");		 
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
		    printf("\n9- Listar Turmas por S�rie"); 
		    printf("\n10- Listar Hor�rio das Turmas"); 
		    printf("\n11- Listar Uso de Salas"); 
		    printf("\n12- Listar Capacidade das Salas"); 
		    printf("\n13- Listar Calend�rio Escolar"); 
		    printf("\n14- Listar Resumo de Atividades"); 
		    printf("\n15- Listar Invent�rio de Materiais"); 
		    printf("\n16- Listar Compra de Materiais"); 
		    printf("\n17- Listar Baixas de Materiais"); 
		    printf("\n0- Retornar\n");						    
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
// 2� param�tro - id: indentifica��o que ser� usada para buscar;
// 3� param�tro - op: op��o que ser� usada para buscar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque, 6==Historico escolar;
int busca(FILE *fl, int id, int op){
	// structs;
	ALUNO aluno;
	
	switch(op){
		case 1:
			rewind(fl);
			fread(&aluno,sizeof(ALUNO),1,fl);
			while(!feof(fl) && id != aluno.CPF){
				fread(&aluno,sizeof(ALUNO),1,fl);
			}
			if(!feof(fl)){
				return(ftell(fl)-sizeof(ALUNO));
			} else{
				return -1;
			}
			break;
	}
}
				
// 1� param�tro - op: op��o que ser� usada para inserir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque, 6==Historico escolar;
void inserir(int op){}
	FILE *fl;
	int pos;
	// structs;
	ALUNO aluno;
	
	switch(op){
		case 1:
			
			fl = fopen("aluno.bin","ab+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno: ");
					scanf("%d", &aluno.CPF);
					pos = busca(fl, aluno.CPF, 1);
					if(pos==-1)
					{
						printf("\n\nInforme o nome completo: ");
						fflush(stdin);
						gets(aluno.nome);
						
						printf("\n\nInforme o sexo do aluno: ");
						fflush(stdin);
						scanf("%c", &aluno.sexo);
						
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
						printf("\n\nId: %d (Aluno ja cadastrado!)",aluno.CPF);
					}
					printf("Deseja cadastrar outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

// 1� param�tro - op: op��o que ser� usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque, 6==Historico escolar;
void atualizar(int op){}
	FILE *fl;	
	int pos;
	// structs;
	ALUNO aluno;
	
	switch(op){
		case 1:			
			fl = fopen("aluno.bin","rb+");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno � ser editado: ");
					scanf("%d", &aluno.CPF);
					pos = busca(fl,aluno.CPF,1);
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
						printf("\nCPF: %d",aluno.CPF);
						printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
						printf("__________________");
						printf("\n\n Deseja alterar: \n1 - Nome \n2 - Fone \n3 - E-mail \n4 - Sexo \n5 - CPF \n6 - Anivers�rio");
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
								printf("\n\nNovo Sexo: ");
								fflush(stdin);
								scanf("%c",&aluno.sexo);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
								break;
							case 5:
								printf("\n\nNovo CPF: ");
								fflush(stdin);
								scanf("%d", &aluno.CPF);
								fseek(fl,pos,0);
								fwrite(&aluno,sizeof(ALUNO),1,fl);
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
					printf("Deseja atualizar outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

// 1� param�tro - op: op��o que ser� usada para excluir, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque, 6==Historico escolar;
void excluir(int op){
	FILE *fl;
	int pos;
	// structs;
	ALUNO aluno;
	
	switch(op){
		case 1:
			fl = fopen("aluno.bin","rb");
			if(fl == NULL){
				printf("\n\nErro no arquivo!");
			} else {						
				do
				{
					printf("\n\nInforme o CPF do aluno � ser excluido: ");
					scanf("%d", &aluno.CPF);
					pos = busca(fl,aluno.CPF,1);
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
						printf("\nCPF: %d",aluno.CPF);
						printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
						printf("__________________");
						printf("\n\nDeseja excluir? (s/n)");
						if(toupper(getch()) == 'S'){
							FILE *temp;
							temp = fopen("auxiliar.bin","wb");
							rewind(fl);
							fread(&aluno,sizeof(ALUNO),1,fl);
							while(!feof(fl)){
								if(strcmp(nome, ctt.nome) != 0){
									fwrite(&aluno,sizeof(ALUNO),1,fl);						
								}
								fread(&aluno,sizeof(ALUNO),1,fl);
							}
							fclose(fl);
							fclose(temp);
							remove("agenda.bin");
							rename("auxiliar.bin","agenda.bin");
							system("cls");
							printf("\n\nArquivo excluido com sucesso!\n");
							system("pause");
						}						
					}
					printf("Deseja excluir outro aluno? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
			
	}
}

// 1� param�tro - op: op��o que ser� usada para mostrar, 1==Aluno, 2==Disciplinas, 3==Professores, 4==S�rie, 5==Estoque, 6==Historico escolar;
void mostrar(int op){
	FILE *fl;
	int pos;
	// structs;
	ALUNO aluno;
	
	switch(op){
		case 1:
			fl = fopen("aluno.bin","rb");
			if (fl==NULL)
				printf("Erro no arquivo!");
			else
			{
				printf("\n\n__________________");
				while(fread(&aluno,sizeof(ALUNO),1,fl)==1)
				{					
					printf("\nNome: %s",aluno.nome);
					printf("\nFone: %s",aluno.telefone);
					printf("\nE-mail: %s",aluno.email);
					printf("\nSexo: %c",aluno.sexo);
					printf("\nCPF: %d",aluno.CPF);
					printf("\nAniversario: %d/%d/%d", aluno.niver.dia, aluno.niver.mes, aluno.niver.ano);																		
					printf("__________________");
					printf("\n");
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
			
			break;
		case 2: // 2- Editar Disciplina;
			
			break;
		case 3: // 3- Excluir Disciplina;
			
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
			
			break;
		case 2: // 2- Editar Professor;
			
			break;
		case 3: // 3- Excluir Professor;
			
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
			
			break;
		case 2: // 2- Editar S�rie;
			
			break;
		case 3: // 3- Excluir S�rie;
			
			break;
		case 0: // 0- Retornar;			
			break;
	}	    	
}

// 1� param�tro - menu: seleciona a op��o do Menu de Gerenciamento do Estoque;
void gerenciar_serie(int menu) { 
	switch(menu){ // Gerenciamento do Estoque;
		case 1: // 1- Compra de Materiais;
			
			break;
		case 2: // 2- Controle do Estoque;
			
			break;
		case 3: // 3- Planejamento de Reposi��es;
			
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


