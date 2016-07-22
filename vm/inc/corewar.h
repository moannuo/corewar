/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:11:30 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/22 13:55:52 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/fpf_printf.h" // a remplacer par les chevrons et compilation

/*
** Toutes les tailles sont en octets.
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_NUMBER				16
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

// # define T_REG					1
// # define T_DIR					2
// # define T_IND					4
// # define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** Enum booléen (parce que c'est plus clair à lire) :
*/

enum							e_bool
{
	FALSE,
	TRUE
};

/*
** Struture du header (imposé par le sujet) :
*/

typedef struct					s_header
{
  unsigned int					magic;
  char							prog_name[PROG_NAME_LENGTH + 1];
  unsigned int					prog_size;
  char							comment[COMMENT_LENGTH + 1];
}								t_header;

/*
** Structure d'un processus :
*/

typedef struct 					s_champion
{
	t_header					*header;
	char						reg[REG_NUMBER][REG_SIZE];
	unsigned short int			pc_origin;
	unsigned short int			pc; // le PC est codé sur 2 octets
	char						carry; // pas besoin de le stocker dans int, un char suffit : 0 ou 1
	uint						inst_c; // nombre de cycles de l'instruction, se decremente a chaque cycle jusqu'a execution
	int							num; // numero du processus
	unsigned int				cycle_cnt;
	unsigned int				lives;
	char						is_champ;
	struct s_champion			*next;
}								t_champion;

/*
** Structure du processeur :
*/

typedef struct 					s_proc
{
	t_champion					*champions;
	// memoire du processeur
	char						mem[MEM_SIZE];
	int							dump;
	int							nb_proc; // nombre de processus courants
	// c_to_die : valeur qui vaut CYCLE_TO_DIE au début et qui sera décrémenté de
	// CYCLE_DELTA tous les blablablas
	unsigned int				c_to_die;
	// c : index des cycles. Init à 0.
	unsigned int				c;
	// live[5] : enregistre le nombre de live émis sur la période CYCLE_TO_DIE par champions.
	unsigned int				live[5];
	unsigned int				lives_total; // nombre total de lives sur toute la partie
	unsigned int				checks;
}								t_proc;

/*
** Enum des types de paramètres :
*/

enum 							e_types
{
	T_DIR = 1,
	T_IND = 2,
	T_REG = 4,
	T_LAB = 8
};

/*
** Nom, nombre de paramètre, taille/type des paramètres, opcode, nombre de cycles, description, OCP
*/

typedef struct					s_op
{
	int							(*ptr)();
	char						name[5];
	unsigned short int			param_nb;
	// type de parametres ?
	// enum e_types				types;
	unsigned char				opcode; // de 1 à 16
	unsigned short int			cycles_nb;
	char						desc[36];
	unsigned char				ocp; // 0 ou 1
}								t_op;

/*
** PROCESSOR
*/

int								cw_processor(t_proc *proc);
int								cw_exec_process(t_proc *proc);
int								cw_cycles(t_proc *proc);
int								cw_check_live_process(t_proc *proc);
void							cw_proc_init(t_proc *proc);

/*
** INSTRUCTIONS
*/

int								cw_ins_add(t_proc *proc);
int								cw_ins_aff(t_proc *proc);
int								cw_instr_and(t_proc *proc);
int								cw_ins_live(t_proc *proc);

void							cw_instruct_init(t_proc *proc);

const t_op							g_op[17] =
{
	{&cw_ins_live, "live", 1, 1, 10, "alive", 0},
	{&cw_ins_ld, "ld", 2, 2, 5, "load", 1},
	{&cw_ins_st, "st", 2, 3, 5, "store", 1},
	{&cw_ins_add, "add", 3, 4, 10, "addition", 1},
	{&cw_ins_sub, "sub", 3, 5, 10, "soustraction", 1},
	{&cw_ins_and, "and", 3, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1},
	{&cw_ins_or, "or", 3, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1},
	{&cw_ins_xor, "xor", 3, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1},
	{&cw_ins_zkmp, "zjmp", 1, 9, 20, "jump if zero", 0},
	{&cw_ins_ldi, "ldi", 3, 10, 25, "load index", 1},
	{&cw_ins_sti, "sti", 3, 11, 25, "store index", 1},
	{&cw_ins_fork, "fork", 1, 12, 800, "fork", 0},
	{&cw_ins_lld, "lld", 2, 13, 10, "long load", 1},
	{&cw_ins_lldi, "lldi", 3, 14, 50, "long load index", 1},
	{&cw_ins_lfork, "lfork", 1, 15, 1000, "long fork", 0},
	{&cw_ins_aff, "aff", 1, 16, 2, "aff", 1},
	{0, 0, 0, 0, 0, 0, 0}
};


#endif
