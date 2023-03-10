/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:46 by migo              #+#    #+#             */
/*   Updated: 2023/03/10 10:46:02 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int	builtin_process(t_cmd *cmd, t_env *env, int count, t_current *current)
{
	if (ft_strncmp((cmd->option[0]), "cd", ft_strlen(cmd->option[0])) == 0)
		return (builtin_cd(cmd, env, current));
	if (ft_strncmp((cmd->option[0]), "echo", ft_strlen(cmd->option[0])) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp((cmd->option[0]), "env", ft_strlen(cmd->option[0])) == 0)
		return (builtin_env(cmd, env));
	if (ft_strncmp((cmd->option[0]), "export", ft_strlen(cmd->option[0])) == 0)
		return (builtin_export(cmd, env, 0, 0));
	if (ft_strncmp((cmd->option[0]), "pwd", ft_strlen(cmd->option[0])) == 0)
		return (builtin_pwd(current));
	if (ft_strncmp((cmd->option[0]), "unset", ft_strlen(cmd->option[0])) == 0)
		return (builtin_unset(cmd, env, 0, 0));
	if (ft_strncmp((cmd->option[0]), "exit", ft_strlen(cmd->option[0])) == 0)
		builtin_exit(cmd, count);
	return (0);
}
