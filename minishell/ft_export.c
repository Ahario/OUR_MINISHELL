/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:24:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/21 18:32:11 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!envp)
		return(NULL);
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
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i] || !envp[i + 1])
		return (NULL);
	i++;
	j = i;
	while (envp[i])
		i++;
	size = i - j;
	ret = (char *)malloc(sizeof(char) * size);
	while (size >= 0)
		ret[size--] = envp[i--];
	return (ret);
}

char	**print_array(char **envp)
{
	char	**array;
	char	*tem;
	int		i;
	int		size;

	i = 0;
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

void	ft_export_narg(char **envp)
{
	char	*val;
	char	*key;
	char	**array;
	int		i;

	i = 0;

	key	= NULL;
	val = NULL;
	array = print_array(envp);
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
		return(1);
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
			break;
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
/*int	check_env_index(char *envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i] == key[i])
	{
		if (envp[i] < key[i] || !key[i])
			return (1);
		i++;
	}
	return (0);
}*/

char	**ft_new_envp(char **tem, char *key, char *val)
{
	char	**ret;
	int		size;

	size = 0;
	while (tem[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * size + 1);
	size = 0;
	while (tem[size])
	{
		ret[size] = tem[size];
		size++;
	}
	ret[size++] = ft_strjoin_keyval(key, val);
	ret[size] = NULL;
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
		return(tem);
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

char	*change_arg(char *arg, char c)
{
	char	*ret;
	int		i;
	int		j;
	int		cnt;

	i  = 0;
	cnt = 0;
	while (arg[i])
	{
		if (arg[i] == c && arg[i - 1] == '\\')
			cnt++;
		i++;
	}
	if (cnt % 2 == 1)
	{
		error_message("Minishell: unexpected EOF while looking for matching ");
		printf ("\'%c\'\n", c);
		return (0);
	}
	ret = (char *)malloc(sizeof(char) * i - cnt);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] != c)
			ret[j++] = arg[i];
		i++;
	}
	ret[j] = '\0';
	free (arg);
	arg = NULL;
	return (ret);
}
/*
char	*ft_dollar_change(char *arg)
{
	int		i;
	int		j;
	int		cnt;
	char	*ret;

	i = 0;
	cnt = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1])
			cnt++;
		i++;
	}
	if (!cnt)
		return (arg);
	ret = (char *)malloc(sizeof(char) * i + cnt);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1] != '\\')
			ret[j++] = '\\';
		ret[j++] = arg[i];
		i++;
	}
	ret[j] = '\0';
	free(arg);
	arg = NULL;
	return (ret);
}

int	ft_export_parse(t_arg *arg)
{
	t_arg *tem;

	tem = arg;
	while (tem)
	{
		if (ft_strchr(tem->ac, '"') || ft_strchr(tem->ac, '\'') ||\
				ft_strchr(tem->ac, '$') || ft_strchr(tem->ac, '\\'))
			break;
		tem = tem->next;
	}
	if (!tem)
		return (0);
	tem = arg;
	while (tem)
	{
		if (ft_strchr_ind(tem->ac, '"') <= ft_strchr_ind(tem->ac, '\''))
			tem->ac = change_arg(tem->ac, '"');
		else if (ft_strchr_ind(tem->ac, '\'') <= ft_strchr_ind(tem->ac, '"'))
			tem->ac = change_arg(tem->ac, '\'');
		 if (ft_strchr(tem->ac, '$') && ft_strchr(tem->ac, '\\'))
			tem->ac = ft_dollar_change(tem->ac);
		 //$ 환경변수 치환필요
		if (tem->ac == NULL)
			return (1);
		tem = tem->next;
	}
	return (0);
}
*/
void	ft_export(t_data *data)
{
	t_arg	*tem;
	char	*key;

	if (!data->cmd->next)
	{
		ft_export_narg(data->envp);
		return ;
	}
	tem = data->cmd->next;
//	if (ft_export_parse(tem))
//		return ;
	while (tem)
	{
		if (ft_check_key(tem->ac, 1))
		{
			error_message("Minishell: export: ");
			printf ("\'%s\': not a vaild identifier\n", tem->ac);
			return;
		}
		key = find_key(tem->ac);
		if (ft_strchr(tem->ac, '=') || ft_strchr(tem->ac, '+'))
		{
			data->envp = ft_change_envp(data, tem->ac, 0);
			free(key);
		}
		else if (ft_check_export(data, key))
		{
			free(key);
			tem = tem->next;
			continue ;
		}
		else
			data->envp = ft_new_envp(data->envp, key, NULL);
		tem = tem->next;
	}
}
