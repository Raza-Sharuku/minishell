/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:14:31 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/14 09:27:25 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static	char	*joint_two_d(char *line, char *str,
						char *env_name)
{
	char	*new_line;

	while (*str == *env_name)
	{
		str++;
		env_name++;
	}
	new_line = line;
	line = ft_strjoin(line, env_name);
	free(new_line);
	if (ft_isalnum(*str) || *str == '_')
		return (line);
	return (line);
}

static	char	*joint_d_str2(char **line, char *str,
						t_env_list **env_list, char *new_line)
{
	while (*env_list)
	{
		if (ft_strncmp((*env_list)->env_name, str,
				ft_strlen((*env_list)->env_name)) == 0)
		{
			if (ft_strlen(str) == ft_strlen((*env_list)->env_name))
			{
				new_line = *line;
				*line = ft_strjoin(*line, (*env_list)->env_value);
				free(new_line);
			}
			else
				*line = joint_two_d(*line, str, (*env_list)->env_name);
			break ;
		}
		*env_list = (*env_list)->next;
	}
	return (*line);
}

static	char	*joint_d_str(char *line, char *str, t_env_list *env_list)
{
	char	*new_line;
	char	*ex_str;

	ex_str = str;
	new_line = NULL;
	if (*(str + 1) == '?')
	{
		new_line = line;
		line = ft_strjoin(line, str);
		free(new_line);
		return (line);
	}
	new_line = str;
	str = ft_strtrim(str, "$");
	line = joint_d_str2(&line, str, &env_list, new_line);
	if (env_list == NULL)
	{
		new_line = line;
		line = ft_strjoin(line, ex_str);
		free(new_line);
	}
	free(str);
	return (line);
}

static	char	*joint_array(char **result, t_env_list *env_list)
{
	int		i;
	char	*line;
	char	*new_line;

	i = 0;
	line = NULL;
	while (result[i] != NULL)
	{
		if (result[i][0] == '$')
		{
			line = joint_d_str(line, result[i], env_list);
		}
		else if (result[i] != NULL && result[i][0] != '$')
		{
			new_line = line;
			line = ft_strjoin(line, result[i]);
			free(new_line);
		}
		i++;
	}
	return (line);
}

char	*change_line(char *line, t_env_list *env_list)
{
	int		i;
	char	**result;
	char	*new_line;

	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (i == (int)ft_strlen(line))
	{
		new_line = malloc(sizeof (char) * (i + 1));
		new_line = duplicate(new_line, line, i);
		return (new_line);
	}
	result = make_strlist(line, env_list);
	new_line = joint_array(result, env_list);
	ft_free_line2(result);
	return (new_line);
}
