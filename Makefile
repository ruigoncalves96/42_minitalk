CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
RM = rm -f

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC_PATH = ./src
SRC_BONUS_PATH = ./bonus_src

SRC_SERVER = $(SRC_PATH)/miniserver.c
SRC_CLIENT = $(SRC_PATH)/miniclient.c
OBJ_SERVER = $(SRC_PATH)/miniserver.o
OBJ_CLIENT = $(SRC_PATH)/miniclient.o
BONUS_SRC_SERVER = $(SRC_BONUS_PATH)/miniserver_bonus.c
BONUS_SRC_CLIENT = $(SRC_BONUS_PATH)/miniclient_bonus.c
BONUS_OBJ_SERVER = $(SRC_BONUS_PATH)/miniserver_bonus.o
BONUS_OBJ_CLIENT = $(SRC_BONUS_PATH)/miniclient_bonus.o

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(LIBFT) $(OBJ_SERVER)
	@$(CC) $(OBJ_SERVER) $(LIBFT) -o $(SERVER)
	@echo " --- SERVER OK ---"

$(CLIENT): $(LIBFT) $(OBJ_CLIENT)
	@$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT)
	@echo " --- CLIENT OK ---"

$(SERVER_BONUS): $(LIBFT) $(BONUS_OBJ_SERVER)
	@$(CC) $(BONUS_OBJ_SERVER) $(LIBFT) -o $(SERVER_BONUS)
	@echo " --- SERVER BONUS OK ---"

$(CLIENT_BONUS): $(LIBFT) $(BONUS_OBJ_CLIENT)
	@$(CC) $(BONUS_OBJ_CLIENT) $(LIBFT) -o $(CLIENT_BONUS)
	@echo " --- CLIENT BONUS OK ---"

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
	@$(RM) $(BONUS_OBJ_SERVER) $(BONUS_OBJ_CLIENT)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(CLIENT) $(SERVER)
	@$(RM) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re
