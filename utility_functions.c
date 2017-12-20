/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:13:18 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/20 17:37:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_dir(char *entry)
{
	struct stat buf;

	if (stat(entry, &buf) == -1)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

int		ft_is_file(char *entry)
{
	struct stat buf;

	if (stat(entry, &buf) == -1)
		return (0);
	return (S_ISREG(buf.st_mode));
}

int		ft_is_invalid(char *entry)
{
	struct stat buf;

	if ((stat(entry, &buf) == -1))
		return (1);
	return (0);
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
