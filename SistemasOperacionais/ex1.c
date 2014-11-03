/* 
 * File:   ex1.c
 * Author: danieljr
 *
 * Created on 3 de Novembro de 2014, 10:10
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *run(void *param) {
    pthread_t thread;
    thread = pthread_self();
    long valor;
    valor = (long) param;
    printf("Eu sou a thread%ld e meu ID é %lu \n", valor, thread);
    pthread_exit(NULL);
}

int main(void) {
    int n;
    printf("Quantidade de threads: ");
    scanf("%d", &n);
    pthread_t threads[n];
    long i;
    for (i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, run, (void *) i);
    }
    pthread_exit(NULL);
    return 0;
}


