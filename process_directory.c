/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:31:00 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 10:37:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_recursive_listing(t_list *lst, t_options *ls, char *dir)
{
	char *str;
	char *path_dir;

	while (lst)
	{
		str = (char*)lst->content;
		path_dir = ft_strjoin(dir, lst->content);
		if (ft_is_dir(path_dir) && ft_strcmp(".", str) && ft_strcmp("..", str))
		{
			if (ls->a || str[0] != '.')
			{
				ft_printf("\n%s:\n", path_dir);
				ft_process_directory(path_dir, path_dir, ls);
			}
		}
		lst = lst->next;
		if (path_dir)
			free(path_dir);
	}
}

void	ft_display_entries(t_list *lst, t_options *ls, char *dir)
{
	char	*str;
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		str = (char*)lst->content;
		if (ls->a || str[0] != '.')
			ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
	lst = tmp;
	if (ls->r_uppercase)
		ft_recursive_listing(lst, ls, dir);
}

char	*ft_path(char *parent_dir, char *dir)
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

void	ft_dir_name(char *dir)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_strsplit(dir, '/');
	while (tab[i + 1])
	{
		free(tab[i]);
		i++;
	}
	ft_printf("%s", tab[i]);
	free(tab[i]);
	free(tab);
}

void	ft_process_directory(char *parent_dir, char *dir, t_options *ls)
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
		ft_dprintf(2, "ft_ls: ");
		ft_dir_name(dir);
		ft_dprintf(2, ": %s\n", strerror(errno));
		free(dir);
		return ;
	}
	while ((entry = readdir(dirp)))
		ft_lstadd(&lst, ft_lstnew(entry->d_name, ft_strlen(entry->d_name) + 1));
	closedir(dirp);
	if (ft_lstlen_ls(lst) > 1)
		ls->r ? ft_lstrevsort_ls(lst) : ft_lstsort_ls(lst);
	ft_display_entries(lst, ls, dir);
	ft_lstfree_ls(lst);
	free(dir);
}
