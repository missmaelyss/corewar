/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:46:53 by qduperon          #+#    #+#             */
/*   Updated: 2019/01/15 18:51:03 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "op.h"

void	ft_end(t_env *env)
{
	if (env->proc == NULL
	|| glfwGetKey(env->draw.window, GLFW_KEY_ESCAPE) == GLFW_PRESS
		|| glfwWindowShouldClose(env->draw.window) != 0)
		ft_win(env);
	else
		ft_hexdump(env, MEM_SIZE);
	env->verbose = 0;
	ft_free(env);
}

void	ft_error_file(char *name, int e)
{
	ft_putstr(name);
	if (e == -42)
		ft_error(" : error opening file");
	else if (e == -1)
		ft_error(" : error reading file");
	else
		ft_error(" : error closing file");
}
