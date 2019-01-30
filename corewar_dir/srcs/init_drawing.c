/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:08:12 by qduperon          #+#    #+#             */
/*   Updated: 2018/10/16 16:37:05 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		init_draw(t_env *env)
{
	GLuint	vertex_array_id;
	GLuint	vertexbuffer;

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	build_shader_program(env);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	env->draw.size_x = 0.018;
	env->draw.size_y = 0.018;
	env->draw.init = 1;
}

void		init_glfw(void)
{
	if (!glfwInit())
		ft_error("Failed to initialize GLFW");
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow	*init_window(void)
{
	GLFWwindow	*window;

	window = glfwCreateWindow(1800, 1200, "Corewar", NULL, NULL);
	if (window == NULL)
	{
		ft_putendl("Failed to open GLFW window.");
		glfwTerminate();
		exit(0);
	}
	return (window);
}

void		init_glew(GLFWwindow *window)
{
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		ft_error("Failed to initialize GLEW");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void		init(t_env *env)
{
	GLFWwindow	*win;

	if (env->q == 1)
	{
		init_glfw();
		win = init_window();
		init_glew(win);
		env->draw.window = win;
		init_draw(env);
		ft_drawing(env);
	}
}
