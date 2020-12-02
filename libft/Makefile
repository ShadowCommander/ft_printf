# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtong <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 09:44:30 by jtong             #+#    #+#              #
#    Updated: 2020/12/01 13:04:36 by jtong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
FILES := ft_atoi ft_isalnum ft_isdigit ft_islower ft_isspace ft_isupper ft_strtol ft_ulltoa_base
HEADERS := .
OBJ := $(addsuffix .o,$(FILES))
CC := clang
CFLAGS := -Werror -Wall -Wextra

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
