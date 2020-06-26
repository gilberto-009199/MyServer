/*
 * MyServer.h
 *
 *  Created on: 25 de jun de 2020
 *      Author: administrador
 */

#ifndef SRC_NETWORK_SERVER_MYSERVER_H_
#define SRC_NETWORK_SERVER_MYSERVER_H_

class MyServer {
  public:
	void setListener(int *listenRef);
	bool start();
	void server(int *listenfd);
	// Circulo de vida de cada requisicao
	static void *run(int connfd);
	// FUncao que sera chamada em cada thread
	static void *execucao_thread(void *arg);
};

#endif /* SRC_NETWORK_SERVER_MYSERVER_H_ */
