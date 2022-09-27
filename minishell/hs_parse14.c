/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 16:35:58 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dq_flag(int flag)
{
	int	i;

	i = flag;
	if (i == 1)
		i = 0;
	else
		i = 1;
	return (i);
}

int	if_char(char const *str)
{
	int	i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"') || (str[i] == '\''))
		{
			if (str[i] == '\"' && q_flag == 0)
				dq_flag = check_dq_flag(dq_flag);
			else if (str[i] == '\'' && dq_flag == 0)
				q_flag = check_dq_flag(q_flag);
		}
		if (q_flag == 0 && dq_flag == 0 && str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

void	add_back(t_arg **head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;

	curr = *head;
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (if_char(ch) + 1));
	ft_strlcpy(new->ac, ch, (if_char(ch) + 1));
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void	play_built(t_data *data, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		ft_echo(data, 0);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(data);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(data);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(data);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(data);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(data->envp);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		ft_exit(data);
	return ;
}

int	check_built(t_data *data, char *str)
{
	(void)data;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (0);
	return (1);
}
