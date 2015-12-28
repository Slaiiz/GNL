NAME=libft.a
SRCS=ft_fuckyou.c
OBJS=$(subst .c,.o,$(SRCS))

$(NAME):
	echo "Fuck You"
	cd srcs; gcc -Wall -Wextra -Werror -c $(SRCS)
	cd srcs; ar -r ../$(NAME) $(OBJS)

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	cd srcs; rm -f $(OBJS)

re: fclean all

.PHONY: all fclean clean
