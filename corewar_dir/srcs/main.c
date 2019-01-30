/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:47:20 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "vm.h"
#include "op.h"

void		ft_add_champ(t_env *env, t_champ *champ)
{
	ft_get_champ_magic(champ);
	if (env->has_spe == 1)
	{
		if (ft_has_number(env, env->spe_number) > 0)
			ft_error("Error: two players can\'t have the same number");
		champ->number_set = 1;
		champ->live = env->spe_number;
		env->has_spe = 0;
	}
	else
		champ->number_set = 0;
	if (env->one == NULL)
		env->one = champ;
	else if (env->two == NULL)
		env->two = champ;
	else if (env->three == NULL)
		env->three = champ;
	else if (env->four == NULL)
		env->four = champ;
	else
		ft_error("Error: too much players");
	env->nbr_champ++;
}

void		ft_readfile(t_env *env, char *name)
{
	t_champ			*champ;
	unsigned char	buf[4096];
	int				fd;
	int				ret;
	unsigned char	*tmp;

	if ((champ = (t_champ*)malloc(sizeof(t_champ))) == NULL)
		ft_error("Malloc error");
	if ((champ->file = ft_strdup(name)) == NULL)
		ft_error("Malloc error");
	champ->len = 0;
	if ((fd = open(name, O_RDONLY)) == -1)
		ft_error_file(name, -42);
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		tmp = ft_strnjoin(champ->content, champ->len, buf, ret);
		if (champ->len > 0)
			free(champ->content);
		champ->content = tmp;
		champ->len += ret;
	}
	if (ret == -1 || close(fd) < 0)
		ft_error_file(name, ret);
	ft_add_champ(env, champ);
}

t_op		ft_get_op(t_env *env, int op)
{
	int i;

	i = 0;
	while (env->op_tab[i].name)
	{
		if (env->op_tab[i].code == op)
			return (env->op_tab[i]);
		i++;
	}
	return (env->op_tab[i]);
}

int			ft_get_argv(int argc, char **argv, int *i, t_env *env)
{
	if (ft_strcmp(argv[*i], "-d") == 0)
		ft_get_dump(env, i, argc, argv);
	else if (ft_strcmp(argv[*i], "-n") == 0)
		ft_get_n(env, i, argc, argv);
	else if (ft_strcmp(argv[*i], "-v") == 0)
		ft_get_v(env, i, argc, argv);
	else if (ft_strcmp(argv[*i], "-a") == 0)
		env->a = 1;
	else if (ft_strcmp(argv[*i], "-c") == 0)
		env->c = 1;
	else if (ft_strcmp(argv[*i], "-q") == 0)
		env->q = 1;
	else
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		i;

	if (argc < 2)
		ft_usage();
	ft_init_env(&env);
	i = 1;
	while (i < argc)
	{
		if (ft_get_argv(argc, argv, &i, &env) == 0)
			ft_readfile(&env, argv[i]);
		i++;
	}
	ft_set_number(&env);
	return (0);
}
