EXE=iron_shell

CC = gcc
CC_FLAGS = -fsanitize=address -Wall

iron_shell: main.o iron_shell.o command.o job.o command_handler.o builtin.o signals.o
	$(CC) $(CC_FLAGS) main.o iron_shell.o command.o job.o command_handler.o builtin.o signals.o -o $(EXE) 

main.o: main.c
	gcc -c main.c 

iron_shell.o : iron_shell.c iron_shell.h
	gcc -c iron_shell.c 

job.o : job.c job.h
	gcc -c job.c

command.o : command.c command.h
	gcc -c command.c

command_handler.o : command_handler.c command_handler.h 
	gcc -c command_handler.c 

builtin.o : builtin.c builtin.h
	gcc -c builtin.c 

signals.o : signals.c signals.h
	gcc -c signals.c

valgrind: iron_shell
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm *.o
