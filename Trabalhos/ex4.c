/* 
 * File:   ex4.c
 * Author: danieljr
 *
 * Created on 3 de Novembro de 2014, 10:25
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *run(void *param) {
    pthread_t thread_id;
    thread_id = pthread_self();
    long pid = getpid();
    long valor;
    valor = (long) param;
    printf("Eu sou a thread%ld. Meu pthread_self é %lu e meu getpid é %ld \n", valor, thread_id, pid);
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

    for(i=0; i < n; i++){
        pthread_join( threads[i], NULL);
    }
    printf("\n-> Explicação: A chamada pthread_self não retorna o mesmo ID da thread de kernel que é o retorno da chamada do getid.\n"
            "Pthread_self retorna o id único da thread (TID) sob a perspectiva do processo.\n"
            "Getid retorna o chamado thread id group (TGID), sendo considerado o id único da thread sob a perspectiva do sistema.\n"
            "Cada processo é composto de uma ou mais threads que possuem seus próprios TIDs, mas compartilham o mesmo"
            "\nTGID que é igual ao PID da thread inicial onde a main executa.\n\n");
    pthread_exit(NULL);
    return 0;
}


