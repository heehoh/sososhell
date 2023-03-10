/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 14:39:08 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "process.h"
#include "../libft/libft.h"

void	set_signal(void);

void	exit_minishell(t_env *env, t_current *current)
{
	t_env	*tem;

	free(current->path);
	while (env)
	{
		tem = env->next;
		free(env->var);
		free(env);
		env = tem;
	}
	write(1, "exit\n", 5);
	exit(0);
}

int	input_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		++i;
	if (input[i] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

void	init_pwd(t_env *env, t_current *current)
{
	while (env)
	{
		if (ft_strncmp(env->var, "PWD=", 4) == 0)
		{
			free(env->var);
			env->var = ft_strjoin("PWD=", current->path);
			if (env->var == NULL)
				error_malloc();
			return ;
		}
		if (env->next == NULL)
		{
			env->next = (t_env *)malloc(sizeof(t_env));
			if (env->next == NULL)
				error_malloc();
			env->next->var = ft_strjoin("PWD=", current->path);
			if (env->next->var == NULL)
				error_malloc();
			return ;
		}
		env = env->next;
	}
}

void	init_setting(char **env, t_env **env_list, t_current *current)
{
	*env_list = get_env_list(env);
	current->path = (char *)malloc(sizeof(char) * 4096);
	if (current->path == NULL)
		error_malloc();
	if (getcwd(current->path, 4096) == NULL)
	{
		perror(INITERR);
		current->path[0] = '\0';
	}
	else
		init_pwd(*env_list, current);
	current->status = 0;
	set_signal();
}

int	main(int argc, __attribute__((unused))char **argv, char **env)
{
	char		*input;
	t_cmd		*cmd;
	t_env		*env_list;
	t_current	current;

	if (argc != 1 && printf("Error: argument\n"))
		return (1);
	init_setting(env, &env_list, &current);
	while (1)
	{
		input = readline(MINISHELL);
		if (input == NULL)
			exit_minishell(env_list, &current);
		if (input_check(input))
			continue ;
		add_history(input);
		if (syntax_error(input, 0, 0))
		{
			current.status = 258;
			free(input);
			continue ;
		}
		cmd = parse_input(input, env_list, current.status);
		current.status = create_process(cmd, env_list, &current);
		cmd_clear(cmd);
		rl_on_new_line();
	}
}
