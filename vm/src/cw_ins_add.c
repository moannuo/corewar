/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 14:49:48 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/28 14:15:10 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 3 registres en paramètre, additionne le contenu des
** 2 premiers et met le résultat dans le troisième. Cette opération modifie le
** carry. add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5.
*/

int			cw_ins_add(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	int		reg1;
	int		reg2;
	int		reg3;

	reg1 = (int)tmp->reg[proc->mem[tmp->pc + 2]];
	reg2 = (int)tmp->reg[proc->mem[tmp->pc + 3]];
	reg3 = reg1 + reg2;
	tmp->reg[proc->mem[tmp->pc + 4]][0] = (reg3 >> 24) & 0xff;
	tmp->reg[proc->mem[tmp->pc + 4]][1] = (reg3 >> 16) & 0xff;
	tmp->reg[proc->mem[tmp->pc + 4]][2] = (reg3 >> 8) & 0xff;
	tmp->reg[proc->mem[tmp->pc + 4]][3] = reg3 & 0xff;
	mvprintw(0, 0, "reg1 == %d || reg2 == %d || reg3 == %d || %.2hhx %.2hhx %.2hhx %.2hhx", reg1, reg2, reg3, tmp->reg[proc->mem[tmp->pc + 4]][0], tmp->reg[proc->mem[tmp->pc + 4]][1], tmp->reg[proc->mem[tmp->pc + 4]][2], tmp->reg[proc->mem[tmp->pc + 4]][3]);

	return (5);
}
