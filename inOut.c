#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <sched.h>


int main(void)
{
    struct termios  canonical_terminal, raw_terminal;
    int c;
    int n = 0;


	struct sched_param param = { .sched_priority = 1 };

	pid_t pid = getpid();

	printf("Default scheduler: %d (SCHED_NORMAL) from process pid: %d \n", sched_getscheduler(pid), pid);
	sched_setscheduler(pid, SCHED_RR, &param);
	printf("New scheduler: %d (SCHED_RR) from process pid: %d \n", sched_getscheduler(pid), pid);
	
    //Para receber e imprimir dados do teclado enquanto uma tecla estiver apertada deve-se entrar no modo raw do terminal

    //Pega as configurações atuais do terminal
    if (tcgetattr(STDIN_FILENO, &canonical_terminal))
        return errno;

    //Inicializa raw_terminal com as configurações atuais do terminal
    raw_terminal = canonical_terminal;

    //Flag para nao gerar signals de teclas especiais
    raw_terminal.c_lflag &= ~ISIG;

    //Flag para desligar echo
    raw_terminal.c_lflag &= ~ECHO;

    //Flag para sair do modo canônico (i.e. entrar no modo raw)
    raw_terminal.c_lflag &= ~ICANON;

    //Aplica as configurações ao stdin
    fflush(stdin);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal))
        return errno;

    fprintf(stdout, "Aperte Q para terminar.\n");
    fflush(stdout);

    do {

        c = getchar();

        if (isprint(c))
            fprintf(stdout, "%c\n", c);
            n++;
        fflush(stdout);

    } while (c != 'Q');
    //Descarta entradas não lidas e saídas não transmitidas.
    fflush(stdin);
    tcflush(STDIN_FILENO, TCIOFLUSH);

    //Volta às configurações originais
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &canonical_terminal);

    fprintf(stdout, "%d caracteres\n", n);
    fprintf(stdout, "Fim.\n");
    return EXIT_SUCCESS;
}
