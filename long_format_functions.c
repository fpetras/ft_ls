/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:06:36 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 10:35:06 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_link(char *entry, char *path_entry)
{
	int		count;
	char	buf[1024];

	if (path_entry)
	{
		if ((count = readlink(path_entry, buf, sizeof(buf) - 1)) == -1)
			return ;
		buf[count] = '\0';
	}
	else
	{
		if ((count = readlink(entry, buf, sizeof(buf) - 1)) == -1)
			return ;
		buf[count] = '\0';
	}
	ft_printf("%s -> %s\n", entry, buf);
}

void	ft_print_time(struct stat *buf)
{
	char *str;

	if (!(str = ctime(&buf->st_mtime)))
		return ;
	ft_printf("%.12s ", &str[4]);
}

void	ft_padding(struct stat *buf, struct passwd *pwd, struct group *grp,
			t_options *ls)
{
	int pad;

	pad = 0;
	if (ls->which_padding == 1)
		pad = (ls->nlink + 2) - ft_unbr_len(buf->st_nlink);
	else if (ls->which_padding == 2)
		pad = (ls->usr_name + 2) - ft_strlen(pwd->pw_name);
	else if (ls->which_padding == 3)
		pad = (ls->grp_name + 2) - ft_strlen(grp->gr_name);
	else if (ls->which_padding == 4)
	{
		if (S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))
			pad = (ls->rdev_maj + 1) - ft_unbr_len(major(buf->st_rdev));
		else
			pad = (ls->size) - ft_unbr_len(buf->st_size);
	}
	else if (ls->which_padding == 5)
		pad = (ls->rdev_min + 1) - ft_unbr_len(minor(buf->st_rdev));
	while (pad)
	{
		ft_printf(" ");
		pad--;
	}
	ls->which_padding++;
}

void	ft_print_permissions(mode_t mode)
{
	char str[10];

	str[0] = (S_IRUSR & mode) ? 'r' : '-';
	str[1] = (S_IWUSR & mode) ? 'w' : '-';
	str[2] = (S_IXUSR & mode) ? 'x' : '-';
	if (S_ISUID & mode)
		str[2] = (S_IXUSR & mode) ? 's' : 'S';
	str[3] = (S_IRGRP & mode) ? 'r' : '-';
	str[4] = (S_IWGRP & mode) ? 'w' : '-';
	str[5] = (S_IXGRP & mode) ? 'x' : '-';
	if (S_ISGID & mode)
		str[5] = (S_IXGRP & mode) ? 's' : 'S';
	str[6] = (S_IROTH & mode) ? 'r' : '-';
	str[7] = (S_IWOTH & mode) ? 'w' : '-';
	str[8] = (S_IXOTH & mode) ? 'x' : '-';
	if (S_ISVTX & mode)
		str[8] = (S_IXOTH & mode) ? 't' : 'T';
	str[9] = '\0';
	ft_printf("%s", str);
}

void	ft_print_file_mode(mode_t mode)
{
	if (S_ISBLK(mode))
		ft_printf("b");
	else if (S_ISCHR(mode))
		ft_printf("c");
	else if (S_ISDIR(mode))
		ft_printf("d");
	else if (S_ISLNK(mode))
		ft_printf("l");
	else if (S_ISFIFO(mode))
		ft_printf("p");
	else if (S_ISSOCK(mode))
		ft_printf("s");
	else if (S_ISWHT(mode))
		ft_printf("w");
	else if (S_ISREG(mode))
		ft_printf("-");
}
