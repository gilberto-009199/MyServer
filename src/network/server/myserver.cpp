/*
 * MyServer.cpp
 *
 *  Created on: 25 de jun de 2020
 *      Author: administrador
 */
#include "myserver.h"

#include "client/client.h"

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


#define SA struct sockaddr
#define SAI struct sockaddr_in


void MyServer::setListener(int *listenRef){
	listenfd = listenRef;
};
bool MyServer::start(){

	// Definindo o
	bool isSucesses = false;
	// tenta abrir a conexao passando o
	// espaco max de memoria que cada solicitacao
	// pode receber e o ponteiro para o socket
	if(listen(*listenfd, MAXPENDING) < 0)
		printf("Erro  ao abrir a conexao");

	MyServer::server(listenfd);
	free(listenfd);
	return isSucesses;

};
void MyServer::server(int *listenfd){
	struct sockaddr_in client; /* define um socket para o cliente */
    socklen_t clientlen;
	int *iptr;
	pthread_t tid;
	// Mantem um loop para procurar clientes
	for( ; ; ){
		iptr = (int *) malloc(sizeof(int)); /* aloca iptr para cada thread */
		*iptr = accept(*listenfd, (SA *) &client, &clientlen); /* iptr aceita a escuta do cliente */
		printf(" Pedido => %s \n", inet_ntoa(client.sin_addr)); /* imprime o endereco IP do cliente */
		/* cria uma thread */
		pthread_create(&tid, NULL, &MyServer::execucao_thread, iptr);
	}
	return;

};
// Circulo de vida de cada requisicao
void *MyServer::run(int connfd){
	printf(" @MyServer.run \n");
	Client cli(connfd);

	cli.run();

	return NULL;
};
// FUncao que sera chamada em cada thread
void *MyServer::execucao_thread(void *arg){

	printf(" @MyServer.execucao_thread \n");

	int  connfd = *((int *) arg);
	pthread_detach(pthread_self()); // @suppress("Invalid arguments")
	MyServer::run(connfd);
	close(connfd);

	return NULL;
};


