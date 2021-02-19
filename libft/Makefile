# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 19:15:52 by nallani           #+#    #+#              #
#    Updated: 2018/10/24 14:42:43 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -fPIC -c
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
	  ft_isprint.c ft_itoa.c ft_lstrev.c ft_lstsize.c ft_lstadd.c\
	  ft_lstaddend.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c\
	  ft_lstmap.c ft_lstnew.c ft_lstsplit.c ft_memalloc.c ft_memcpy.c\
	  ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memdel.c ft_memmove.c ft_memset.c\
	  ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c\
	  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c\
	  ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c\
	  ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c\
	  ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c\
	  ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c\
	  ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c\
	  ft_toupper.c ft_lstaddat.c ft_min.c
OBJ = $(subst .c,.o,$(SRC))
.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c libft.h
	gcc $(FLAGS) $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

