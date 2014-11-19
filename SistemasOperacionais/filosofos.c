#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define N 5 /* Number of philosphers */
#define DIREITA(i) (((i)+1) %N)
#define ESQUERDA(i) (((i)==N) ? 0 : (i)+1)

typedef enum { PENSANDO, COMFOME, COMENDO } estado_filosofo;
pthread_mutex_t esq,dir;
pthread_mutex_t garfo;

estado_filosofo estado[N];
semaphore mutex =1;
semaphore s[N]; /* one per philosopher, all 0 */

void test(int i) {
	if ( state[i] == HUNGRY &&
		state[LEFT(i)] != EATING &&
		state[RIGHT(i)] != EATING ) {state[i] = EATING;
		 V(s[i]);
	}
}

void get_forks(int i) {
	P(mutex);
	state[i] = HUNGRY;
	test(i);
	V(mutex);
	P(s[i]);
}

void put_forks(int i) {
	P(mutex);
	state[i]= THINKING;
	test(LEFT(i));
	test(RIGHT(i));
	V(mutex);
}


void pensa(id){
	printf("Filósofo %d pensando...\n");
}
void pega_garfos(id){
	pthread_mutex_lock(&garfo);
	estado_filosofo[i] = COMFOME;
}
void come(id){}
void devolve_garfos(id){}

void *filosofo(void *param) {
    int id = (int param)
    pensa(id);
    pega_garfos(id);
    come(id);
    devolve_garfos(id);
    pthread_exit(NULL);
}

int main(void) {
    int n;
    pthread_mutex_init(&garfo, NULL);
    printf("Quantidade de threads: ");
    scanf("%d", &n);
    pthread_t filosofos[n];
    long i;
    //cria as threads
    for (i = 0; i < n; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, (void *) i);
    }
    //força a thread principal esperar o término das outras
    for(i=0; i < n; i++){
      pthread_join( filosofos[i], NULL);
   }

    pthread_exit(NULL);
    return 0;
}



