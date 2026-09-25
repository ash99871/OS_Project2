#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


struct {
  char *name;
  int   num;
} syscall_table[] = {
  {"sys_fork",    1},
  {"sys_exit",    2},
  {"sys_wait",    3},
  {"sys_pipe",    4},
  {"sys_read",    5},
  {"sys_kill",    6},
  {"sys_exec",    7},
  {"sys_fstat",   8},
  {"sys_chdir",   9},
  {"sys_dup",    10},
  {"sys_getpid", 11},
  {"sys_sbrk",   12},
  {"sys_sleep",  13},
  {"sys_uptime", 14},
  {"sys_open",   15},
  {"sys_write",  16},
  {"sys_mknod",  17},
  {"sys_unlink", 18},
  {"sys_link",   19},
  {"sys_mkdir",  20},
  {"sys_close",  21},
};

int
name_to_num(char *name)
{
  int n = sizeof(syscall_table) / sizeof(syscall_table[0]);
  for (int i = 0; i < n; i++) {
    if (strcmp(syscall_table[i].name, name) == 0)
      return syscall_table[i].num;
  }
  return -1;
}

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "uso: trace <nombre_syscall> [comando args...]\n");
    exit(1);
  }

  int num = name_to_num(argv[1]);
  if (num < 0) {
    fprintf(2, "trace: syscall desconocida '%s'\n", argv[1]);
    exit(1);
  }

  if (trace(num) < 0) {
    fprintf(2, "trace: no se pudo activar el trace para %s\n", argv[1]);
    exit(1);
  }

  if (argc > 2) {
    exec(argv[2], argv + 2);
    
    fprintf(2, "trace: exec %s falló\n", argv[2]);
    exit(1);
  }

  exit(0);
}