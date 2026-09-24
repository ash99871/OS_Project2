#include "commands.h"
#include "utils.h"
#include "parser.h"
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int is_exit(struct cmd *cmds, int numCmds){
    return numCmds == 1 && cmds[0].argc > 0 && streq(cmds[0].argv[0], "exit");
}

void run_pipeline(struct cmd *cmds, int numCmds){
    int fd_in = -1; //herencia del pipe pasado
    int p[2];

    for (int i=0; i<numCmds; i++){
        if(i< numCmds -1 && pipe(p)<0){
            die("Error al crear el pipe");
        }

        int pid = fork();
        if (pid <0){
            die("Error del fork");
        }

        if(pid ==0){
            if(fd_in != -1){
                close(0);
                dup(fd_in);
                close(fd_in);
            }
            
            if(cmds[i].infile){
                close(0);
                if (open(cmds[i].infile, O_RDONLY)<0){
                    printf("Error al abrir %s\n", cmds[i].infile);
                    exit(1);
                } 

            }

            if(i< numCmds-1){
                close(1);
                dup(p[1]);
                close(p[0]);
                close(p[1]);
            }

            if(cmds[i].outfile){
                close(1);
                if(open(cmds[i].outfile, O_WRONLY | O_CREATE)<0){
                    printf("Error en abrir %s\n", cmds[i].argv[0]);
                    exit(1);
                }

            }

            exec(cmds[i].argv[0], cmds[i].argv);
            printf("Comando no hallado: %s\n", cmds[i].argv[0]);
            exit(1);
        }

        if(fd_in != -1){
            close(fd_in);
        }

        if(fd_in!= -1){
            close(p[1]);
            fd_in= p[0];
        }
    }

    for(int i=0; i <numCmds; i++){
        wait(0);
    }
}


