# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pi <pi@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 09:44:30 by jtong             #+#    #+#              #
#    Updated: 2020/12/13 00:34:18 by pi               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
LIBDIR := libft/
LIB := ft
LIBNAME := $(addprefix lib,$(addsuffix .a,$(LIB)))
LIBFULL := $(addprefix $(LIBDIR)/,$(LIBNAME))
FILENAMES := ft_printf ft_va_char ft_va_hex ft_va_integer ft_va_percent ft_va_string ft_va_ull pf_print pf_utils ft_va_pointer
FILEDIR := srcs
HEADERDIR := . $(LIBDIR)
OBJ := $(addsuffix .o,$(FILENAMES))
CC := clang
OFLAGS := ${CFLAGS} -Werror -Wall -Wextra $(addprefix -I,$(HEADERDIR))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFULL)
	cp $(LIBFULL) $(NAME)
	ar rc $@ $(OBJ)
	ranlib $(NAME)

%.o : $(FILEDIR)/%.c
	$(CC) $(OFLAGS) -c $<

$(LIBFULL): $(LIBDIR)
	$(MAKE) -C $(LIBDIR)

clean:
	$(MAKE) fclean -C $(LIBDIR)
	/bin/rm -f $(OBJ) *.o

fclean: clean
	/bin/rm -f $(NAME) *.h.gch

re: fclean all

.PHONY: $(LIBDIR)
