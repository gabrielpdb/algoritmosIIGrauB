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
	bool finalizado;
} PRODUTO_PEDIDO;

typedef struct { // Definição da ordem de produção
	int id;
	char status[20], nome[50];
} ORDEM_PRODUCAO;

typedef struct { // Definição dos produtos que compõem uma ordem de procução
	int id, produto_id, op_id, quantidade;
	bool finalizado;
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
int menu_alterar_pedido(PEDIDO pedido);
int menu_op();
void opcao_invalida();
void valor_invalido(char mensagem[40]);
void erro_arquivo();
int get_increment(char counter[30]);
void save_increment(char counter[30], int id);

// Produtos
void novo_produto();
void alterar_produto();
void apagar_produto();
bool print_produtos();
void print_um_produto(int id);
void save_produto(PRODUTO produto);
void update_produto(PRODUTO produto, char action[20]);
void delete_produto(int id);
bool check_produto_existe(int id);
PRODUTO get_produto_by_id(int id);

// Pedidos
void novo_pedido();
void alterar_pedido();
void apagar_pedido();
bool print_pedidos(char status[20]);
void print_pedido(int id);
void save_pedido(PEDIDO pedido);
void update_pedido(PEDIDO pedido, char action[20]);
void delete_pedido(int id);
bool check_pedido_existe(int id);
PEDIDO get_pedido_by_id(int id);
void listar_pedidos(char status[20]);
void finalizar_pedido();
void end_pedido(int id);
void alterar_infos_pedido(int id);

// Produtos de pedidos
void cadastrar_produtos_pedido(int pedidoID, char nomeCliente[50]);
void save_produto_pedido(int pedidoID, int produtoID, int quantidade);
void alterar_produtos_pedido(int pedidoID);
void update_produto_pedido(PRODUTO_PEDIDO produto);
bool print_produtos_pedido(int pedidoID);
int get_quantidade_nao_finalizada_pedido_by_produto_id(int produtoID);
void delete_todos_produtos_by_pedido_id(int pedidoID);
void finaliza_todos_produtos_by_pedido_id(int pedidoID);
bool check_produto_esta_em_pedido(int produtoID);
bool check_estoque_valido_produtos_pedidos(int pedidoID);
void apagar_produto_pedido(int pedidoID);
void delete_produto_pedido(int id);
bool check_produto_pedido_existe(int id);
bool check_produto_do_pedido(int id, int pedidoID);
PRODUTO_PEDIDO get_produto_pedido_by_id(int id);
void print_produto_pedido(int id);

// Ordens de produção
void gerar_op_by_pedido_id(int pedidoID, char nomeCliente[50]);
void listar_ops(char status[20]);
bool check_op_existe(int id);
bool print_ops(char status[20]);
void print_op(int id);
ORDEM_PRODUCAO get_op_by_id(int id);
void apagar_op();
void delete_op(int id);
void finalizar_op();
void end_op(int id);
bool check_op_finalizada(int id);
void update_op(ORDEM_PRODUCAO op, char action[20]);
void nova_op();
void save_op(ORDEM_PRODUCAO op);

// Produtos de ordens de produção
void cadastrar_produtos_op(int opID, char nome[50]);
void save_produto_op(int opID, int produtoID, int quantidade);
int get_quantidade_nao_finalizada_op_by_produto_id(int produtoID);
bool print_produtos_op(int opID);
void update_produto_op(ORDEM_PRODUCAO op);
void delete_todos_produtos_by_op_id(int opID);
void finaliza_todos_produtos_by_op_id(int opID);
bool check_produto_esta_em_op(int produtoID);

// Funções

int menu_inicial() {
	int n;
	
	printf("Bem vindo ao %s!\n\n", NOME_PROJETO);
	printf("Escolha abaixo que área do sistema você deseja acessar: \n\n");
	printf("1 - Produtos\n");
	printf("2 - Pedidos\n");
	printf("3 - Ordens de produção\n\n");
	printf("0 - Sair\n");
	scanf("%d", &n);
	
	return n;
}

int menu_produtos() {
	int n;
	
	printf("%s - Produtos\n\n", NOME_PROJETO);
	printf("O que deseja fazer agora?\n\n");
	printf("1 - Listar produtos\n");
	printf("2 - Cadastrar novo produto\n");
	printf("3 - Atualizar um produto\n");
	printf("4 - Apagar um produto\n\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_pedidos() {
	int n;
	
	printf("%s - Pedidos\n\n", NOME_PROJETO);
	printf("O que deseja fazer agora?\n\n");
	printf("1 - Pedidos em produção\n");
	printf("2 - Pedidos finalizados\n");
	printf("3 - Cadastrar novo pedido\n");
	printf("4 - Atualizar um pedido\n");
	printf("5 - Apagar um pedido\n");
	printf("6 - Finalizar um pedido\n\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_alterar_pedido(PEDIDO pedido) {
	int n;
	
	printf("%s - Alterar pedido: %d - %s\n\n", NOME_PROJETO, pedido.id, pedido.nome_cliente);
	printf("O que deseja fazer agora?\n\n");
	printf("1 - Alterar informações do pedido\n");
	printf("2 - Alterar produto do pedido\n");
	printf("3 - Adicionar novo produto ao pedido\n");
	printf("4 - Apagar produto do pedido\n\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

int menu_op() {
	int n;
	
	printf("%s - Ordens de produção\n\n", NOME_PROJETO);
	printf("O que deseja fazer agora?\n\n");
	printf("1 - Ordens em produção\n");
	printf("2 - Ordens finalizadas\n");
	printf("3 - Cadastrar nova ordem de produção\n");
	printf("4 - Atualizar uma ordem de produção\n");
	printf("5 - Apagar uma ordem de produção\n");
	printf("6 - Finalizar uma ordem de produção\n\n");
	printf("0 - Voltar\n");
	scanf("%d", &n);
	
	return n;
}

void opcao_invalida() {
	system("cls");
	printf("Opção inválida, tente novamente!\n\n");
}

void valor_invalido(char mensagem[40]) {
	if(strlen(mensagem) > 0) {
		printf("\n%s\n", mensagem);
	}else {
		printf("\nValor inválido, tente novamente!\n");	
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
			system("cls");
			valor_invalido("Nome não pode ser vazio!");
		}
	} while(strlen(novoProduto.nome) <= 0);
	
	do {
		printf("Quantidade em estoque do produto: ");
		scanf("%d", &novoProduto.estoque);
		
		if(novoProduto.estoque < 0) {
			system("cls");
			valor_invalido("Estoque não pode ser negativo!");
		}
	}while (novoProduto.estoque < 0);
	
	novoProduto.id = get_increment("produto"); // Pega o último valor do incremento
	novoProduto.id++; // Incrementa o incremento
	
	save_produto(novoProduto); // Envia o produto para ser salvo
}

void alterar_produto() { // Função que pede para o usuário as informações para atualizar um produto
	PRODUTO produto_atualizado;
	
	system("cls");
	if(!print_produtos()){
		return;
	}
	
	printf("\nQual o ID do produto que deseja alterar? (0 - Voltar)\n");
	scanf("%d", &produto_atualizado.id);
	
	if(produto_atualizado.id == 0) {
		return;
	}
	
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
	
	update_produto(produto_atualizado, "");	
	getch();
}

void apagar_produto() { // Função que pede para o usuário qual produto quer apagar
	int id;
	char confirm;
	
	system("cls");
	if(!print_produtos()){
		return;
	}
	
	printf("\nQual o ID do produto que deseja apagar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_produto_existe(id)) {
		printf("\nProduto não encontrado!\n");
		getch();
		return;
	}
	
	if(check_produto_esta_em_pedido(id)) {
		printf("\nProduto está inserido em algum pedido, por isso não pode ser excluído!\n");
		getch();
		return;
	}
	
	if(check_produto_esta_em_op(id)) {
		printf("\nProduto está inserido em alguma ordem de produção, por isso não pode ser excluído!\n");
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
	getch();
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

void update_produto(PRODUTO produto, char action[20]) { // Função que atualiza um produto no arquivo
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
	
	if(achou && strcmp(action, "Finalizar") == 0) {
		
	}
	else if (achou) {
		printf("\nProduto atualizado com sucesso!\n");
	}else {
		printf("\nProduto não encontrado!\n");
	}
	
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
}

bool print_produtos() { // Exibe na tela os produtos do arquivo de produtos
	int counter = 0;
	FILE *arquivo = fopen("produtos.dat", "rb");
	
	if(!arquivo){
		erro_arquivo();
		return false;
	}
	
	PRODUTO produto;
	
	printf("Lista de produtos cadastrados: \n\n");

	while(fread(&produto, sizeof(PRODUTO), 1, arquivo)) {
		printf("%d: %s - %d unidades\n", produto.id, produto.nome, produto.estoque);
		counter++;
	}
	
	fclose(arquivo);
	
	if(counter == 0) {
		printf("Nenhum produto encontrado!");
		getch();
		return false;
	}
	
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

PRODUTO get_produto_by_id(int id) {
	FILE *arquivo = fopen("produtos.dat", "rb");
	
	PRODUTO temp;
	
	if(!arquivo) {
		erro_arquivo();
		fclose(arquivo);
		return temp;
	}
	

	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return temp;
}

// Funções de pedido

void listar_pedidos(char status[20]) {
	int pedidoID;
	
	do {
		if(!print_pedidos(status)) {
			return;
		}
		
		printf("\nQual pedido você deseja visualizar? (0 - Voltar)\n");
		scanf("%d", &pedidoID);
		
		if(!check_pedido_existe(pedidoID)) {
			valor_invalido("Informe um pedido válido!");
		} else {
			system("cls");
			print_pedido(pedidoID);
			getch();
			pedidoID = 0;
		}
		
	}while(pedidoID != 0);
	
}

void novo_pedido() { // Função que pede para o usuário as informações sobre o novo pedido
	PEDIDO novoPedido;
	int dia, mes, ano;
	
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
	
	cadastrar_produtos_pedido(novoPedido.id, novoPedido.nome_cliente);
	
	gerar_op_by_pedido_id(novoPedido.id, novoPedido.nome_cliente);
}

void alterar_pedido() { // Função que pede para o usuário as informações para atualizar um pedido
	bool isValid = true, repeat = true;
	int id;
	
	if(!print_pedidos("Todos")) {
		return;
	}
	
	printf("\nQual o ID do pedido que deseja atualizar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_pedido_existe(id)) {
		printf("\nPedido não encontrado!\n");
		getch();
		return;
	}
	
	PEDIDO pedido = get_pedido_by_id(id);
	
	do {
		system("cls");

		if(!isValid){
			opcao_invalida();
		}
		
		isValid = true;
		
		switch(menu_alterar_pedido(pedido)) {
			case 1:
				alterar_infos_pedido(pedido.id);
				break;
			case 2:
				alterar_produtos_pedido(pedido.id);
				break;
			case 3:
				cadastrar_produtos_pedido(pedido.id, pedido.nome_cliente);
				break;
			case 4: 
				apagar_produto_pedido(pedido.id);
				break;
			case 0:
				isValid = true;
				repeat = false;
				break;
			default:
				isValid = false;
		}
	} while(!isValid || repeat);
}

void alterar_infos_pedido(int id) { // Função que pede para o usuário as informações para atualizar as informações de um pedido
	int dia, mes, ano;
	PEDIDO pedido_atualizado = get_pedido_by_id(id);
	
	system("cls");
	print_pedido(id);
	
	do {
		printf("\nInforme o nome do cliente: ");
		fflush(stdin);
		gets(pedido_atualizado.nome_cliente);
		
		if(strlen(pedido_atualizado.nome_cliente) <= 0) {
			system("cls");
			valor_invalido("Nome do cliente não pode ser vazio!");
		}
	} while(strlen(pedido_atualizado.nome_cliente) <= 0);
	
	do {
		printf("Previsão de entrega (DD/MM/AAAA): ");
		scanf("%d/%d/%d", &dia, &mes, &ano);
        
        if((dia <= 0 || dia > 31) || (mes <= 0 || mes > 12)) {
        	system("cls");
        	valor_invalido("Data inválida");
		}
		
    } while((dia <= 0 || dia > 31) || (mes < 0 || mes > 12));
    
    pedido_atualizado.data_entrega.tm_year = ano - 1900;
    pedido_atualizado.data_entrega.tm_mon = mes - 1;
	pedido_atualizado.data_entrega.tm_mday = dia;
	
	strcpy(pedido_atualizado.status, get_pedido_by_id(pedido_atualizado.id).status);
	
	update_pedido(pedido_atualizado, "");
	getch();
}

void apagar_pedido() {
	int id;
	char confirm;
	
	if(!print_pedidos("Todos")) {
		return;
	}
	
	printf("\nQual o ID do pedido que deseja apagar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_pedido_existe(id)) {
		printf("\nPedido não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja excluir permanentemente o seguinte pedido? (S - Sim / N - Não)\n\n");
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
	
	delete_todos_produtos_by_pedido_id(id);
	
	getch();
}

void update_pedido(PEDIDO pedido, char action[20]) { // Função que atualiza um pedido no arquivo
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
	
	if(achou && strcmp(action, "Finalizar") == 0) {
		
	}
	else if (achou) {
		printf("\nPedido atualizado com sucesso!\n");
	}else {
		printf("\nPedido não encontrado!\n");
	}
	
	fclose(arquivo);
}

bool print_pedidos(char status[20]) { // Função que lista em tela todos os pedidos
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
		if(strcmp(pedido.status, status) == 0) {
			printf("%d: %s - ", pedido.id, pedido.nome_cliente);
			printDate(pedido.data_entrega);
			printf(" - %s\n", pedido.status);
			counter++;			
		} else if (strcmp(status, "Todos") == 0) {
			printf("%d: %s - ", pedido.id, pedido.nome_cliente);
			printDate(pedido.data_entrega);
			printf(" - %s\n", pedido.status);
			counter++;	
		}
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
	FILE *produtos = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo || !produtos) {
		erro_arquivo();
		return;
	}
	
	int counter_produtos = 0;
	PRODUTO_PEDIDO produto_pedido;
	PRODUTO produto;
	PEDIDO pedido;
	
	while(fread(&pedido, sizeof(PEDIDO), 1, arquivo)) {
		if(pedido.id == id) {
			printf("%d: %s - ", pedido.id, pedido.nome_cliente);
			printDate(pedido.data_entrega);
			printf(" - %s\n", pedido.status);
			break;
		}
	}
	
	printf("\n");
	
	while(fread(&produto_pedido, sizeof(PRODUTO_PEDIDO), 1, produtos)) {
		if(produto_pedido.pedido_id == id) {
			produto = get_produto_by_id(produto_pedido.produto_id);
			
			printf("%s: %d unidades\n", produto.nome, produto_pedido.quantidade);
			counter_produtos++;
		}
	}
	
	if(counter_produtos == 0) {
		printf("Nenhum produto encontrado!");
	}
	
	fclose(arquivo);
	fclose(produtos);
}

void finalizar_pedido() {
	int id;
	char confirm;
	
	if(!print_pedidos("Em produção")) {
		return;
	}
	
	printf("\nQual o ID do pedido que deseja finalizar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_pedido_existe(id)) {
		printf("\Pedido não encontrado!\n");
		getch();
		return;
	}
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja finalizar o seguinte pedido? (S - Sim / N - Não)\n\n");
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
		if(check_estoque_valido_produtos_pedidos(id)){
			end_pedido(id);	
		} else {
			valor_invalido("Estoque insuficiente para o pedido escolhido!");
			getch();
		}
		
	}
}

void end_pedido(int id) { // Finaliza o pedido e atualiza o estoque
	// Muda o status do pedido para Finalizado
	PEDIDO pedido = get_pedido_by_id(id);
	strcpy(pedido.status, "Finalizado");
	update_pedido(pedido, "Finalizar");
	
	finaliza_todos_produtos_by_pedido_id(id);
	
	getch();
}

// Funções de produtos de pedido

void cadastrar_produtos_pedido(int pedidoID, char nomeCliente[50]) {
	int produtoID, quantidade;
	
	do {
		system("cls");
		printf("Produtos do pedido %d - %s:\n\n", pedidoID, nomeCliente);
		
		print_produtos();
	
		printf("\nInforme o ID do produto que deseja inserir no pedido: (0 - Finalizar)\n");
		scanf("%d", &produtoID);
		
		if(produtoID == 0) {
			break;
		} else if(!check_produto_existe(produtoID)) {
			system("cls");
			valor_invalido("Produto não existe, informe um ID válido!");
		} else {
			do {
				printf("Informe a quantidade: ");
				scanf("%d", &quantidade);
				
				if(quantidade <= 0) {
					system("cls");
					valor_invalido("Informe uma quantidade válida!");
				}
			} while (quantidade <= 0);
			
			save_produto_pedido(pedidoID, produtoID, quantidade);
		}		
	} while (produtoID != 0);
}

void save_produto_pedido(int pedidoID, int produtoID, int quantidade) {
	PRODUTO_PEDIDO produto;
	produto.id = get_increment("produto_pedido");
	produto.id++;
	produto.pedido_id = pedidoID;
	produto.produto_id = produtoID;
	produto.quantidade = quantidade;
	produto.finalizado = false;
	
	FILE *arquivo = fopen("produtos_pedidos.dat", "ab");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	fwrite(&produto, sizeof (PRODUTO_PEDIDO), 1, arquivo);
	fclose(arquivo);
	save_increment("produto_pedido", produto.id);
}

void alterar_produtos_pedido(int pedidoID) {
	PRODUTO_PEDIDO produto;
	int id;
	bool valido = true;
	
	system("cls");
	
	do {
		valido = true;
			
		if(!print_produtos_pedido(pedidoID)){
			return;
		}
			
		printf("\nQual o ID do produto que deseja alterar? (0 - Voltar)\n");
		scanf("%d", &id);
		
		if(id == 0) {
			return;
		}
		
		if(!check_produto_pedido_existe(id) || !check_produto_do_pedido(id, pedidoID)) {
			system("cls");
			valor_invalido("Produto inválido!");
			valido = false;
		} else {
			produto = get_produto_pedido_by_id(id);
		}
		
	} while (!valido);
	
	do {
		system("cls");
		print_produto_pedido(produto.id);
		
		printf("\n\nInforme a quantidade atualizada: ");
		scanf("%d", &produto.quantidade);
		
		if(produto.quantidade <= 0) {
			system("cls");
			valor_invalido("Informe uma quantidade válida!");
		}
	} while (produto.quantidade <= 0);
	
	update_produto_pedido(produto);
}

bool check_produto_pedido_existe(int id) { // Retorna true se encontrar o id no arquivo, false se não encontrar
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO_PEDIDO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

bool check_produto_do_pedido(int id, int pedidoID) { // Retorna true se o id pertence ao pedido, false se não
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO_PEDIDO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.id == id && temp.pedido_id == pedidoID) {
			achou = true;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

PRODUTO_PEDIDO get_produto_pedido_by_id(int id) {
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	PRODUTO_PEDIDO temp;
	
	if(!arquivo) {
		erro_arquivo();
		return temp;
	}

	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return temp;
}

void update_produto_pedido(PRODUTO_PEDIDO produto) { // Função que atualiza o produto de um pedido no arquivo
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb+");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_PEDIDO temp;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if (temp.id == produto.id) {
			fseek(arquivo, -sizeof(PRODUTO_PEDIDO), SEEK_CUR);
			fwrite(&produto, sizeof(PRODUTO_PEDIDO), 1, arquivo);
			break;
		}
	}
	
	fclose(arquivo);
}

bool print_produtos_pedido(int pedidoID) {
	int counter = 0;
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	PEDIDO pedido = get_pedido_by_id(pedidoID);
	
	if(!arquivo){
		erro_arquivo();
		fclose(arquivo);
		return false;
	}
	
	PRODUTO_PEDIDO temp;
	
	printf("Produtos do pedido %d - %s:\n\n", pedido.id, pedido.nome_cliente);
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.pedido_id == pedidoID) {
			PRODUTO produto = get_produto_by_id(temp.produto_id);
			printf("%d: %s - %d unidades\n", temp.id, produto.nome, temp.quantidade);
			counter++;
		}
	}
	
	fclose(arquivo);
	
	if(counter == 0) {
		printf("Nenhum produto encontrado!");
		getch();
		return false;
	}
	
	return true;
}

void print_produto_pedido(int id)  { // Função que exibe na tela um produto do pedido pelo id informado
	FILE *produtos = fopen("produtos_pedidos.dat", "rb");
	
	if(!produtos) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_PEDIDO temp;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, produtos)) {
		if(temp.id == id) {
			PRODUTO produto = get_produto_by_id(temp.produto_id);
			printf("%d: %s - %d unidades", temp.id, produto.nome, temp.quantidade);
			break;
		}
	}
	
	fclose(produtos);
}

int get_quantidade_nao_finalizada_pedido_by_produto_id(int produtoID) {
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo) {
		return 0;
	}
	
	int quantidade = 0;
	PRODUTO_PEDIDO temp;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.produto_id == produtoID && temp.finalizado == false) {
			quantidade = quantidade + temp.quantidade;
		}
	}
	
	fclose(arquivo);
	
	return quantidade;
}

void delete_todos_produtos_by_pedido_id(int pedidoID) {
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb"); // Arquivo de produtos em pedidos
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar produtos que não devem ser apagados
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_PEDIDO produto;
	
	// Lê todos os pedidos do arquivo original
	while(fread(&produto, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(produto.pedido_id != pedidoID) {
			fwrite(&produto, sizeof(PRODUTO_PEDIDO), 1, temp); // Os que não tem o id de apagar são passados para temp
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	// Remove produtos_pedidos.dat e renomeia temp.dat para produtos_pedidos.dat
	if (remove("produtos_pedidos.dat") == 0 && rename("temp.dat", "produtos_pedidos.dat") == 0) {
	} else {
		erro_arquivo();
	}
	
	getch();
}

void finaliza_todos_produtos_by_pedido_id(int pedidoID) {
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb"); // Arquivo de produtos em pedidos
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar produtos atualizados
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_PEDIDO produto;
	
	// Lê todos os pedidos do arquivo original
	while(fread(&produto, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(produto.pedido_id == pedidoID) {
			// Atualiza o estoque do produto com a quantidade do pedido
			PRODUTO produto_estoque = get_produto_by_id(produto.produto_id);
			produto_estoque.estoque = produto_estoque.estoque - produto.quantidade;
			update_produto(produto_estoque, "Finalizar");
			
			produto.finalizado = true; // Finaliza os produtos do pedido
		}
		fwrite(&produto, sizeof(PRODUTO_PEDIDO), 1, temp); // Salva em temp todos os produtos
	}
	
	fclose(arquivo);
	fclose(temp);
	
	// Remove produtos_pedidos.dat e renomeia temp.dat para produtos_pedidos.dat
	if (remove("produtos_pedidos.dat") == 0 && rename("temp.dat", "produtos_pedidos.dat") == 0) {
	} else {
		erro_arquivo();
	}
	
	getch();
}

bool check_produto_esta_em_pedido(int produtoID) { // Retorna true se o produto estiver relacionado em algum pedido
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO_PEDIDO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(temp.produto_id == produtoID) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

bool check_estoque_valido_produtos_pedidos(int pedidoID) {
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO_PEDIDO temp;
	
	while(fread(&temp, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		PRODUTO produto = get_produto_by_id(temp.produto_id);
		if(produto.estoque < temp.quantidade) {
			return false;
		}
	}
	
	
	fclose(arquivo);
	
	return true;
}

void apagar_produto_pedido(int pedidoID) {
	char confirm;
	
	int id;
	bool valido = true;
	
	system("cls");
	
	do {
		valido = true;
			
		if(!print_produtos_pedido(pedidoID)){
			return;
		}
			
		printf("\nQual o ID do produto que deseja apagar do pedido? (0 - Voltar)\n");
		scanf("%d", &id);
		
		if(id == 0) {
			return;
		}
		
		if(!check_produto_pedido_existe(id) || !check_produto_do_pedido(id, pedidoID)) {
			valor_invalido("Produto inválido!");
			valido = false;
		}
		
	} while (!valido);
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja excluir permanentemente o seguinte produto? (S - Sim / N - Não)\n\n");
		print_produto_pedido(id);
		printf("\n");
		confirm = toupper(getch());
		
		if(confirm != 'S' && confirm != 'N') {
			opcao_invalida();
		}
	} while (confirm != 'S' && confirm != 'N');
	
	if(confirm == 'N') {
		return;
	} else if (confirm == 'S') {
		delete_produto_pedido(id);
	}
}

void delete_produto_pedido(int id) { // Apaga o produto de pedido do arquivo
	FILE *arquivo = fopen("produtos_pedidos.dat", "rb"); // Arquivo de produtos de pedidos
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para grava os produtos de pedidos sem o que deve ser apagado
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_PEDIDO produto;
	bool achou = false;
	
	// Lê todos os produtos do arquivo original
	while(fread(&produto, sizeof(PRODUTO_PEDIDO), 1, arquivo)) {
		if(produto.id == id) {
			achou = true; // Encontrou o produto, não gravou em temp
		} else {
			fwrite(&produto, sizeof(PRODUTO_PEDIDO), 1, temp); // Os que não tem o id de apagar são passados para temp
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	if(achou) {
		// Se o pedido foi encontrado e excluído de temp, remove pedidos.dat e renomeia temp.dat para pedidos.dat
		if (remove("produtos_pedidos.dat") == 0 && rename("temp.dat", "produtos_pedidos.dat") == 0) {
			printf("\nProduto excluído com sucesso!\n");
		} else {
			erro_arquivo();
		}
	} else {
		// Se o produto não foi encontrado
		printf("\nProduto não encontrado!\n");
		remove("temp.dat"); // Caso o produto não tenha sido encontrado, apaga temp.dat
	}
	
	getch();
}

// Funções de ordem de produção

void gerar_op_by_pedido_id(int pedidoID, char nomeCliente[50]) {
	int counter = 0;
	FILE *produtos_pedidos = fopen("produtos_pedidos.dat", "rb");
	
	if(!produtos_pedidos) {
		erro_arquivo();
		return;
	}
	
	ORDEM_PRODUCAO nova_op;
	
	nova_op.id = get_increment("ordem_producao");
	nova_op.id++;
	strcpy(nova_op.status, "Em produção");
	sprintf(nova_op.nome, "%s(%d)", nomeCliente, pedidoID);
	
	PRODUTO_PEDIDO temp_produto_pedido;
	
	while(fread(&temp_produto_pedido, sizeof(PRODUTO_PEDIDO), 1, produtos_pedidos)) {
		if(temp_produto_pedido.pedido_id == pedidoID) {
			int estoque = get_produto_by_id(temp_produto_pedido.produto_id).estoque;
			int ops = get_quantidade_nao_finalizada_op_by_produto_id(temp_produto_pedido.produto_id);
			int pedidos = get_quantidade_nao_finalizada_pedido_by_produto_id(temp_produto_pedido.produto_id);
			int quantidade = pedidos - estoque - ops;
			if(quantidade > 0) {
				save_produto_op(nova_op.id, temp_produto_pedido.produto_id, quantidade);
				counter++;
			}
			
		}
	}
	
	if(counter > 0) {
		save_op(nova_op);
	}
	
	fclose(produtos_pedidos);
	getch();
	return;
}

void nova_op() { // Função que pede para o usuário as informações sobre a nova ordem de produção
	ORDEM_PRODUCAO novaOp;
	
	system("cls");
	
	do {
		printf("Informe o nome da ordem de produção: ");
		fflush(stdin);
		gets(novaOp.nome);
		
		if(strlen(novaOp.nome) <= 0) {
			valor_invalido("Nome da ordem de produção não pode ser vazio!");
		}
	} while(strlen(novaOp.nome) <= 0);
		
	strcpy(novaOp.status, "Em produção");
	
	novaOp.id = get_increment("ordem_producao"); // Pega o último valor do incremento
	novaOp.id++; // Incrementa o incremento
	
	save_op(novaOp); // Envia a ordem para ser salva
	
	cadastrar_produtos_op(novaOp.id, novaOp.nome);
}

void save_op(ORDEM_PRODUCAO op) { // Função que salva a ordem de produção no arquivo
	FILE *arquivo = fopen("ordens_producao.dat", "ab");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	fwrite(&op, sizeof(ORDEM_PRODUCAO), 1, arquivo);
	fclose(arquivo);
	save_increment("ordem_producao", op.id);
}

void listar_ops(char status[20]) {
	int opID;
	
	do {
		if(!print_ops(status)) {
			return;
		}
		
		printf("\nQual ordem de produção deseja visualizar? (0 - Voltar)\n");
		scanf("%d", &opID);
		
		if(opID == 0) {
			return;
		}
		
		if(!check_op_existe(opID)) {
			system("cls");
			valor_invalido("Informe uma ordem de produção válida!");
		} else {
			system("cls");
			print_op(opID);
			getch();
			opID = 0;
		}
	} while (opID != 0);
}

bool check_op_existe(int id) {
	FILE *arquivo = fopen("ordens_producao.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	ORDEM_PRODUCAO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

bool check_op_finalizada(int id) {
	FILE *arquivo = fopen("ordens_producao.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	ORDEM_PRODUCAO temp;
	
	while(fread(&temp, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.id == id && strcmp("Finalizada", temp.status) == 0) {
			printf("%s", temp.status);
			return true;
		}
	}
	
	fclose(arquivo);
	
	return false;
}

bool print_ops(char status[20]) { // Função que lista em tela todas as ordens de produção
	int counter = 0;
	FILE *arquivo = fopen("ordens_producao.dat", "rb");
	
	if(!arquivo){
		erro_arquivo();
		fclose(arquivo);
		return false;
	}
	
	ORDEM_PRODUCAO op;
	
	system("cls");
	printf("Lista de ordens de produção cadastradas: \n\n");
	
	while(fread(&op, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(strcmp(status, op.status) ==0) {
			printf("%d: %s - %s\n", op.id, op.nome, op.status);
			counter++;
		} else if (strcmp(status, "Todas") == 0) {
			printf("%d: %s - %s\n", op.id, op.nome, op.status);
			counter++;
		}
	}
	
	fclose(arquivo);
	
	if(counter == 0) {
		printf("Nenhuma ordem de produção encontrada!");
		getch();
		return false;
	}
	
	return true;
}

void print_op(int id)  { // Função que exibe na tela uma ordem de produção pelo id informado
	FILE *arquivo = fopen("ordens_producao.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	ORDEM_PRODUCAO op;
	
	while(fread(&op, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(op.id == id) {
			printf("%d: %s - %s\n", op.id, op.nome, op.status);
			break;
		}
	}
	
	fclose(arquivo);
	
	printf("\n");

	print_produtos_op(id);
}

ORDEM_PRODUCAO get_op_by_id(int id) {
	FILE *arquivo = fopen("ordens_producao.dat", "rb");
	
	ORDEM_PRODUCAO temp;
	
	if(!arquivo) {
		erro_arquivo();
		fclose(arquivo);
		return temp;
	}
	

	bool achou = false;
	
	while(fread(&temp, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.id == id) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return temp;
}

void update_op(ORDEM_PRODUCAO op, char action[20]) { // Função que atualiza uma ordem no arquivo
	FILE *arquivo = fopen("ordens_producao.dat", "rb+");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	ORDEM_PRODUCAO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if (temp.id == op.id) {
			fseek(arquivo, -sizeof(ORDEM_PRODUCAO), SEEK_CUR);
			fwrite(&op, sizeof(ORDEM_PRODUCAO), 1, arquivo);
			achou = true;
			break;
		}
	}
	
	if(achou && strcmp("Finalizar", action) == 0) {
		printf("\nOrdem de produção finalizada com sucesso!\n");
	} else if (achou) {
		printf("\nOrdem de produção atualizada com sucesso!\n");
	} else {
		printf("\nOrdem de produção não encontrada!\n");
	}
	getch();
	
	fclose(arquivo);
}

void apagar_op() {
	int id;
	char confirm;
	
	if(!print_ops("Todas")) {
		return;
	}
	
	printf("\nQual o ID da ordem de produção que deseja apagar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_op_existe(id)) {
		printf("\Ordem de produção não encontrada!\n");
		getch();
		return;
	}
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja excluir permanentemente a seguinte ordem de produção? (S - Sim / N - Não)\n\n");
		print_op(id);
		printf("\n");
		confirm = toupper(getch());
		
		if(confirm != 'S' && confirm != 'N') {
			opcao_invalida();
		}
	} while (confirm != 'S' && confirm != 'N');
	
	if(confirm == 'N') {
		return;
	} else if (confirm == 'S') {
		delete_op(id);
	}
}

void delete_op(int id) { // Apaga a ordem de produção do arquivo
	FILE *arquivo = fopen("ordens_producao.dat", "rb"); // Arquivo de ordens de produção
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar pedidos sem o que deve ser apagado
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	ORDEM_PRODUCAO op;
	bool achou = false;
	
	// Lê todas as ordens do arquivo original
	while(fread(&op, sizeof(ORDEM_PRODUCAO), 1, arquivo)) {
		if(op.id == id) {
			achou = true; // Encontrou a ordem, não gravou em temp
		} else {
			fwrite(&op, sizeof(ORDEM_PRODUCAO), 1, temp); // Os que não tem o id de apagar são passados para temp
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	if(achou) {
		// Se a ordem foi encontrada e excluída de temp, remove ordens_producao.dat e renomeia temp.dat para ordens_producao.dat
		if (remove("ordens_producao.dat") == 0 && rename("temp.dat", "ordens_producao.dat") == 0) {
			printf("\Ordem de produção excluída com sucesso!\n");
		} else {
			erro_arquivo();
		}
	} else {
		// Se a ordem não foi encontrado
		printf("\Ordem de produção não encontrada!\n");
		remove("temp.dat"); // Caso a ordem não tenha sido encontrada, apaga temp.dat
	}
	
	delete_todos_produtos_by_op_id(id);
	
	getch();
}

void finalizar_op() {
	int id;
	char confirm;
	
	if(!print_ops("Em produção")) {
		return;
	}
	
	printf("\nQual o ID da ordem de produção que deseja finalizar? (0 - Voltar)\n");
	scanf("%d", &id);
	
	if(id == 0) {
		return;
	}
	
	if(!check_op_existe(id)) {
		printf("\Ordem de produção não encontrada!\n");
		getch();
		return;
	}
	
	if(check_op_finalizada(id)) {
		printf("\Ordem de produção já finalizada!\n");
		getch();
		return;
	}
	
	system("cls");
	
	do {
		printf("Tem certeza de que deseja finalizar a seguinte ordem de produção? (S - Sim / N - Não)\n\n");
		print_op(id);
		printf("\n");
		confirm = toupper(getch());
		
		if(confirm != 'S' && confirm != 'N') {
			opcao_invalida();
		}
	} while (confirm != 'S' && confirm != 'N');
	
	if(confirm == 'N') {
		return;
	} else if (confirm == 'S') {
		end_op(id);
	}
}

void end_op(int id) { // Finaliza a ordem de produção e atualiza o estoque
	// Muda o status da ordem para Finalizada
	ORDEM_PRODUCAO op = get_op_by_id(id);
	strcpy(op.status, "Finalizada");
	update_op(op, "Finalizar");
	
	finaliza_todos_produtos_by_op_id(id);
	
	getch();
}

// Funções de produtos de ordem de produção

void cadastrar_produtos_op(int opID, char nome[50]) {
	int produtoID, quantidade;
	
	do {
		system("cls");
		printf("Produtos da ordem %d - %s:\n\n", opID, nome);
		
		print_produtos();
	
		printf("\nInforme o ID do produto que deseja inserir na ordem: (0 - Finalizar)\n");
		scanf("%d", &produtoID);
		
		if(produtoID == 0) {
			break;
		} else if(!check_produto_existe(produtoID)) {
			system("cls");
			valor_invalido("Produto não existe, informe um ID válido!");
		} else {
			do {
				printf("Informe a quantidade: ");
				scanf("%d", &quantidade);
				
				if(quantidade <= 0) {
					system("cls");
					valor_invalido("Informe uma quantidade válida!");
				}
			} while (quantidade <= 0);
			
			save_produto_op(opID, produtoID, quantidade);
		}		
	} while (produtoID != 0);
}

void save_produto_op(int opID, int produtoID, int quantidade) {
	PRODUTO_ORDEM_PRODUCAO produto;
	
	produto.finalizado = false;
	produto.id = get_increment("produto_ordem_producao");
	produto.id++;
	produto.op_id = opID;
	produto.produto_id = produtoID;
	produto.quantidade = quantidade;
	
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "ab");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	fwrite(&produto, sizeof (PRODUTO_ORDEM_PRODUCAO), 1, arquivo);
	fclose(arquivo);
	save_increment("produto_ordem_producao", produto.id);
}

int get_quantidade_nao_finalizada_op_by_produto_id(int produtoID) {
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb");
	
	if(!arquivo) {
		return 0;
	}
	
	int quantidade = 0;
	PRODUTO_ORDEM_PRODUCAO temp;
	
	while(fread(&temp, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.produto_id == produtoID && temp.finalizado == false) {
			quantidade = quantidade + temp.quantidade;
		}
	}
	
	fclose(arquivo);
	
	return quantidade;
}

bool print_produtos_op(int opID) {
	int counter = 0;
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb");
	ORDEM_PRODUCAO op = get_op_by_id(opID);
	
	if(!arquivo){
		erro_arquivo();
		fclose(arquivo);
		return false;
	}
	
	PRODUTO_ORDEM_PRODUCAO temp;
	
	while(fread(&temp, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.op_id == opID) {
			PRODUTO produto = get_produto_by_id(temp.produto_id);
			printf("%s: %d unidades\n", produto.nome, temp.quantidade);
			counter++;
		}
	}
	
	fclose(arquivo);
	
	if(counter == 0) {
		printf("Nenhum produto encontrado!");
		getch();
		return false;
	}
	
	return true;
}

void update_produto_op(ORDEM_PRODUCAO op) { // Função que atualiza um produto da ordem no arquivo
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb+");
	
	if(!arquivo) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_ORDEM_PRODUCAO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if (temp.id == op.id) {
			fseek(arquivo, -sizeof(PRODUTO_ORDEM_PRODUCAO), SEEK_CUR);
			fwrite(&op, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo);
			achou = true;
			break;
		}
	}
	
	if(achou) {
		printf("\Produto atualizado com sucesso!\n");
	}else {
		printf("\Produto não encontrado!\n");
	}
	
	fclose(arquivo);
}

void delete_todos_produtos_by_op_id(int opID) {
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb"); // Arquivo de produtos em op
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar produtos que não devem ser apagados
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_ORDEM_PRODUCAO produto;
	
	// Lê todos os pedidos do arquivo original
	while(fread(&produto, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if(produto.op_id != opID) {
			fwrite(&produto, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, temp); // Os que não tem o id de apagar são passados para temp
		}
	}
	
	fclose(arquivo);
	fclose(temp);
	
	// Remove produtos_ordens_producao.dat e renomeia temp.dat para produtos_ordens_producao.dat
	if (remove("produtos_ordens_producao.dat") == 0 && rename("temp.dat", "produtos_ordens_producao.dat") == 0) {
	} else {
		erro_arquivo();
	}
	
	getch();
}

void finaliza_todos_produtos_by_op_id(int opID) {
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb"); // Arquivo de produtos em op
	FILE *temp = fopen("temp.dat", "wb"); // Arquivo temporário para gravar produtos atualizados
	
	if(!arquivo || !temp) {
		erro_arquivo();
		return;
	}
	
	PRODUTO_ORDEM_PRODUCAO produto;
	
	// Lê todos os pedidos do arquivo original
	while(fread(&produto, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if(produto.op_id == opID) {
			// Atualiza o estoque do produto com a quantidade da op
			PRODUTO produto_estoque = get_produto_by_id(produto.produto_id);
			produto_estoque.estoque = produto_estoque.estoque + produto.quantidade;
			update_produto(produto_estoque, "Finalizar");
			
			produto.finalizado = true; // Finaliza os produtos da ordem em questão
		}
		fwrite(&produto, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, temp); // Salva em temp todos os produtos
	}
	
	fclose(arquivo);
	fclose(temp);
	
	// Remove produtos_ordens_producao.dat e renomeia temp.dat para produtos_ordens_producao.dat
	if (remove("produtos_ordens_producao.dat") == 0 && rename("temp.dat", "produtos_ordens_producao.dat") == 0) {
	} else {
		erro_arquivo();
	}
	
	getch();
}

bool check_produto_esta_em_op(int produtoID) { // Retorna true se o produto estiver relacionado em alguma ordem de produção
	FILE *arquivo = fopen("produtos_ordens_producao.dat", "rb");
	
	if(!arquivo) {
		erro_arquivo();
		return false;
	}
	
	PRODUTO_ORDEM_PRODUCAO temp;
	bool achou = false;
	
	while(fread(&temp, sizeof(PRODUTO_ORDEM_PRODUCAO), 1, arquivo)) {
		if(temp.produto_id == produtoID) {
			achou = true;
			break;
		}
	}
	
	fclose(arquivo);
	
	return achou;
}

// MAIN

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
							system("cls");
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
					
					switch(menu_pedidos()) {
						case 1:
							listar_pedidos("Em produção");
							break;
						case 2:
							listar_pedidos("Finalizado");
							break;
						case 3:
							novo_pedido();
							break;
						case 4: 
							alterar_pedido();
							break;
						case 5:
							apagar_pedido();
							break;
						case 6:
							finalizar_pedido();
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
					
					switch(menu_op()) {
						case 1:
							listar_ops("Em produção");
							break;
						case 2:
							listar_ops("Finalizada");
							break;
						case 3: 
							nova_op();
							break;
						case 4:
							//alterar_op();
							break;
						case 5:
							apagar_op();
							break;
						case 6:
							finalizar_op();
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
	printf("Obrigado por usar o %s!!!", NOME_PROJETO);

	return 0;
}
