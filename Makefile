NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror 
RSC = philo.c
OBG = $(RSC.c=.o)

all : $(NAME)

$(NAME) : $(OBG)
	$(CC) $(FLAGS) $(OBG) -o $(NAME)
$(OBG) : $(RSC)
	$(CC) $(FLAGS) $@ -o $^
