/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mode_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 15:48:25 by fpetras           #+#    #+#             */
/*   Updated: 2017/12/31 15:16:56 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_file(char *entry)
{
	struct stat buf;

	if (lstat(entry, &buf) == -1)
		return (0);
	return (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)
		|| S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)
		|| S_ISSOCK(buf.st_mode) || S_ISWHT(buf.st_mode)
		|| S_ISFIFO(buf.st_mode));
}

int		ft_is_link(char *entry)
{
	struct stat buf;

	if (lstat(entry, &buf) == -1)
		return (0);
	return (S_ISLNK(buf.st_mode));
}

int		ft_is_dir(char *entry)
{
	struct stat buf;

	if (lstat(entry, &buf) == -1)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

int		ft_is_invalid(char *entry)
{
	struct stat buf;

	if (lstat(entry, &buf) == -1)
		return (1);
	return (0);
}

int		ft_is_valid(char *entry)
{
	struct stat buf;

	if (lstat(entry, &buf) == -1)
		return (0);
	else if (S_ISREG(buf.st_mode))
		return (1);
	else if (S_ISDIR(buf.st_mode))
		return (2);
	else if (S_ISLNK(buf.st_mode))
		return (3);
	else if (S_ISSOCK(buf.st_mode))
		return (4);
	else if (S_ISBLK(buf.st_mode))
		return (5);
	else if (S_ISWHT(buf.st_mode))
		return (6);
	else if (S_ISCHR(buf.st_mode))
		return (7);
	else if (S_ISFIFO(buf.st_mode))
		return (8);
	else
		return (9);
}
