/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 10:19:26 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/29 11:53:19 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	t_options	ls;

	i = 1;
	ft_bzero(&ls, sizeof(t_options));
	if (ac > 1)
		if (!(i = ft_parse_options(ac, av, &ls)))
			return (1);
	if (!av[i] || (!ft_strcmp(".", av[i]) && !av[i + 1]))
		ft_process_directory(NULL, av[i], &ls);
	else
		ft_get_operands(i, ac, av, &ls);
	return (0);
}
