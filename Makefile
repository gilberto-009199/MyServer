# Pasta do Codigo Fonte
SRC		:= src
# Arquivos de codigo da SRC
SOURCES := $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*.h))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*.cpp))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*.h))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*.cpp))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*/*.h))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*/*.cpp))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*/*/*.h))
SOURCES += $(patsubst %.cpp,%.o,$(wildcard $(SRC)/*/*/*/*.cpp))


# DIR Sources diretorio dos codigo
SUBDIRS := config network 

all: ${SOURCES}
#	echo "Chamando o all";
	gcc -o server ${SOURCES} -Wall -pedantic -pthread 

install: 
	echo "Ainda nao criado utilize o arquivo server";

# Faz a limpeza do make
clean:
	rm -r ${SRC}/*.o
	for dir in $(SUBDIRS); do \
      echo "${SRC}/$${dir}";\
      rm -f ${SRC}/$${dir}/*.o;\
    done