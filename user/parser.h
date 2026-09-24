#ifndef PARSER_H
#define PARSER_H
#define MAXCMDS 10
#define MAXARGS 10
#define MAXTOKENS 64



struct cmd {
  char *argv[MAXARGS + 1];
  int argc;
  char *infile;
  char *outfile;
  int append;
};

int tokenize(char *buffer, char *tokens[MAXTOKENS+1]);

int build_pipeline(char *tokens[], int numt, struct cmd *cmds);

#endif