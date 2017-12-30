/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:07:34 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/30 13:24:53 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_link(char *entry, char *path_entry)
{
	int		count;
	char 	buf[1024];

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

static void	ft_print_time(struct stat *buf)
{
	char *str;

	if (!(str = ctime(&buf->st_mtime)))
		return ;
	ft_printf("%.12s ", &str[4]);
}

static void	ft_print_permissions(mode_t mode)
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

static void	ft_print_file_mode(mode_t mode)
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

static void	ft_padding(struct stat *buf, struct passwd *pwd, struct group *grp,
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
		pad = (ls->size) - ft_unbr_len(buf->st_size);
	while (pad)
	{
		ft_printf(" ");
		pad--;
	}
	ls->which_padding++;
}

static void	ft_print_long_format2(char *entry, char *path_entry,
			t_options *ls, struct stat *buf)
{
	struct passwd	*pwd;
	struct group	*grp;

	if (!(pwd = getpwuid(buf->st_uid)))
		return ;
	if (!(grp = getgrgid(buf->st_gid)))
		return ;
	ft_print_file_mode(buf->st_mode);
	ft_print_permissions(buf->st_mode);
	ls->which_padding = 1;
	ft_padding(buf, pwd, grp, ls);
	ft_printf("%d ", buf->st_nlink);
	ft_printf("%s", pwd->pw_name);
	ft_padding(buf, pwd, grp, ls);
	ft_printf("%s", grp->gr_name);
	ft_padding(buf, pwd, grp, ls);
	ft_padding(buf, pwd, grp, ls);
	ft_printf("%d ", buf->st_size);
	ft_print_time(buf);
	if (S_ISLNK(buf->st_mode))
		ft_print_link(entry, path_entry);
	else
		ft_printf("%s\n", entry);
}

void		ft_print_long_format(char *entry, char *path, t_options *ls)
{
	int			ret;
	char		*path_entry;
	struct stat	buf;

	if (path)
	{
		path_entry = ft_strjoin(path, entry);
		ret = lstat(path_entry, &buf);
	}
	else
		ret = lstat(entry, &buf);
	if (ret == -1)
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", entry, strerror(errno));
		return ;
	}
	ft_print_long_format2(entry, path_entry, ls, &buf);
	if (path_entry)
		free(path_entry);
}
