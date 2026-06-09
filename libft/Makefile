NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= ft_bzero.c ft_itoa.c ft_putstr.c ft_strcmp.c ft_strdup.c ft_strim.c \
		  ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strstr.c ft_strtok.c ft_calloc.c \
		  ft_substr.c ft_memmove.c ft_memcpy.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c libftutils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
