# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 10:43:56 by fpetras           #+#    #+#              #
#    Updated: 2017/12/21 15:10:34 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_ls

SRC =	main.c \
		parse_options.c \
		process_operands.c \
		process_directory.c \
		utility_functions.c \
		\
		ft_lstlen_ls.c \
		ft_lstsort_ls.c \
		ft_lstrevsort_ls.c \
		ft_lstfilesort_ls.c \
		ft_lstinvalidsort_ls.c \
		ft_lstfree_ls.c

OBJ =	$(SRC:.c=.o)

CC =	gcc

FLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME) $(SRC) libft/libft.a

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
