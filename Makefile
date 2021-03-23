EXE=iron_shell

CC = gcc
CC_FLAGS = -fsanitize=address -Wall

SOURCE = main.c				\
	   	iron_shell.c		\
	   	command.c			\
	   	job.c				\
	   	command_handler.c	\
	   	builtin.c			\
	   	signals.c			\

OBJECT = $(SOURCE:.c=.o)

$(EXE): $(OBJECT)
	$(CC) $(CC_FLAGS) $(OBJECT) -o $(EXE)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

valgrind: iron_shell
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

clean:
	rm *.o
