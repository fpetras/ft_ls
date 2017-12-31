/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:33:31 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 15:30:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_process_operands(t_list *ops, t_options *ls, int nb_ops)
{
	t_list	*tmp;

	tmp = NULL;
	while (ops)
	{
		if (ft_is_valid(ops->content) && !ft_is_dir(ops->content))
		{
			if (ls->l)
				ft_print_long_format(ops->content, NULL, ls);
			else if (!ft_is_link(ops->content))
				ft_printf("%s\n", ops->content);
		}
		if (ft_is_dir(ops->content) || (ft_is_link(ops->content) && !ls->l))
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

static void	ft_sort_operands(t_list *ops, t_options *ls)
{
	ft_lstsort_ls(ops);
	ft_lstfilesort_ls(ops);
	ft_lstinvalidsort_ls(ops);
	ft_no_such_file_or_directory(ops);
	if (ls->r && !ls->t)
		ft_lstrevsort_ls(ops);
	else if (ls->t && !ls->r)
		ft_lsttimesort_ops_ls(ops);
	else if (ls->r && ls->t)
		ft_lstrevtimesort_ops_ls(ops);
	if (ls->r || ls->t)
	{
		ft_lstfilesort_ls(ops);
		ft_lstinvalidsort_ls(ops);
	}
	if (ls->l)
		ft_padding_sizes_ops(ops, ls);
	ft_process_operands(ops, ls, ft_lstlen_ls(ops));
}

void		ft_get_operands(int i, int ac, char **av, t_options *ls)
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
