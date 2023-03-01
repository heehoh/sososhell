/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/01 18:36:52 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;

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
		cmd = parsing(input);
		execution(cmd);
		free(input);
	}
}
