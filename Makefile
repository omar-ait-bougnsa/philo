NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror  -pthread  -g -fsanitize=thread
RSC = philo.c monitur.c  philo_utilis.c
OBJ = $(RSC:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) 

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
