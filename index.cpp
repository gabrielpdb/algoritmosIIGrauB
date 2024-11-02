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

int menu() {
	int n;
	
	printf("Bem vindo ao %s!\n", NOME_PROJETO);
	
	
	return n;
}

int main (void) {
	setlocale(LC_ALL, "");
	
	PRODUTO produtos[100];
	PEDIDO pedidos[200];
	PRODUTO_KIT produtos_kit[1000];
	PRODUTO_PEDIDO produtos_pedido[1000];
	ORDEM_PRODUCAO ordens_producao[100];
	PRODUTO_ORDEM_PRODUCAO produtos_op[1000];
	
	
	

	return 0;
}

































