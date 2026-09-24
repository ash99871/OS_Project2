// Shell.
#include "commands.h"
#include "parser.h"
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"



static int getcmd(char *buffer, int nbuffer){
  printf("$ ");
  memset(buffer, 0, nbuffer);
  gets(buffer, nbuffer);
  if(buffer[0] == 0){
    return -1;
  } else{return 0;}

}

int main(void){
  static char buffer[128];
  int fd;

  //descriptores 0, 1 y 2
  while((fd= open("console", O_RDWR)) >= 0){
    if (fd >= 3){
      break;
    }
  }

  while (getcmd(buffer, sizeof(buffer)) >= 0){
    char *tokens[MAXTOKENS +1];
    int numt = tokenize(buffer, tokens);
    if(numt == 0){
      continue;
    }

    struct cmd cmds[MAXCMDS];
    int numbCmd = build_pipeline(tokens, numt, cmds);
    if (numbCmd <= 0){
      continue;
    } //parser.c

    if (is_exit(cmds, numbCmd)){
      exit(0);
    }
    run_pipeline(cmds, numbCmd);
  }

  exit(0);
}


