

### Instruções do projeto:

- Nomeie seus arquivos executáveis como cliente e servidor.
- Tem que entregar um Makefile que irá compilar seus arquivos fonte. Não deve
vincular novamente.
- Pode utilizar a **libft.h.**
- Pode ter uma variável global por programa (uma para o cliente e outra para
o servidor), mas terá que justificar seu uso.

<aside>
⚠️ Deve ser criado um programa de comunicação na forma de cliente e servidor.
</aside>

1. O servidor deve ser iniciado primeiro. Após o seu lançamento, deverá imprimir seu **PID.**
2. O cliente usa dois parâmetros:
◦ O PID do servidor.
◦ A string a ser enviada.
3. O cliente deve enviar a string passada como parâmetro ao servidor.
Assim que a string for recebida, o servidor deverá imprimi-la.
4. O servidor precisa exibir a string rapidamente. Rapidamente significa que se você pensar
demora muito, então provavelmente é muito longo.
5. O servidor deve ser capaz de receber strings de vários clientes seguidos sem
precisando reiniciar.
6. A comunicação entre seu cliente e seu servidor deve ser feita apenas usando
Sinais UNIX.
7. Só pode usar estes dois sinais: **SIGUSR1 e SIGUSR2.**

### O que é sinal?

Um sinal é uma notificação de software a um processo da ocorrência de um evento. O mecanismo de sinais define uma maneira se trabalhar com eventos assíncronos no Unix.

- Um sinal é entregue quando o processo reage ao sinal, ou seja, executa alguma ação baseada no sinal (ele executa um tratador do sinal – signal handler).
- O tempo de vida de um sinal (signal lifetime) é o intervalo entre a
geração e a entrega do sinal.
- O Unix define códigos para um número fixo de sinais (31 no Linux), de
tipo int. Cada um desses sinais é caracterizado por um nome simbólico
iniciado com SIG e podem ser consultados em diversos locais:
    - O arquivo /usr/include/signal.h
    - Comando kill –l
- Sinais são caros porque o emissor tem que fazer syscall.
- Com exceção de SIGCHLD, sinais não são empilhados.
- **O usuário não pode definir sinais, mas o Unix disponibiliza dois sinais
(SIGUSR1 e SIGUSR2) para o utilizador usar como bem entender.**

### Geração de sinal:

A partir do shell, utilizamos o comando **<kill>**

Ex: `kill -USR1 1234` (envia o sinal SIGUSR1 para o processo cujo PID é 1234)

```bash
1. Formato: 
**kill –s pid**

2. Em caso de falha na emissão do sinal:
****if (kill(3423,SIGUSR1)==-1) perror("Failed to send the
SIGUSR1 signal");

3. Exemplos: 
%kill –9 3423
%kill –s USR1 3423
%kill –l (lista sinais disponíveis)
```

- Lista de sinais disponíveis:
    - EXIT HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE
    ALRM TERM USR1 USR2 CLD PWR WINCH URG POLL STOP TSTP CONT TTIN
    TTOU VTALRM PROF XCPU XFSZ WAITING LWP FREEZE THAW CANCEL LOST
    RTMIN RTMIN+1 RTMIN+2 RTMIN+3 RTMAX-3 RTMAX-2 RTMAX-1 RTMAX
     Valores numéricos de sinais:
    sIGHUP(1),SIGINT(2),SIGQUIT(3),SIGABRT(6),SIGKILL(9),SIGALRM(14),
    SIGTERM(15)

A função **kill()** é usada dentro de um programa para enviar um sinal para outros processos

```bash
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);

/*O primeiro parâmetro identifica o processo alvo, o segundo indica o sinal*/
```

- Se `pid>0`: sinal enviado para processo indicado por PID
- Se `pid=0`: sinal enviado para os processos do grupo do remetente.
- Se `pid=-1`: sinal enviado para todos os processos para os quais ele pode enviar sinais (depende do UID do usuário).
- Se `pid<0` (exceto -1): sinal é enviado para todos os processos com GroupID igual a |pid| .
- **Se sucesso, kill retorna 0**. Se erro, retorna -1 e seta a variável errno.
