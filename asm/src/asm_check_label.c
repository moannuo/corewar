/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 18:34:32 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/22 11:03:44 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check si le label existe bien dans la struct(header)
*/

int		asm_match_label(t_label *label, char *str)
{
	int len;

	len = 0;
	while (label)
	{
		while (str[len] && str[len] != ' ' && str[len] != '\t' &&
		str[len] != '\n' && str[len] != SEPARATOR_CHAR)
			len++;
		if (ft_strncmp(label->name, str, len) == 0)
		{
			if (!label->name[len])
				return (1);
		}
		label = label->next;
	}
	return (asm_error(10));
}

/*
** Check si le label existe bien dans la struct(header)
*/

int		asm_check_label_exist(t_label *label, char *str)
{
	if (!str)
		return (0);
	while (*str && *str != DIRECT_CHAR && *str != '\0')
	{
		str++;
		if (*str == '%')
		{
			str++;
			if (*str == LABEL_CHAR)
			{
				str++;
				asm_match_label(label, str);
			}
		}
	}
	label = NULL;
	return (1);
}

/*
** Check si il y a un label et si celui-ci et le label_char sont bien formatés
*/

int		asm_check_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == LABEL_CHAR && i > 0)
	{
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\n' || str[i] == '\0' || str[i] == COMMENT_CHAR)
			return (1);
		return (2);
	}
	else if (str[i] && str[i] != ' ' && str[i] != '\0' &&
	str[i] != '\n' && str[i] != '\t' && str[i] != COMMENT_CHAR)
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0')
			return (asm_error(4));
		return (asm_error(3));
	}
	return (0);
}

/*
** Check si il y a un doublon dans les labels
*/

int		asm_check_double_label(t_label *label)
{
	t_label *start;

	start = label;
	if (!label)
		return (1);
	label = label->next;
	while (label)
	{
		if (!ft_strcmp(start->name, label->name))
			return (asm_error(9));
		label = label->next;
	}
	return (asm_check_double_label(start->next));
}
