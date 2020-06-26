/*
 * Config.cpp
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */
#include "config.h"

#include <string.h>

/*define variaveis constantes e seus respectivos valores */
#define BUFFSIZE 800
#define MAXPENDING 5

#define TYPE 16
#define TIPODATA "%a, %m %b %Y %X %Z"
#define SERVER "AS(2008-2011)"

int Config::getBUFFSIZE(){
	return BUFFSIZE;
};
int Config::getMAXPENDING(){
	return MAXPENDING;
};

char *Config::getSERVER(){
	return SERVER;
};
char *Config::getTIPODATA(){
	return TIPODATA;
};
int Config::getTYPE(){
	return TYPE;
};
