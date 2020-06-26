/*
 * client.cpp
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */
#include <stdio.h>
#include <stddef.h>

#include <sys/socket.h>     /* struct sockaddr, socket, listen, bind, accept, recv, send */

#include "../../../config/config.h";

#include "client.h"
#include "http.h"


// Circulo de vida de cada requisicao
void Client::run(){

	printf(" @Client.run \n");
	char buffer[Config::getBUFFSIZE()], caminho[Config::getBUFFSIZE()],
		 tipo[Config::getBUFFSIZE()], sizechar[Config::getBUFFSIZE()];

	char POST[Config::getBUFFSIZE()];
	int situacao, n, i, novo;
	long size;

	// Recebendo Protocolo http do cliente
	/* recv (
			 socket			=> inteiro descrevendo o socket
			 buffer			=> Local aonde a operação devera escrever os dados recebidos
			 size_t			=> Tamanho do Local aonde os dados sera recebidos
			 flags			=>
			 	 	 	 	 	 0 => nao conectado ainda
			 	 	 	 	 	 1 => ja foi conectado ( Nao sei Realmente )
		)
	*/
	if((n = recv(connfd, buffer, Config::getBUFFSIZE(), 0)) < 0)
		printf("Falhou ao receber os dados iniciais do cliente");


	printf("%s\n", buffer);
	printf("-------------------- Resposta Servidor -------------------\n");
	situacao = Http::pedidoHTTP(buffer, caminho, tipo);

	  if(situacao == 1){
	    /*Verica se o link foi mudado, veja o arquivo htaccess.serv.*/
	    novo = Http::redirect(caminho);

	    if(strcmp(caminho, "/") == 0)
	      strcpy(caminho, "index.html");
	    else{
	      for(i = strlen(caminho); i>=0; i--)
		caminho[i+1] = caminho[i];
	      caminho[0] = '.';
	    }

	    size = Http::isFile(caminho);
	    if(size){
	    	Http::dec_string(size, sizechar);
	      if(!novo){
	    	  Http::sendResponse("HTTP/1.1 200 OK", tipo, caminho, connfd, sizechar);
	    	  Http::sendResponseFile(caminho, connfd);
	      }
	      else{
	    	  Http::sendResponse("HTTP/1.1 301 Moved Permanently", tipo, caminho, connfd, sizechar);
	    	  Http::sendResponseFile(caminho, connfd);
	      }
	    }
	    else{
	      size = Http::isFile("notfound.html");
	      Http::dec_string(size, sizechar);
	      Http::sendResponse("HTTP/1.1 404 Not Found", "html", caminho, connfd, sizechar);
	      Http::sendResponseFile("notfound.html", connfd);
	    }
	  }
	  else if(situacao == 2){
	    size = Http::isFile("notsupported.html");
	    Http::dec_string(size, sizechar);
	    Http::sendResponse("HTTP/1.1 505 HTTP Version Not Supported", "html", caminho, connfd, sizechar);
	    Http::sendResponseFile("notsupported.html", connfd);
	  }
	  else if(situacao == 3){
	    size = sizeof(tipo);
	    Http::dec_string(size, sizechar);
	    Http::sendResponse("HTTP/1.1 200 OK", "html", caminho, connfd, sizechar);
	    strcpy(POST, "<hmtl>\n<head>\n<title>Post</title>\n</head>\n<body>");
	    strcat(POST, "\n<b>Post:</b> ");
	    strcat(POST, tipo);
	    strcat(POST, "\n</body>\n</html>");
	    send(connfd, POST, sizeof(POST), 0);
	  }
	  else{
	    size = Http::isFile("badrequest.html");
	    Http::dec_string(size, sizechar);
	    Http::sendResponse("HTTP/1.1 400 Bad Request", "html", caminho, connfd, sizechar);
	    Http::sendResponseFile("badrequest.html", connfd);
	  }
	  printf("--------------------- Fim Comunicação --------------------\n\n");




	return;
};

Client::Client(int connfd) {
	this->connfd = connfd;
}
