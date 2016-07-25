/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/25 17:27:15 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Imprime la mémoire :
*/

void		cw_vizualizer_memprint(t_proc *proc, WINDOW *win)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			wprintw(win, "\n");
		else
			wprintw(win, " ");
		if (i == proc->champions->pc) // partiellement faux, car seulement pour un PC ! Marche pas :/
		{
			wattron(win, COLOR_PAIR(1));
			wprintw(win, "%.2hhx", proc->mem[i]);
			wattroff(win, COLOR_PAIR(1));
		}
		else
			wprintw(win, "%.2hhx", proc->mem[i]);
		refresh();
		i++;
	}
}

/*
** À compiler avec "gcc -lncurses ..."
*/

void		cw_vizualizer(t_proc *proc)
{
	WINDOW	*win;

	initscr();
	win = newwin(80, 200, 0, 0);
	refresh();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	noecho();
	cw_vizualizer_memprint(proc, win);
	wrefresh(win);
	getch();
	delwin(win);
	endwin();
}

int			main(void)
{
	t_proc	proc;
	t_champion champ;

	proc.champions = &champ;
	champ.pc = 0;
	proc.champions->inst_c = 25;
	proc.champions->next = NULL;

	ft_bzero(proc.mem, MEM_SIZE);

	proc.mem[0] = 0x0b;
	proc.mem[1] = 0x68;
	proc.mem[2] = 0x01;
	proc.mem[3] = 0x00;
	proc.mem[4] = 0x0f;
	proc.mem[5] = 0x00;
	proc.mem[6] = 0x01;
	proc.mem[7] = 0x06;
	proc.mem[8] = 0x64;
	proc.mem[9] = 0x01;
	proc.mem[10] = 0x00;
	proc.mem[11] = 0x00;
	proc.mem[12] = 0x00;
	proc.mem[13] = 0x00;
	proc.mem[14] = 0x01;
	proc.mem[15] = 0x01;
	proc.mem[16] = 0x00;
	proc.mem[17] = 0x00;
	proc.mem[18] = 0x00;
	proc.mem[19] = 0x01;
	proc.mem[20] = 0x09;
	proc.mem[21] = 0xff;
	proc.mem[22] = 0xfb;

	cw_processor(&proc);

	return (0);
}
