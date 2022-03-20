# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 20:17:28 by anonymous         #+#    #+#              #
#    Updated: 2022/03/20 12:26:06 by anonymous        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER			:=	server
NAME_CLIENT			:=	client

LIB_DIR				:=	lib

LIBFT_INC_DIR		:=	includes
LIBFT_DIR			:=	libft
LIBFT				:=	$(LIB_DIR)/libft.a

LIB_INCLUDE			:=	libft.h ft_printf.h get_next_line.h
LIB_INCLUDE			:=	$(addprefix $(LIBFT_DIR)/$(LIBFT_INC_DIR)/, $(LIB_INCLUDE))
INCLUDES			:=	minitalk.h $(LIB_INCLUDE)

SRC_SERVER			:=	server.c
SRC_CLIENT			:=	client.c
OBJ_SERVER			:=	$(SRC_SERVER:%.c=%.o)
OBJ_CLIENT			:=	$(SRC_CLIENT:%.c=%.o)

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror
LDLIBS				:=	-L$(LIB_DIR) -lft

.PHONY : all bonus clean fclean re

all : $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT) : $(LIB_DIR)
	$(MAKE) --directory=$(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)

$(NAME_SERVER) : $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LDLIBS) -o $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LDLIBS) -o $(NAME_CLIENT)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR) :
	mkdir -p $@

clean :
	rm -rf *.o $(LIB_DIR)
	$(MAKE) clean --directory=$(LIBFT_DIR)

fclean : clean
	rm -rf $(NAME_SERVER)
	rm -rf $(NAME_CLIENT)
	$(MAKE) fclean --directory=$(LIBFT_DIR)

re : fclean all