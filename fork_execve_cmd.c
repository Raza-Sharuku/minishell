/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execve_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:17:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 00:49:55 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

int	init_fork_execve_cmd(t_proccess_data *pro_data, t_env_list *env_list,
		int pipe_cnt)
{
	get_pipe_2darr(&pro_data->pipe_2darr, pipe_cnt);
	if (pro_data->pipe_2darr == NULL)
		return (FAILURE);
	pro_data->env_2darr = NULL;
	if (env_list != NULL)
		pro_data->env_2darr = get_env_2darr(env_list);
	if (env_list != NULL && pro_data->env_2darr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	advance_list_to_pipe_char(t_word_list **word_list)
{
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
	if (*word_list != NULL)
		*word_list = (*word_list)->next;
}

int	fork_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, int pipe_cnt)
{
	t_proccess_data	pro_data;

	pro_data.pipe_cnt = pipe_cnt;
	if (init_fork_execve_cmd(&pro_data, *env_list, pipe_cnt) == FAILURE)
		put_error_exit("failed to init_ford_execve_cmd");
	pro_data.i = 0;
	while (pro_data.i < pipe_cnt + 1 && word_list != NULL)
	{
		if (pro_data.i < pipe_cnt && pipe(pro_data.pipe_2darr[pro_data.i]) < 0)
			put_error_exit("pipe");
		pro_data.pid = fork();
		if (pro_data.pid < 0)
			put_error_exit("fork");
		if (pro_data.pid == 0)
			child_execve_cmd(word_list, env_list, here_list, pro_data);
		else
			parent(pro_data);
		pro_data.i++;
		advance_list_to_pipe_char(&word_list);
	}
	pro_data.i = 0;
	while (pro_data.i < pipe_cnt + 1)
	{
		if (wait(NULL) < 0)
			put_error_exit("wait");
		pro_data.i++;
	}
	return (SUCCESS);
}