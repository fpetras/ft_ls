/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:31:00 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/30 12:22:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_recursive_listing(t_list *lst, t_options *ls, char *dir)
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

static void	ft_display_blocks(t_list *lst, char *dir)
{
	char		*path_entry;
	size_t		total;
	struct stat	buf;

	total = 0;
	if (!lst)
		return ;
	while (lst)
	{
		path_entry = ft_strjoin(dir, lst->content);
		if (lstat(path_entry, &buf) != -1)
			total += buf.st_blocks;
		lst = lst->next;
		free(path_entry);
	}
	ft_printf("total %zu\n", total);
}

static void	ft_display_entries(t_list *lst, t_options *ls, char *dir)
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

static void	ft_error(char *dir)
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
	ft_dprintf(2, "ft_ls: %s: %s\n", tab[i], strerror(errno));
	free(tab[i]);
	free(tab);
	free(dir);
}

static char	*ft_path(char *parent_dir, char *dir)
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

void		ft_process_directory(char *parent_dir, char *dir, t_options *ls)
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
	{
		if (ls->a || entry->d_name[0] != '.')
			ft_lstadd(&lst, ft_lstnew(entry->d_name,
			ft_strlen(entry->d_name) + 1));
	}
	closedir(dirp);
	if (ft_lstlen_ls(lst) > 1)
		ls->r ? ft_lstrevsort_ls(lst) : ft_lstsort_ls(lst);
	ft_display_entries(lst, ls, dir);
	ft_lstfree_ls(lst);
	free(dir);
}
