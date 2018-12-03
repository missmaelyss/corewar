/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H

# define OP_H

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define REGISTER_CHAR			'r'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				    prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				    comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct        s_op
{
    char            *name;
    unsigned int    param_nb;
    unsigned int    possible_param[3];
    unsigned char   opcode;
    unsigned int    cycle;
    char            *description;
    unsigned int    encoding_byte;
    unsigned int    direct_size;
}                    t_op;

t_op    op_tab[17];

typedef struct        s_mem
{
    header_t  header;
    char      *file;
    char      **data;
    char      *tmp;
    int       enc_b_i;
    int       i;
    int       where;
    char      **labels;
    int       n_label;
    int       *i_label;
    int       *where_used_label;
    int       *where_write_label;
    char      **used_label;
    int       *size_used_label;

}                    t_mem;

char			**ft_strsplit_2(char const *s, char *c);
char			**ft_strsplit_3(char const *s, char *c);

#endif
