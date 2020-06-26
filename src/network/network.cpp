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




/*define variaveis constantes e seus respectivos valores */
#define BUFFSIZE 800
#define MAXPENDING 5
#define SA struct sockaddr
#define SAI struct sockaddr_in
#define TYPE 16
#define tipoData "%a, %m %b %Y %X %Z"
#define SERVER "AS(2008-2011)"

int mult(int a, int b){
	return a * b;
}

class MyServer{
  public:
	// 0 = operando, 1 = nao operando
	int status;
	// porta do servidor
	int porta;
	// Ligacao do socket
	int *listenfd;
	void setListener(int *listenRef){
		listenfd = listenRef;
	}
	bool start(){
		// Definindo o
		bool isSucesses = false;
		// tenta abrir a conexao passando o
		// espaco max de memoria que cada solicitacao
		// pode receber e o ponteiro para o socket
		if(listen(*listenfd, MAXPENDING) < 0)
			printf("Erro  ao abrir a conexao");



		return isSucesses;
	}
	void server(int *listenfd){
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
		    pthread_create(&tid, NULL, &execucao_thread, iptr);
		  }
		  return;
	}
	// Circulo de vida de cada requisicao
	static void *run(int connfd){

	}
	// FUncao que sera chamada em cada thread
	static void *execucao_thread(void *arg){
	  int connfd;

	  connfd = *((int *) arg);
	  pthread_detach(pthread_self());
	  // CHamando o codigo do circulo de vida
	  // de cada thread
	  run(connfd);
	  // Fechando a execucao
	  close(connfd);

	  return NULL;
	}
};

class network {
  public:
    int *listenfd;
    MyServer create(int porta){

    	MyServer serve;

    	listenfd = createSocket(porta);

    	serve.setListener(listenfd);

    	return serve;
    }

    int* createSocket(int porta){
		int *listenfd;
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

};




