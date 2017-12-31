# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 10:43:56 by fpetras           #+#    #+#              #
#    Updated: 2017/12/31 10:43:21 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_ls

SRC =	main.c \
		parse_options.c \
		process_operands.c \
		process_directory.c \
		padding.c \
		print_blocks.c \
		print_long_format.c \
		long_format_functions.c \
		file_mode_functions.c \
		error_functions.c \
		ft_unbr_len.c \
		ft_lstlen_ls.c \
		ft_lstsort_ls.c \
		ft_lstrevsort_ls.c \
		ft_lsttimesort_ls.c \
		ft_lstrevtimesort_ls.c \
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
