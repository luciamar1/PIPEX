NAME = pipex

SRCS = ft_splitpip.c main.c 

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCS:.c=.ob)

LIB = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3  -fsanitize=address

$(NAME): $(OBJS)
	@make -C libft
	@rm -rf $(OBJSB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

%.o:%.c
	$(CC) -D BONUS=0 $(CFLAGS) -c $< -o $@
	
%.ob:%.c
	$(CC) -D BONUS=1 $(CFLAGS) -c $< -o $@
	
bonus: $(OBJSB)
	@make -C libft
	@rm -rf $(OBJS)
	$(CC) $(CFLAGS) $(OBJSB) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	@make clean -C libft
	@rm -rf $(OBJS)
	@rm -rf $(OBJSB)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norma bonus
#NAME = pipex
#SRC = ft_split.c main.c pepo.c
#CC = gcc
#CFLAGS = -Wall -Wextra ##-Werror
#RM = /bin/rm -rf
#OBJ = $(SRC:.c=.o)
#$(NAME): $(OBJ) 
#	make -C libft
#	gcc $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)


#all: $(NAME)
#clean: 
#	$(RM) $(OBJ)
#	make -C libft clean
#fclean: clean 
#	$(RM) $(NAME)
#	make -C libft fclean
 
#re: fclean all
#.PHONY: all clean fclean re	

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