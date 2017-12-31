/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrevtimesort_ls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 08:01:19 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 11:04:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_revtimesort(t_list *lst, struct stat *buf, struct stat *buf2)
{
	time_t	diff;
	void	*swap;

	if (lst && lst->next)
	{
		diff = buf->st_mtime - buf2->st_mtime;
		if (diff > 0)
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			return (1);
		}
		else if (diff == 0)
		{
			if (ft_strcmp(lst->content, lst->next->content) < 0)
			{
				swap = lst->content;
				lst->content = lst->next->content;
				lst->next->content = swap;
				return (1);
			}
		}
	}
	return (0);
}

t_list		*ft_lstrevtimesort_ops_ls(t_list *lst)
{
	int			ret;
	int			ret2;
	t_list		*tmp;
	struct stat	buf;
	struct stat	buf2;

	tmp = lst;
	while (lst && lst->next)
	{
		ret = lstat(lst->content, &buf);
		ret2 = lstat(lst->next->content, &buf2);
		if (ret != -1 && ret2 != -1)
			if (ft_revtimesort(lst, &buf, &buf2))
				lst = tmp;
			else
				lst = lst->next;
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

t_list		*ft_lstrevtimesort_ls(t_list *lst, char *dir)
{
	int			ret[2];
	char		*path_entry[2];
	t_list		*tmp;
	struct stat	buf;
	struct stat	buf2;

	tmp = lst;
	while (lst && lst->next)
	{
		path_entry[0] = ft_strjoin(dir, lst->content);
		path_entry[1] = ft_strjoin(dir, lst->next->content);
		ret[0] = lstat(path_entry[0], &buf);
		ret[1] = lstat(path_entry[1], &buf2);
		free(path_entry[0]);
		free(path_entry[1]);
		if (ret[0] != -1 && ret[1] != -1)
			if (ft_revtimesort(lst, &buf, &buf2))
				lst = tmp;
			else
				lst = lst->next;
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
