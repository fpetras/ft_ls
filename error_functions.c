/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 15:49:38 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 14:57:23 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(char *dir)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_strsplit(dir, '/');
	while (tab[i + 1])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	ft_dprintf(2, "ft_ls: %s: %s\n", tab[i], strerror(errno));
	if (tab[i])
		free(tab[i]);
	if (tab)
		free(tab);
	if (dir)
		free(dir);
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
