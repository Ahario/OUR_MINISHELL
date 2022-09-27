/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:05:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/27 16:20:32 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"
#include <readline/history.h>

void	exit2(int flag)
{
	if (!flag)
		printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	count_total(t_arg *head)
{
	int		i;
	t_arg	*tem;

	i = 0;
	tem = head;
	while (tem != NULL)
	{
		i++;
		tem = tem->next;
	}
	return (i);
}

void	error_message(char *str, char *des)
{
	rl_on_new_line();
	ft_putstr_fd("MINISHELL: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (des)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(des, 2);
		ft_putstr_fd("'", 2);
	}
	g_exit_number = 127;
}

void	ft_exit_error(int flag)
{
	if (!flag)
		ft_putstr_fd("exit\n", 1);
	error_message("exit: ", NULL);
	ft_putstr_fd("numeric argument required\n", 2);
	g_exit_number = 255;
	exit(255);
}

int	ft_atoi_exit(char *str, int i, int flag)
{
	int					sign;
	unsigned long long	ret;

	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9' && ret <= 9223372036854775808u)
		ret = ret * 10 + (str[i++] - '0');
	if ((ret > 9223372036854775807u && sign == 1) \
			|| (ret > 9223372036854775808u && sign == -1))
	{
		ft_exit_error(flag);
	}
	if (!flag)
		ft_putstr_fd("exit\n", 1);
	return (sign * ret);
}

static void	exit_numeric_check(char *str, int flag)
{
	int	j;

	j = 0;
	while (str[j] == ' ')
		j++;
	if (str[j] == '-' || str[j] == '+')
		j++;
	while (ft_isdigit(str[j]))
		j++;
	while (str[j] == ' ')
		j++;
	if (j != (int)ft_strlen(str))
	{
		ft_exit_error(flag);
	}
}

void	ft_exit(t_data *data)
{
	int		t_cnt;
	char	*str;
	int		flag;
	t_arg	*head;

	flag = 0;
	if (data->pipe)
		flag = 1;
	head = data->cmd;
	t_cnt = count_total(head);
	if (t_cnt > 1 && t_cnt < 3)
	{
		head = head->next;
		str = head->ac;
		exit_numeric_check(str, flag);
		exit(ft_atoi_exit(head->ac, 0, flag));
	}
	if (t_cnt >= 3)
	{
		error_message("exit: ", NULL);
		ft_putstr_fd("too many arguments\n", 2);
		g_exit_number = 1;
	}
	else
		exit2(flag);
}

void	exit_c_d(void)
{
	printf ("\033[1A");
	printf ("\033[11C");
	printf (" exit\n");
	exit (EXIT_FAILURE);
}
