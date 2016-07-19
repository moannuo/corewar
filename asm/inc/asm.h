/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:10:01 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/18 17:30:11 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../../libft/ft_printf/include/fpf_printf.h"
# include "../../libft/libft.h"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define REG_NUMBER				16

int						g_line;
int						g_pos;
char					*g_file;

/*
** Labels
*/

typedef struct			s_label
{
	char				*name;
	unsigned int		pos;
	struct s_label		*next;

}						t_label;

/*
** Header
*/

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

/*
** Library
*/

int						asm_error(int error);

t_header				*asm_header_init(void);
t_label					*asm_label_init(void);

void					asm_free_join(char *line);
int						asm_free_tab(char **tab, int ret);

/*
** asm_parse_instruct
*/

int						asm_instruct_name_sec(char **line);
int						asm_instruct_name(char **line);
int						asm_check_label(char *str);
int						asm_check_double_label(t_label *label);
int						asm_check_instruct(char *line);

/*
** asm_check_arg
*/

int						asm_check_arg(char *line, int op);
int						asm_check_arg_sec(char *line, int op);

/*
** asm_check_instruct
*/

int						asm_copy_name_comment(char *line, t_header *head,
	int first, int last);
int						asm_handler_name_comment(int fd, char *line,
	t_header *head);
int						check_valid_line(char *line);
t_label					*asm_parse_line(char *line, int fd, int check);
int						asm_parsing(char *line, t_header *head);
/*
** asm_check_instruct
*/

int						asm_check_virgule(char **line);
int						asm_check_dir(char **line, int op, int check);
int						asm_check_reg(char **line, int check);
int						asm_check_ind(char **line, int check);

/*
** asm_writer
*/
int                cw_invert_endian(int x);
int		asm_binary_creator(int fd, t_label *label);
char  *asm_morph_cor(char *champ);
int   asm_reader(t_label *label, t_header *header, char *champ);
#endif
