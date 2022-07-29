#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main(){

// >>> Início mesmos parâmetros
    char *ip ="127.0.0.1"; // (localhost)
    int port = 5432;

    int sock; 
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[16384];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sock < 0){
        perror("Erro ao definir o protocolo de rede"); 
        exit(1);
    } 
    printf("Conexão definida com sucesso.\n"); 

    memset(&addr, '\0', sizeof(addr)); // Python parâmetros
    addr.sin_family = AF_INET; 
    addr.sin_port = port;
    addr.sin_port.s_addr = inet_addr(ip);
// <<< Fim mesmos parâmetros

//Nesse caso o cliente precisa se concetar apenas com o server.

    connect(sock,(struct sockaddr*)&addr, sizeof(addr)); //Cliente efetuando a conexão com o servidor
    printf("Conexão definida com sucesso.\n");

    bzero(buffer, 16384); //Limpar o buffer, E preencher ele com zero.
    strcpy(buffer, "Bom dia, aqui quem fala é o cliente");
    printf("Cliente: %s\n*", buffer); //Imprimir a mensagem que o cliente vai enviar.
    send(sock, buffer, strlen(buffer, 0)); // variável com o comando para enviar a mensagem sevidor.

    bzero(buffer, 16384);
    recv(sock, buffer, sizeof(buffer, 0));
    printf("Server: %s\n", buffer);

//Encerrar a conexão
    close(sock);
    printf("Desconectou-se do server com sucesso!\n*");

    return 0;
}
