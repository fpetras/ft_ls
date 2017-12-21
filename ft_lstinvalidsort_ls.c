/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinvalidsort_ls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:43:35 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/21 07:59:07 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_lstinvalidsort_ls(t_list *lst)
{
	void		*swap;
	t_list		*tmp;

	tmp = lst;
	while (lst && lst->next)
	{
		if (ft_is_invalid(lst->content) && !ft_is_invalid(lst->next->content))
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
