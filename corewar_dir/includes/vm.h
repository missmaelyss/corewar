/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:23:53 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:49:37 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <fcntl.h>

# include "../deps/glew/include/GL/glew.h"
# include "../deps/glfw/include/GLFW/glfw3.h"

# define BUFFER_SIZE 128

typedef struct		s_shader
{
	GLuint			red;
	GLuint			green;
	GLuint			blue;
	GLuint			yellow;
	GLuint			grey;
}					t_shader;

typedef struct		s_draw
{
	GLFWwindow		*window;
	t_shader		shader;
	float			size_x;
	float			size_y;
	float			pos_x;
	float			pos_y;
	GLfloat			g_vertex_buffer_data[12];
	int				init;
}					t_draw;

typedef struct		s_op
{
	char			*name;
	int				params;
	int				types[4];
	int				code;
	int				cycles;
	char			*description;
	int				octet;
	int				unknown;
}					t_op;

typedef struct		s_flag
{
	int				i;
	void			(*f)();
}					t_flag;

typedef struct		s_proc
{
	int				*reg;
	unsigned char	*pc;
	int				carry;
	int				live;
	int				cycle;
	t_op			op;
	int				index;
	struct s_proc	*next;
	struct s_proc	*previous;
	int				last_live;
	int				color;
}					t_proc;

typedef struct		s_champ
{
	unsigned int	len;
	char			*file;
	unsigned char	*content;
	int				number;
	int				live;
	int				number_set;
	char			*name;
	char			*comment;
	unsigned int	size;
	unsigned int	magic;
	unsigned char	*code;
	int				color;
}					t_champ;

typedef struct		s_env
{
	t_op			*op_tab;
	t_champ			*one;
	t_champ			*two;
	t_champ			*three;
	t_champ			*four;
	int				nbr_champ;
	unsigned char	*arena;
	unsigned char	*color;
	int				spe_number;
	int				has_spe;
	int				dump;
	struct s_proc	*proc;
	int				check;
	int				live;
	int				cycle;
	int				cycle_to_die;
	int				last_alive;
	int				total_cycle;
	int				index;
	int				verbose;
	int				a;
	int				c;
	int				q;
	t_draw			draw;
}					t_env;

void				init(t_env *env);
GLFWwindow			*init_window(void);
void				init_glew(GLFWwindow *window);
void				init_glfw(void);
void				init_draw(t_env *env);

void				set_cycle(t_env *env);
void				ft_drawing(t_env *env);

int					champ_is_alive(t_env *env, int i);
char				*champ_name(t_env *env, int i);

void				build_shader_program(t_env *env);

void				ft_op_tab(t_env *env);
void				ft_get_dump(t_env *env, int *i, int argc, char **argv);
void				ft_get_n(t_env *env, int *i, int argc, char **argv);
void				ft_get_v(t_env *env, int *i, int argc, char **argv);
void				ft_get_champ_magic(t_champ *champ);
void				ft_get_champ_name(t_champ *champ);
void				ft_get_champ_size(t_champ *champ);
void				ft_get_champ_comment(t_champ *champ);
void				ft_get_champ_code(t_champ *champ);
int					ft_get_dir(t_env *env, unsigned char *pc, char *str);
int					ft_get_ind(t_env *env, unsigned char *pc,
					unsigned char *start);
int					ft_get_reg(t_env *env, unsigned char *pc);
void				ft_init_env(t_env *env);
void				ft_create_arena(t_env *env);
void				ft_set_number(t_env *env);
int					ft_has_number(t_env *env, int number);
unsigned char		*ft_modulo_pc(t_env *env, unsigned char *pc);
int					ft_get_dir_size(char *str);
void				ft_play(t_env *env);
void				ft_new_proc(t_env *env, int number, unsigned char *pc,
					int carry);
void				ft_set_live(t_env *env, int i);
void				ft_init_live(t_proc *proc);
void				ft_introduce(t_env *env);
int					ft_check(t_env *env);
t_op				ft_get_op(t_env *env, int op);
void				ft_win(t_env *env);
void				ft_hexdump(t_env *env, unsigned int len);
void				ft_live(t_env *env, t_proc *proc);
void				ft_ld(t_env *env, t_proc *proc);
void				ft_st(t_env *env, t_proc *proc);
void				ft_add(t_env *env, t_proc *proc);
void				ft_sub(t_env *env, t_proc *proc);
int					ft_get_val(t_env *env, t_proc *proc, int *i, int d);
void				ft_and(t_env *env, t_proc *proc);
void				ft_or(t_env *env, t_proc *proc);
void				ft_xor(t_env *env, t_proc *proc);
void				ft_zjmp(t_env *env, t_proc *proc);
int					ft_get_val2(t_env *env, t_proc *proc, int *i, int d);
void				ft_ldi(t_env *env, t_proc *proc);
void				ft_sti(t_env *env, t_proc *proc);
void				ft_fork(t_env *env, t_proc *proc);
void				ft_lld(t_env *env, t_proc *proc);
void				ft_lldi(t_env *env, t_proc *proc);
void				ft_lfork(t_env *env, t_proc *proc);
void				ft_aff(t_env *env, t_proc *proc);
t_proc				*ft_get_first_proc(t_proc *proc);
t_proc				*ft_malloc_proc(t_env *env, unsigned char *pc, int *i);
void				ft_copy_proc(t_env *env, t_proc *dad, unsigned char *pc);
t_proc				*ft_remove_proc(t_env *env, t_proc *proc);
void				ft_move(t_env *env, t_proc *proc, int i);
int					ft_check_arg(t_env *env, t_proc *proc);
int					ft_size(t_env *env, t_proc *proc);
void				ft_set_carry(t_proc *proc, int r);
unsigned char		*ft_strnjoin(unsigned char *s1, unsigned int n1,
					unsigned char *s2, unsigned int n2);
char				*ft_itao_base(int value, int size);
void				ft_set_color(t_env *env, int start, int size, int color);
void				ft_color(int i);
void				ft_usage(void);
void				ft_free(t_env *env);
int					ft_get_ind_no_mod(t_env *env, unsigned char *pc,
					unsigned char *start);
void				ft_end(t_env *env);
void				ft_error_file(char *name, int e);

#endif
