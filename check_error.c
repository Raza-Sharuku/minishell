/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execute_execute_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/08 11:37:31 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	int	one_string(t_word_list *string, t_env_list **env)
{
	if (string->flag >= 5 && string->flag < 10)
	{
		if (is_just_meta(string->word) == 5)
			printf("syntax error near unexpected token '%s'\n", string->word);
		else if (string->flag > 5 && string->flag < 10)
			printf("syntax error near unexpected token `newline'\n");
		free((*env)->env_value);
		(*env)->env_value = malloc(sizeof (char) * (4));
		(*env)->env_value = duplicate((*env)->env_value, "258", 3);
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int	command_error(t_word_list *string, t_env_list **env)
{
	if (string->next != NULL)
	{
		if (string->flag == 1 && (string->next->flag
				> 5 && string->next->flag < 10) && string->next->next == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
			free((*env)->env_value);
			(*env)->env_value = malloc(sizeof (char) * (4));
			(*env)->env_value = duplicate((*env)->env_value, "258", 3);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static	int	redirect_error(t_word_list *string, t_env_list **env)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
		{
			if (string->next->flag > 5 && string->next->flag < 10)
			{
				printf("syntax error near unexpected token '%s'\n",
					string->word);
				free((*env)->env_value);
				(*env)->env_value = malloc(sizeof (char) * (4));
				(*env)->env_value = duplicate((*env)->env_value, "258", 3);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

static	int	last_error(t_word_list *string, t_env_list **env)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
		{
			printf("syntax error near unexpected token `newline'\n");
			free((*env)->env_value);
			(*env)->env_value = malloc(sizeof (char) * (4));
			(*env)->env_value = duplicate((*env)->env_value, "258", 3);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	check_error(t_word_list *string, t_env_list **env)
{
	int			s_len;

	s_len = len_of_string(string);
	if (s_len == 1 && string->flag != 0)
		if (one_string(string, env) != 0)
			return (FAILURE);
	while (string)
	{
		if (command_error(string, env) != 0)
			return (FAILURE);
		if (redirect_error(string, env) != 0)
			return (FAILURE);
		if (string->next == NULL)
			if (last_error(string, env) != 0)
				return (FAILURE);
		string = string->next;
	}
	return (SUCCESS);
}
