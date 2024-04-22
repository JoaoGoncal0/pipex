NAME = pipex

LIBFT = libft/libft.a

CC = cc -Wall -Werror -Wextra

RM = rm -f

SRCS = pipex.c \
		heredoc.c \
		parsing.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(OBJ) $(LIBFT) -o $(NAME)
			@echo "$(NAME) created"

clean:
	@make -C ./libft fclean --no-print-directory

fclean:		clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)
				@$(RM) *.o
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			start all clean fclean re