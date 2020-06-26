#ifndef _H_NETWORK
#define _H_NETWORK

#include "server/myserver.h";

//int mult(int a, int b);

class Network{
  public:
	int *listenfd;
	static MyServer create(int porta);
	static int* createSocket(int porta);
};


#endif
