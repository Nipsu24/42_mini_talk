# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/05/08 16:27:56 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CC = cc
FLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

SRC_DIR = ./
OBJ_DIR = obj
LIBFT = ./libft

FILES1 = server.c error_check_utils.c utils.c
FILES2 = client.c error_check_utils.c utils.c
BONUS_FILES1 = server_bonus.c error_check_utils_bonus.c utils_bonus.c
BONUS_FILES2 = client_bonus.c error_check_utils_bonus.c utils_bonus.c

OBJ_FILES1 = $(addprefix $(OBJ_DIR)/, $(FILES1:.c=.o))
OBJ_FILES2 = $(addprefix $(OBJ_DIR)/, $(FILES2:.c=.o))
OBJ_FILES1_BONUS = $(BONUS_FILES1:.c=.o)
OBJ_FILES2_BONUS = $(BONUS_FILES2:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_FILES1) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(SERVER) $(OBJ_FILES1) -L$(LIBFT) -lft
	@echo "\033[32m$(SERVER) has been built successfully!\033[0m"

$(CLIENT): $(OBJ_FILES2) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJ_FILES2) -L$(LIBFT) -lft
	@echo "\033[32m$(CLIENT) has been built successfully!\033[0m"

fsanitize1: 
	$(CC) -o $(SERVER) $(FILES1) -L$(LIBFT) -lft -g -fsanitize=address -static-libsan 
fsanitize2: 
	$(CC) -o $(CLIENT) $(FILES2) -L$(LIBFT) -lft -g -fsanitize=address -static-libsan 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)mini_talk.h | $(OBJ_DIR) 
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)
	rm -rf $(OBJ_FILES1_BONUS)
	rm -rf $(OBJ_FILES2_BONUS)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(SERVER)
	rm -f $(CLIENT)
	rm -f .bonus

re: fclean all

bonus: .bonus
.bonus: $(LIBFT) $(OBJ_FILES1_BONUS) $(OBJ_FILES2_BONUS)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(SERVER) $(BONUS_FILES1) -L$(LIBFT) -lft 
	$(CC) $(FLAGS) -o $(CLIENT) $(BONUS_FILES2) -L$(LIBFT) -lft
	@echo "\033[32m$(SERVER)- and $(CLIENT)-bonus has been built successfully!\033[0m"
	@touch .bonus

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
