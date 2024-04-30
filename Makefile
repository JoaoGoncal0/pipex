NAME = pipex

LIBFT = libft/libft.a

PRINTF = ft_printf/libftprintf.a

CC = cc -Wall -Werror -Wextra

RM = rm -f

SRCS = pipex.c \
		heredoc.c \
		parsing.c \
		get_next_line/get_next_line_bonus.c \
		free_functions.c \
		get_next_line/get_next_line_utils_bonus.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(PRINTF):
	@make -s -C ./ft_printf

$(NAME):	$(OBJ) $(LIBFT) $(PRINTF)
			$(CC) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
			@echo "$(NAME) created"

clean:
	@make -C ./libft clean --no-print-directory
	@make -C ./ft_printf clean --no-print-directory
	
fclean:		clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)
				@$(RM) $(PRINTF)
				@$(RM) *.o
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:		all clean fclean re