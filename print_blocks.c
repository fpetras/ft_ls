/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 10:41:49 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 15:00:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_blocks(t_list *lst, char *dir)
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
		if (path_entry)
			free(path_entry);
	}
	ft_printf("total %zu\n", total);
}
