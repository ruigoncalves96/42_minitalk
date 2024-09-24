CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
RM = rm -f

SERVER = server
CLIENT = client

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC_SERVER = miniserver.c
SRC_CLIENT = miniclient.c
OBJ_SERVER = miniserver.o
OBJ_CLIENT = miniclient.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT) $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LIBFT) -o $(SERVER)

$(CLIENT): $(LIBFT) $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
