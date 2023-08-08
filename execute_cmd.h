/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 15:49:13 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMD_H
# define EXECUTE_CMD_H

# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1
# define ADD 1
# define UPDATE 2
# define CREATE 3
# define READ 0
# define WRITE 1

typedef struct s_fd
{
	int			in_fd;
	int			out_fd;
}				t_fd;

typedef struct s_flg
{
	int			builtin_flg;
	int			exit_flg;
}				t_flg;

typedef struct s_p_data
{
	int			**pipe_2darr;
	int			i;
	int			cnt;
}				t_p_data;

typedef struct s_child
{
	t_fd		fd_struct;
	t_flg		flg_struct;
	t_here_list	*tmp_here;
	t_word_list	*tmp_word;
}				t_child;

typedef struct s_env_2d
{
	char		**ans;
	int			cnt;
	int			i;
	size_t		name_len;
	size_t		str_len;
}				t_env_2d;

typedef struct s_cmds
{
	pid_t		pid;
	int			ret;
	char		*status;
}				t_cmds;

typedef enum e_builtin_no
{
	echo_no,
	cd_no,
	pwd_no,
	export_no,
	unset_no,
	env_no,
	exit_no
}				t_builtin_no;

// builtin_error.c
int				cd_error(char *str);
void			exit_error(char *str);
int				export_error_update_exit_status(char *str,
					t_env_list **env_list);
int				env_error_update_exit_status(char *str, t_env_list **env_list);
// builtin.c
bool			is_builtin(t_word_list *word_list, int *builtin_flg);
int				execute_builtin(t_word_list *word_list, t_env_list **env_list,
					t_fd fd_struct, t_flg *flg_struct);
int				main_builtin(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list, t_flg flg_struct);
// cd_and_pwd.c
int				cd_cmd(t_word_list *word_list, t_env_list **env_list);
int				pwd_cmd(int fd, int *exit_flg);
// dup2_close.c
void			dup2_fd_struct(t_fd fd_struct, t_word_list **word_list,
					t_env_list **env_list);
void			dup2_pipe(t_p_data p_data, t_word_list **word_list,
					t_env_list **env_list);
void			close_pipe(t_p_data p_data, t_word_list **word_list,
					t_env_list **env_list);
// command.c
void			get_command(t_word_list **head);
// echo.c
void			echo_cmd(t_word_list *word_list, int fd);
// env.c
int				env_cmd(t_env_list **env_list, int fd);
// error.c
int				put_error(char *str);
int				ft_perror(char *str);
void			command_error(char *str);
char			**perror_change_err_flg(char *err_msg, int *err_flg);
void			put_error_exit_cmdsver(char *err_msg, t_p_data p_data,
					t_word_list **word_list, t_env_list **env_list);
// execve.c
void			execve_cmd(char **env_2darr, char **cmd_argv);
// execute_one_cmd.c
int				execute_one_cmd(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list);
// execute_some_cmds.c
int				execute_some_cmds(t_word_list **word_list,
					t_env_list **env_list, t_here_list **here_list,
					t_p_data p_data);
// execute_some_cmds_utils.c
void			advance_word_list(t_word_list *word_list, t_word_list **tmp,
					int start);
void			find_child_num(t_here_list *here_list, t_here_list **tmp,
					int i);
void			execute_builtin_cmdsver(t_child c_data, t_word_list **word_list,
					t_env_list **env_list);
bool			find_flg_until_pipe(t_word_list *word_list, int find_flg,
					int cnt);
int				itoa_status(int ret, char **status);
// exit.c
void			exit_cmd(t_word_list **word_list, t_env_list **env_list);
// export_nooption.c
int				export_nooption(t_env_list **env_list, int fd);
// export_utils.c
void			write_env_exportver(t_env_list *env_list, int fd);
bool			search_env_name_advance_env_list(char *word,
					t_env_list **env_list);
// export.c
int				export_cmd(t_word_list *word_list, t_env_list **env_list,
					int fd, int *exit_flg);
// main_execute_cmd.c
int				main_execute_cmd(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list, int pipe_cnt);
// free_exit.c
void			free_list_exit(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list, int exit_status);
void			free_list_pipe2darr_exit(t_p_data p_data,
					t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list);
void			free_2darr_exit(char ***arr, char ***arr2);
void			perror_free_2darr_exit(char *err_msg, char ***arr,
					char ***arr2);
void			perror_free_list_exit(char *errmsg, t_word_list **word_list,
					t_env_list **env_list, t_here_list **here_list);
// free_2darr.c
void			free_int_2darr(int ***arr, int cnt);
void			free_char_2darr(char ***arr);
// free_list.c
void			free_word_list(t_word_list **list);
void			free_env_list(t_env_list **list);
void			free_here_list(t_here_list **list);
void			free_all_list(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list);
// ft_atoll.c
long long		ft_atoll(char *str, int *error_flg);
// get_cmd_argv.c
char			**get_cmd_argv(t_word_list *word_list, int *err_flg);
// get_env_2darr.c
char			**get_env_2darr(t_env_list *env_list, int *err_flg);
// get_env_list.c
size_t			get_name_len(char *str);
int				new_env_node(t_env_list **node, char *envp);
int				get_env_list(char **envp, t_env_list **head);
// get_heredoc_file.c
char			*get_file_name(int i);
int				get_heredoc_file(t_here_list **node, char *eof);
int				unlink_here_list(t_here_list **here_list);
// heredoc.c
int				get_here_list(t_word_list *word_list, t_here_list **here_list);
// set_redirection.c
int				set_redirection(t_word_list *word_list, t_here_list *here_list,
					t_fd *fd_struct, int *exit_flg);
int				unlink_here_file(t_here_list *here_list, int *exit_flg);
// signal.c
int				set_sigint(void);
int				set_signal_parent(void);
// execute_utils.c
void			ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp);
int				ft_strcmp(char *s1, char *s2);
int				get_fd(char *file_name, int flg);
int				update_exit_status(t_env_list **env_list, char *estatus);
int				change_exit_flg(int *exit_flg);
// read_word_list.c
bool			find_flg(t_word_list *word_list, int flag);
void			set_child_num(t_word_list *word_list, t_here_list **here_list);
int				read_word_list(t_word_list **word_list, t_env_list **env_list,
					t_here_list **here_list);
void			init_minishell(char **envp, t_env_list **env_list_head,
					t_word_list **word_list_head, t_here_list **here_list);
// unset.c
bool			search_env_name(t_word_list *word_list, t_env_list *env_list);
void			unset_cmd(t_word_list *word_list, t_env_list **env_list);
#endif
