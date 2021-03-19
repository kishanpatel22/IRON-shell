# Basic Shell 

## Building executable 

* Run the following commands to create the executable file and start the shell
```sh
    $ make
    $ ./shell
```
* Can also use make clean to clean all the objects files created by make 


## Build in Shell commands 

* Support to build in shell commands include the following things 
    + **cd** : command to change the current working directory
    + **history** : history of commands where executed
    + **exit** : to exit the shell

## PIPES, RIDRECTION and BACKGROUND processes

* Support to unix pipelining, redirection I/O with files and runing process in background.

* Examples for Redirection

```sh
    shell-prompt $  ls -l > file.txt    
    shell-prompt $  cat file.txt
    total 64
    -rw-r--r-- 1 kishan kishan 11966 Feb  2 11:50 command_handler.c
    -rw-r--r-- 1 kishan kishan  2532 Jan 31 21:39 command_handler.h
    -rw-r--r-- 1 kishan kishan 10632 Feb  2 14:17 command_handler.o
    -rw------- 1 kishan kishan     0 Feb  2 14:30 file.txt
    -rw-r--r-- 1 kishan kishan   299 Jan 31 12:45 Makefile
    -rw-r--r-- 1 kishan kishan   766 Feb  2 14:30 README.md
    -rwxr-xr-x 1 kishan kishan 13696 Feb  2 14:17 shell
    -rw-r--r-- 1 kishan kishan  1014 Jan 31 12:45 shell.c
    -rw-r--r-- 1 kishan kishan  2216 Feb  2 14:17 shell.o
    -rw-r--r-- 1 kishan kishan  2447 Jan 29 02:04 tags
    
    shell-prompt $ grep shell < file.txt
    -rwxr-xr-x 1 kishan kishan 13696 Feb  2 14:17 shell
    
    shell-prompt $ wc < file.txt > temp.txt
    shell-prompt $ cat temp.txt
        11  92 578
```

* Examples for Pipelining 

```sh
    shell-prompt $  ls -l | sort -r | wc
        10      83     523
```


* Examples for Background process 

```sh
```




