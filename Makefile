# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pi <pi@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 09:44:30 by jtong             #+#    #+#              #
#    Updated: 2021/01/19 11:52:08 by jtong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
LIBDIR := libft
LIB := ft
LIBNAME := $(addprefix lib,$(addsuffix .a,$(LIB)))
LIBFULL := $(addprefix $(LIBDIR)/,$(LIBNAME))
FILENAMES := ft_printf ft_va_char ft_va_hex ft_va_integer ft_va_percent ft_va_string ft_va_ull pf_print pf_utils ft_va_pointer
FILEDIR := srcs
HEADERDIR := . $(LIBDIR)
OBJ := $(addsuffix .o,$(FILENAMES))

BONUSFILENAMES := ft_printf_bonus ft_va_char_bonus ft_va_hex_bonus ft_va_integer_bonus ft_va_percent_bonus ft_va_string_bonus ft_va_ull_bonus ft_va_printed_bonus pf_print_bonus pf_utils_bonus ft_va_pointer_bonus pf_utils_extra_bonus
BONUSFILEDIR := bonus
BONUSHEADERDIR := bonus $(LIBDIR)
BONUSOBJ := $(addsuffix .o,$(BONUSFILENAMES))

CC := clang
OFLAGS := ${CFLAGS} -Werror -Wall -Wextra $(addprefix -I,$(HEADERDIR))

vpath %.c $(FILEDIR) $(BONUSFILEDIR)

all: $(NAME)

bonus: $(BONUSOBJ) $(LIBFULL)
	cp $(LIBFULL) $(NAME)
	ar rc $(NAME) $(BONUSOBJ)
	ranlib $(NAME)

$(NAME): $(OBJ) $(LIBFULL)
	cp $(LIBFULL) $@
	ar rc $@ $(OBJ)
	ranlib $@

%.o : %.c
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
