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
	int dia,
		mes,
		ano;
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
		telefone[15], // telefone de contato: (18) 12345-1234;
		email[100],
		sexo;
	int CPF; // CPF do aluno ex: 12345678912;
	DATA niver; // anivers�rio do aluno ex: dia->02, mes->07, ano->2000
	SERIE turma; // turma do aluno ex: ano->1, sala->B;
	HISTORICO_ESCOLAR hist_esco;
}ALUNO;

typedef struct {
	int cod_material,
		quantidade,
		cod_pessoa;
	char motivo[100];
	DATA dt_retirada;
}HISTORICO_RETIRADA;

typedef struct {
	int cod,
		estoque;
	char descricao[100];
	DATA ultima_compra;
}ESTOQUE;

typedef struct {
	char nome[100],
		telefone[15],
		CPF,
		email[100],
		sexo;
	DATA niver;
	SERIE turma[50];
	DISCIPLINA disc[MAX_DISCIPLINA];
}PROFESSOR;


void mostrar_menu(int *menu, int op){		
	system("cls");
	switch (op) {
        case 1:
            printf("\n\nMenu de Gerenciamento de Alunos");
		    printf("\n1- Cadastrar Alunos");
		    printf("\n2- Editar Alunos");
		    printf("\n3- Excluir Alunos");
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
		    printf("\n1- Listar Alunos por Turma"); //Exibe todos os alunos matriculados em uma turma espec�fica (Nome, matr�cula, s�rie, contatos);
		    printf("\n2- Listar Hist�rico Acad�mico"); //Mostra as notas e frequ�ncia dos alunos ao longo do ano letivo (Nome do aluno, disciplina, notas, frequ�ncia, e observa��es);
		    printf("\n3- Listar Alunos por S�rie"); //Lista de todos os alunos agrupados por s�rie (Nome, matr�cula, e turma);
			printf("\n4- Listar Disciplinas"); //Lista de todas as disciplinas (Nome da disciplina, carga hor�ria, e professor respons�vel);
		    printf("\n5- Listar Disciplinas por Turma"); //Exibe quais disciplinas est�o alocadas em cada turma (Nome da turma, disciplinas oferecidas, e professores);
		    printf("\n6- Listar Professores"); //Exibe todos os professores cadastrados na escola (Nome, �rea de atua��o, e contatos);
		    printf("\n7- Listar Disciplinas Ministradas por Professor"); //Mostra as disciplinas que cada professor est� ensinando (Nome do professor, disciplinas, e turmas);
		    printf("\n8- Listar Hor�rios dos Professores"); //Lista os hor�rios dispon�veis e ocupados dos professores (Nome do professor, hor�rios de aula, e per�odos livres);
		    printf("\n9- Listar Turmas por S�rie"); //Exibe todas as turmas associadas a uma s�rie espec�fica (Nome da s�rie, turmas, e n�mero de alunos);
		    printf("\n10- Listar Hor�rio das Turmas"); //Mostra os hor�rios de aula para cada turma (Nome da turma, hor�rio, e disciplinas);
		    printf("\n11- Listar Uso de Salas"); //Relata a utiliza��o das salas de aula ao longo do tempo (Nome da sala, turma, hor�rios de uso, e atividades.);						
		    printf("\n12- Listar Capacidade das Salas"); //Exibe a capacidade e recursos dispon�veis em cada sala (Nome da sala, capacidade, e equipamentos dispon�veis);						
		    printf("\n13- Listar Calend�rio Escolar"); //Mostra o calend�rio completo do ano letivo com datas importantes (Datas de in�cio e fim, feriados, e datas de provas);						
		    printf("\n14- Listar Resumo de Atividades"); //Resumo das principais atividades e eventos do ano letivo (Eventos programados, atividades extracurriculares, e observa��es);						
		    printf("\n15- Listar Invent�rio de Materiais"); //Relata o estado atual do invent�rio de materiais did�ticos e administrativos (Nome do material, quantidade em estoque, e estado);						
		    printf("\n16- Listar Compra de Materiais"); //Mostra um hist�rico de compras de materiais (Nome do material, quantidade comprada, fornecedor, e data de compra);						
		    printf("\n17- Listar Baixas de Materiais"); //Registra as baixas de materiais, ou seja, materiais que foram utilizados ou descartados (Nome do material, quantidade baixada, e motivo);
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

int busca(FILE *fl, int id, int op){
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

void inserir(int op){	
	FILE *fl;
	int pos;
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
					printf("Deseja continuar? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

void atualizar(int op){	
	FILE *fl;
	ALUNO aluno;
	int pos;
	
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
					printf("Deseja continuar? (s)(n)");
				}while(toupper(getche())=='S');						
			}
			fclose(fl);
			break;
	}
}

void mostrar(int op){
	FILE *fl;
	int pos;
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


void gerenciar_alunos(int menu) { 
	switch(menu){
		case 1:
			inserir(1);
			break;
		
	}
	    	
}

main(){
	setlocale(LC_ALL ,"portuguese");
	
	int i,
		menu,
		sub_menu;
	
	mostrar_menu(&menu, 0);
	
	
	while(menu != 0){
		switch(menu){
			case 1:
				mostrar_menu(&menu, 1);				
				while(menu != 0){
					gerenciar_alunos(menu);
					mostrar_menu(&menu, 1);
				}
				break;
			case 0:
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


