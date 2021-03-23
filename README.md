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

### :eight\_pointed\_black\_star: PIPES, RIDRECTION and SUSPENSION of processes

* Support to unix pipelining, redirection I/O with files and suspension for 
  processes in iron-shell background.

* Examples for Redirection

```sh
      

```

* Examples for Pipelining 

```sh
```


* Examples for Background process 

```sh
```

