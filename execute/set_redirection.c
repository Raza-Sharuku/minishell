/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:58:02 by reira             #+#    #+#             */
/*   Updated: 2023/08/13 19:58:20 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static int	update_fd(char *filename, t_fd *fd_struct, int flg)
{
	if (flg == in_file)
	{
		if (fd_struct->in_fd != STDIN_FILENO)
			if (close(fd_struct->in_fd) < 0)
				return (ft_perror("close"));
		fd_struct->in_fd = get_fd(filename, flg);
	}
	else if (flg == heredoc)
	{
		fd_struct->in_fd = open(filename, O_RDONLY);
		if (fd_struct->in_fd < 0)
			return (ft_perror("open"));
	}
	else
	{
		if (fd_struct->out_fd != STDOUT_FILENO)
			if (close(fd_struct->out_fd) < 0)
				return (ft_perror("close"));
		fd_struct->out_fd = get_fd(filename, flg);
	}
	return (SUCCESS);
}

static int	is_valid_fd(t_fd *fd_struct)
{
	if (fd_struct->in_fd < 0)
		return (FAILURE);
	if (fd_struct->out_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	unlink_here_file(t_here_list *here_list, int *exit_flg)
{
	if (here_list == NULL)
		return (SUCCESS);
	if (unlink(here_list->here_file_name) < 0)
	{
		ft_perror("unlink");
		return (change_exit_flg(exit_flg));
	}
	return (SUCCESS);
}

static void	init_fd_struct(t_fd *fd_struct)
{
	fd_struct->in_fd = STDIN_FILENO;
	fd_struct->out_fd = STDOUT_FILENO;
}

int	set_redirection(t_word_list *word_list, t_here_list *here_list,
		t_fd *fd_struct, int *exit_flg)
{
	init_fd_struct(fd_struct);
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == in_file && update_fd(word_list->word, fd_struct,
				in_file) == FAILURE)
			return (change_exit_flg(exit_flg));
		else if (word_list->flag == out_file && update_fd(word_list->word,
				fd_struct, out_file) == FAILURE)
			return (change_exit_flg(exit_flg));
		else if (word_list->flag == append_file && update_fd(word_list->word,
				fd_struct, append_file) == FAILURE)
			return (change_exit_flg(exit_flg));
		else if (word_list->flag == heredoc
			&& update_fd(here_list->here_file_name, fd_struct,
				heredoc) == FAILURE)
			return (change_exit_flg(exit_flg));
		if (is_valid_fd(fd_struct) == FAILURE)
			return (ft_perror(word_list->word));
		word_list = word_list->next;
	}
	return (unlink_here_file(here_list, exit_flg));
}
