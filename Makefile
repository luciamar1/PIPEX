NAME = pipex
SRC = ft_split.c main.c pepo.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf
OBJ = $(SRC:.c=.o)
$(NAME): $(OBJ) 
	make -C libft
	gcc $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)


all: $(NAME)
clean: 
	$(RM) $(OBJ)
	make -C libft clean
fclean: clean 
	$(RM) $(NAME)
	make -C libft fclean
 
re: fclean all
.PHONY: all clean fclean re	

# NAME = pipex
# SRC = utils.c main.c executer.c list_operations.c
# CFLAGS = -Wall -Wextra -Werror
# RM = /bin/rm -rf
# OBJ = $(SRC:.c=.o)

# $(NAME): $(OBJ) 
# 	make -C libft
# 	make -C gnl
# 	gcc libft/libft.a gnl/gnl.a $(OBJ) -o pipex

# all: $(NAME)
# clean: 
# 	$(RM) $(OBJ)
# fclean: clean 
# 	$(RM) $(NAME)
# re: fclean all
# .PHONY: all clean fclean re	