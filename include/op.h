/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/01/15 17:05:48 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H

# define OP_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define REGISTER_CHAR		'r'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char				t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char				*name;
	unsigned int		param_nb;
	unsigned int		possible_param[3];
	unsigned char		opcode;
	unsigned int		cycle;
	char				*description;
	unsigned int		encoding_byte;
	unsigned int		direct_size;
}					t_op;

t_op				g_op_tab[17];

typedef struct		s_tmp_lab
{
	char				**used_label;
	int					*where_used_label;
	int					*where_write_label;
	int					*size_used_label;
	int					*to_add;
}					t_tmp_lab;

typedef struct		s_mem
{
	t_header			header;
	int					nb_c;
	int					p_c;
	char				*file;
	char				**data;
	char				*tmp;
	int					enc_b_i;
	int					i;
	int					where;
	char				**labels;
	int					n_label;
	int					*i_label;
	char				**used_label;
	int					*where_used_label;
	int					*where_write_label;
	int					*size_used_label;
	int					*to_add;
}					t_mem;

char				**ft_strsplit_2(char const *s, char *c);
char				**ft_strsplit_3(char const *s, char *c);
void				ft_exit(char *exit_msg, int status, t_mem *mem);
void				ft_freetab(char **tab);
void				ft_stock_label(char *word, t_mem *mem, int size, int add);
void				ft_label_place(t_mem *mem);
int					ft_str_is_label(char *str);
int					ft_label_exist(char *word, t_mem *mem, int where);
void				fill_label_in_mem(t_mem *mem);
void				ft_add_label(t_mem *mem, char *str);
int					ft_strchrword(char *str, char *word);
int					ft_del_char_ptr(char **tmp);
int					ft_str_is_digit(char *str);
int					reverse_endian_int(int a);
short				reverse_endian_short(short a);
void				ft_clear_word(char **word);
int					find_max_len(char *str);
char				*add_space_direct_char(char *str);
char				*remove_space_add_char(char *str);
char				*ft_strrpl(char *dest, const char *src, char a, char b);
int					ft_fill_mem(int n, int i, char *word, t_mem *mem);
int					ft_mem_instr(int n, int i, char *word, t_mem *mem);
int					ft_instruction(int i, char **word_in_line, t_mem *mem);
int					fill_mem(t_mem *mem, char const *av);
int					fill_header_name(t_mem *mem, int n);
int					fill_header_comment(t_mem *mem, int n);
int					create_new_cor(char const *av);
int					ft_str_in_op_tab(char *str);

#endif
