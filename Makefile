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
SRC_DIR := src
OBJ_DIR := obj
FUNC_SERVER := server.c
FUNC_CLIENT := client.c
SRC_SERVER := $(addprefix $(SRC_DIR)/,$(FUNC_SERVER))
SRC_CLIENT := $(addprefix $(SRC_DIR)/,$(FUNC_CLIENT))
OBJ_SERVER := $(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT := $(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_CLIENT) $(FT_PRINTF) $(SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) -o $(NAME) $(LIBRARIES)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) -o $(SERVER) $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_DIR)/minitalk.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_DIR)/minitalk.h
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
