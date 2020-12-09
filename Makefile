# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pi <pi@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 09:44:30 by jtong             #+#    #+#              #
#    Updated: 2020/12/09 10:41:41 by pi               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
LIBDIR := libft/
LIB := ft
LIBNAME := $(addprefix lib,$(addsuffix .a,$(LIB)))
LIBFULL := $(addprefix $(LIBDIR),$(LIBNAME))
FILES := ft_printf
HEADERDIRS := . libft
OBJ := $(addsuffix .o,$(FILES))
CC := clang
OFLAGS := ${CFLAGS} -Werror -Wall -Wextra $(addprefix -I,$(HEADERDIRS))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFULL)
	cp $(LIBFULL) $(NAME)
	ar rc $@ $(OBJ)

%.o : %.c
	$(CC) $(OFLAGS) -c $<

$(LIBFULL): $(LIBDIR)
	$(MAKE) -C ./libft

clean:
	$(MAKE) fclean -C libft
	/bin/rm -f $(OBJ) *.o

fclean: clean
	/bin/rm -f $(NAME) libft.h.gch

re: fclean all

.PHONY: $(LIBDIR)