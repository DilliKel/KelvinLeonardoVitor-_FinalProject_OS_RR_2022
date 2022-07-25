#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

// ------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>

//#include "zlib.h"

// #include <sys/socket.h>
//#include <arpa/inet.h>

int main(){

// O IP e a porta desse programa precisa ser o mesmo para o cliente e o servidor
// pois ambos estarão rodando na mesma máquina e precisam se comunicar.
// Utilizamos uma porta superior a 5000, para garantir que não haveria conflito com 
// outras portas já usadas por padrão pelo sistema.

  char *ip = "127.0.0.1";
  int port = 5566;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");

  while(1){
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");
    
    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    bzero(buffer, 1024);
    strcpy(buffer, "Olá, aqui é o Servidor. Tenha um bom dia");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

    close(client_sock);
    printf("[+]Client disconnected.\n\n");

  }

  return 0;
}
