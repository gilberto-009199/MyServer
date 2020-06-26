/*
 * client.h
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */

#ifndef SRC_NETWORK_SERVER_CLIENT_CLIENT_H_
#define SRC_NETWORK_SERVER_CLIENT_CLIENT_H_

class Client {
public:
	Client(int connfd);
	void run();
	int connfd;
};

#endif /* SRC_NETWORK_SERVER_CLIENT_CLIENT_H_ */
