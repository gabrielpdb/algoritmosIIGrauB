// Yuri Strada, Valdoir de Oliveira e Gabriel Dal B�

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<time.h> // Para lidar com data e hora

#define NOME_PROJETO "Gerente de produ��o"
#define MAX_PRODUTOS 1000

typedef struct { // Defini��o de produto
	int id, estoque;
	char nome[40];
} PRODUTO;

typedef struct { // Defini��o de pedido
	int id;
	char status[20], nome_cliente[50];
	struct tm data_entrega;
} PEDIDO;

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

typedef struct { // Defini��o da struct que lida com os auto increments
	int produto_count;
	int pedido_count;
	int produto_pedido_count;
	int ordem_producao_count;
	int produto_ordem_producao_count;
} INCREMENT;

// Prototipa��o

int menu_inicial();
int menu_produtos();
int menu_estoque();
int menu_pedidos();
int menu_op();
void opcao_invalida();
void valor_invalido();
void erro_arquivo();
int get_increment(char counter[30]);
void novo_produto();
void save_produto(PRODUTO produto);

// Fun��es

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

void erro_arquivo() {
	printf("\n\nDeu erro abrindo o arquivo, tenta de novo a�\n\n");
	system("pause");
}

int get_increment(char counter[30]) { // Essa fun��o recebe o tipo de dado que ser� incrementado como string e retorna o �ltimo valor de incremento v�lido.
	INCREMENT incremento;
	
	FILE *arquivo = fopen("auto_increment.dat", "rb");
	
	if(arquivo) {
		fread(&incremento, sizeof(INCREMENT), 1, arquivo);
		fclose(arquivo);
	} else {
		incremento.ordem_producao_count = 1;
		incremento.pedido_count = 1;
		incremento.produto_count = 1;
		incremento.produto_ordem_producao_count = 1;
		incremento.produto_pedido_count = 1;
	}
	
	if(strcmp(counter, "produto") == 0)
		return incremento.produto_count;
	else if(strcmp(counter, "pedido") == 0)
		return incremento.pedido_count;
	else if(strcmp(counter, "produto_pedido") == 0)
		return incremento.produto_pedido_count;
	else if(strcmp(counter, "ordem_producao") == 0)
		return incremento.ordem_producao_count;
	else if(strcmp(counter, "produto_ordem_producao") == 0)
		return incremento.produto_ordem_producao_count;
	else
		printf("\n\n\nTipo de incremento inv�lido!\\n\n\n");
}

void save_increment(char counter[30], int id){ // Essa fun��o recebe o tipo de dado que ser� incrementado e o valor do incremento a ser salvo
	INCREMENT incremento;
	
	FILE *arquivo = fopen("auto_increment.dat",  "rb+");
	
	if(arquivo) {
		fread(&incremento, sizeof(INCREMENT), 1, arquivo);
		fseek(arquivo, 0, SEEK_SET);
	} else {
		arquivo = fopen("auto_increment.dat", "wb");
		
		incremento.ordem_producao_count = 1;
		incremento.pedido_count = 1;
		incremento.produto_count = 1;
		incremento.produto_ordem_producao_count = 1;
		incremento.produto_pedido_count = 1;
	}
	
	if(strcmp(counter, "produto") == 0)
		incremento.produto_count = id;
	else if(strcmp(counter, "pedido") == 0)
		incremento.pedido_count = id;
	else if(strcmp(counter, "produto_pedido") == 0)
		incremento.produto_pedido_count = id;
	else if(strcmp(counter, "ordem_producao") == 0)
		incremento.ordem_producao_count = id;
	else if(strcmp(counter, "produto_ordem_producao") == 0)
		incremento.produto_ordem_producao_count = id;
	else
		printf("\n\n\nTipo de incremento inv�lido!\\n\n\n");
	
	fwrite(&incremento, sizeof(INCREMENT), 1, arquivo);
	fclose(arquivo);
}

void novo_produto() { // Fun��o que pede para o usu�rio as informa��es sobre o novo produto
	PRODUTO novoProduto;
	
	system("cls");
	
	printf("Informe a descri��o do produto: ");
	fflush(stdin);
	gets(novoProduto.nome);
	
	printf("Quantidade em estoque do produto: ");
	scanf("%d", &novoProduto.estoque);
	
	novoProduto.id = get_increment("produto"); // Pega o �ltimo valor do incremento
	novoProduto.id++; // Incrementa o incremento
	
	save_produto(novoProduto); // Envia o produto para ser salvo
}

void save_produto(PRODUTO produto) { // Fun��o que salva um produto no arquivo
	FILE *arquivo = fopen("produtos.dat", "ab"); // Abre o arquivo de produtos para append bin�rio
	
	if(!arquivo) { // Retorna uma mensagem para o usu�rio caso d� problema com o arquivo
		erro_arquivo();
		return;
	}
	
	fwrite(&produto, sizeof(PRODUTO), 1, arquivo); // Escreve no arquivo o produto novo
	fclose(arquivo); // Fecha o arquivo
	save_increment("produto", produto.id); // Salva o id do �ltimo produto como valor do incremento para ser usado no pr�ximo produto cadastrado
}

void load_produtos(PRODUTO produtos[MAX_PRODUTOS]) { // Fun��o que carrega os produtos do arquivo para o array de PRODUTO
	FILE *arquivo = fopen("produtos.dat", "rb"); // Carrega o arquivo de produtos como leitura bin�ria
	int i = 0;
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	while(fread(&produtos[i], sizeof(PRODUTO), 1, arquivo)) { // Enquanto houver linhas no arquivo, insere no array de produtos
		i++;
	}
}

void print_produtos(PRODUTO produtos[MAX_PRODUTOS]) { // Exibe na tela os produtos carregados no array de produtos
	load_produtos(produtos);

	system("cls");
	printf("Lista de produtos cadastrados: \n\n");

	int i = 0;
	while(produtos[i].id != NULL) {
		printf("%d: %s - %d unidades\n", produtos[i].id, produtos[i].nome, produtos[i].estoque);

		i++;
	}
	
	getch();
}

int main (void) {
	setlocale(LC_ALL, "");
	
	int escolha_menu;
	bool isValid = true, repeat = true;
	
	PRODUTO produtos[MAX_PRODUTOS] = {0};
	PEDIDO pedidos[200] = {0};
	PRODUTO_PEDIDO produtos_pedido[1000] = {0};
	ORDEM_PRODUCAO ordens_producao[100] = {0};
	PRODUTO_ORDEM_PRODUCAO produtos_op[1000] = {0};
	
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
							print_produtos(produtos);
							break;
						case 2:
							novo_produto();
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
							print_produtos(produtos);
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

































