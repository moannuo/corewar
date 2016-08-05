/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_cycles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:18:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/05 16:31:16 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

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
** Affiche la mémoire selon la norme imposée dans le sujet : 32 octets par
** ligne.
*/

void		cw_dump_display(t_proc *proc)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0)
			i % 32 == 0 ? ft_printf("\n") : ft_printf(" ");
		ft_printf("%.2hhx", proc->mem[i]);
		i++;
	}
}

/*
** cw_cycles vérifie si un nouveau cycle doit être exécuté.
** Si les conditions suivantes sont remplies alors les cycles s'arrêtent :
** - CYCLE_TO_DIE atteint 0 ;
** - depuis CYCLE_TO_DIE cycles un seul processus a été rapporté en vie.
*/

int			cw_cycles(t_proc *proc)
{
	if (proc->c_to_die <= 0)
		return(0);
	// if (proc->checks % MAX_CHECKS == 0)
	// 	proc->c_to_die -= CYCLE_DELTA;
	// if (proc->c % CYCLE_TO_DIE == 0) // condition a verifier si on a decrementer ctd entre temps
	// 	cw_check_live_process(proc);
	// if (proc->lives_total >= NBR_LIVE)
	// 	proc->c_to_die -= CYCLE_DELTA;
	return (1);
}

void		cw_kill_process(t_proc *proc, t_champion *tmp)
{
	if (tmp->is_champ == 1) // si cest un champion on conserve ses infos...
		tmp->is_champ = -1; // alors on met le is_champ a -1 et fera en sorte de le sauter dans les process
	else
	{
		if (tmp->next !=NULL) // si pas dernier maillon
			tmp->next->prev = tmp->prev;
		if (tmp->prev != NULL) // si pas premier maillon
			tmp->prev->next = tmp->next;
		if (tmp == proc->champions)
			proc->champions = tmp->next;
		free(tmp);
	}
	proc->nb_proc--;
}

void		cw_cycles_checks_lives(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->is_champ != -1)
		{
			if (tmp->lives == 0)
			{
				cw_kill_process(proc, tmp); // retire le processus definitivement de la liste
				// if () // si bonus son active produit un son pour le kill !
				// printf("\a"); produit un son
			}
			else
				tmp->lives = 0;
		}
		tmp = tmp->next;
	}
}

/*
** cw_cycles_checks va vérifier en fin de cycle différentes choses, dont les
** condtions de victoires.
*/

int		cw_cycles_checks(t_proc *proc)
{
	if (proc->dump != 0 && proc->c == proc->dump) // vérifie si -dump
	{
		cw_dump_display(proc);
		return (0);
	}
	if (proc->c % proc->c_to_die == 0 && proc->c != 0) // tous les CYCLE_TO_DIE
	{
		proc->checks++;
		if (proc->lives_total >= NBR_LIVE) // si nombre de lives totaux > NBR LIVE on decremente
			proc->c_to_die -= CYCLE_DELTA;
		if (proc->checks == MAX_CHECKS)
		{
			proc->c_to_die -= CYCLE_DELTA;
			proc->checks = 0;
		}
		cw_cycles_checks_lives(proc);
		proc->lives_total = 0;
	}

	return (1);
}
