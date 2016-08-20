/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 14:49:48 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/20 16:04:55 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 3 registres en paramètre, additionne le contenu des
** 2 premiers et met le résultat dans le troisième. Cette opération modifie le
** carry. add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5.
*/

// void		cw_ins_add_db()
// {
//
// }

int			cw_ins_add(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	param[3];

	if (proc->mem[tmp->pc + 2] > 0 && proc->mem[tmp->pc + 2] <= REG_NUMBER
		&& proc->mem[tmp->pc + 3] > 0 && proc->mem[tmp->pc + 3] <= REG_NUMBER)
	{
		param[0] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2] - 1);
		param[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 3] - 1);
		param[2] = param[0] + param[1];
		tmp->reg[proc->mem[tmp->pc + 4] - 1][0] = param[2] >> 24;
		tmp->reg[proc->mem[tmp->pc + 4] - 1][1] = param[2] >> 16;
		tmp->reg[proc->mem[tmp->pc + 4] - 1][2] = param[2] >> 8;
		tmp->reg[proc->mem[tmp->pc + 4] - 1][3] = param[2];
	}
	if (param[2] == 0)
		tmp->carry = 1;
	else
		tmp->carry = 0;
	// if (g_bon['d'] == 1)
	// 	cw_ins_add_db();
	return (5);
}
