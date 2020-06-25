#ifndef _H_NETWORK
#define _H_NETWORK

int mult(int a, int b);
void error(char *msg); /* imprime mensagens de erro */
void sig_chld(int sinal); /* trata o sinal, para evitar filhos zumbis */
char *extensao(char *nome); /* verifica e retorna a extensao do arquivo para respota HTTP*/
int redirect(char *caminho); /* Verifica se o arquivo não sofreu uma modificação permanente*/
void respostaHTTP(char *resposta, char *tipo, char* caminho, int connfd, char *size); /* Cria uma resposta Http e envia ao cliente*/
void enviaArquivo(char *caminho, int connfd); /* Envia o arquivo solicitado ao Cliente */
long verificaArquivo(char *caminho); /* Verifica se o arquivo solicitado existe na raiz */
/* Verifica o que é pedido no protocolo Http solicitado pelo cliente*/
int TratandoPedido(char *metodo, char *versao, char *caminho, char *p, char *tipo, int i);
int pedidoHTTP(char *p, char *caminho, char *tipo);/* Manipula pedido do cliente essa função necessita da TratandoPedido */
int *criarSocket(int porta); /* Cria um socket utilizando TCP/IP */
void dec_string(long size, char *s); /* Transforma um inteiro em uma String*/
void execucao(int connfd); /* execucao da conexao com o metodo fork */
void in_fork(int *listenfd); /* metodo que utiliza o fork para execucao */
static void *execucao_thread(void *arg); /* execucao da conexao com o metodo thread */
void in_thread(int *listenfd); /* metodo que utiliza threads para execucao */

#endif
