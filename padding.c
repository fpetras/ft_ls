/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 11:29:48 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/30 12:16:56 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_set_padding_sizes(t_options *ls, int *tmp)
{
	ls->nlink = (tmp[0] > ls->nlink) ? tmp[0] : ls->nlink;
	ls->usr_name = (tmp[1] > ls->usr_name) ? tmp[1] : ls->usr_name;
	ls->grp_name = (tmp[2] > ls->grp_name) ? tmp[2] : ls->grp_name;
	ls->size = (tmp[3] > ls->size) ? tmp[3] : ls->size;
}

static void	ft_reset_padding_sizes(t_options *ls)
{
	ls->nlink = 0;
	ls->usr_name = 0;
	ls->grp_name = 0;
	ls->size = 0;
}

void		ft_padding_sizes_ops(t_list *ops, t_options *ls)
{
	int				tmp[4];
	struct stat		buf;
	struct passwd	*pwd;
	struct group	*grp;

	ft_reset_padding_sizes(ls);
	while (ops)
	{
		if (ft_is_valid(ops->content) && !ft_is_dir(ops->content))
		{
			if (lstat(ops->content, &buf) != -1)
			{
				tmp[0] = ft_unbr_len(buf.st_nlink);
				if ((pwd = getpwuid(buf.st_uid)))
					tmp[1] = ft_strlen(pwd->pw_name);
				if ((grp = getgrgid(buf.st_gid)))
					tmp[2] = ft_strlen(grp->gr_name);
				tmp[3] = ft_unbr_len(buf.st_size);
			}
			ft_set_padding_sizes(ls, tmp);
		}
		ops = ops->next;
	}
}

void		ft_padding_sizes(t_list *lst, char *dir, t_options *ls)
{
	int				tmp[4];
	char			*path_entry;
	struct stat		buf;
	struct passwd	*pwd;
	struct group	*grp;

	ft_reset_padding_sizes(ls);
	while (lst)
	{
		path_entry = ft_strjoin(dir, lst->content);
		if (lstat(path_entry, &buf) != -1)
		{
			tmp[0] = ft_unbr_len(buf.st_nlink);
			if ((pwd = getpwuid(buf.st_uid)))
				tmp[1] = ft_strlen(pwd->pw_name);
			if ((grp = getgrgid(buf.st_gid)))
				tmp[2] = ft_strlen(grp->gr_name);
			tmp[3] = ft_unbr_len(buf.st_size);
		}
		ft_set_padding_sizes(ls, tmp);
		lst = lst->next;
		free(path_entry);
	}
}
