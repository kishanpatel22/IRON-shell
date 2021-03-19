EXE=iron_shell

iron_shell: iron_shell.o process_command_list.o command_handler.o builtin.o
	gcc iron_shell.o process_command_list.o command_handler.o builtin.o -o $(EXE)

iron_shell.o : iron_shell.c 
	gcc -c iron_shell.c 

process_command_list.o : process_command_list.c process_command_list.h
	gcc -c process_command_list.c

command_handler.o : command_handler.c command_handler.h 
	gcc -c command_handler.c 

builtin.o : builtin.c builtin.h
	gcc -c builtin.c 

valgrind: iron_shell
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm *.o
