/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 11:12:46 by qduperon          #+#    #+#             */
/*   Updated: 2019/01/15 18:45:12 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	display(t_env *env)
{
	int i;

	i = 1;
	ft_printf("\x1b[2J");
	ft_printf("\x1b[999999A");
	ft_printf("It is now cycle %d\n", env->total_cycle);
	while (i <= env->nbr_champ)
	{
		if (champ_is_alive(env, i) == 1)
			ft_printf("the champ named : %s is alive\n", champ_name(env, i));
		else
			ft_printf("the champ named : %s is dead\n", champ_name(env, i));
		i++;
	}
}

void	set_cycle(t_env *env)
{
	env->total_cycle++;
	env->cycle++;
	if (env->draw.init == 1)
		display(env);
}

void	get_buffer(t_env *env)
{
	env->draw.g_vertex_buffer_data[0] = env->draw.pos_x;
	env->draw.g_vertex_buffer_data[1] = env->draw.pos_y;
	env->draw.g_vertex_buffer_data[2] = 0;
	env->draw.g_vertex_buffer_data[3] = env->draw.pos_x + env->draw.size_x;
	env->draw.g_vertex_buffer_data[4] = env->draw.pos_y;
	env->draw.g_vertex_buffer_data[5] = 0;
	env->draw.g_vertex_buffer_data[6] = env->draw.pos_x + env->draw.size_x;
	env->draw.g_vertex_buffer_data[7] = env->draw.pos_y - env->draw.size_y;
	env->draw.g_vertex_buffer_data[8] = 0;
	env->draw.g_vertex_buffer_data[9] = env->draw.pos_x;
	env->draw.g_vertex_buffer_data[10] = env->draw.pos_y - env->draw.size_y;
	env->draw.g_vertex_buffer_data[11] = 0;
}

void	ft_choose_color(t_env *env, int i)
{
	if (i == 1)
		glUseProgram(env->draw.shader.red);
	else if (i == 2)
		glUseProgram(env->draw.shader.green);
	else if (i == 3)
		glUseProgram(env->draw.shader.blue);
	else if (i == 4)
		glUseProgram(env->draw.shader.yellow);
	else
		glUseProgram(env->draw.shader.grey);
}

void	ft_drawing(t_env *env)
{
	int	i;
	int	j;

	env->draw.pos_y = 0.90;
	i = 0;
	while (i < 64)
	{
		env->draw.pos_x = -0.90;
		j = 0;
		while (j < 64)
		{
			ft_choose_color(env, env->color[(i * 64) + j]);
			get_buffer(env);
			glBufferData(GL_ARRAY_BUFFER, sizeof(env->draw.g_vertex_buffer_data)
			, env->draw.g_vertex_buffer_data, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			env->draw.pos_x += env->draw.size_x + 0.01;
			j++;
		}
		env->draw.pos_y -= env->draw.size_y + 0.01;
		i++;
	}
	glfwSwapBuffers(env->draw.window);
	glfwPollEvents();
}
