#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAX_NOME 30
#define TAM_CPF 11
#define TAM_TELEFONE 15
#define TAM_MAX_ENDERECO 50

#define TAM_AGENCIA 20

#define MAX_CONTAS 200
#define MAX_CLIENTES 100
#define MAX_TRANSACOES 1000

/**
 * Criado por: Mateus da Silveira Batista
 * Programa para simulação de açoes bancárias como depósito,
 * criação de fixas de clientes e contas para estas.
 * Obs.: É necessário criação de cadastro de cliente no "Menu Cliente"
 * para o cadastro de uma conta para este cliente, um número de conta será
 * gerado para identificação do cliente. Um número de conta é gerado aleatóriamente para
 * o número da conta. As transações de cada conta são registradas: depósitos, saques e transferências.
**/

static int num_clientes   = 0;
static int num_contas     = 0;
static int num_transacoes = 0;

typedef struct fixa_cliente {
    int codigo;
    char nome[TAM_MAX_NOME + 1];
    char cpf[TAM_CPF + 1];
    char telefone[TAM_TELEFONE + 1];
    char endereco[TAM_MAX_ENDERECO + 1];
    struct conta* conta;
}fixa;

typedef struct transacoes {
    char tipo[12];
    int quantia;
    int dia;
    int mes;
    int ano;
    struct conta* conta;
    char descricao[101];
}transacao;

static struct transacoes transacoes[MAX_TRANSACOES];

typedef struct conta {
    char agencia[TAM_AGENCIA+1];
    int numero_conta;
    fixa* cliente;
    int saldo;
}conta;

void printlista(){
    system("cls");
    setlocale(LC_ALL,"");
    printf("\n============ Bem Vindo! ============\n");
    printf("Digite um comando para prosseguir:\n");
    printf("C - Gerenciar Clientes\n");
    printf("T - Gerenciar Contas\n");
    printf("S - Sair\n");
    printf("\nEscolha: ");
}

void menu_principal(fixa* fixa,conta * conta) {
    char opcao = '*';
    printlista();
    while(scanf("%c", &opcao)){

        switch (opcao) {
            case 'C':
                menu_gerenciar_cliente(fixa,conta);
                break;
            case 'T':
                menu_gerenciar_conta(fixa,conta);
                break;
            case 'S':
                return;
                break;
            default:
                printf("\n** Comando invalido digite C, T ou S para prosseguir **\n");
        }
        printlista();
    }
}

void printLista_Cliente(){
    system("cls");
    setlocale(LC_ALL,"");
    printf("============ Gerenciar Clientes ============\n");
    printf("Digite um comando para prosseguir:\n");
    printf("C - Cadastrar um cliente\n");
    printf("L - Listar todos os clientes cadastrados\n");
    printf("B - Buscar cliente ja cadastrado\n");
    printf("A - Atualizar um cliente cadastrado\n");
    printf("E - Excluir um cliente cadastrado\n");
    printf("S - Sair\n");
}

void menu_gerenciar_cliente(fixa* cliente, conta* conta){
    char opcao;
    printLista_Cliente();
    while(scanf("%c", &opcao)){
        switch (opcao){
            case 'C':
                Cadastro_cliente(cliente,conta);
                break;
            case 'L':
                Lista_clientes(cliente);
                break;
            case 'B':
                busca(cliente);
                break;
            case 'A':
                altera_cliente(cliente);
                break;
            case 'E':
                excluir_cliente(cliente,conta);
                break;
            case 'S':
                return;
            default:
                printf("insira um valor valido\n");
                break;
        }
        printLista_Cliente();
    }
}

void printLista_conta(){
    setlocale(LC_ALL,"");
    system("cls");
    printf("============== Gerenciar Contas ==============\n");
    printf("Digite um comando para prosseguir:\n");
    printf("R - Listagem de todas as contas cadastradas.\n");
    printf("C - Cadastrar uma conta para um cliente.\n");
    printf("L - Listar todas as contas de um cliente.\n");
    printf("W - Realizar um saque em uma conta.\n");
    printf("D - Realizar um deposito em uma conta.\n");
    printf("T - Realizar transferencia entre contas.\n");
    printf("E - Exibir extrato de uma conta.\n");
    printf("S - Sair\n");
}

 void menu_gerenciar_conta(fixa * cliente,conta * conta){
    char opcao;

    printLista_conta();
    char op;
    while(scanf("%c", &op)){
        if(op == 'R'){
            lista_contas(cliente,conta);
        }else{
        if(op == 'C'){
            cadastrar_conta(cliente,conta);
        }else{
        if(op == 'L'){
            lista_conta_cliente(cliente,conta);
        }else{
        if(op == 'W'){
            saque(cliente,conta);
        }else{
        if(op == 'D'){
            deposito(cliente,conta);
        }else{
        if(op == 'T'){
            transferencia(cliente,conta);
        }else{
        if(op == 'E'){
            extrato(cliente,conta);
        }else{
        if(op == 'S'){
            return;
        }
        }
        }
        }
        }
        }
        }
        }
        printLista_conta();
    }

 }

void Cadastro_cliente(fixa * cliente,conta* conta){
    srand(time(NULL));
    system("cls");

    setlocale(LC_ALL,"");
    char nome[TAM_MAX_NOME + 1];
    char cpf[TAM_CPF + 1];
    char telefone[TAM_TELEFONE + 1];
    char endereco[TAM_MAX_ENDERECO + 1];

    //entradas:
    getchar();
    printf("NOME: ");
    scanf("%[^\n]", nome);
    getchar();

    printf("CPF: ");
    scanf("%[^\n]", cpf);
    getchar();

    printf("TELEFONE: ");
    scanf("%[^\n]", telefone);
    getchar();

    printf("ENDERECO: ");
    scanf("%[^\n]", endereco);
    getchar();

    int i;
    for(i=0; i<num_clientes; i++){
        if(strcmp(cliente[i].cpf,cpf) == 0){
            printf("cliente ja cadastrado\n");
            getchar();
            return;
        }
    }

    int codigo = (rand()%900) + 100;
    while(search_codigo(codigo,cliente) == 1){
        codigo = (rand()%900) + 100;
    }
    strcpy(cliente[num_clientes].cpf,cpf);
    strcpy(cliente[num_clientes].endereco,endereco);
    strcpy(cliente[num_clientes].nome,nome);
    strcpy(cliente[num_clientes].telefone,telefone);
    cliente[num_clientes].codigo = codigo;
    num_clientes++;
}

int me_compare(char *me1, char *me2) {
  return strcmp(me1,me2);
}

int search_codigo(int n,fixa* cliente){
    int i;
    for(i=0; i<num_clientes; i++){
        if(n == cliente[i].codigo){
            return (1);
        }
    }
    return 0;
}

void cadastrar_conta(fixa * cliente,conta * conta) {
    char agencia[TAM_AGENCIA+1];

    srand(time(NULL));
    setlocale(LC_ALL,"");
    int indice = busca(cliente);
    if(indice < 0){
        printf("Cliente nao cadastrado\n");
        printf("**Pressione qualquer tecla pra continuar**\n");
        getchar();
        return;
    }
    printf("AGENCIA: ");
    conta[num_contas].cliente = &cliente[indice];
    scanf("%[^\n]", agencia);
    strcpy(conta[num_contas].agencia,agencia);

    conta[num_contas].saldo = 0;
    conta[num_contas].numero_conta = (rand() % 900) + 100;
    while(busca_conta_num(conta,conta[num_contas].numero_conta) == 1){
        conta[num_contas].numero_conta = (rand() % 900) + 100;
    }
    cliente[indice].conta = &conta[num_contas];
    num_contas++;
}

void Lista_clientes(fixa *cliente) {
    int i;
    system("cls");
    if(num_clientes == 0){
        printf("Nenhum cliente cadastrado\n");
        getchar();
        printf("pressione qualquer tecla para continuar\n");
        getchar();
        return;
    }
    for(i=0; i<num_clientes; i++){
        printf("Nome: %s\n", cliente[i].nome);
        printf("Codigo: %d\n\n", cliente[i].codigo);
    }
    getchar();
    printf("pressione qualquer tecla para continuar\n");
    getchar();
}

int busca_conta_num(conta * conta, int n){
    int i;
    for(i=0; i<num_contas; i++){
        if(conta[i].numero_conta == n){
            return 1;
        }
    }
    return 0;
}

int busca_conta_agencia(conta * conta, char * agencia){
    int i;
    for(i=0; i<num_contas; i++){
        if(strcmp(conta[i].agencia,agencia) == 0){
            return 1;
        }
    }
    return 0;
}

void lista_conta_cliente(fixa * cliente,conta * conta) {
    int indice = busca(cliente);
    if(indice < 0){
        printf("cliente nao cadastrado\n");
        getchar();
        getchar();
    }
    int i;
    for(i=0; i<num_contas; i++){
        if(conta[i].cliente->cpf == cliente[indice].cpf){
            printf("Agencia: %s\n", conta[i].agencia);
            printf("Codigo: %d\n", conta[i].numero_conta);
            printf("Saldo: %d\n\n", conta[i].saldo);
        }
    }
    printf("pressione qualquer tecla\n");
    getchar();
    getchar();
}

void deposito(fixa * cliente,conta * conta){
    int quantia;
    char deposito[] = "CREDITO";
    int numero;
    char agencia[TAM_AGENCIA+1];
    char descricao[100];
    int i;
    struct tm * data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);

    setlocale(LC_ALL,"");
    printf("AGENCIA: ");

    getchar();
    scanf("%[^\n]", agencia);
    printf("CONTA numero: ");

    scanf("%d", &numero);
    for(i=0; i<num_contas; i++){
        if(strcmp(conta[i].agencia,agencia) == 0 && conta[i].numero_conta == numero){
            printf("NOME: %s\n", conta[i].cliente->nome);
            printf("CPF: %s\n", conta[i].cliente->cpf);
            printf("CODIGO: %d\n", conta[i].cliente->codigo);

            printf("QUANTIA: ");
            scanf("%d", &quantia);

            printf("DESCRICAO DO DEPOSITO: ");
            getchar();
            scanf("%[^\n]", descricao);

            printf("DEPOSITO FEITO COM SUCESSO!!\n");
            printf("R$ %d << +(R$ %d)\n", conta[i].saldo, quantia);
            transacoes[num_transacoes].quantia = quantia;
            conta[i].saldo += quantia;

            strcpy(transacoes[num_transacoes].descricao,descricao);
            strcpy(transacoes[num_transacoes].tipo,deposito);
            transacoes[num_transacoes].conta = &conta[i];

            transacoes[num_transacoes].dia = data->tm_mday;
            transacoes[num_transacoes].mes = data->tm_mon+1;
            transacoes[num_transacoes].ano = data->tm_year+1900;
            printf("%d/%d/%d\n", transacoes[num_transacoes].dia, transacoes[num_transacoes].mes, transacoes[num_transacoes].ano);

            num_transacoes++;
            getchar();
            getchar();
            return;
        }
    }
}

void saque(fixa * cliente,conta * conta) {
    int quantia;
    char deposito[] = "DEBITO";
    int numero;
    char agencia[TAM_AGENCIA+1];
    char descricao[100];
    int i;
    struct tm * data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);

    setlocale(LC_ALL,"");
    printf("AGENCIA: ");

    getchar();
    scanf("%[^\n]", agencia);
    printf("CONTA numero: ");

    scanf("%d", &numero);
    for(i=0; i<num_contas; i++){
        if(strcmp(conta[i].agencia,agencia) == 0 && conta[i].numero_conta == numero){
            printf("NOME: %s\n", conta[i].cliente->nome);
            printf("CPF: %s\n", conta[i].cliente->cpf);
            printf("CODIGO: %d\n", conta[i].cliente->codigo);
            printf("%d R$\n", conta[i].saldo);

            printf("QUANTIA A SACAR: ");
            scanf("%d", &quantia);
            while(quantia > conta[i].saldo){
                printf("por favor, ensira um valor abaixo do saldo da conta\nQUANTIA A SACAR: ");
                scanf("%d", &quantia);
            }

            printf("DESCRICAO DO SAQUE: ");
            getchar();
            scanf("%[^\n]", descricao);

            printf("SAQUE FEITO COM SUCESSO!!\n");
            printf("R$ %d >> -(R$ %d)\n", conta[i].saldo, quantia);
            transacoes[num_transacoes].quantia = quantia;
            conta[i].saldo -= quantia;

            strcpy(transacoes[num_transacoes].descricao,descricao);
            strcpy(transacoes[num_transacoes].tipo,deposito);
            transacoes[num_transacoes].conta = &conta[i];

            transacoes[num_transacoes].dia = data->tm_mday;
            transacoes[num_transacoes].mes = data->tm_mon+1;
            transacoes[num_transacoes].ano = data->tm_year+1900;
            printf("%d/%d/%d\n", transacoes[num_transacoes].dia, transacoes[num_transacoes].mes, transacoes[num_transacoes].ano);

            printf(">>>SACANDO>>>\n");
            if(quantia >= 200){
                printf(">> %d notas de 200\n", quantia/200);
            }
            if(quantia%200 >= 100){
                printf(">> %d notas de 100\n", (quantia%200)/100);
            }
            if((quantia%200)%100 >= 50){
                printf(">> %d notas de 50\n", (quantia%200)%100/50);
            }
            if(((quantia%200)%100)%50 >= 20){
                printf(">> %d notas de 20\n", (((quantia%200)%100)%50)/20);
            }
            if((((quantia%200)%100)%50)%20 >= 10){
                printf(">> %d notas de 10\n", ((((quantia%200)%100)%50)%20)/10);
            }
            if(((((quantia%200)%100)%50)%20)%10 >= 5){
                printf(">> %d notas de 5\n", (((((quantia%200)%100)%50)%20)%10)/5);
            }
            if((((((quantia%200)%100)%50)%20)%10)%5 >= 2){
                printf(">> %d notas de 2\n", ((((((quantia%200)%100)%50)%20)%10)%5)/2);
            }
            num_transacoes++;
            getchar();
            getchar();
            return;
        }
    }
}

void transferencia(fixa * cliente,conta * conta){
    char buffer[] = "CREDITO";
    char buffer2[] = "DEBITO";
    char creditando[] = "Transferencia para conta : {";
    char debitando[] = "Transferencia de conta: {";
    char numero_char[5];

    int numero_conta;
    int quantia;
    int i;
    int indice;
    int indice2;

    struct tm * data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);

    setlocale(LC_ALL,"");
    char agencia[TAM_AGENCIA+1];
    int numero;
    printf("AGENCIA QUE RELIZARA TRANSFERENCIA: ");
    getchar();
    scanf("%[^\n]", agencia);
    printf("NUMERO DA CONTA QUE REALIZARA TRANSFERENCIA: ");
    scanf("%d", &numero);
    if(busca_conta_num(conta,numero) != 1 || busca_conta_agencia(conta,agencia) != 1){
        printf("CONTA NAO ENCONTRADA\n");
        getchar();
        return;
    }
    for(i=0; i<num_contas; i++){
        if(numero == conta[i].numero_conta && strcmp(conta[i].agencia,agencia) == 0){
            indice = i;
        }
    }
    printf("NOME: %s\n", conta[indice].cliente->nome);
    printf("CODIGO: %d\n", conta[indice].cliente->codigo);
    printf("SALDO: %d\n", conta[indice].saldo);

    printf("AGENCIA DA CONTA DESTINO: ");
    getchar();
    scanf("%[^\n]", agencia);

    printf("NUMERO DA CONTA DESTINO: ");
    scanf("%d", &numero);

    if(busca_conta_agencia(conta,agencia) != 1 || busca_conta_num(conta,numero) != 1){
        printf("CONTA NAO ENCONTRADA\n");
        getchar();
        return;
    }
    for(i=0; i<num_contas; i++){
        if(strcmp(conta[i].agencia,agencia) == 0 && conta[i].numero_conta == numero){
            indice2 = i;
        }
    }
    printf("NOME: %s\n", conta[indice2].cliente->nome);
    printf("CODIGO: %d\n", conta[indice2].cliente->codigo);
    printf("SALDO: %d\n", conta[indice2].saldo);

    printf("QUANTIA: ");
    scanf("%d", &quantia);
    while(quantia > conta[indice].saldo){
        printf("INSIRA UM VALOR ABAIXO DE %d:\n", conta[indice].saldo);
        scanf("%d", &quantia);
    }
    //printf("analisado\n");
    //getchar();
    conta[indice].saldo -= quantia;
    conta[indice2].saldo += quantia;

    strcpy(transacoes[num_transacoes].tipo,buffer2);
    //printf("colocado\n");
    //getchar();
    transacoes[num_transacoes].conta  = &conta[indice];
    transacoes[num_transacoes].quantia = quantia;
    //printf("linkando conta\n");
    //getchar();
    transacoes[num_transacoes].ano = data->tm_year+1900;
    transacoes[num_transacoes].mes = data->tm_mon+1;
    transacoes[num_transacoes].dia = data->tm_mday;

    //printf("datando\n");
    //getchar();
    strcpy(transacoes[num_transacoes].descricao,creditando);

    strcat(transacoes[num_transacoes].descricao,conta[indice2].agencia);
    strcat(transacoes[num_transacoes].descricao,"}-{");
    //printf("fazendo a descricao\n");
    //getchar();
    itoa(conta[indice2].numero_conta,numero_char,10);
    //printf("convertendo\n");
    //getchar();
    strcat(transacoes[num_transacoes].descricao,numero_char);
    strcat(transacoes[num_transacoes].descricao,"}");
    num_transacoes++;
    //printf("transferencia conta A feita\n");
    //getchar();

    strcpy(transacoes[num_transacoes].tipo,buffer);
    //printf("colocado\n");
    //getchar();
    transacoes[num_transacoes].conta  = &conta[indice2];
    transacoes[num_transacoes].quantia = quantia;
    //printf("linkando conta\n");
    //getchar();
    transacoes[num_transacoes].ano = data->tm_year+1900;
    transacoes[num_transacoes].mes = data->tm_mon+1;
    transacoes[num_transacoes].dia = data->tm_mday;

    //printf("datando\n");
    //getchar();
    strcpy(transacoes[num_transacoes].descricao,debitando);

    strcat(transacoes[num_transacoes].descricao,conta[indice].agencia);
    strcat(transacoes[num_transacoes].descricao,"}-{");
    //printf("fazendo a descricao\n");
    //getchar();
    itoa(conta[indice].numero_conta,numero_char,10);
    //printf("convertendo\n");
    //getchar();
    strcat(transacoes[num_transacoes].descricao,numero_char);
    strcat(transacoes[num_transacoes].descricao,"}");
    num_transacoes++;
    //printf("transferencia conta A feita\n");
    //getchar();

    return;
}

void extrato(fixa * cliente,conta * conta){
    int i;
    char buffer[] = "DEBITO";
    int numero;
    int indice = -1;

    printf("Número da CONTA: ");
    scanf("%d", &numero);
    for(i=0; i<num_contas; i++){
        if(conta[i].numero_conta == numero){
            indice = i;
        }
    }
    while(indice < 0){
        printf("nao encontrado\n");
        indice = busca(cliente);
    }
    for(i=0; i<num_transacoes; i++){
        if(transacoes[i].conta->numero_conta == conta[indice].numero_conta){
            printf("%s %d/%d/%d\n", transacoes[i].tipo, transacoes[i].dia, transacoes[i].mes, transacoes[i].ano);
            printf("%s\n", transacoes[i].descricao);
            if(strcmp(transacoes[i].tipo,buffer) == 0){
                printf("-");
            }
            else{
                printf("+");
            }
            printf("%d\n\n", transacoes[i].quantia);
        }
    }
    printf("pressione qualquer tecla para continuar\n");
    getchar();
    getchar();
}

int busca_nome(fixa * cliente){
    setlocale(LC_ALL,"");
    system("cls");
    char buffer[TAM_MAX_NOME+1];
    printf("NOME: ");
    getchar();
    scanf("%[^\n]", buffer);

    int i;
    for(i=0; i<num_clientes; i++){
        if(strcmp(cliente[i].nome,buffer) == 0){
            printf("Achado:\nNome: %s\n", cliente[i].nome);
            printf("Codigo: %d\n", cliente[i].codigo);
            getchar();
            printf("pressione qualquer tecla para continuar\n");
            getchar();
            return i;
        }
    }
    getchar();
    printf("Nao cadastrado\npressione qualquer tecla para continuar\n");
    getchar();
    return -1;
}

void  lista_contas(fixa * cliente,conta * conta){
    int i;
    if(num_contas == 0){
        printf("Sem contas cadastradas\n");
        printf("Pressione qualquer tecla pra continuar\n");
        getchar();
        getchar();
        return;
    }
    for(i=0; i<num_contas; i++){
        printf("Conta numero %d\n", conta[i].numero_conta);
        printf("Agencia: %s\n", conta[i].agencia);
        printf("Saldo: %d\n\n", conta[i].saldo);
    }
    printf("pressione qualquer tecla para continuar\n");
    getchar();
    getchar();
}

int busca_cpf_exp(fixa * cliente,int n){
    int i;
    for(i=0; i< num_clientes; i++){
        if(cliente[n].codigo == cliente[i].codigo){
            return 1;
        }
    }
    return 0;
}

int busca_cpf(fixa * cliente){
    setlocale(LC_ALL,"");
    system("cls");
    char buffer[TAM_CPF+1];
    printf("CPF: ");
    getchar();
    scanf("%[^\n]", buffer);

    int i;
    for(i=0; i<num_clientes; i++){
        if(strcmp(cliente[i].cpf,buffer) == 0){
            printf("Achado:\nNome: %s\n", cliente[i].nome);
            printf("Codigo: %d\n", cliente[i].codigo);
            getchar();
            printf("pressione qualquer tecla para continuar\n");
            getchar();
            return i;
        }
    }
    getchar();
    printf("Nao cadastrado\npressione qualquer tecla para continuar\n");
    getchar();
    return -1;
}

int busca_codigo(fixa * cliente){


    setlocale(LC_ALL,"");
    system("cls");
    int buffer;
    printf("CODIGO: ");
    getchar();
    scanf("%d", &buffer);

    int i;
    for(i=0; i<num_clientes; i++){
        if(cliente[i].codigo == buffer){
            printf("Achado:\nNome: %s\n", cliente[i].nome);
            printf("Codigo: %d\n", cliente[i].codigo);
            getchar();
            printf("pressione qualquer tecla para continuar\n");
            getchar();
            return i;
        }
    }
    getchar();
    printf("Nao cadastrado\npressione qualquer tecla para continuar\n");
    getchar();
    return -1;
}

int busca_codigo_exp(fixa * cliente,int n){
    int i;
    for(i=0; i<num_clientes; i++){
        if(n == cliente[i].codigo){
            return 1;
        }
    }
    return 0;
}

void excluir_cliente(fixa * cliente,conta * conta){
    char buffer[TAM_MAX_NOME+1];
    char op;
    int indice = busca(cliente);
    if(indice < 0){
        printf("**Cliente nao cadastrado**\n");
        printf("V - voltar ao menu\n");
        printf("R - buscar novamente\n");
        switch(op){
            case 'V':
                menu_gerenciar_cliente(cliente,conta);
                break;
            case 'R':
                excluir_cliente(cliente,conta);
                break;
            default:
                printf("valor incorreto\ninsira qualquer chave para continuar\n");
                getchar();
                menu_gerenciar_cliente(cliente,conta);
                break;
        }
    }
    int i;
    for(i=indice; i < num_clientes-1; i++){
        cliente[i].codigo = cliente[i+1].codigo;
        strcpy(cliente[i].cpf,cliente[i+1].cpf);
        strcpy(cliente[i].endereco,cliente[i+1].endereco);
        strcpy(cliente[i].nome,cliente[i+1].nome);
        strcpy(cliente[i].telefone,cliente[i+1].telefone);
    }
    printf("**EXCLUIDO**\n");
    num_clientes--;
    getchar();
}

void altera_cliente(fixa * cliente, conta * conta){
    setlocale(LC_ALL,"");
    char op = '*';

    int indice = busca(cliente);
    if(indice < 0){
        system("cls");
        printf("**Cliente nao cadastrado**\n");
        printf("V - voltar ao menu\n");
        printf("R - buscar novamente\n");
        scanf("%c", &op);
        switch(op){
            case 'V':
                return;
                //menu_gerenciar_cliente(cliente,conta);
                break;
            case 'R':
                altera_cliente(cliente,conta);
                return;
                break;
            default:
                printf("valor incorreto\ninsira qualquer chave para continuar\n");
                getchar();
                return;
                menu_gerenciar_cliente(cliente,conta);
                break;
        }
    }
    char nome[TAM_MAX_NOME+1];
    char cpf[TAM_CPF+1];
    char telefone[TAM_TELEFONE+1];
    char endereco[TAM_MAX_ENDERECO+1];

    getchar();
    printf("NOME ATUAL: %s\nATUALIZAR NOME: ", cliente[indice].nome);
    scanf("%[^\n]", nome);
    getchar();

    printf("CPF ATUAL: %s\nATUALIZAR CPF: ", cliente[indice].cpf);
    scanf("%[^\n]", cpf);
    getchar();

    printf("TELEFONE ATUAL: %s\nATUALIZAR TELEFONE: ", cliente[indice].telefone);
    scanf("%[^\n]", telefone);
    getchar();

    printf("ENDERECO ATUAL: %s\nNOVO ENDERECO: ", cliente[indice].endereco);
    scanf("%[^\n]", endereco);
    getchar();

    strcpy(cliente[indice].nome,nome);
    strcpy(cliente[indice].cpf,cpf);
    strcpy(cliente[indice].telefone,telefone);
    strcpy(cliente[indice].endereco,endereco);
}

void altera_cliente_nome(fixa * cliente, int indice){
    char buffer[TAM_MAX_NOME+1];
    //system("cls");
    printf("NOVO NOME: ");
    getchar();
    scanf("%[^\n]", buffer);

    strcpy(cliente[indice].nome,buffer);
}

void altera_cliente_endereco(fixa * cliente, int n){
    char buffer[TAM_MAX_ENDERECO+1];
    //system("cls");
    setlocale(LC_ALL,"");
    printf("NOVO ENDERECO: ");
    getchar();
    scanf("%[^\n]", buffer);

    strcpy(cliente[n].endereco,buffer);
}

void altera_cliente_telefone(fixa * cliente,int n){
    char buffer[TAM_TELEFONE+1];
    //system("cls");
    printf("NOVO TELEFONE: ");
    getchar();
    scanf("%[^\n]", buffer);

    strcpy(cliente[n].telefone,buffer);
}

void altera_cliente_cpf(fixa * cliente, int n){
    char buffer[TAM_CPF+1];
    //system("cls");
    printf("NOVO CPF: ");
    getchar();
    scanf("%[^\n]", buffer);

    strcpy(cliente[n].cpf,buffer);
}

void printLista_busca(){
    setlocale(LC_ALL,"");
    system("cls");
    printf("**BUSCA**\n");
    printf("N - Nome\n");
    printf("C - Codigo\n");
    printf("P - CPF/CNPJ\n");
}

int busca(fixa * cliente) {
    char op;
    printLista_busca();
    getchar();
    scanf("%c", &op);
        if(op == 'C'){
            busca_codigo(cliente);
            return;
        }else{
        if(op == 'N'){
            busca_nome(cliente);
            return;
        }else{
        if(op == 'P'){
            busca_cpf(cliente);
            return;
        }
        }
        }
}

void print_cliente(fixa * cliente,int n){
    setlocale(LC_ALL,"");

    printf("NOME: %s\n", cliente[n].nome);
    printf("CPF: %s\n", cliente[n].cpf);
    printf("TELEFONE: %s\n", cliente[n].telefone);
    printf("CODIGO: %d\n", cliente[n].codigo);
    printf("ENDERECO: %s\n", cliente[n].endereco);
    printf("pressione qualquer teclar para continuar\n");
}

void print_lista_altera_dados(){
        printf("==========Alterar==========\n");
        printf("N - Alterar Nome\n");
        printf("E - Alterar Endereco\n");
        printf("T - Alterar telefone\n");
        printf("C - Alterar CPF\n");
        printf("S - Voltar ao menu de gerenciar cliente\n");
}

int main(){
    fixa cliente[MAX_CLIENTES];
    conta Conta[MAX_CONTAS];
    menu_principal(&cliente,&Conta);
}

