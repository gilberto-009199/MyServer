/*
 * Http.cpp
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */

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

#include "../../../config/config.h";
#include "http.h"

Http::Http() {
	// TODO Auto-generated constructor stub

}
/* Envia o arquivo solicitado ao cliente */
void Http::enviaArquivo(char *caminho, int connfd){
  FILE *file;
  long size;
  char *c;

  file = fopen(caminho, "rb");

  if(file){
    fseek(file , 0 , SEEK_END);
    size = ftell(file);
    rewind(file);
    c = (char*) malloc(sizeof(char) * size);
    fread(c, 1, size, file);
    send(connfd, c, size, 0);
    fclose(file);
    free(c);
  }
  return;
}
void Http::respostaHTTP(char *resposta, char *tipo, char *caminho, int connfd, char *size){
  time_t rawtime;
  struct tm *timeinfo, *ltime;
  struct stat arq;
  char timebuf[50], encaminhar[Config::getBUFFSIZE()], *aux, lastime[50];
  long s;

  lstat(caminho, &arq);

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  ltime = localtime(&arq.st_mtime);

  strftime(lastime, sizeof(lastime), Config::getTIPODATA(), ltime);
  strftime(timebuf, sizeof(timebuf), Config::getTIPODATA(), timeinfo);

  if(strcmp(resposta, "HTTP/1.1 200 OK") == 0){
    strcpy(encaminhar, resposta);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Connection: close\r\n");
    strcat(encaminhar, "Date: ");
    strcat(encaminhar, timebuf);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Server: ");
    strcat(encaminhar, Config::getSERVER());
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Length: ");
    strcat(encaminhar, size);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Last-Modified: ");
    strcat(encaminhar, lastime);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Type: ");
    if(strcmp(tipo, "/") == 0){
      aux = extensao("html");
      strcat(encaminhar, aux);
    }
    else{
      aux = extensao(tipo);
      if(aux != NULL)
	strcat(encaminhar, aux);
      else{
	s= verificaArquivo("badrequest.html");
	dec_string(s, size);
	respostaHTTP("HTTP/1.1 400 Bad Request", tipo, "badrequest.html", connfd, size);
	enviaArquivo("badrequest.html", connfd);
	close(connfd);
	exit(0);
      }
    }
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "\r\n");
    printf("%s\n", encaminhar);
    send(connfd, encaminhar, strlen(encaminhar), 0);
  }
  else if(strcmp(resposta, "HTTP/1.1 404 Not Found") == 0){
    strcpy(encaminhar, resposta);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Connection: close\r\n");
    strcat(encaminhar, "Date: ");
    strcat(encaminhar, timebuf);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Server: ");
    strcat(encaminhar, Config::getSERVER());
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Length: ");
    strcat(encaminhar, size);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Last-Modified: ");
    strcat(encaminhar, lastime);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Type: ");
    aux = extensao("html");
    strcat(encaminhar, aux);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "\r\n");
    printf("%s\n", encaminhar);
  }
  else if(strcmp(resposta, "HTTP/1.1 505 HTTP Version Not Supported") == 0){
    strcpy(encaminhar, resposta);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Connection: close\r\n");
    strcat(encaminhar, "Date: ");
    strcat(encaminhar, timebuf);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Server: ");
    strcat(encaminhar, Config::getSERVER());
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Length: ");
    strcat(encaminhar, size);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Last-Modified: ");
    strcat(encaminhar, lastime);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Type: ");
    aux = extensao("html");
    strcat(encaminhar, aux);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "\r\n");
    printf("%s\n", encaminhar);
  }
  else if(strcmp(resposta, "HTTP/1.1 400 Bad Request") == 0){
    strcpy(encaminhar, resposta);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Connection: close\r\n");
    strcat(encaminhar, "Date: ");
    strcat(encaminhar, timebuf);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Server: ");
    strcat(encaminhar, Config::getSERVER());
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Length: ");
    strcat(encaminhar, size);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Last-Modified: ");
    strcat(encaminhar, lastime);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Type: ");
    aux = extensao("html");
    strcat(encaminhar, aux);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "\r\n");
    printf("%s\n", encaminhar);
  }
  else if(strcmp(resposta, "HTTP/1.1 301 Moved Permanently") == 0){
    strcpy(encaminhar, resposta);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Connection: close\r\n");
    strcat(encaminhar, "Date: ");
    strcat(encaminhar, timebuf);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Server: ");
    strcat(encaminhar, Config::getSERVER());
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Length: ");
    strcat(encaminhar, size);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Location: ");
    strcat(encaminhar, caminho);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Last-Modified: ");
    strcat(encaminhar, lastime);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "Content-Type: ");
    aux = extensao("html");
    strcat(encaminhar, aux);
    strcat(encaminhar, "\r\n");
    strcat(encaminhar, "\r\n");
    printf("%s\n", encaminhar);
  }

  return;
}
void Http::dec_string(long size, char *s){
  int i, j, l;
  char aux;

  for(i = 0; size > 0; size = size/10, i++){
    s[i] = '0' + ((size%10) - 0);
  }
  s[i] = '\0';

  j = strlen(s) - 1;
  for(l = 0; l < i/2; l++, j--){
    aux = s[l];
    s[l] = s[j];
    s[j] = aux;
  }

  return;
}
long Http::verificaArquivo(char *caminho){
  FILE *file;
  long size;
  file = fopen(caminho, "rb");
  if(file){
    fseek(file , 0 , SEEK_END);
    size = ftell(file);
    rewind(file);
    fclose(file);
    return size;
  }
  else
    return 0;
}
int Http::redirect(char *caminho){
  FILE *file;
  char novo[Config::getBUFFSIZE()], antigo[Config::getBUFFSIZE()];
  file = fopen("htaccess.serv", "rb");

  if(file){
	while(!feof(file)){
	  fscanf(file, "%s %s", antigo, novo);
	  if(strcmp(antigo, caminho) == 0){
	strcpy(caminho, novo);
	return 1;
	  }
	}
	return 0;
  }
  else
	return 0;
}
int Http::TratandoPedido(char *metodo, char *versao, char *caminho, char *p, char *tipo, int i){
  char *HTTP="HTTP/1.1";
  int k;

  for(i = i+1, k = 0; p[i] != ' ' && p[i] != '\0'; i++, k++)
	  caminho[k] = p[i];
	caminho[k] = '\0';

	for(i = i+1, k = 0; p[i] != '\0' && k < 8; i++, k++)
	  versao[k] = p[i];
	versao[k] = '\0';

	if((strcmp(HTTP, versao) != 0) && (strcmp("HTTP/1.0", versao) != 0))
	  return 0;

	if(strcmp(caminho, "/") != 0){
	  for(i = strlen(caminho); p[i] != '.' && i >=0; i--);
	  for(i = i+1, k = 0; p[i] != '\0' && p[i] != ' '; i++, k++)
	tipo[k] = p[i];
	  tipo[k] = '\0';
	}
	else
	  strcpy(tipo, "/");

  return 1;
}
int Http::pedidoHTTP(char *p, char *caminho, char *tipo){

  char *GET="GET", *POST="POST", metodo[9], versao[10];
  char aux;

  int i, k, l;

  for(i = 0; p[i] != ' ' && p[i] != '\0' && i < 9; i++)
	metodo[i] = p[i];
  metodo[i] = '\0';

  if(strcmp(GET, metodo) == 0){
	if(!TratandoPedido(metodo, versao, caminho, p, tipo, i))
	  return 2;
  }
  else if(strcmp(POST, metodo) == 0){
	i = strlen(p) - 1;
	for(k = 0; p[i] != '\n'; k++, i--)
	  tipo[k] = p[i];
	tipo[k] = '\0';

	l = strlen(tipo) - 1;
	for(k = 0, i = l; k <= l/2; k++, i--){
	  aux = tipo[k];
	  tipo[k] = tipo[i];
	  tipo[i] = aux;
	}
	return 3;
  }
  else{
	return 0;
  }

  return 1;
}
char *Http::extensao(char *nome){
  char ext[20];
  strcpy(ext, ".");
  strcat(ext, nome);

  if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) return "text/html";
  if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
  if (strcmp(ext, ".gif") == 0) return "image/gif";
  if (strcmp(ext, ".png") == 0) return "image/png";
  if (strcmp(ext, ".css") == 0) return "text/css";
  if (strcmp(ext, ".au") == 0) return "audio/basic";
  if (strcmp(ext, ".wav") == 0) return "audio/wav";
  if (strcmp(ext, ".avi") == 0) return "video/x-msvideo";
  if (strcmp(ext, ".mpeg") == 0 || strcmp(ext, ".mpg") == 0) return "video/mpeg";
  if (strcmp(ext, ".mp3") == 0) return "audio/mpeg";
  if (strcmp(ext, ".js") == 0) return "text/javascript";
  if (strcmp(ext, ".ico") == 0) return "image/x-icon";

  return NULL;
}

