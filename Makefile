EXE=shell

shell: shell.o command.o command_handler.o buildin.o
	gcc shell.o command.o command_handler.o buildin.o -o $(EXE)

shell.o : shell.c 
	gcc -c shell.c 

command.o : command.c command.h
	gcc -c command.c 

command_handler.o : command_handler.c command_handler.h 
	gcc -c command_handler.c 

buildin.o : buildin.c buildin.h
	gcc -c buildin.c 

valgrind: shell
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm *.o
