/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 13:42:41 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

unsigned int		cw_ins_param_sze(char param, int dir)
{
	if (param == 1)
		return (1);
	if (param == 2)
		return (dir);
	if (param == 3)
		return (2);
	return (cw_error_msg("Wrong DIR_CODE ref passed to cw_ins_param_sze"));
}

int					cw_ins_sti(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	param[3];
	short int		res;
	int				i;

	i = -1;
	param[0] = cw_ins_param_sze(ocp->first, 2);
	param[1] = cw_ins_param_sze(ocp->second, 2);
	param[2] = cw_ins_param_sze(ocp->third, 2);
	res = proc->mem[tmp->pc + 1 + 1 + param[0]] << 8 |
	proc->mem[tmp->pc + 1 + 1 + param[0] + 1];
	res += proc->mem[tmp->pc + 1 + 1 + param[0] + param[1]] << 8 |
	proc->mem[tmp->pc + 1 + 1 + param[0] + param[1] + 1];
	while (++i < REG_SIZE)
		proc->mem[(res + i % MEM_SIZE) % IDX_MOD]
		= tmp->reg[proc->mem[tmp->pc + 1 + 1] - 1][i];
	return (1 + 1 + param[0] + param[1] + param[2]);
}
