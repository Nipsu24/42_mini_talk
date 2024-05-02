# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/04/22 16:12:57 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CC = cc
FLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

SRC_DIR = ./
OBJ_DIR = obj
LIBFT = ./libft

FILES1 = server.c
FILES2 = client.c \
		 error_check_utils.c

OBJ_FILES1 = $(addprefix $(OBJ_DIR)/, $(FILES1:.c=.o))
OBJ_FILES2 = $(addprefix $(OBJ_DIR)/, $(FILES2:.c=.o))

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_FILES1) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(SERVER) $(OBJ_FILES1) -L$(LIBFT) -lft
	@echo "\033[32m$(SERVER) has been built successfully!\033[0m"

$(CLIENT): $(OBJ_FILES2) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJ_FILES2) -L$(LIBFT) -lft
	@echo "\033[32m$(SERVER) has been built successfully!\033[0m"

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
	

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
