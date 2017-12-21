/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 07:26:09 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/21 13:59:13 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_lstfree_ls(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		lst = lst->next;
	}
}
