/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/03 17:22:28 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

// TODO cw_check_live_process()
	// TODO verifier que les processus ont bien fait au moins un live
// TODO verifier que CYCLE_TO_DIE != 0
	// TODO renvoyer 0 sinon.

/*
** cw_check_live_process vérifie si un processus a bien fait un live en
** CYCLE_TO_DIE cycles.
*/

int			cw_check_live_process(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->lives == 0)
			// kill le process en le retirant de la liste
		tmp = tmp->next;
	}
	proc->checks++; // incremente le checks car on a effectue un nouveau check
	return (1);
}

/*
** cw_cycles vérifie si un nouveau cycle doit être exécuté.
** Si les conditions suivantes sont remplies alors les cycles s'arrêtent :
** - CYCLE_TO_DIE atteint 0 ;
** - depuis CYCLE_TO_DIE cycles un seul processus a été rapporté en vie.
*/

int			cw_cycles(t_proc *proc)
{
	// if (proc->checks % MAX_CHECKS == 0)
	// 	proc->c_to_die -= CYCLE_DELTA;
	// if (proc->c % CYCLE_TO_DIE == 0) // condition a verifier si on a decrementer ctd entre temps
	// 	cw_check_live_process(proc);
	// if (proc->lives_total >= NBR_LIVE)
	// 	proc->c_to_die -= CYCLE_DELTA;
	return (1);
}

/*
** Effectue l'instruction puis fait sauter le PC et réinitialise le cycles
** d'instruction avec la nouvelle valeur.
** Si une instruction n'était pas em cours (tmp->ins == NULL) alors on signale
** cette instruction et on charge le temps de l'instruction.
*/

void		cw_exec_process_instruct(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	int		size;

	size = 0;
	if (tmp->ins == NULL)
	{
		tmp->ins = &proc->mem[tmp->pc];
		tmp->inst_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
	}
	else
	{
		cw_ins_ocp(proc, tmp, ocp);
		size = g_op[proc->mem[tmp->pc] - 1].ptr(proc, tmp, ocp);
		tmp->pc = (tmp->pc + size) % MEM_SIZE;
		if (proc->mem[tmp->pc] > 0x00 && proc->mem[tmp->pc] < 0x11)
		{
			tmp->ins = &proc->mem[tmp->pc];
			tmp->inst_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
		}
		else
			tmp->ins = NULL;
	}
}

/*
** cw_exec_process itère sur chaque processus pour savoir s'il y a
** quelque chose à faire ou pas. Si le temps d'une instruction est écoulé, alors
** elle va appeler la fonction qui exécute. Si non, elle incrémente le PC
** jusqu'à tomber sur une instruction.
*/

void		cw_exec_process(t_proc *proc)
{
	t_champion	*tmp;
	t_ocp		ocp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->inst_c == 0)
		{
			if (proc->mem[tmp->pc] > 0x00 && proc->mem[tmp->pc] < 0x11)
				cw_exec_process_instruct(proc, tmp, &ocp);
			else
				tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		}
		else
			tmp->inst_c--;
		tmp = tmp->next;
	}
}

/*
** cw_processor mîme le processeur.
** Elle exécute les cycles, lit la mémoire tout en traitant les instructions.
*/

int			cw_processor(t_proc *proc)
{
	cw_proc_init(proc);
	cw_load_ins_c(proc);
	while (cw_cycles(proc))
	{
		cw_exec_process(proc);
		proc->c++;
	}
	return (1);
}
