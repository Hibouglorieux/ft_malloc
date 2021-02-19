
NAME = libft_malloc

FILES = ft_malloc.c ft_number_to_hexa.c ft_malloc_print.c ft_malloc_variable.c ft_malloc_multithread.c \
		ft_realloc.c ft_free.c ft_malloc_block.c ft_malloc_addr.c ft_malloc_alloc.c ft_free_2.c

OBJ = $(addprefix obj/, $(FILES:.c=.o))

INCLUDES = includes/ft_malloc.h

LIBS = -Llibft -lft

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FULL_LIBRARY = $(addsuffix .so, $(addsuffix _$(HOSTTYPE), $(NAME)))

SHORT_LIBRARY = $(addsuffix .so, $(NAME))

COMPILE_FLAGS = -Wall -Wextra -fPIC #-Werror isnt present because of the norminette bug

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) -shared -Wl,--version-script=libft_malloc_script.exp -o $(FULL_LIBRARY) $(OBJ) $(LIBS)
	ln -f -s $(FULL_LIBRARY) $(SHORT_LIBRARY)

test: $(OBJ) obj/test.o
	@make -C libft
	$(CC) $^ -o malloc $(LIBS)
	
obj/%.o:src/%.c $(INCLUDES)
	@mkdir -p obj
	$(CC) $(COMPILE_FLAGS) -c $< -o $@ -Iincludes -Ilibft

clean:
	@make clean -C libft
	rm -rf obj/

fclean: clean
	@make fclean -C libft
	rm -rf $(FULL_LIBRARY) $(SHORT_LIBRARY)

re: fclean all
