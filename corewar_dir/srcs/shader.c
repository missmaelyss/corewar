/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:21:47 by qduperon          #+#    #+#             */
/*   Updated: 2019/01/15 18:45:51 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

const GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_error("shader source file opening failed.");
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			success;
	GLuint			shader;
	const GLchar	*shader_source;

	shader_source = get_shader_source(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	free((void*)shader_source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		ft_error("shader compilation failed.");
	return (shader);
}

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		ft_error("shader program compilation failed.");
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
}

void			build_shader_program(t_env *env)
{
	GLuint	shader_vert;

	shader_vert = create_shader("./corewar_dir/shader/vertex.glsl",
	GL_VERTEX_SHADER);
	env->draw.shader.red = create_shader_program(shader_vert,
		create_shader("./corewar_dir/shader/red.glsl", GL_FRAGMENT_SHADER));
	env->draw.shader.green = create_shader_program(shader_vert,
		create_shader("./corewar_dir/shader/green.glsl", GL_FRAGMENT_SHADER));
	env->draw.shader.blue = create_shader_program(shader_vert,
		create_shader("./corewar_dir/shader/blue.glsl", GL_FRAGMENT_SHADER));
	env->draw.shader.yellow = create_shader_program(shader_vert,
		create_shader("./corewar_dir/shader/yellow.glsl", GL_FRAGMENT_SHADER));
	env->draw.shader.grey = create_shader_program(shader_vert,
		create_shader("./corewar_dir/shader/grey.glsl", GL_FRAGMENT_SHADER));
}
