/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/08/08 14:20:17 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

volatile sig_atomic_t	g_sig;

static int	update_here_file(t_here_list **node, char *eof)
{
	char	*new_name;

	if (unlink((*node)->here_file_name) < 0)
		return (ft_perror("unlink"));
	free((*node)->here_file_name);
	new_name = get_file_name(1);
	if (new_name == NULL)
		return (ft_perror("failed to get file_name"));
	(*node)->here_file_name = ft_strdup(new_name);
	if (new_name == NULL)
	{
		free(new_name);
		return (ft_perror("ft_strdup"));
	}
	free(new_name);
	if (get_heredoc_file(node, eof) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	create_or_update_here_node(t_word_list **word_list, int *here_flg)
{
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
	{
		if ((*word_list)->flag == eof_num && *here_flg == false)
		{
			*here_flg = true;
			return (CREATE);
		}
		else if ((*word_list)->flag == eof_num && *here_flg == true)
			return (UPDATE);
		*word_list = (*word_list)->next;
	}
	*here_flg = false;
	return (false);
}

static int	new_here_node(t_here_list **new, char *eof)
{
	char	*name;

	*new = malloc(sizeof(t_here_list));
	if (*new == NULL)
		return (ft_perror("malloc"));
	name = get_file_name(0);
	if (name == NULL)
		return (ft_perror("failed to get file_name"));
	(*new)->here_file_name = ft_strdup(name);
	if (name == NULL)
	{
		free(name);
		return (ft_perror("ft_strdup"));
	}
	free(name);
	if (get_heredoc_file(new, eof) == FAILURE)
		return (FAILURE);
	(*new)->child_num = 0;
	(*new)->next = NULL;
	return (SUCCESS);
}

static int	create_head_node(t_here_list **node, t_word_list **word_list,
		int *here_flg)
{
	while (*word_list != NULL && (*word_list)->flag != eof_num)
		*word_list = (*word_list)->next;
	if (new_here_node(node, (*word_list)->word) == FAILURE)
		return (ft_perror("failed to new here node"));
	*word_list = (*word_list)->next;
	*here_flg = true;
	return (SUCCESS);
}

int	get_here_list(t_word_list *word_list, t_here_list **here_list)
{
	t_here_list	*new;
	t_here_list	*node;
	int			here_flg;

	if (create_head_node(&node, &word_list, &here_flg) == FAILURE)
		return (FAILURE);
	*here_list = node;
	while (word_list != NULL && g_sig != SIGINT)
	{
		if (create_or_update_here_node(&word_list, &here_flg) == CREATE)
		{
			if (new_here_node(&new, word_list->word) == FAILURE)
				return (FAILURE);
			node->next = new;
			node = new;
		}
		else if (create_or_update_here_node(&word_list, &here_flg) == UPDATE
			&& update_here_file(&node, word_list->word) == FAILURE)
			return (FAILURE);
		if (word_list != NULL)
			word_list = word_list->next;
	}
	if(g_sig==SIGINT)
	return(unlink_here_list(here_list));
	return (SUCCESS);
}
