NAME := client
SERVER := server
LIBFT_DIR := ./ftprintf/libft
FT_PRINTF_DIR := ./ftprintf
FT_PRINTF := $(FT_PRINTF_DIR)/libftprintf.a
HEADER_DIR := ./headers
HEADERS := -I$(FT_PRINTF_DIR) -I$(LIBFT_DIR) -I$(HEADER_DIR)
LIBRARIES := -L$(FT_PRINTF_DIR) -lftprintf
CC := gcc
CFLAGS := -Wall -Werror -Wextra
RM := rm -rf
SERVER_DIR := src/server
CLIENT_DIR := src/client
OBJ_DIR := obj
FUNC_SERVER := server.c
FUNC_CLIENT := client.c
SRC_SERVER := $(addprefix $(SERVER_DIR)/,$(FUNC_SERVER))
SRC_CLIENT := $(addprefix $(CLIENT_DIR)/,$(FUNC_CLIENT))
OBJ_SERVER := $(SRC_SERVER:$(SERVER_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT := $(SRC_CLIENT:$(CLIENT_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_CLIENT) $(FT_PRINTF) $(SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) -o $(NAME) $(LIBRARIES)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) -o $(SERVER) $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SERVER_DIR)/%.c $(HEADER_DIR)/server.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c $(HEADER_DIR)/client.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	$(RM) $(NAME) $(SERVER)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

bonus: all

re: fclean all
.PHONY: all clean fclean re bonus
