/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:03:45 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 17:10:32 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ('a' <= c && c <= 'z')
		return (0);
	else if ('A' <= c && c <= 'Z')
		return (0);
	else if ('0' <= c && c <= '9')
		return (0);
	else
		return (1);
}
