/* Inspirado em https://www.vivaolinux.com.br/script/Simples-servidor-http-com-concorrencia-feito-em-C/ */
#include <stdio.h>

// Meus modulos
#include "network/network.h";
#include "network/server/myserver.h";
#include "config/config.h";

// Minhas Constantes
#define VAL0 2
#define VAL1 3

int main(){

	MyServer server = Network::create(8080);

	server.start();

    printf(" Final da excecucao! \n");

    return 0;
}



