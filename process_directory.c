/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:31:00 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 15:01:10 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_recursive_listing(t_list *lst, t_options *ls, char *dir)
{
	char *str;
	char *path_dir;

	while (lst)
	{
		str = (char*)lst->content;
		path_dir = ft_strjoin(dir, lst->content);
		if (ft_is_dir(path_dir) && ft_strcmp(".", str) && ft_strcmp("..", str))
		{
			ft_printf("\n%s:\n", path_dir);
			ft_process_directory(path_dir, path_dir, ls);
		}
		lst = lst->next;
		if (path_dir)
			free(path_dir);
	}
}

static void		ft_display_entries(t_list *lst, t_options *ls, char *dir)
{
	t_list	*tmp;

	tmp = lst;
	if (ls->l)
	{
		ft_display_blocks(lst, dir);
		ft_padding_sizes(lst, dir, ls);
	}
	while (lst)
	{
		if (ls->l)
			ft_print_long_format(lst->content, dir, ls);
		else
			ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
	lst = tmp;
	if (ls->r_uppercase)
		ft_recursive_listing(lst, ls, dir);
}

static t_list	*ft_sorting(t_list *lst, t_options *ls, char *dir)
{
	if (ls->r && !ls->t)
		return (ft_lstrevsort_ls(lst));
	else if (ls->t && !ls->r)
		return (ft_lsttimesort_ls(lst, dir));
	else if (ls->r && ls->t)
		return (ft_lstrevtimesort_ls(lst, dir));
	else
		return (ft_lstsort_ls(lst));
}

static char		*ft_path(char *parent_dir, char *dir)
{
	if (!parent_dir)
		parent_dir = ".";
	else if (ft_strequ(parent_dir, dir))
		return (ft_strjoin(dir, "/"));
	else
	{
		if (parent_dir[ft_strlen(parent_dir) - 1] != '/')
			parent_dir = ft_strjoin(parent_dir, "/");
		if (!ft_strequ(parent_dir, "./"))
			dir = ft_strjoin(parent_dir, dir);
	}
	return (ft_strjoin(dir, "/"));
}

void			ft_process_directory(char *parent_dir, char *dir, t_options *ls)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_list			*lst;

	lst = NULL;
	if (!dir)
		dir = ".";
	dir = ft_path(parent_dir, dir);
	dirp = opendir(dir);
	if (!dirp)
	{
		ft_error(dir);
		return ;
	}
	while ((entry = readdir(dirp)))
		if (ls->a || entry->d_name[0] != '.')
			ft_lstadd(&lst, ft_lstnew(entry->d_name,
			ft_strlen(entry->d_name) + 1));
	closedir(dirp);
	if (ft_lstlen_ls(lst) > 1)
		ft_sorting(lst, ls, dir);
	ft_display_entries(lst, ls, dir);
	ft_lstfree_ls(lst);
	if (dir)
		free(dir);
}
