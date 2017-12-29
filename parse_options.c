/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 14:25:58 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 12:12:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_illegal_option(char opt)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\n", opt);
	ft_dprintf(2, "usage: ./ft_ls [-Ralrt1] [file ...]\n");
	return (0);
}

static void	ft_set_options(char opt, t_options *ls)
{
	ls->l = (opt == 'l') ? 1 : ls->l;
	ls->r_uppercase = (opt == 'R') ? 1 : ls->r_uppercase;
	ls->a = (opt == 'a') ? 1 : ls->a;
	ls->r = (opt == 'r') ? 1 : ls->r;
	ls->t = (opt == 't') ? 1 : ls->t;
	ls->l = (opt == '1') ? 0 : ls->l;
}

int			ft_parse_options(int ac, char **av, t_options *ls)
{
	int i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 1;
		while (av[i][j] != '\0' && av[i][0] == '-')
		{
			if (!(ft_strcmp("--", av[i])))
				return (i + 1);
			else if (ft_strchr("1lRart", av[i][j]))
				ft_set_options(av[i][j], ls);
			else if (!ft_strchr("1lRart", av[i][j]))
				return (ft_illegal_option(av[i][j]));
			j++;
		}
		if (av[i][0] != '-' || !ft_strcmp("-", av[i]))
			return (i);
		i++;
	}
	return (i);
}
