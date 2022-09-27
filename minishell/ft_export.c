/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:24:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 16:26:14 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

char	*find_key(char *envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=' && envp[i] != '+')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 1);
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = envp[i];
	return (ret);
}

char	*find_value(char *envp)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i] || !envp[i + 1])
		return (NULL);
	i++;
	j = i;
	while (envp[i])
		i++;
	size = i - j;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	while (size >= 0)
		ret[size--] = envp[i--];
	return (ret);
}

char	**print_array(char **envp, int i)
{
	char	**array;
	char	*tem;
	int		size;

	array = ft_strdup_2(envp);
	while (array[i])
		i++;
	size = i - 1;
	while (size)
	{
		i = 0;
		while (i < size)
		{
			if (array[i] && ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tem = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tem;
			}
			i++;
		}
		size--;
	}
	return (array);
}

void	ft_export_narg(char **envp, char *key, char *val)
{
	char	**array;
	int		i;

	i = 0;
	array = print_array(envp, 0);
	while (array[i])
	{
		key = find_key(array[i]);
		val = find_value(array[i]);
		if (key)
		{
			printf("declare -x ");
			printf ("%s", key);
			free(key);
		}
		if (val)
		{
			printf ("=\"%s\"\n", val);
			free(val);
		}
		else
			printf ("\n");
		i++;
	}
	free_split(array);
}

int	ft_check_key(char *str, int flag)
{
	int	i;

	if (!str || !str[0])
		return (1);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '=' && str[i] != '+' \
				&& !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (1);
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		if (str[i] == '=' && !flag)
			return (1);
		else if ((str[i] == '=' || str[i] == '+') && flag)
			break ;
		i++;
	}
	return (0);
}

char	*ft_change_val(char *envp, char *str, int len)
{
	if (envp)
	{
		if (str[len] == '+' && str[len + 1] == '=')
			envp = ft_strjoin_free(envp, ft_strdup(&str[len + 2]));
		else if (envp)
		{
			free(envp);
			envp = ft_strdup(str);
		}
	}
	return (envp);
}

char	**ft_new_envp(char **tem, char *key, char *val)
{
	char	**ret;
	int		size;

	size = 0;
	while (tem[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	size = 0;
	while (tem[size])
	{
		ret[size] = tem[size];
		size++;
	}
	ret[size] = ft_strjoin_keyval(key, val);
	ret[++size] = NULL;
	free(tem);
	return (ret);
}

char	**ft_change_envp(t_data *data, char *str, int len)
{
	char	*key;
	char	**tem;
	int		i;

	i = 0;
	tem = data->envp;
	len = ft_strchr_ind(str, '+');
	if (!len)
		len = ft_strchr_ind(str, '=');
	key = find_key(str);
	while (tem[i] && ft_strncmp(tem[i], key, len))
		i++;
	if (tem[i])
	{
		tem[i] = ft_change_val(tem[i], str, len);
		free(key);
		return (tem);
	}
	tem = ft_new_envp(tem, key, find_value(str));
	return (tem);
}

int	ft_check_export(t_data *data, char *key)
{
	char	**tem;
	char	*check;
	int		i;

	i = 0;
	tem = data->envp;
	while (tem[i])
	{
		check = find_key(tem[i]);
		if (!ft_strcmp(check, key))
		{
			free(check);
			check = NULL;
			return (1);
		}
		free(check);
		check = NULL;
		i++;
	}
	return (0);
}

static void	add_export(t_data *data, t_arg *tem)
{
	char	*key;

	key = find_key(tem->ac);
	if (ft_strchr(tem->ac, '=') || ft_strchr(tem->ac, '+'))
	{
		data->envp = ft_change_envp(data, tem->ac, 0);
		free(key);
		key = NULL;
	}
	else if (ft_check_export(data, key))
	{
		free(key);
		key = NULL;
	}
	else
		data->envp = ft_new_envp(data->envp, key, NULL);
}

int	ft_export_error(t_arg **tem)
{
	error_message("export: ", (*tem)->ac);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	if ((*tem)->next)
		(*tem) = (*tem)->next;
	else
	{
		g_exit_number = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_data *data)
{
	t_arg	*tem;

	if (!data->cmd->next)
	{
		ft_export_narg(data->envp, 0, 0);
		return ;
	}
	tem = data->cmd->next;
	while (tem)
	{
		while (ft_check_key(tem->ac, 1))
		{
			if (ft_export_error(&tem))
				return ;
		}
		add_export(data, tem);
		tem = tem->next;
	}
}
