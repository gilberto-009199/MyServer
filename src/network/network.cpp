#include <stdio.h>          /* printf */
#include <stdlib.h>         /* exit */
#include <string.h>         /* bzero */

#include <sys/socket.h>     /* struct sockaddr, socket, listen, bind, accept, recv, send */
#include <sys/wait.h>       /* waitpid */
#include <arpa/inet.h>      /* struct sockaddr */
#include <unistd.h>         /* exit, fork */
#include <signal.h>         /* signal */
#include <time.h>           /* TIME, time_t */
#include <pthread.h>        /* pthread_t, pthread_create */
#include <sys/stat.h>       /* lstat() */
#include <sys/types.h>      /* mode_t */


#include "network.h";
#include "server/myserver.h";


#define SA struct sockaddr
#define SAI struct sockaddr_in

//int mult(int a, int b){
//	return a * b;
//}

MyServer Network::create(int porta){

	MyServer serve;

	printf(" @Network.create \n");

	int *liste = createSocket(porta);

	serve.setListener(liste);

	return serve;
}

int* Network::createSocket(int porta){
	int *listenfd;

	printf(" @Network.createSocket \n");

	struct sockaddr_in servaddr;
	// malloc para um ponteiro de tamanho (int)
	listenfd = (int *) malloc(sizeof(int));

	if((*listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Falha ao criar o socket");

	// Chamando o bezero kkk! Para limpar a estrutura
	// passando a referencia (&servaddr) e o tamanho
	// a ser limpo (sizeof(servaddr))
	bzero(&servaddr, sizeof(servaddr));

	// Definindo configuracao
	// Pegando a CONSTATE (AF_INET) da socket.h
	// para ipv4
	servaddr.sin_family = AF_INET;
	// Definindo todos os IP's como aceitos na comunicacao
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// PORTA
	servaddr.sin_port = htons(porta);

	/* vincula um socket a um endereco */
	if(bind(*listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		printf("Erro ao vincular o socket");

	return listenfd;

}






