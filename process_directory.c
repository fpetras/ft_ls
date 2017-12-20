/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:31:00 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/20 13:32:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_entries(t_list *lst, t_options *ls)
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
/*	lst = tmp;
	while (ls->r_uppercase && lst)
	{
		str = (char*)lst->content;
		if (ft_is_dir(str)
			&& ft_strcmp(".", lst->content) && ft_strcmp("..", lst->content))
		{
			ft_printf("\n./%s:\n", lst->content);
			ft_process_directory(lst->content, ls);
		}
		lst = lst->next;
	}*/
}

void	ft_process_directory(char *dir, t_options *ls)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_list			*lst;

	lst = NULL;
	if (!dir)
		dirp = opendir(".");
	else
		dirp = opendir(dir);
	if (!dirp)
		return ;
	while ((entry = readdir(dirp)))
		ft_lstadd(&lst, ft_lstnew(entry->d_name, ft_strlen(entry->d_name) + 1));
	closedir(dirp);
	if (ft_lstlen_ls(lst) > 1)
		ls->r ? ft_lstrevsort_ls(lst) : ft_lstsort_ls(lst);
	ft_display_entries(lst, ls);
}
