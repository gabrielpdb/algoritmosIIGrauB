// Yuri Strada, Valdoir de Oliveira e Gabriel Dal Bó

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<time.h> // Para lidar com data e hora

#define NOME_PROJETO "Gerente de produção"
#define MAX_PRODUTOS 1000

typedef struct { // Definição de produto
	int id, estoque;
	char nome[40];
} PRODUTO;

typedef struct { // Definição de pedido
	int id;
	char status[20], nome_cliente[50];
	struct tm data_entrega;
} PEDIDO;

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

typedef struct { // Definição da struct que lida com os auto increments
	int produto_count;
	int pedido_count;
	int produto_pedido_count;
	int ordem_producao_count;
	int produto_ordem_producao_count;
} INCREMENT;

// Prototipação

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

// Funções

int menu_inicial() {
	int n;
	
	printf("Bem vindo ao %s!\n\n", NOME_PROJETO);
	printf("Escolha abaixo que área do sistema você deseja acessar: \n");
	printf("1 - Produtos\n");
	printf("2 - Estoque\n");
	printf("3 - Pedidos\n");
	printf("4 - Ordens de produção\n");
	printf("0 - Sair\n");
	scanf("%d", &n);
	
	return n;
}

int menu_produtos() {
	int n;
	
	printf("%s - Produtos\n\n", NOME_PROJETO);
	printf("O que você deseja fazer agora?\n");
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
	printf("O que você deseja fazer agora?\n");
	printf("1 - Listar estoque\n");
	printf("2 - Ajustar estoque de produto\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_pedidos() {
	int n;
	
	printf("%s - Pedidos\n\n", NOME_PROJETO);
	printf("O que você deseja fazer agora?\n");
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
	
	printf("%s - Ordens de produção\n\n", NOME_PROJETO);
	printf("O que você deseja fazer agora?\n");
	printf("1 - Listar ordens de produção\n");
	printf("2 - Cadastrar nova ordem de produção\n");
	printf("3 - Atualizar uma ordem de produção\n");
	printf("4 - Apagar uma ordem de produção\n");
	printf("5 - Finalizar uma ordem de produção\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

void opcao_invalida() {
	system("cls");
	printf("Opção inválida, tente novamente!\n\n");
}

void valor_invalido(char mensagem[40]) {
	system("cls");
	if(strlen(mensagem) > 0) {
		printf("%s", mensagem);
	}else {
		printf("Valor inválido, tente novamente!\n\n");	
	}
}

void erro_arquivo() {
	printf("\n\nDeu erro abrindo o arquivo, tenta de novo aí\n\n");
	system("pause");
}

int get_increment(char counter[30]) { // Essa função recebe o tipo de dado que será incrementado como string e retorna o último valor de incremento válido.
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
		printf("\n\n\nTipo de incremento inválido!\\n\n\n");
}

void save_increment(char counter[30], int id){ // Essa função recebe o tipo de dado que será incrementado e o valor do incremento a ser salvo
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
		printf("\n\n\nTipo de incremento inválido!\\n\n\n");
	
	fwrite(&incremento, sizeof(INCREMENT), 1, arquivo);
	fclose(arquivo);
}

void novo_produto() { // Função que pede para o usuário as informações sobre o novo produto
	PRODUTO novoProduto;
	
	system("cls");
	
	printf("Informe a descrição do produto: ");
	fflush(stdin);
	gets(novoProduto.nome);
	
	printf("Quantidade em estoque do produto: ");
	scanf("%d", &novoProduto.estoque);
	
	novoProduto.id = get_increment("produto"); // Pega o último valor do incremento
	novoProduto.id++; // Incrementa o incremento
	
	save_produto(novoProduto); // Envia o produto para ser salvo
}

void save_produto(PRODUTO produto) { // Função que salva um produto no arquivo
	FILE *arquivo = fopen("produtos.dat", "ab"); // Abre o arquivo de produtos para append binário
	
	if(!arquivo) { // Retorna uma mensagem para o usuário caso dê problema com o arquivo
		erro_arquivo();
		return;
	}
	
	fwrite(&produto, sizeof(PRODUTO), 1, arquivo); // Escreve no arquivo o produto novo
	fclose(arquivo); // Fecha o arquivo
	save_increment("produto", produto.id); // Salva o id do último produto como valor do incremento para ser usado no próximo produto cadastrado
}

void load_produtos(PRODUTO produtos[MAX_PRODUTOS]) { // Função que carrega os produtos do arquivo para o array de PRODUTO
	FILE *arquivo = fopen("produtos.dat", "rb"); // Carrega o arquivo de produtos como leitura binária
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
	
	// Interação com menus
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

































