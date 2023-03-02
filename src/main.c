/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/02 14:52:43 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

void	read_env(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s\n", env->var);
		env = env->next;
	}
}

void	builtin_export(t_cmd *cmd)
{
	int		i;
	t_env	*node;

	i = 0;
	node = g_global;
	if (ft_strncmp((cmd->option[0]), "export", ft_strlen(cmd->option[0])) == 0)
	{
		while (node->next)
			node = node->next;
		if (cmd->option[1] != NULL)
		{
			node->next = malloc(sizeof(t_env));
			if (node->next == 0)
				return (0);
			node->next->var = ft_strdup(cmd->option[1]);
			node->next->next = NULL;
		}
		else
		{
			read_env(g_global);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
	int		j;

	get_env_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf(" exit\n");
			return (0);
		}
		add_history(input);
		cmd = parse_input(input);
		j = 1;
		while (cmd)
		{
		int i = 0;
		while (cmd->option[i])
		{
			printf("%d pipe -> option : %s\n",j, cmd->option[i]);
			i++;
		}
		i = 0;
		while (cmd->file[i].redirection != 0)
		{
			printf("redirection : %d\n", cmd->file[i].redirection);
			printf("file : %s\n", cmd->file[i].name);
			i++;
		}
		cmd = cmd->next;
		++j;
		}
		builtin_export(cmd);
		free(input);
	}
}
/*널문자만 들어올 경우 main에서 처리"
cc src/main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c -lreadline*/