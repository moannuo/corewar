/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:17:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 13:42:24 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction est suivie d’un octet de paramétrage pour décrire
** les paramètres. Elle prend en paramètre un registre et a che le
** caractère dont le code ascii est présent dans ce registre (base
** 10). (un modulo 256 est appliqué au code ascii, le caractère
** est affiché sur la sortie standard).
*/

int			cw_ins_aff(t_proc *proc, t_ocp *ocp)
{
	return (1);
}
