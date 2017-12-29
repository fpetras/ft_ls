/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:33:31 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 09:04:05 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_process_operands(t_list *ops, t_options *ls)
{
	int		nb_ops;
	t_list	*tmp;

	nb_ops = ft_lstlen_ls(ops);
	tmp = NULL;
	while (ops)
	{
		if (ft_is_valid(ops->content) && !ft_is_dir(ops->content))
			ft_printf("%s\n", ops->content);
		else if (ft_is_dir(ops->content))
		{
			if (nb_ops > 1)
			{
				if (tmp)
					ft_printf("\n");
				ft_printf("%s:\n", ops->content);
			}
			ft_process_directory(ops->content, ops->content, ls);
		}
		tmp = ops;
		ops = ops->next;
	}
}

void	ft_sort_operands(t_list *ops, t_options *ls)
{
	ft_lstsort_ls(ops);
	ft_lstfilesort_ls(ops);
	ft_no_such_file_or_directory(ops);
	if (ls->r)
	{
		ft_lstrevsort_ls(ops);
		ft_lstfilesort_ls(ops);
		ft_lstinvalidsort_ls(ops);
	}
	ft_process_operands(ops, ls);
}

void	ft_get_operands(int i, int ac, char **av, t_options *ls)
{
	t_list *ops;

	ops = NULL;
	while (i < ac)
	{
		ft_lstadd(&ops, ft_lstnew(av[i], ft_strlen(av[i]) + 1));
		i++;
	}
	ft_sort_operands(ops, ls);
	ft_lstfree_ls(ops);
}
