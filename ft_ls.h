/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:35:42 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/21 09:53:09 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <termios.h>
# include <time.h>
# include <uuid/uuid.h>

typedef struct	s_options
{
	int			l;
	int			r_uppercase;
	int			a;
	int			r;
	int			t;
}				t_options;

int				ft_parse_options(int ac, char **av, t_options *ls);
void			ft_process_directory(char *dir, t_options *ls);
void			ft_get_operands(int i, int ac, char **av, t_options *ls);
int				ft_is_dir(char *entry);
int				ft_is_file(char *entry);
int				ft_is_invalid(char *entry);
void			ft_no_such_file_or_directory(t_list *ops);

size_t			ft_lstlen_ls(t_list *lst);
t_list			*ft_lstsort_ls(t_list *lst);
t_list			*ft_lstrevsort_ls(t_list *lst);
t_list			*ft_lstfilesort_ls(t_list *lst);
t_list			*ft_lstinvalidsort_ls(t_list *lst);
void			ft_lstfree_ls(t_list *lst);

#endif
