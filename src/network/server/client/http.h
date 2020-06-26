/*
 * Http.h
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */

#ifndef SRC_NETWORK_SERVER_CLIENT_HTTP_H_
#define SRC_NETWORK_SERVER_CLIENT_HTTP_H_

class Http {
public:
	Http();
	static void sendResponseFile(char *caminho, int connfd);
	static void sendResponse(char *resposta, char *tipo, char *caminho, int connfd, char *size);
	static void dec_string(long size, char *s);
	static long isFile(char *caminho);
	static int redirect(char *caminho);
	static int TratandoPedido(char *metodo, char *versao, char *caminho, char *p, char *tipo, int i);
	static int pedidoHTTP(char *p, char *caminho, char *tipo);
	static char *extensao(char *nome);
};

#endif /* SRC_NETWORK_SERVER_CLIENT_HTTP_H_ */
