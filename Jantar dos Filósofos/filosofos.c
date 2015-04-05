/* 
 * File:   filosofos.c
 * Author: danieljr
 *
 * Created on 20 de Novembro de 2014, 13:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5 /* Number of philosphers */
#define ESQUERDA(i) ( ((i) + N - 1) % N ) 
#define DIREITA(i) ( ((i) + 1) % N )

typedef enum { PENSANDO, COMFOME, COMENDO } estado_filosofo;
estado_filosofo estados[N];
pthread_mutex_t garfos[N];

void pensar(int i);
void obterTalherEsquerda(int i);
void obterTalherDireita(int i);
void comer(int i);
void devolverTalherEsquerda(int i);
void devolverTalherDireita(int i);
void *filosofo(void *param);
void *filosofo_diferente(void *param);

int main(void) {
    pthread_t filosofos[N];
    int i;
    //inicializa os mutexes
    for(i = 0; i < N; i++){
    	pthread_mutex_init(&garfos[i], NULL);	
    }
    //cria as threads
    for (i = 0; i < N; i++) {
    	if(i == (N-1)){
    		pthread_create(&filosofos[i], NULL, filosofo_diferente, (void *) i);
    	}else{
        	pthread_create(&filosofos[i], NULL, filosofo, (void *) i);
    	}
	}
    //força a thread principal esperar o término das outras
    for(i=0; i < N; i++){
      pthread_join( filosofos[i], NULL);
   }

    pthread_exit(NULL);
    return 0;
}

void *filosofo(void *param) {
	int i = (int) param;
   	pensar(i);
	obterTalherEsquerda(i);
	printf("Filósofo %d está com fome\n", i);
	obterTalherDireita(i);
	comer(i);
	devolverTalherEsquerda(i);
	devolverTalherDireita(i);
	printf("Filósofo %d terminou de comer\n", i);
	pthread_exit(NULL);
}

void *filosofo_diferente(void *param){
	int i = (int) param;
   	pensar(i);
	obterTalherDireita(i);
	printf("Filósofo %d está com fome\n", i);
	obterTalherEsquerda(i);
	comer(i);
	devolverTalherDireita(i);	
	devolverTalherEsquerda(i);
	printf("Filósofo %d terminou de comer\n", i);
	pthread_exit(NULL);
}

void pensar(int i){
	estados[i] = PENSANDO;
	printf("Filósofo %d está pensando...\n",i);
}

void obterTalherEsquerda(int i){
	pthread_mutex_lock(&garfos[ESQUERDA(i)]);
	estados[i] = COMFOME;
}

void obterTalherDireita(int i){
	pthread_mutex_lock(&garfos[DIREITA(i)]);
}

void comer(int i){
	estados[i] = COMENDO;
	printf("Filósofo %d está comendo\n",i);

}
void devolverTalherEsquerda(int i){
	pthread_mutex_unlock(&garfos[ESQUERDA(i)]);
}
void devolverTalherDireita(int i){
	pthread_mutex_unlock(&garfos[DIREITA(i)]);
	estados[i] = PENSANDO;	
}