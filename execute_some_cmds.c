/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_some_c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:31:32 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 00:55:34 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

static int	parent_close(t_p_data p_data)
{
	if (p_data.i > 0 && p_data.i <= p_data.cnt)
	{
		if (close(p_data.pipe_2darr[p_data.i - 1][READ]) < 0)
			return (ft_perror("close p"));
		if (close(p_data.pipe_2darr[p_data.i - 1][WRITE]) < 0)
			return (ft_perror("close p"));
	}
	return (SUCCESS);
}

static int	wait_some_cmds(int cnt)
{
	int	wstatus;

	if (set_signal_parent() == FAILURE)
		return (ft_perror("failed to set signal parent"));
	while (cnt >= 0)
	{
		if (wait(&wstatus) < 0)
			return (ft_perror("wait"));
		cnt--;
	}
	if (set_sigint() == FAILURE)
		return (ft_perror("failed to set sigint"));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	else
		return (WEXITSTATUS(wstatus));
}

static void	prepare_execve_cmds(t_word_list **word_list, t_env_list **env_list,
		int start)
{
	char		**env_2darr;
	char		**cmd_argv;
	int			err_flg;
	t_word_list	*tmp;

	advance_word_list(*word_list, &tmp, start);
	err_flg = false;
	env_2darr = get_env_2darr(*env_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	cmd_argv = get_cmd_argv(tmp, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	free_all_list(word_list, env_list, NULL);
	execve_cmd(env_2darr, cmd_argv);
}

// t_child ↓
// 	t_fd				fd_struct;
// 	t_flg				flg_struct;
// 	t_here_list			*tmp_here;
// 	t_word_list			*tmp_word;

static void	child_execute_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_p_data p_data)
{
	t_child	c_data;

	advance_word_list(*word_list, &c_data.tmp_word, p_data.i);
	if (find_flg_until_pipe(*word_list, command, p_data.i) == false)
		free_list_exit(word_list, env_list, here_list, EXIT_SUCCESS);
	find_child_num(*here_list, &c_data.tmp_here, p_data.i);
	if (set_redirection(c_data.tmp_word, c_data.tmp_here, &c_data.fd_struct,
			&c_data.flg_struct.exit_flg) == FAILURE)
		free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
	free_here_list(here_list);
	dup2_pipe(p_data, word_list, env_list);
	close_pipe(p_data, word_list, env_list);
	free_int_2darr(&p_data.pipe_2darr, p_data.cnt);
	if (is_builtin(c_data.tmp_word, &c_data.flg_struct.builtin_flg) == true)
		execute_builtin_cmdsver(c_data, word_list, env_list);
	else
	{
		dup2_fd_struct(c_data.fd_struct, word_list, env_list);
		prepare_execve_cmds(word_list, env_list, p_data.i);
	}
}

int	execute_some_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_p_data p_data)
{
	t_cmds	cmds_data;

	p_data.i = -1;
	while (++p_data.i <= p_data.cnt)
	{
		if (p_data.i < p_data.cnt
			&& pipe(p_data.pipe_2darr[p_data.i]) == FAILURE)
			return (ft_perror("pipe"));
		cmds_data.pid = fork();
		if (cmds_data.pid < 0)
			return (ft_perror("fork"));
		if (cmds_data.pid == 0)
			child_execute_cmds(word_list, env_list, here_list, p_data);
		else
			parent_close(p_data);
	}
	cmds_data.ret = wait_some_cmds(p_data.cnt);
	if (itoa_status(cmds_data.ret, &cmds_data.status) == FAILURE)
		return (FAILURE);
	update_exit_status(env_list, cmds_data.status);
	return (SUCCESS);
}
