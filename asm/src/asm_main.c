/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 19:31:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		main(int argc, char **argv)
{
	t_header	*head;
	char		*line;

	line = NULL;
	head = asm_header_init();
	if (argc == 2)
		asm_parsing(argv[1], head);
	else
		ft_printf("Put one champion, please !")
	return (0);
}
