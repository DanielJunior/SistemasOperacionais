/* 
 * File:   ex2.c
 * Author: danieljr
 *
 * Created on 3 de Novembro de 2014, 10:10
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void mensagem(int i) {
    long pid;
    pid = getpid();
    printf("Eu sou o %dº filho e meu PID é %ld\n", (i + 1), pid);
    //sleep(5);
    exit(0);
}

int main(void) {

    pid_t filho_pid;
    int i, n;
    printf("Quantidade de processos filhos a serem criados: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        filho_pid = fork();

        switch (filho_pid) {
                //filho = 0
                //erro = -1
                //default = pai
            case 0:
                mensagem(i);
                break;
            case -1:
                perror("fork");
                puts("Erro");
                exit(-1);
            default:
                break;
        }
    }

    long pid;
    pid = getpid();
    printf("Eu sou o pai e meu PID é %ld\n", pid);
    return 0;
}