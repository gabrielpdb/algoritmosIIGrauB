// Yuri Strada, Valdoir de Oliveira e Gabriel Dal Bó

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdbool.h>
#include<time.h> // Para lidar com data e hora

#define NOME_PROJETO "Gerente de produção"

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
void valor_invalido(char mensagem[40]);
void erro_arquivo();
int get_increment(char counter[30]);
void save_increment(char counter[30], int id);

void novo_produto();
void alterar_produto();
void apagar_produto();
bool print_produtos();
void print_um_produto(int id);
void save_produto(PRODUTO produto);
void update_produto(PRODUTO produto);
void delete_produto(int id);
bool check_produto_existe(int id);

void novo_pedido();
void alterar_pedido();
void apagar_pedido();
bool print_pedidos();
void print_pedido(int id);
void save_pedido(PEDIDO pedido);
void update_pedido(PEDIDO pedido);
void delete_pedido(int id);
bool check_pedido_existe(int id);
PEDIDO get_pedido_by_id(int id);


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
		printf("\n\n");
	}else {
		printf("Valor inválido, tente novamente!\n\n");	
	}
}

void erro_arquivo() {
	perror("\nErro ao abrir o arquivo");
	system("pause");
}

void printDate(tm data) {
	printf("%02d/%02d/%d", data.tm_mday, data.tm_mon + 1, data.tm_year + 1900);
}

int get_increment(char counter[30]) { // Essa função recebe o tipo de dado que será incrementado como string e retorna o último valor de incremento válido.
	INCREMENT incremento;
	
	FILE *arquivo = fopen("auto_increment.dat", "rb");
	
	if(arquivo) {
		fread(&incremento, sizeof(INCREMENT), 1, arquivo);
		fclose(arquivo);
	} else {
		incremento.ordem_producao_count = 0;
		incremento.pedido_count = 0;
		incremento.produto_count = 0;
		incremento.produto_ordem_producao_count = 0;
		incremento.produto_pedido_count = 0;
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
		
		incremento.ordem_producao_count = 0;
		incremento.pedido_count = 0;
		incremento.produto_count = 0;
		incremento.produto_ordem_producao_count = 0;
		incremento.produto_pedido_count = 0;
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

// Funções de produto

void novo_produto() { // Função que pede para o usuário as informações sobre o novo produto
	PRODUTO novoProduto;
	
	system("cls");
	
	do {
		printf("Informe o nome do produto: ");
		fflush(stdin);
		gets(novoProduto.nome);
		
		if(strlen(novoProduto.nome) <= 0) {
			valor_invalido("Nome não pode ser vazio!");
		}
	} while(strlen(novoProduto.nome) <= 0);
	
	do {
		printf("Quantidade em estoque do produto: ");
		scanf("%d", &novoProduto.estoque);
		
		if(novoProduto.estoque < 0) {
			valor_invalido("Estoque não pode ser negativo!");
		}
	}while (novoProduto.estoque < 0);
	
	novoProduto.id = get_increment("produto"); // Pega o último valor do incremento
	novoProduto.id++; // Incrementa o incremento
	
	save_produto(novoProduto); // Envia o produto para ser salvo
}

void alterar_produto() { // Função que pede para o usuário as informações para atualizar um produto
	PRODUTO produto_atualizado;
	
	if(!print_produtos()){
		return;
	}
	
	printf("\nQual o ID do produto que deseja alterar?\n");
	scanf("%d", &produto_atualizado.id);
	
	if(!check_produto_existe(produto_atualizado.id)) {
		printf("\nProduto não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
	print_um_produto(produto_atualizado.id);
	
	do {
		printf("Informe o novo nome dele: ");
		fflush(stdin);
		gets(produto_atualizado.nome);
		
		if(strlen(produto_atualizado.nome) <= 0){
			valor_invalido("Nome não pode ser vazio!");
		}	
	} while(strlen(produto_atualizado.nome) <= 0);
	
	do {
		printf("Estoque atual: ");
		scanf("%d", &produto_atualizado.estoque);
		
		if(produto_atualizado.estoque < 0) {
			valor_invalido("Estoque não pode ser negativo!");
		}
	} while(produto_atualizado.estoque < 0);
	
	update_produto(produto_atualizado);	
}

void apagar_produto() { // Função que pede para o usuário qual produto quer apagar
	int id;
	char confirm;
	
	if(!print_produtos()){
		return;
	}
	
	printf("\nQual o ID do produto que deseja apagar?\n");
	scanf("%d", &id);
	
	if(!check_produto_existe(id)) {
		printf("\nProduto não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
		
	do {
		printf("Tem certeza de que deseja excluir permanentemente o seguinte produto? (S - Sim / N - Não)\n");
		print_um_produto(id);
		confirm = toupper(getch());
		
		if(confirm != 'S' && confirm != 'N') {
			opcao_invalida();
		}
	} while (confirm != 'S' && confirm != 'N');
	
	if(confirm == 'N') {
		return;
	} else if(confirm == 'S') {
		delete_produto(id);
	}
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

bool check_produto_existe(int id) { // Retorna true se encontrar o id no arquivo, false se não encontrar
	FILE *arquivo = fopen("produtos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

void update_produto(PRODUTO produto) { // Função que atualiza um produto no arquivo
	FILE *arquivo = fopen("produtos.dat", "rb+");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PRODUTO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO), 1, arquivo)) {
		if (temp.id == produto.id) {
			fseek(arquivo, -sizeof(PRODUTO), SEEK_CUR);
			fwrite(&produto, sizeof(PRODUTO), 1, arquivo);
			achou = true;
			break;
		}
	}
	
	if(achou) {
		printf("\nProduto atualizado com sucesso!\n");
	}else {
		printf("\nProduto não encontrado!\n");
	}
	getch();
	
	fclose(arquivo);
}

void delete_produto(int id) { // Função que apaga um produto do arquivo
	FILE *arquivo = fopen("produtos.dat", "rb");
	FILE *temp = fopen("temp.dat", "wb");
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO produto;
	bool achou = false;
	
	// Lê todos os produtos do arquivo original
	while(fread(&produto, sizeof(PRODUTO), 1, arquivo)) {
		if(produto.id == id) {
			achou = true; // Marca que encontrou o produto
		} else {
			fwrite(&produto, sizeof(PRODUTO), 1, temp); // Escreve o produto no arquivo temporário
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	if(achou) {
		// Se o produto foi encontrado e excluído, renomeia o arquivo temporário para substituir o original
		if (remove("produtos.dat") == 0) {
			if (rename("temp.dat", "produtos.dat") == 0) {
				printf("\nProduto excluído com sucesso!\n");
			} else {
				erro_arquivo();
			}
		} else {
			erro_arquivo();
		}
	} else {
		// Se o produto não foi encontrado
		printf("\nProduto não encontrado!\n");
		remove("temp.dat"); // Remove o arquivo temporário caso o produto não tenha sido encontrado
	}
	
	getch();
}

bool print_produtos() { // Exibe na tela os produtos do arquivo de produtos
	int counter = 0;
	FILE *arquivo = fopen("produtos.dat", "rb");
	
	if(!arquivo){
		erro_arquivo();
		return false;
	}
	
	PRODUTO produto;
	
	system("cls");
	printf("Lista de produtos cadastrados: \n\n");

	while(fread(&produto, sizeof(PRODUTO), 1, arquivo)) {
		printf("%d: %s - %d unidades\n", produto.id, produto.nome, produto.estoque);
		counter++;
	}
	
	if(counter == 0) {
		printf("Nenhum produto encontrado!");
		getch();
		return false;
	}
	
	fclose(arquivo);
	
	return true;
}

void print_um_produto(int id) { // Exibe na tela um produto do arquivo filtrado pelo id
	FILE *arquivo = fopen("produtos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PRODUTO produto;
	
	while(fread(&produto, sizeof(PRODUTO), 1, arquivo)) {
		if(produto.id == id) {
			printf("%d: %s - %d unidades\n", produto.id, produto.nome, produto.estoque);
		}
	}
	
	fclose(arquivo);
}

// Funções de pedido

void novo_pedido() { // Função que pede para o usuário as informações sobre o novo pedido
	PEDIDO novoPedido;
	int dia, mes, ano;
	/*
		int id;
		char status[20], nome_cliente[50];
		struct tm data_entrega;
	*/
	
	system("cls");
	
	do {
		printf("Informe o nome do cliente: ");
		fflush(stdin);
		gets(novoPedido.nome_cliente);
		
		if(strlen(novoPedido.nome_cliente) <= 0) {
			valor_invalido("Nome do cliente não pode ser vazio!");
		}
	} while(strlen(novoPedido.nome_cliente) <= 0);
	
	do {
		printf("Previsão de entrega (DD/MM/AAAA): ");
		scanf("%d/%d/%d", &dia, &mes, &ano);
        
        if((dia <= 0 || dia > 31) || (mes <= 0 || mes > 12)) {
        	valor_invalido("Data inválida");
		}
		
    } while((dia <= 0 || dia > 31) || (mes < 0 || mes > 12));
    
    novoPedido.data_entrega.tm_year = ano - 1900;
    novoPedido.data_entrega.tm_mon = mes - 1;
	novoPedido.data_entrega.tm_mday = dia;
		
	strcpy(novoPedido.status, "Em produção");
	
	novoPedido.id = get_increment("pedido"); // Pega o último valor do incremento
	novoPedido.id++; // Incrementa o incremento
	
	save_pedido(novoPedido); // Envia o pedido para ser salvo;
}

void alterar_pedido() { // Função que pede para o usuário as informações para atualizar um pedido
	int dia, mes, ano;
	PEDIDO pedido_atualizado;
	
	if(!print_pedidos()){
		return;
	}
	
	printf("\nQual o ID do pedido que deseja alterar?\n");
	scanf("%d", &pedido_atualizado.id);
	
	if(!check_pedido_existe(pedido_atualizado.id)) {
		printf("\nPedido não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
	print_pedido(pedido_atualizado.id);
	
	do {
		printf("Informe o nome do cliente: ");
		fflush(stdin);
		gets(pedido_atualizado.nome_cliente);
		
		if(strlen(pedido_atualizado.nome_cliente) <= 0) {
			valor_invalido("Nome do cliente não pode ser vazio!");
		}
	} while(strlen(pedido_atualizado.nome_cliente) <= 0);
	
	do {
		printf("Previsão de entrega (DD/MM/AAAA): ");
		scanf("%d/%d/%d", &dia, &mes, &ano);
        
        if((dia <= 0 || dia > 31) || (mes <= 0 || mes > 12)) {
        	valor_invalido("Data inválida");
		}
		
    } while((dia <= 0 || dia > 31) || (mes < 0 || mes > 12));
    
    pedido_atualizado.data_entrega.tm_year = ano - 1900;
    pedido_atualizado.data_entrega.tm_mon = mes - 1;
	pedido_atualizado.data_entrega.tm_mday = dia;
	
	strcpy(pedido_atualizado.status, get_pedido_by_id(pedido_atualizado.id).status);
	
	update_pedido(pedido_atualizado);
}

void apagar_pedido() {
	int id;
	char confirm;
	
	if(!print_pedidos()) {
		
		
		return;
	}
	
	printf("\nQual o ID do pedido que deseja apagar?\n");
	scanf("%d", &id);
	
	if(!check_pedido_existe(id)) {
		printf("\nPedido não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja excluir permanentemente o seguinte produto? (S - Sim / N - Não)\n\n");
		print_pedido(id);
		printf("\n");
		confirm = toupper(getch());
		
		if(confirm != 'S' && confirm != 'N') {
			opcao_invalida();
		}
	} while (confirm != 'S' && confirm != 'N');
	
	if(confirm == 'N') {
		return;
	} else if (confirm == 'S') {
		delete_pedido(id);
	}
}

bool check_pedido_existe(int id) { // Retorna true se encontrar o id no arquivo, false se não encontrar
	FILE *arquivo = fopen("pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PEDIDO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PEDIDO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

PEDIDO get_pedido_by_id(int id) {
	FILE *arquivo = fopen("pedidos.dat", "rb");
	
	PEDIDO temp;
	
	if(!arquivo) {
		erro_arquivo();
		fclose(arquivo);
		return temp;
	}
	

	bool achou = false;
	
	while(fread(&temp, sizeof(PEDIDO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return temp;
}

void save_pedido(PEDIDO pedido) { // Função que salva o pedido no arquivo
	FILE *arquivo = fopen("pedidos.dat", "ab");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	fwrite(&pedido, sizeof(PEDIDO), 1, arquivo);
	fclose(arquivo);
	save_increment("pedido", pedido.id);
}

void delete_pedido(int id) { // Apaga o pedido do arquivo
	FILE *arquivo = fopen("pedidos.dat", "rb"); // Arquivo de pedidos
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar pedidos sem o que deve ser apagado
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PEDIDO pedido;
	bool achou = false;
	
	// Lê todos os pedidos do arquivo original
	while(fread(&pedido, sizeof(PEDIDO), 1, arquivo)) {
		if(pedido.id == id) {
			achou = true; // Encontrou o pedido, não gravou em temp
		} else {
			fwrite(&pedido, sizeof(PEDIDO), 1, temp); // Os que não tem o id de apagar são passados para temp
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	if(achou) {
		// Se o pedido foi encontrado e excluído de temp, remove pedidos.dat e renomeia temp.dat para pedidos.dat
		if (remove("pedidos.dat") == 0 && rename("temp.dat", "pedidos.dat") == 0) {
			printf("\nPedido excluído com sucesso!\n");
		} else {
			erro_arquivo();
		}
	} else {
		// Se o pedido não foi encontrado
		printf("\nPedido não encontrado!\n");
		remove("temp.dat"); // Caso o pedido não tenha sido encontrado, apaga temp.dat
	}
	
	getch();
}

void update_pedido(PEDIDO pedido) { // Função que atualiza um pedido no arquivo
	FILE *arquivo = fopen("pedidos.dat", "rb+");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PEDIDO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PEDIDO), 1, arquivo)) {
		if (temp.id == pedido.id) {
			fseek(arquivo, -sizeof(PEDIDO), SEEK_CUR);
			fwrite(&pedido, sizeof(PEDIDO), 1, arquivo);
			achou = true;
			break;
		}
	}
	
	if(achou) {
		printf("\Pedido atualizado com sucesso!\n");
	}else {
		printf("\Pedido não encontrado!\n");
	}
	getch();
	
	fclose(arquivo);
}

bool print_pedidos() { // Função que lista em tela todos os pedidos
	int counter = 0;
	FILE *arquivo = fopen("pedidos.dat", "rb");
	
	if(!arquivo){
		erro_arquivo();
		fclose(arquivo);
		return false;
	}
	
	PEDIDO pedido;
	
	system("cls");
	printf("Lista de pedidos cadastrados: \n\n");
	
	while(fread(&pedido, sizeof(PEDIDO), 1, arquivo)) {
		printf("%d: %s - ", pedido.id, pedido.nome_cliente);
		printDate(pedido.data_entrega);
		printf(" - %s\n", pedido.status);
		counter++;
	}
	
	fclose(arquivo);
	
	if(counter == 0) {
		printf("Nenhum pedido encontrado!");
		getch();
		return false;
	}
	

	
	return true;
}

void print_pedido(int id)  { // Função que exibe na tela um pedido pelo id informado
	FILE *arquivo = fopen("pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PEDIDO pedido;
	
	while(fread(&pedido, sizeof(PEDIDO), 1, arquivo)) {
		if(pedido.id == id) {
			printf("%d: %s - ", pedido.id, pedido.nome_cliente);
			printDate(pedido.data_entrega);
			printf(" - %s\n", pedido.status);
		}
	}
	
	fclose(arquivo);
}

int main (void) {
	setlocale(LC_ALL, "");
	
	int escolha_menu;
	bool isValid = true, repeat = true;
	
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
							print_produtos();
							getch();
							break;
						case 2:
							novo_produto();
							break;
						case 3: 
							alterar_produto();
							break;
						case 4:
							apagar_produto();
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
							print_produtos();
							getch();
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
							print_pedidos();
							getch();
							break;
						case 2:
							novo_pedido();
							break;
						case 3: 
							alterar_pedido();
							break;
						case 4:
							apagar_pedido();
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
