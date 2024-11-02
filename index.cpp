// Yuri Strada, Valdoir de Oliveira e Gabriel Dal B�

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<time.h> // Para lidar com data e hora

#define NOME_PROJETO "Gerente de produ��o"

typedef struct { // Defini��o de produto
	int id, estoque;
	char nome[40];
	bool is_kit;
} PRODUTO;

typedef struct { // Defini��o de pedido
	int id;
	char status[20], nome_cliente[50];
	struct tm data_entrega;
} PEDIDO;

typedef struct { // Defini��o dos produtos que comp�em um produto_kit
	int id, produto_id, kit_id, quantidade;
} PRODUTO_KIT;

typedef struct { // Defini��o dos produtos que comp�em um pedido
	int id, produto_id, pedido_id, quantidade;
} PRODUTO_PEDIDO;

typedef struct { // Defini��o da ordem de produ��o
	int id;
	char status[20];
} ORDEM_PRODUCAO;

typedef struct { // Defini��o dos produtos que comp�em uma ordem de procu��o
	int id, produto_id, op_id, quantidade;
} PRODUTO_ORDEM_PRODUCAO;

// Declara��o dos contadores de id 
int produto_count = 1;
int pedido_count = 1;
int produto_kit_count = 1;
int produto_pedido_count = 1;
int ordem_producao_count = 1;
int produto_ordem_producao_count = 1;

// Prototipa��o

int menu_inicial() {
	int n;
	
	printf("Bem vindo ao %s!\n\n", NOME_PROJETO);
	printf("Escolha abaixo que �rea do sistema voc� deseja acessar: \n");
	printf("1 - Produtos\n");
	printf("2 - Estoque\n");
	printf("3 - Pedidos\n");
	printf("4 - Ordens de produ��o\n");
	printf("0 - Sair\n");
	scanf("%d", &n);
	
	return n;
}

int menu_produtos() {
	int n;
	
	printf("%s - Produtos\n\n", NOME_PROJETO);
	printf("O que voc� deseja fazer agora?\n");
	printf("1 - Listar produtos\n");
	printf("2 - Cadastrar novo produto\n");
	printf("3 - Atualizar um produto\n");
	printf("4 - Apagar um produto\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_estoque() {
	int n;
	
	printf("%s - Estoque\n\n", NOME_PROJETO);
	printf("O que voc� deseja fazer agora?\n");
	printf("1 - Listar estoque\n");
	printf("2 - Ajustar estoque de produto\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_pedidos() {
	int n;
	
	printf("%s - Pedidos\n\n", NOME_PROJETO);
	printf("O que voc� deseja fazer agora?\n");
	printf("1 - Listar pedidos\n");
	printf("2 - Cadastrar novo pedido\n");
	printf("3 - Atualizar um pedido\n");
	printf("4 - Apagar um pedido\n");
	printf("5 - Finalizar um pedido\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_op() {
	int n;
	
	printf("%s - Ordens de produ��o\n\n", NOME_PROJETO);
	printf("O que voc� deseja fazer agora?\n");
	printf("1 - Listar ordens de produ��o\n");
	printf("2 - Cadastrar nova ordem de produ��o\n");
	printf("3 - Atualizar uma ordem de produ��o\n");
	printf("4 - Apagar uma ordem de produ��o\n");
	printf("5 - Finalizar uma ordem de produ��o\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

void opcao_invalida() {
	system("cls");
	printf("Op��o inv�lida, tente novamente!\n\n");
}

void valor_invalido(char mensagem[40]) {
	system("cls");
	if(strlen(mensagem) > 0) {
		printf("%s", mensagem);
	}else {
		printf("Valor inv�lido, tente novamente!\n\n");	
	}
}

int main (void) {
	setlocale(LC_ALL, "");
	
	int escolha_menu;
	bool isValid = true, repeat = true;
	
	PRODUTO produtos[100];
	PEDIDO pedidos[200];
	PRODUTO_KIT produtos_kit[1000];
	PRODUTO_PEDIDO produtos_pedido[1000];
	ORDEM_PRODUCAO ordens_producao[100];
	PRODUTO_ORDEM_PRODUCAO produtos_op[1000];
	
	
	// Intera��o com menus
	do {
		system("cls");
		
		if(!isValid){
			opcao_invalida();
		}
		
		isValid = true;
		
		switch(menu_inicial()) {
			case 1:
				do {
					system("cls");
		
					if(!isValid){
						opcao_invalida();
					}
					
					isValid = true;
					
					switch(menu_produtos()) {
						case 1:
							//lista
							break;
						case 2:
							//novo
							break;
						case 3: 
							//atualiza
							break;
						case 4:
							//apaga
							break;
						case 0:
							isValid = true;
							repeat = false;
							break;
						default:
							isValid = false;
					}
				} while(!isValid || repeat);
				repeat = true;
				break;
			case 2: 
				do {
					system("cls");
		
					if(!isValid){
						opcao_invalida();
					}
					
					isValid = true;
					
					switch(menu_estoque()) {
						case 1:
							//lista
							break;
						case 2:
							//ajusta estoque produto
							break;
						case 0:
							isValid = true;
							repeat = false;
							break;
						default:
							isValid = false;
					}
				} while(!isValid || repeat);
				repeat = true;
				break;
			case 3: 
				do {
					system("cls");
		
					if(!isValid){
						opcao_invalida();
					}
					
					isValid = true;
					
					switch(menu_pedidos()) {
						case 1:
							//lista
							break;
						case 2:
							//novo
							break;
						case 3: 
							//atualiza
							break;
						case 4:
							//apaga
							break;
						case 5:
							//finalizar pedido
							break;
						case 0:
							isValid = true;
							repeat = false;
							break;
						default:
							isValid = false;
					}
				} while(!isValid || repeat);
				repeat = true;
				break;
			case 4: 
				do {
					system("cls");
		
					if(!isValid){
						opcao_invalida();
					}
					
					isValid = true;
					
					switch(menu_op()) {
						case 1:
							//lista
							break;
						case 2:
							//novo
							break;
						case 3: 
							//atualiza
							break;
						case 4:
							//apaga
							break;
						case 5:
							//finalizar ordem
							break;
						case 0:
							isValid = true;
							repeat = false;
							break;
						default:
							isValid = false;
					}
				} while(!isValid || repeat);
				repeat = true;
				break;
			case 0: 
				isValid = true;
				repeat = false;
				break;
			default: 
				isValid = false;
		}
		
	}while(!isValid || repeat);
	
	system("cls");
	printf("\n\n\nObrigado por usar o %s!!!", NOME_PROJETO);

	return 0;
}

































