# Proyecto de Sistemas Operativos 
## Implementación de llamadas al sistema - Autoevaluación Ashly
### Ashly Sofia Robayo - Samuel Quintero 
### Curso 
Sistemas Operativos 
### Semestre 
2026-2 --- 
# Descripción 
Este proyecto implementa dos syscalls nuevas además de las que tiene Xv6: Trace y Sysinfo. Con un shell ya construido, se hacen las llamadas que den información de un proceso en específico y de la información del sistema Xv6. En ellas se evidencia el cambio de modo usuario a modo kernel para, por ejemplo, obtener las páginas libres que tiene el sistema operativo, usando copyout para devolverlas al usuario; y el uso de traps tanto para trace como para sysinfo.

La solución fue desarrollada utilizando lenguaje C y se integra al proceso de 
compilación estándar de xv6 ejecutado sobre QEMU. --- 
# Estructura de archivos 
```text
kernel/
|_____sysinfo.h
user/ 
├── sh.c 
├── parser.c 
├── parser.h 
├── commands.c 
├── commands.h 
└── utils.h
|____ sysinfo.c
|____ trace.c
``` 
## Descripción de los archivos 
### sh.c 
Archivo principal del shell. 
### parser.c 
Contiene las funciones encargadas de analizar la línea de comandos ingresada por 
el usuario. 
### parser.h 
Definiciones y prototipos asociados al parser. 
### commands.c 
Implementación de rutinas relacionadas con la ejecución de comandos y 
tuberías. 
### commands.h 
Prototipos de funciones relacionadas con la ejecución. 
### utils.h 
Constantes y funciones auxiliares utilizadas en el proyecto.
### sysinfo.h
Recopila el estado actual de la memoria del sistema (páginas disponibles, utilizadas y memoria libre total en MB) consultando la lista enlazada de kalloc, además de contabilizar los procesos en estado RUNNABLE directamente desde la tabla de proc.c
### trace.c
Permite interceptar la ejecución de una llamada al sistema específica. Al activarse, monitorea el proceso actual y todos sus subprocesos heredados, capturando información crítica desde el trapframe RISC-V (PID, nombre de la syscall, valor de retorno y registros s0, s1, a0, a1) justo en el momento en el que el flujo de ejecución cambia del espacio de usuario al kernel
--- 
# Archivos modificados
### kalloc.c
Se implementó count_free_pages(), la cual bloquea y recorre la lista kmem.freelist para contar los bloques de 4096 bytes disponibles en la memoria física.
### proc.c/.h
Se agregó count_runnable_procs() para iterar la tabla global proc[NPROC] buscando procesos en estado RUNNABLE. Además, se modificaron kfork() y freeproc() para heredar la variable trace_syscall a los procesos hijos y limpiarla cuando el proceso muere. Se modificó struct proc añadiendo el campo numérico int trace_syscall para que cada proceso recuerde qué llamada al sistema está rastreando independientemente.
### defs.h
Se expusieron las cabeceras de las nuevas funciones auxiliares de memoria y procesos para evitar problemas de compilación en sysproc.c.
### sysproc.c
Aloja la implementación principal. En sys_sysinfo, se orquesta la recolección de métricas y se utiliza copyout para escribir sobre el espacio virtual del usuario de manera segura. En sys_trace, simplemente se asigna el número recibido al proceso actual.
### syscall.c/.h
Se declararon los identificadores SYS_sysinfo (23) y SYS_trace (24). Se modificó el despachador dinámico syscall(void) para interceptar el flujo y registrar el estado de los registros cuando p->trace_syscall coincide con la llamada en ejecución.
### user.h y usys.pl
Se agregaron los prototipos de las funciones y los puntos de entrada (entry) de Perl para generar automáticamente las instrucciones ecall de RISC-V hacia el kernel.
---

# Integración con xv6 
## Paso 1. Obtener xv6 
```bash 
git clone https://github.com/mit-pdos/xv6-riscv.git 
``` 
## Paso 2. Copiar archivos 
Copiar todos los archivos entregados dentro del directorio `user/`. 
## Paso 3. Modificar el Makefile 
Agregar el programa al listado de aplicaciones de usuario. 
## Paso 4. Compilar xv6 
```bash 
make qemu 
``` 
## Paso 5. Ejecutar el shell 
```bash 
sh 
```
--- 
# Autoevaluación
Aprendí más del automapeo de este sistema operativo y de como funcionan los procesos, llamadas, traps y paginación. No tengo conocimiento tan profundo del trace porque mi compañero lo desarrolló en su mayoría, mas comprendo su estructura y como funciona.

--- 
# Limitaciones conocidas 
- No soporta comillas. 
- No soporta variables de entorno. 
- No soporta ejecución en segundo plano. 

--- 

# Declaración de uso de IA 
Durante el desarrollo del proyecto se utilizaron herramientas de inteligencia 
artificial generativa como apoyo para comprensión de conceptos, revisión de 
código y generación de ejemplos. 
Los integrantes asumen plena responsabilidad académica sobre el contenido 
entregado.
