NAME = pipex

LIBFT = libft/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

SRCS = 

OBJS = $(SRCS:.c=.o)

$(LIBFTT):
		@make -s -C ./libft
		@make bonus -s -C ./libft

all = $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "$(NAME) created"

clean:		$(RM) $(OBJS)
			@make clean -s -C ./libft

fclean: 	clean
			$(RM) $(NAME)
			@$(RM) $(LIBFT)
			@echo "$(NAME) deleted"

re: 		fclean all

.PHONY: 	fclean all



