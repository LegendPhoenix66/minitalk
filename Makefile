# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Header file
HEADER = minitalk.h

# Source files for the server
SERVER_SRC = server.c

# Source files for the client
CLIENT_SRC = client.c

# Name of the server executable
SERVER_NAME = server

# Name of the client executable
CLIENT_NAME = client

# Subfolder for object files
OBJDIR = obj/

# Object files for the server
SERVER_OBJS = $(patsubst %.c,$(OBJDIR)%.o,$(SERVER_SRC))

# Object files for the client
CLIENT_OBJS = $(patsubst %.c,$(OBJDIR)%.o,$(CLIENT_SRC))

# Rule for creating the executables
all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	make -C printf
	$(CC) $(CFLAGS) $(SERVER_OBJS) printf/libftprintf.a -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	make -C printf
	$(CC) $(CFLAGS) $(CLIENT_OBJS) printf/libftprintf.a -o $(CLIENT_NAME)

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C printf
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	make fclean -C printf
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re