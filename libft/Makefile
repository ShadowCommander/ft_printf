# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pi <pi@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 09:44:30 by jtong             #+#    #+#              #
#    Updated: 2020/12/13 18:33:39 by pi               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
FILES := ft_bzero ft_isalnum ft_isalpha ft_isdigit ft_islower \
	ft_isspace ft_isupper ft_memalloc ft_putchar_fd ft_putnbr_fd ft_strlen \
	ft_strnew ft_strtol ft_toupper ft_ulltoa_base ft_strdup ft_strsub \
	ft_strndup ft_strncpy ft_itoa
HEADERS := .
OBJ := $(addsuffix .o,$(FILES))
CC := clang
CFLAGS := ${CFLAGS} -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -I $(HEADERS) $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME) libft.h.gch

re: fclean all
