#include "parser.h"
#include "kernel/types.h"
#include "user/user.h"

int tokenize(char *buffer, char *tokens[MAXTOKENS + 1]){
  int numt = 0;
  char *token = buffer;
  while (*token){
    while(*token == ' ' || *token == '\t' || *token == '\n'){
        *token++ = 0;
    }
    if (*token == 0){
        break;
    }
    if (numt >= MAXTOKENS){
        break;
    }

    tokens[numt++] = token;
    while(*token && *token != ' ' && *token != '\t' && *token != '\n'){
        token++;
    }
  }
  tokens[numt] = 0;
  return numt;
}

int build_pipeline(char **tokens, int numt, struct cmd *cmds){
  int cmdIndex = 0;
  struct cmd *nCmd = &cmds[0];
  nCmd->argc = 0;
  nCmd->infile = 0;
  nCmd->outfile = 0;

  for (int i = 0; i < numt; i++){
    if (strcmp(tokens[i], "|") == 0){
      if (nCmd->argc == 0){
        printf("Sin comando antes del pipe\n");
        return -1; // Error
      }
      nCmd->argv[nCmd->argc] = 0; 
      cmdIndex++;
      if (cmdIndex >= MAXCMDS){
        printf("Muchos comandos\n");
        return -1; // Error
      }
      nCmd = &cmds[cmdIndex];
      nCmd->argc = 0;
      nCmd->infile = 0;
      nCmd->outfile = 0;

    } else if (strcmp(tokens[i], "<") == 0){
      if (i + 1 >= numt){
        printf("Sin archivo tras el '<'\n");
        return -1; // Error
      }
      nCmd->infile = tokens[++i];
    } else if (strcmp(tokens[i], ">") == 0){
      if (i + 1 >= numt){
        printf("Sin archivo despues del '>'\n");
        return -1; // Error
      }
      nCmd->outfile = tokens[++i];

    } else {
      if (nCmd->argc < MAXARGS){
        nCmd->argv[nCmd->argc++] = tokens[i];
      }
    }
    
  }

  if (nCmd->argc == 0){
    printf("Sin comando\n");
    return -1;
  }

  nCmd->argv[nCmd->argc] = 0;
  cmdIndex++;
  return cmdIndex; 
}
