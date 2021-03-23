# :crossed\_swords: IRON shell

* 💻 Shell's are programs which provide **command line interface** to prefrom tasks,
  or in true sense they invoke execution of other programs. **IRON** here means 
  **hard/strong**. This Shell inherits alot similar functionality as provided 
  by many shells in market like bash, zsh. 
 
* 😄 Fun Fact: Windows command prompt is world's most horrible shell program.

## :sunglasses: UNIX Ideaology 

* UNIX is made on basis of writing various programs such that each one of them 
  can executes, handle and manage **one particular task completely**. In-order 
  to achieve execution of complicated task, it is broken in sub-task and each
  sub-task is handled independently by the programs written and execution
  happens concurrently with each subtask I/O connected using **PIPES**.

* UNIX assumes everthing to be file (there are no drives, even folder/directory 
  are files !!). The program execution can make use of file for I/O purpose.
  This is made possible using I/O **REDIRECTION** to files.

## :wrench: Installation Building IRON-shell executable 

* Install for github UI, or by any command line interface with following commands 

```sh
    $ git clone https://github.com/kishanpatel22/IRON-shell
    $ cd IRON-shell
```

* Run the following commands to create the executable file and start the shell

```sh
    $ make
    $ ./iron-shell
```

* Tip : use make clean to clean all the objects files created by make 


## :dart: Example regarding the features and usage 

* The video contains a small demo of how to user the command line interface 
    
    [![asciicast](https://asciinema.org/a/401781.svg)](https://asciinema.org/a/401781)

## :package: FEATURES OF IRON-SHELL

### :eight\_pointed\_black\_star: Build in IRON-Shell commands 

* Support to build in iron-shell commands include the following things 
    
    |  Command    | Significance                                    |
    |-------------|-------------------------------------------------|
    | **cd**      | command to change the current working directory |
    | **exit**    | to exit the shell                               |
    | **fg**      | to run any fore-ground process                  |
    | **bg**      | run any background process                      |

* Support to signals for the iron-shell 
    
    |  Signal       | Significance                                    |
    |---------------|-------------------------------------------------|
    | **control-c** | terminates the currently executing program / process |
    | **control-z** | suspends the execution of the currently running program / processes |
    | **control-d** | to exit from the iron-shell prompt |

### :eight\_pointed\_black\_star: PIPES, RIDRECTION and STOPPING/RESUMING of processes

* Support to unix pipelining, redirection I/O with files and suspension for 
  processes in iron-shell background.

* Examples for OUTPUT and INPUT Redirection

```sh

    /home/kishan/code/shell
    ISHELL >> wc < satellite_data.txt > file.txt

    /home/kishan/code/shell
    ISHELL >> cat file.txt
    864000  6912000 77817099 satellite_data.txt

```

* Examples for Pipelining 

```sh
    /home/kishan/code/C++_codes
    ISHELL >> ls -l | grep ^d | sort   
    drwxr-xr-x 21 kishan kishan  4096 Feb  9 22:14 DSA
    drwxr-xr-x  2 kishan kishan  4096 Jan 10 21:04 Makefile
    drwxr-xr-x  2 kishan kishan  4096 Jan 11 15:04 cmake_demo
    drwxr-xr-x  2 kishan kishan  4096 Mar  7 19:52 pavan
    drwxr-xr-x  2 kishan kishan  4096 May 15  2020 cplusplus
    drwxr-xr-x  5 kishan kishan  4096 Aug 24  2020 TOC
    drwxr-xr-x  8 kishan kishan  4096 Jan  2 22:24 OOPS
    
    /home/kishan/code/C++_codes
    ISHELL >> ls -l | grep ^d | sort | head -n 3 
    drwxr-xr-x 21 kishan kishan  4096 Feb  9 22:14 DSA
    drwxr-xr-x  2 kishan kishan  4096 Jan 10 21:04 Makefile
    drwxr-xr-x  2 kishan kishan  4096 Jan 11 15:04 cmake_demo

    /home/kishan/code/C++_codes
     ISHELL >> ls -l | grep ^d | sort | head -n 3 | wc > new_data.txt
    
    /home/kishan/code/C++_codes
     ISHELL >> cat new_data.txt
          3      27     165
```


* Examples for Background process 

```sh

    /home/kishan/code/shell
    ISHELL >> firefox &
    
    /home/kishan/code/shell
    ISHELL >> echo I can run next command
    I can run next command

    /home/kishan/code/shell
    ISHELL >> jobs

    [1]	+ 29020 running	firefox

```

* Example of signal handling and jobs

```sh

    /home/kishan/code/shell
    ISHELL >> ping www.google.com | grep ttl
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=1 ttl=120 time=5.88 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=2 ttl=120 time=8.36 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=3 ttl=120 time=8.82 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=4 ttl=120 time=8.42 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=5 ttl=120 time=8.50 ms
    ^Z
     [1]	+ 28924 stopped	grep
         	+ 28923 stopped	ping
    
    /home/kishan/code/shell
     ISHELL >> jobs
    
     [1]	+ 28924 stopped	grep
         	+ 28923 stopped	ping
    
    /home/kishan/code/shell
     ISHELL >> fg 
    
     [1]	+ 28924 running	grep
         	+ 28923 running	ping
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=6 ttl=120 time=8.48 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=7 ttl=120 time=8.62 ms
    64 bytes from bom12s04-in-f4.1e100.net (216.58.203.4): icmp_seq=8 ttl=120 time=10.4 ms
    ^C

    /home/kishan/code/shell
     ISHELL >> 

```

