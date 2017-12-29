/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:13:18 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 09:10:16 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_file(char *entry)
{
	struct stat buf;

	if (stat(entry, &buf) == -1)
		return (0);
	return (S_ISREG(buf.st_mode));
}

int		ft_is_dir(char *entry)
{
	struct stat buf;

	if (stat(entry, &buf) == -1)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

int		ft_is_invalid(char *entry)
{
	struct stat buf;

	if ((stat(entry, &buf) == -1))
		return (1);
	return (0);
}

int		ft_is_valid(char *entry)
{
	struct stat buf;

	if (stat(entry, &buf) == -1)
		return (0);
	else if (S_ISREG(buf.st_mode))
		return (1);
	else if (S_ISDIR(buf.st_mode))
		return (2);
	else if (S_ISLNK(buf.st_mode))
		return (3);
	else if (S_ISSOCK(buf.st_mode))
		return (4);
	else if (S_ISBLK(buf.st_mode))
		return (5);
	else if (S_ISWHT(buf.st_mode))
		return (6);
	else if (S_ISCHR(buf.st_mode))
		return (7);
	else if (S_ISFIFO(buf.st_mode))
		return (8);
	else
		return (9);
}

void	ft_no_such_file_or_directory(t_list *ops)
{
	struct stat buf;

	while (ops)
	{
		if ((stat(ops->content, &buf) == -1) && !ft_is_dir(ops->content))
			ft_dprintf(2, "ft_ls: %s: %s\n", ops->content, strerror(errno));
		ops = ops->next;
	}
}
