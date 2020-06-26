/*
 * Config.h
 *
 *  Created on: 26 de jun de 2020
 *      Author: administrador
 */


#ifndef SRC_CONFIG_CONFIG_H_
#define SRC_CONFIG_CONFIG_H_


#include <string.h>

class Config {
public:
	static int getBUFFSIZE();
	static int getMAXPENDING();
	static char *getSERVER();
	static char *getTIPODATA();
	static int getTYPE();
};

#endif /* SRC_CONFIG_CONFIG_H_ */
