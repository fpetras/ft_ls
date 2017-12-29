/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilesort_ls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:43:35 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 11:01:52 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_lstfilesort_ls(t_list *lst)
{
	void		*swap;
	t_list		*tmp;

	tmp = lst;
	while (lst && lst->next)
	{
		if (!ft_is_file(lst->content) && ft_is_valid(lst->next->content)
		&& !ft_is_dir(lst->next->content))
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
