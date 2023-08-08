/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:06:39 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/08 14:38:34 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include"./libft/libft.h"
# define SUCCESS 0
# define FAILURE -1

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}						t_word_list;

typedef struct s_env_list
{
	char				*env_name;
	char				*env_value;
	int					write_flg;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_here_list
{
	int					here_fd;
	char				*here_file_name;
	int					child_num;
	struct s_here_list	*next;
}						t_here_list;

typedef struct s_dollar
{
	int					*d_count;
	int					len;
}						t_dollar;

typedef struct s_main_data
{
	t_word_list			*word_list;
	t_env_list			*env_list;
	t_here_list			*here_list;
	char				*line;
	char				*new_line;
}						t_main_data;

typedef enum s_flags
{
	command = 1,
	option,
	arguments,
	env,
	pipe_char = 5,
	output,
	append,
	input,
	heredoc,
	meta_char = 10,
	out_file,
	append_file,
	in_file,
	eof_num = 14,
}						t_flags;

//parse_line_1.c
t_word_list				*parse_line(char *line);
void					print_words(t_word_list *string);

//parse_line_2.c
t_word_list				*set_flags(t_word_list	*string);

//check_execute_error.c
int						check_error(t_word_list *string, t_env_list **env);

//make_list.c
t_word_list				*make_list(char *line);

//make_list2.c
t_word_list				*ft_newlst(char *content);
// int						dquotes_sprt(char *line);
// int						squotes_sprt(char *line);
t_word_list				*creat_list(char *line, int i);
t_word_list				*sp_sprt(char **line, t_word_list *string, int i);

//make_list3.c
t_word_list				*find_meta(t_word_list *string);

//make_list4.c
t_word_list				*argument_flag(t_word_list *string);
t_word_list				*divide_meta_str(t_word_list *string, int flag);
char					*give_flag(int i);
int						is_include_meta(char *str);
int						is_just_meta(char *str);

//utils.c
void					*ft_free_line2(char **result);
char					*duplicate(char *content, char *line, unsigned int n);
int						len_of_string(t_word_list *string);

//split_str.c
char					**split_str(char *str, char *charset);

// //get_env.c
// t_env_list				*init_minishell(char **envp,
// 							t_env_list **env_list_head);
//change_line_1.c
char					*change_line(char *line, t_env_list *env_list);

//change_line_2.c
char					**make_strlist(char *line, t_env_list *env_list);

//change_line_3.c
char					*count_s_str(char **line);
// char					*copy_str(char *line, char *str);

#endif
