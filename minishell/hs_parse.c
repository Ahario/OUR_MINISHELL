/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:35:53 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/27 18:06:13 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->error = 0;
	data->prev = NULL;
	data->next = NULL;
	data->pipe = NULL;
}

t_data	*clean_all(t_data *data, char *ch)
{
	char	**new_envp;
	t_data	*new;

	free(ch);
	if (!data->cmd)
		return (data);
	new_envp = ft_malloc_envp(data->envp);
	while (data)
	{
		ft_clean_all_utill(&data);
	}
	new = (t_data *)malloc(sizeof(t_data));
	new->envp = new_envp;
	ft_set_data(new);
	return (new);
}

void	ft_envp_change(char **envp)
{
	int	shlvl;
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 5))
		{
			free(envp[i]);
			envp[i] = ft_strdup("OLDPWD=");
		}
		else if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(&envp[i][6]);
			free(envp[i]);
			shlvl += 1;
			if (shlvl < 0)
				shlvl = 0;
			envp[i] = ft_strjoin_flag("SHLVL", ft_itoa(shlvl), 2);
		}
		i++;
	}
}

char	**ft_malloc_envp(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while (envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = NULL;
	i -= 1;
	while (i >= 0 && envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		i--;
	}
	return (ret);
}

t_data	*ft_before(int argc, char *argv[], char **envp)
{
	t_data			*data;
	struct termios	change;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
	g_exit_number = 0;
	data = (t_data *)malloc(sizeof(t_data));
	ft_set_data(data);
	data->envp = ft_malloc_envp(envp);
	ft_envp_change(data->envp);
	ft_signal();
	return (data);
}
