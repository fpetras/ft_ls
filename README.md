# ft_ls

A recreation of the Unix command "ls".

This project is about discovering a sub-system of functions of the system's API, the associated data structures, as well as memory allocation and data management.

## Installation:

`git clone --recurse-submodules https://github.com/fpetras/ft_ls.git && cd ft_ls && make`

## Usage:

`usage: ./ft_ls [-Ralrt1] [file ...]`

The following options are available:

 - **`-1`** &ensp; Force output to be one entry per line.
 - **`-a`** &ensp; Include directory entries whose names begin with a dot.
 - **`-l`** &ensp; List in long format.
 - **`-R`** &ensp; Recursively list subdirectories encountered.
 - **`-r`** &ensp; Reverse the order of the sort to get reverse lexicographical order\
 &ensp;&ensp;&ensp;&ensp; or the oldest entries first (if combined with -t).
 - **`-t`** &ensp; Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.
 
 The **`-1`** and **`-l`** options override each other; the last one specified determines the format used.
 
 ### In action:
 
 ![GIF](http://g.recordit.co/32i6i2LakI.gif)
 
 ## Code snippets:
 
 ```C
void    ft_recursive_listing(t_list *lst, t_options *ls, char *dir)
{
    char *str;
    char *path_dir;

    while (lst)
    {
        str = (char*)lst->content;
        path_dir = ft_strjoin(dir, lst->content);
        if (ft_is_dir(path_dir) && ft_strcmp(".", str) && ft_strcmp("..", str))
        {
            ft_printf("\n%s:\n", path_dir);
            ft_process_directory(path_dir, path_dir, ls);
        }
        lst = lst->next;
        (path_dir) ? free(path_dir) : 0;
    }
}
```
```C
char    *ft_path(char *parent_dir, char *dir)
{
    if (!parent_dir)
        parent_dir = ".";
    else if (ft_strequ(parent_dir, dir))
        return (ft_strjoin(dir, "/"));
    else
    {
        if (parent_dir[ft_strlen(parent_dir) - 1] != '/')
            parent_dir = ft_strjoin(parent_dir, "/");
        if (!ft_strequ(parent_dir, "./"))
            dir = ft_strjoin(parent_dir, dir);
    }
    return (ft_strjoin(dir, "/"));
}
```
```C
void    ft_process_directory(char *parent_dir, char *dir, t_options *ls)
{
    DIR             *dirp;
    struct dirent   *entry;
    t_list          *lst;

    lst = NULL;
    if (!dir)
        dir = ".";
    dir = ft_path(parent_dir, dir);
    dirp = opendir(dir);
    if (!dirp)
    {
        ft_error(dir);
        return ;
    }
    while ((entry = readdir(dirp)))
        if (ls->a || entry->d_name[0] != '.')
            ft_lstadd(&lst, ft_lstnew(entry->d_name,
            ft_strlen(entry->d_name) + 1));
    closedir(dirp);
    (ft_lstlen_ls(lst) > 1) : ft_sorting(lst, ls, dir) : 0;
    ft_display_entries(lst, ls, dir);
    ft_lstfree_ls(lst);
    (dir) ? free(dir) : 0;
}
```
 
 ## [Subject](https://github.com/fpetras/42-subjects/blob/master/ft_ls.en.pdf "ft_ls.en.pdf")
