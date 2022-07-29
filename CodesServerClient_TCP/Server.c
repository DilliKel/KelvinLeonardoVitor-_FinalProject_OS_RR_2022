#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>  
#include <sys/socket.h> // define a estrutura sockaddr / binding
#include <sys/types.h> // Armazena o sizeMax
#include <netinet/in.h>  // define a estrutura in_addr
#include <arpa/inet.h> // Veículo da chamada <netinet/in.h> 

int main(){

    char *ip ="127.0.0.1"; // Tudo oq vc mandar pra cá, volta pra vc mesmo. (localhost)
    int port = 5432; // TCP	PostgreSQL.

    int server_sock, client_sock; // Definindo as variáveis do servidor de do cliente.
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[16384];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0); // Declarando o server.
    if (server_sock < 0){
        perror("Erro ao definir o protocolo de rede"); // Imprimir uma mensagem caso ocarra um erro.
        exit(1);
    } //Se o acesso ao servidor for menor que 0 então vamos encerrar o programa.
    printf("Conexão definida com sucesso"); 
    // Se não ocorrer erros, vai imprimir uma mensagem de sucesso ao estabelecer conexão com o socket.

    memset(&server_addr, '\0', sizeof(server_addr)); // Python parâmetros
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = port; // Refere-se a porta que foi declarada na main
    server_addr.sin_port.s_addr = inet_addr(ip); // Refere-se ao IP que foi declarado na main

// Vincular o endereço de IP à porta do socket. 
// Bind é define qual porta vamos usar, e qual socket estamos usando.
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0){
        perror("Erro ao acessar o socket"); // Error in binding
        exit(1);  // Caso não consiga acessar a porta, retorna erro, e encerra a conexão.
    }
    printf("Conexão com a porta efetuada com sucesso %d\n"); 
    // Se não ocorrer erros, vai imprimir uma mensagem de sucesso ao estabelecer conexão com o socket.

    // Identificar o cliente
    listen(server_sock, 5);
    printf("Aguardando resposta do cliente...\n");

    // Loop para aceitar conexão do cliente. 
    // Vai rodar por tempo finito.
    while(1){
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr &addr_size);
        printf("Cliente conectado com sucesso \n");
    }

//Cliente envia mensagem
    bzero(buffer, 16384); //Limpar o buffer, E preencher ele com zero.
    recv(client_sock, buffer, sizeof(buffer, 0)); //Função com o parâmetro de mensagem recebida??????
    printf("Cliente: %s\n", buffer); //Imprimir a mensagem que o cliente vai enviar.

//Servidor responde a mensagem do cliente.
    bzero(buffer, 16384);
    strcpy(buffer, "Bom dia, aqui é o servidor. ");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer, 0)); // Limpar o buffer

//Encerrar a conexão
    close(client_sock);
    printf("O cliente desconectou-se. \n\n"); // encerra a conexão e retorna para o while.

    return 0;
}
