/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/15 15:27:17 by gseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		asm_check_arg(char *line, int instruct)
{
	int	i;

	i = 0;
	while (line[i] != ' ' || line[i] != '\t')
		i++;
	// if (instruct == 1 || instruct == 9 || instruct == 10 || instruct == 15)
	// {
	// 	asm_check_dir(line);
	// }
	return (0);
}

/*
** Verifie les instructions
** !!! FREE LES TAB !!!
*/

int		asm_check_instruct(char *line)
{
	char	**tab;
	int		ret;

	ret = 0;
	if (ft_strchr(line, '\t'))
		tab = ft_strsplit(line, '\t');
	else
		tab = ft_strsplit(line, ' ');
	if (tab[0])
	{
		if (asm_check_label(tab[0]) == 0)
			ret = asm_instruct_name(line);
		asm_check_arg(line, ret);
	}
	return (1);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
** !!!! FAIRE DES FREE !!!!
*/

int		asm_copy_name_comment(char *line, t_header *head, int first, int last)
{
	if (ft_strncmp(NAME_CMD_STRING, line, first) == 0)
	{
		first = first + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->prog_name, ft_strsub(line, first, last));
		head->prog_name[PROG_NAME_LENGTH] = '\0';
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
		head->comment[COMMENT_LENGTH] = '\0';
	}
	if (g_line == 1 && !head->prog_name[0])
		return (asm_error(1));
	if (g_line > 1 && !head->comment[0])
		return (asm_error(2));
	return (1);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_handler_name_comment(int fd, char *line, t_header *head)
{
	int	first;
	int	last;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0' &&
	line[0] != '\n')
	{
		g_line++;
		ft_printf("%s\n", line);
		first = ft_strlen(NAME_CMD_STRING);
		last = ft_strlen(COMMENT_CMD_STRING);
		if (asm_copy_name_comment(line, head, first, last) == 0)
			return (0);
	}
	return (1);
}

/*
** !!!! FAIRE FONCTION QUI JOIN + FREE EN MEME TEMPS !!!!
** VOIR POUR REALLOC
*/
t_label *asm_label_init(void)
{
	t_label *new;
	new = malloc(sizeof(t_label));
	new->name = NULL;
	new->next = NULL;
	new->pos = 0;
	return (new);
}
t_label *asm_parse_line(char *line, int fd)
{
	t_label *new;
	new = NULL;

	if (get_next_line(fd, &line) == 1)
	{
			if (asm_check_label(line) == 1)
			{
				new = asm_label_init();
				new->name = ft_strsub(line, 0, ft_strclen(line, LABEL_CHAR));
				new->pos = 0;
				new->next = asm_parse_line(line, fd);
			}
			else
				return(asm_parse_line(line, fd));
	}
	return (new);
}
int        asm_parsing(char *champion, t_header *head)
{
    int         fd;
    int            pos;
    char         *line;
    t_label *label;

    pos = 0;
    line = NULL;

    if ((fd = open(champion, O_RDONLY, 0555)) == -1)
        return (-1);
    if (asm_handler_name_comment(fd, line, head) == 0)
        return (0);
		label = asm_parse_line(line, fd);
    // while (get_next_line(fd, &line) > 0)
    // {
    //     if (line[0] == COMMENT_CHAR)
    //         free(line);
    //     else if (!g_file)
    //     {
    //       if (asm_parse_line(line, label, pos))
    //         g_file = ft_strdup(line);
    //         g_file = ft_strjoin(g_file, "\n");
    //         free(line);
    //     }
    //     else
    //     {
		// 				asm_parse_line(line, label, pos);
    //         g_file = ft_strjoin(g_file, line);
    //         g_file = ft_strjoin(g_file, "\n");
    //         free(line);
    //     }
    // }
    while(label)
    {
        printf("qq----NAME : %s\n", label->name);
        label = label->next;
    }
    return (0);
}
