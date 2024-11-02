// Yuri Strada, Valdoir de Oliveira e Gabriel Dal Bó

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<time.h> // Para lidar com data e hora

#define NOME_PROJETO "Gerente de produção"

typedef struct { // Definição de produto
	int id, estoque;
	char nome[40];
	bool is_kit;
} PRODUTO;

typedef struct { // Definição de pedido
	int id;
	char status[20], nome_cliente[50];
	struct tm data_entrega;
} PEDIDO;

typedef struct { // Definição dos produtos que compõem um produto_kit
	int id, produto_id, kit_id, quantidade;
} PRODUTO_KIT;

typedef struct { // Definição dos produtos que compõem um pedido
	int id, produto_id, pedido_id, quantidade;
} PRODUTO_PEDIDO;

typedef struct { // Definição da ordem de produção
	int id;
	char status[20];
} ORDEM_PRODUCAO;

typedef struct { // Definição dos produtos que compõem uma ordem de procução
	int id, produto_id, op_id, quantidade;
} PRODUTO_ORDEM_PRODUCAO;

// Declaração dos contadores de id 
int produto_count = 1;
int pedido_count = 1;
int produto_kit_count = 1;
int produto_pedido_count = 1;
int ordem_producao_count = 1;
int produto_ordem_producao_count = 1;

// Prototipação

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

































