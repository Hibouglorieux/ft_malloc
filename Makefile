
NAME = libft_malloc

FILES = ft_malloc.c ft_number_to_hexa.c

OBJ = $(addprefix obj/, $(FILES:.c=.o))

INCLUDES = includes/ft_malloc.h

LIBS = -Llibft -lft

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FULL_LIBRARY = $(addsuffix .so, $(addsuffix $(HOSTTYPE), $(NAME)))

SHORT_LIBRARY = $(addsuffix .so, $(NAME))



all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) -shared -o $(FULL_LIBRARY) $(OBJ) $(LIBS)
	ln -f -s $(FULL_LIBRARY) $(SHORT_LIBRARY)

test: $(OBJ) obj/main.o
	@make -C libft
	$(CC) $^ -o malloc $(LIBS)
	
obj/%.o:src/%.c $(INCLUDES)
	$(CC) -g -Wall -Wextra -fPIC -c $< -o $@ -Iincludes -Ilibft

clean:
	@make clean -C libft
	rm -rf obj/*.o

fclean: clean
	@make fclean -C libft
	rm -rf $(FULL_LIBRARY) $(SHORT_LIBRARY)

re: fclean all
