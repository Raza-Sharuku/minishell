/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:57:57 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/08 14:18:21 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

volatile sig_atomic_t	g_sig;

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ans;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = (ft_strlen(s1));
	s2_len = (ft_strlen(s2));
	ans = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ans == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(ans, s1, s1_len + 1);
	ft_strlcpy(ans + s1_len, s2, s2_len + 1);
	free(s1);
	return (ans);
}

void	handle_signal_gnl(int sig)
{
	if (sig == SIGINT)
		g_sig = SIGINT;
}

int	set_signal_gnl(void)
{
	struct sigaction	sigstruct;

	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_handler = handle_signal_gnl;
	sigstruct.sa_flags = 0;
	if (sigaction(SIGINT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_handler = SIG_IGN;
	sigstruct.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
