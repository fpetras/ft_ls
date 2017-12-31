/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:07:34 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 10:35:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_device_id(struct stat *buf, struct passwd *pwd,
			struct group *grp, t_options *ls)
{
	ft_printf("%d,", major(buf->st_rdev));
	ft_padding(buf, pwd, grp, ls);
	ft_printf("%d ", minor(buf->st_rdev));
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
	if (S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))
		ft_print_device_id(buf, pwd, grp, ls);
	else
		ft_printf("%d ", buf->st_size);
	ft_print_time(buf);
	S_ISLNK(buf->st_mode) ? ft_print_link(entry, path_entry) :
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
