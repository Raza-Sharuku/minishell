/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/08/18 09:25:20 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*新しいリストを作る→次のノードの指す場所はNUll埋めする*/
t_word_list	*ft_newlst(char *content)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (new == NULL)
		return (NULL);
	new->word = ft_strdup(content);
	new->next = NULL;
	return (new);
}

int	dquotes_sprt(char *line)
{
	int	i;

	i = 0;
	line++;
	while (*line != '"' && *line != '\0')
	{
		i++;
		line++;
	}
	i += 2;
	return (i);
}

int	squotes_sprt(char *line)
{
	int	i;

	i = 0;
	line++;
	while (*line != '\'' && *line != '\0')
	{
		i++;
		line++;
	}
	i += 2;
	return (i);
}

t_word_list	*creat_list(char *line, int i)
{
	char		*content;
	t_word_list	*new;

	if (*line == ' ')
		line++;
	if (*line == '"')
		i = dquotes_sprt(line);
	else if (*line == '\'')
		i = squotes_sprt(line);
	else
	{
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0'
			&& line[i] != '"' && line[i] != '\'')
			i++;
	}
	content = malloc(sizeof (char) * (i + 1));
	content = duplicate(content, line, i);
	new = ft_newlst(content);
	free(content);
	return (new);
}

t_word_list	*sp_sprt(char **line, t_word_list *string, int i)
{
	t_word_list	*new;

	new = creat_list(*line, i);
	string->next = new;
	string = string->next;
	*(line) += (ft_strlen(new->word));
	return (string);
}
