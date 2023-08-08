/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:50:56 by reira             #+#    #+#             */
/*   Updated: 2023/08/08 13:06:21 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

static bool	should_putstr(t_word_list *word)
{
	if (word == NULL)
		return (false);
	if (word->flag == arguments || word->flag == option)
		return (true);
	
	return (false);
}

static bool	is_echo_option_n(char *str)
{
	size_t	i;

	if (ft_strncmp(str, "-n", 2))
		return (false);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	echo_cmd(t_word_list *word_list, int fd)
{
	int	opt_flg;

	opt_flg = 0;
	word_list = word_list->next;
	if (word_list != NULL && is_echo_option_n(word_list->word) == true)
	{
		opt_flg = 1;
		word_list = word_list->next;
	}
	while (should_putstr(word_list))
	{
		ft_putstr_fd(word_list->word, fd);
		if (word_list->next != NULL && should_putstr(word_list->next))
			ft_putstr_fd(" ", fd);
		word_list = word_list->next;
	}
	if (opt_flg == 0)
		ft_putstr_fd("\n", fd);
}
