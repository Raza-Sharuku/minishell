/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:17:17 by reira             #+#    #+#             */
/*   Updated: 2023/08/08 14:25:08 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"

volatile sig_atomic_t	g_sig;

static bool	ft_eof_cmp(char *line, char *eof)
{
	size_t	eof_len;

	eof_len = ft_strlen(eof);
	if (ft_strncmp(line, eof, eof_len) == 0 && line[eof_len] == '\n')
		return (true);
	return (false);
}

char	*get_file_name(int i)
{
	char	*file_name;
	char	*file_num;

	file_num = ft_itoa(i);
	if (file_num == NULL)
		return (NULL);
	file_name = ft_strjoin(".heredoc", file_num);
	if (file_name == NULL)
	{
		free(file_num);
		return (NULL);
	}
	free(file_num);
	if (access(file_name, F_OK) < 0)
		return (file_name);
	free(file_name);
	return (get_file_name(i + 1));
}

static int	write_to_heredocfile(char *eof, int fd)
{
	char	*line;
	int		flg;

	line = NULL;
	flg = 0;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, &flg);
		if (g_sig == SIGINT && flg == 0 && line == NULL)
			return (SUCCESS);
		if (g_sig == 0 && flg == 0 && line == NULL)
			return (FAILURE);
		if ((flg == 1 && line == NULL) || ft_eof_cmp(line, eof) == true)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (g_sig == 0 && line != NULL)
		free(line);
	return (SUCCESS);
}

int	get_heredoc_file(t_here_list **node, char *eof)
{
	(*node)->here_fd = get_fd((*node)->here_file_name, heredoc);
	if ((*node)->here_fd < 0)
		return (ft_perror((*node)->here_file_name));
	if (write_to_heredocfile(eof, (*node)->here_fd) == FAILURE)
		return (ft_perror("failed to write to heredocfile"));
	if (close((*node)->here_fd) < 0)
		return (ft_perror("close"));
	set_sigint();
	return (SUCCESS);
}

int	unlink_here_list(t_here_list **here_list)
{
	t_here_list *head;

	head = *here_list;
	if (*here_list == NULL)
		return (SUCCESS);
	while (*here_list != NULL)
	{
		unlink((*here_list)->here_file_name);
		*here_list = (*here_list)->next;
	}
	*here_list = head;
	return (SUCCESS);
}
