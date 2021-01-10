
NAME = libft_malloc

FILES = ft_malloc.c

OBJ = $(addprefix obj/, $(FILES:.c=.o))

INCLUDES = includes/ft_malloc.h

LIBS = libft/libft.a

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FULL_LIBRARY = $(addsuffix .so, $(addsuffix $(HOSTTYPE), $(NAME)))

SHORT_LIBRARY = $(addsuffix .so, $(NAME))



all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	ar rs $(FULL_LIBRARY) $(OBJ)
	ln -s $(FULL_LIBRARY) $(SHORT_LIBRARY)

test: $(OBJ) obj/main.o
	@make -C libft
	$(CC) $^ -o malloc $(LIBS)
	
obj/%.o:src/%.c $(INCLUDES)
	$(CC) -g -Wall -Wextra -c $< -o $@ -Iincludes -Ilibft

clean:
	@make clean -C libft
	rm -rf obj/*.o

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)
