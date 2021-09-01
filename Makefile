NAME = pipex

MANDATORY	=	main.c\
				src/ft_split_comma.c\
				src/get.c\
				src/free.c

OBJ = $(MANDATORY:.c=.o)

CC = gcc

INC_1 = -I./includes

FLAGS	= -Wall -Wextra -Werror

SANITIZE = -fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./ft_printf
		cp ft_printf/libftprintf.a .
		cp ft_printf/libft/libft.a .
		$(CC) $(FLAGS) -g $(INC_1) $(MANDATORY) $(SANITIZE) libftprintf.a libft.a -o $(NAME)

clean:
	$(MAKE) clean -C ./ft_printf
	rm -rf *.o
	rm -rf a.out
	rm -rf a.out*

fclean: clean
	$(MAKE) fclean -C ./ft_printf
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf *.a

re: fclean all

.PHONY:	all clean fclean bonus re
