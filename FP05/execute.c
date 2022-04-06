/*
   execute . cria um processo progénito e executa um programa
*/
#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

int ultimo(int *numargs, char **args)
{
  if (args[*numargs - 1][0] == '&')
  {
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG; /*return FG ou BG definidos no shell.h */
}

void execute(int numargs, char **args)
{
  int pid, status;
  int code = ultimo(&numargs, args);

  if ((pid = fork()) < 0)
  {                  // cria um processo progenito
    perror("forks"); // NOTE: perror() produz uma pequema mensagem de erro para o stream
    exit(1);         // estandardizado de erros que descreve o ultimo erro encontrado
  }                  // durante uma chamada ao sistema ou funcao duma biblioteca

  if (pid == 0)
  {
    redirects(numargs, args);
    execvp(*args, args);
    perror(*args);
    exit(1);
  }

  if (FG == code)
    while (wait(&status) != pid)
      ;
  /*spin fazer nada */;

  // NOTE: as versoes execv() e
  // execvp() de execl() sao uteis quando
  // o numero de argumentos nao e. conhecido
  // Os argumentos de execv() e execvp()
  // sao o nome do ficheiro a ser executado e um
  // vector de strings que contem os
  // argumentos. O ultimo argument */

  return;
}
