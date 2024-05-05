# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Ilibft

# Header file
HEADER = ft_printf.h

# Source files for the mandatory part
SRC = ft_printf.c ft_printf_utils.c

# Source files for the bonus part
BONUS_SRC = ft_printf_bonus.c

# Subfolder for object files
OBJDIR = obj/

# Object files for the mandatory part
OBJS = $(addprefix $(OBJDIR),$(notdir $(SRC:.c=.o)))

# Object files for the bonus part
BONUS_OBJS = $(addprefix $(OBJDIR),$(notdir $(BONUS_SRC:.c=.o)))

# Name of the library
NAME = libftprintf.a

# Name of the bonus library
BONUS_NAME = libftprintf_bonus.a

# Rule for creating the library
all: $(NAME)

# Rule for creating the bonus library
bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -C libft
	mkdir -p $(OBJDIR)
	cd $(OBJDIR) && ar -x ../libft/libft.a
	ar rcs $(NAME) $(OBJS) $(OBJDIR)/*.o


$(BONUS_NAME): $(BONUS_OBJS)
	make -C libft
	mkdir -p $(OBJDIR)
	cd $(OBJDIR) && ar -x ../libft/libft.a
	ar rcs $(BONUS_NAME) $(BONUS_OBJS) $(OBJDIR)/*.o


$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
