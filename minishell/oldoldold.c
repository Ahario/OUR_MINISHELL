/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:15:32 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/22 19:24:07 by sunglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


	// t_arg *hed = data->cmd;
	// while(hed != NULL) 
	// {
	// 	printf("%s\n", hed->ac);
	// 	hed = hed->next;
	// }

/*int	check(char const str, char *charset)
{
	if (str == charset[0])
		return (1);
	return (0);
}*/

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

int	if_char(char const *str, char *charset)
{
	int	i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	(void)charset;
	while (str[i] != '\0')
	{
		if ((str[i - 1] != '\\' && str[i] == '\"')
			|| (str[i - 1] != '\\' && str[i] == '\''))
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

// int add_back_1(t_arg **head, char *ch)
// {
// 	t_arg	*curr;
// 	t_arg	*new;
// 	int 		i;

// 	i = 0;
// 	curr = *head;
// 	while (ch[i] != '\0')
// 	{
// 		i++;
// 		if ((ch[i] == ch[0] && ch[i - 1] != '\\'))
// 		{
// 			i++;
// 			break;
// 		}
// 	}
// 	new = malloc(sizeof(t_arg) * 1);
// 	new->ac = malloc(sizeof(char) * (i + 1));
// 	ft_strlcpy(new->ac, ch, (i + 1));
// 	new->next = NULL;
// 	if (*head == NULL)
// 		*head = new;
// 	else
// 	{
// 		while(curr->next != NULL)
// 			curr = curr->next;
// 		curr->next = new;
// 	}
// 	return (i);
// }

void	add_back(t_arg **head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;

	curr = *head;
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (if_char(ch, " ") + 1));
	ft_strlcpy(new->ac, ch, (if_char(ch, " ") + 1));
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

void play_built(t_data *data, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		ft_echo(data);
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
		ft_exit(data->cmd);
	return ;
}

int check_built(t_data *data, char *str)
{
	(void)data;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (0);
	return (1);
}


int	check_q(char *str)
{
	int	i;
	int	dq_flag;

	i = 0;
	dq_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			if (dq_flag == 1)
				dq_flag = 0;
			else
				dq_flag = 1;
		}
		if (str[i] == '\'' && dq_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_dq(char *str)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (q_flag == 1)
				q_flag = 0;
			else
				q_flag = 1;
		}
		if (str[i] == '\"' && q_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_redirect(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (0);
	else if (str[0] == '>' && str[1] == '>')
		return (0);
	else if (str[0] == '>')
		return (0);
	else if (str[0] == '<')
		return (0);
	return (1);
}

int	check_exitnumber(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (0);
	return (1);
}

int	check_pipe(char *str)
{
	if (str[0] == '|')
		return (0);
	return (1);
}

void	assign_q(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = SINQ;
}

void	assign_dq(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = DOUQ;
}

void	assign_redirect(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = RDRT;
}

void	assign_pipe(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = PIPE;
}

void	assign_norm(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = NORM;
}

void	assign_parse (t_data *data)
{
	t_arg	*curr;

	curr = data->cmd;

	while(curr != NULL)
	{
		if (check_q(curr->ac) == 0)
			assign_q(&curr);
		else if (check_dq(curr->ac) == 0)
			assign_dq(&curr);
		else if (check_redirect(curr->ac) == 0)
			assign_redirect(&curr);
		else if (check_pipe(curr->ac) == 0)
			assign_pipe(&curr);
		else
			assign_norm(&curr);
		curr = curr->next;
	}
	replace_ds_parse(data);
	replace_parse (data);
}

int total_path_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' 
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '$')
		i++;

	return (i);
}

char *get_path(char *str)
{
	int			i;
	int			j;
	char	*temp;

	temp = NULL;
	i = 0;
	j = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			temp = malloc(sizeof(char) * (total_path_len(&str[i]) + 1));
			while (j != total_path_len(&str[i]))
			{
				temp[j] = str[i + j];
				j++;
			}
			temp[j] = '\0';
			break;
		}
		i++;
	}
	return (temp);
}

int search_mini_path(int j, char *envp[], char *str)
{
	int	i;

	i = 0;
	while(envp[j][i] == str[i])
	{
		if (str[i] == envp[j][i])
			i++;
		else
			return (1);
	}
	if (envp[j][i] == '=' && str[i] == '\0')
		return (0);
	return (1);
}

char *get_full_path(char *str, t_data *data)
{
	int			i;
	int			j;
	int			k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	temp = NULL;
	while(data->envp[i] != NULL && search_mini_path(i, data->envp, str))
		i++;
	if (data->envp[i] == NULL)
	{
		temp = malloc(sizeof(char) * (1));
		temp[0] = '\0';
		return (temp);
	}
	while(data->envp[i][j] != '=')
		j++;
	j++;
	temp = malloc(sizeof(char) * (get_temp_size(&data->envp[i][j]) + 1));
	while (data->envp[i][j] != '\0')
		temp[k++] = data->envp[i][j++];
	temp[k] = '\0';
	return (temp);
}

char *replace_dollar_sign(char *st, t_data *data)
{
	char	*temp;
	char	*temp2;
	int			i;

	temp = NULL; 
	temp2 = NULL;
	i = 0;
	while (st[i] != '\0')
	{
		if (st[i] == '$')
		{
			if (st[i] == '$' && st[i + 1] == '?')
				temp = ft_itoa(g_exit_number);
			else
			{
				temp2 = get_path(st);
				temp = get_full_path(temp2, data);
				free(temp2);
			}
			return (temp);
		}
		i++;
	}
	return (NULL);
}

int	before_r_ds_parse(char *str, t_data *data)
{
	int			i;
	int			j;
	int		flag;
	char	*temp;

	i = 0;
	j = 1;
	flag = 0;
	temp = NULL;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if (str[i] == '$' && flag != 2)
		{
			temp = replace_dollar_sign(&str[i], data);
			j += ft_charlen(temp);
			temp = NULL;
			i++;
			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0' && str[i] != ' ' && str[i] != '$')
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

// void replace_ds_parse(t_data *data)
// {
// 	int		flag;
// 	t_arg	*curr;
// 	char	*temp;
// 	char	*temp2;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		l;


// 	curr = data->cmd;
// 	temp = NULL;
// 	temp2 = NULL;
// 	i = 0;
// 	k = 0;
// 	l = 0;
// 	flag = 0;
// 	j = 0;
// 	while (curr != NULL)
// 	{
// 		flag = 0;
// 		i = 0;
// 		k = 0;
// 		j = 0;
// 		temp = malloc(sizeof(char) * ((before_r_ds_parse(curr->ac, data)) + 1));
// 		while (curr->ac[i] != '\0')
// 		{
// 			flag = check_flag(flag, &curr->ac[i]);
// 			if (curr->ac[i] == '$' && flag != 2)
// 			{
// 				l = 0;
// 				temp2 = replace_dollar_sign(&curr->ac[i], data);
// 				while (temp2[l] != '\0')
// 					temp[k++] = temp2[l++];
// 				free(temp2);
// 				i++;
// 				while (curr->ac[i] != '\"' && curr->ac[i] != '\'' && curr->ac[i] != '\0' && curr->ac[i] != ' ' && curr->ac[i] != '$')
// 					i++;
// 			}
// 			else
// 				temp[k++] = curr->ac[i++];
// 		}
// 		temp[k] = '\0';
// 		free(curr->ac);
// 		curr->ac = temp;
// 		temp = NULL;
// 		curr = curr->next;
// 	}
// }

// char *replace_ds_parse(char *str, t_data *data)
// {
// 	int		flag;
// 	char	*temp;
// 	char	*temp2;
// 	char	*ch;
// 	int		i;


// 	temp = NULL; 
// 	temp2 = NULL;
// 	str = NULL;
// 	i = 0;
// 	flag = 0;
// 	while (str[i] != '\0')
// 	{
// 		flag = check_flag(flag, &str[i]);
// 		if (str[i] == '$' && flag != 2)
// 		{   
// 			temp2 = replace_dollar_sign(str[i], data);
// 			temp = ft_strjoin_normal(ch, temp2);
// 			free(ch);
// 			free(temp2);
// 			ch = temp;
// 			i++;
// 			while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0' && str[i] != ' ' && str[i] != '$')
// 				i++;
// 		}
// 		else
// 		{	
// 			temp = ft_strjoin(ch, &str[i]);
// 			free(ch);
// 			ch = temp;
// 			i++;
// 		}
// 	}
// 	free(str);
// 	return (str);
// }

void replace_ds_parse(t_data *data)
{
	int		flag;
	t_arg	*curr;
	char	*temp;
	char	*temp2;
	char	*str;
	int		i;


	curr = data->cmd;
	temp = NULL; 
	temp2 = NULL;
	str = NULL;
	i = 0;
	flag = 0;
	while (curr != NULL)
	{
		flag = 0;
		i = 0;
		while (curr->ac[i] != '\0')
		{
			flag = check_flag(flag, &curr->ac[i]);
			if (curr->ac[i] == '$' && flag != 2)
			{   
				temp2 = replace_dollar_sign(&curr->ac[i], data);
				temp = ft_strjoin_normal(str, temp2);
				free(str);
				free(temp2);
				str = temp;
				i++;
				while (curr->ac[i] != '\"' && curr->ac[i] != '\'' && curr->ac[i] != '\0' && curr->ac[i] != ' ' && curr->ac[i] != '$')
					i++;
			}
			else
			{	
				temp = ft_strjoin(str, &curr->ac[i]);
				free(str);
				str = temp;
				i++;
			}
		}
		free(curr->ac);
		curr->ac = temp;
		temp = NULL;
		str = NULL;
		curr = curr->next;
	}
}

char *ft_strcpy_hth(char *str, int here, int there)
{
	int			i;
	int			j;
	char	*temp;

	i = here;
	j = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (there - here));
	while (i + j != there)
	{
		temp[j] = str[i + j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

// int get_total(char *str)
// {
// 	int 	i;
// 	int		j;
// 	int		flag;

// 	i = 0;
// 	j = 0;
// 	flag = 0;
// 	while (str[i] != '\0')
// 	{
// 		while(str[i] == '\"' && flag != 2)
// 		{
// 			j++;
// 			i++;
// 			if (flag == 1)
// 				flag = 0;
// 		}
// 		while(str[i] == '\'' && flag == 0)
// 		{
// 			j++;
// 			i++;
// 			if (flag != 1)
// 				flag = 2;
// 		}
// 		i++;
// 	}
// 	return (i - j);
// }

int get_temp_size(char *str)
{
	int			i;
	int			j;
	char	charset;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			charset = str[i];
			i++;
			while (str[i] != charset && str[i] != '\0')
			{
				i++;
				j++;
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

// char	*replace_parse(char *str)
// {
// 	int			i;
// 	int			j;
// 	char	*temp;
// 	char	charset;

// 	i = 0;
// 	j = 0;
// 	temp = malloc(sizeof(char) * ((get_temp_size(str)) + 1));
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			charset = str[i];
// 			i++;
// 			while (str[i] != charset && str[i] != '\0')
// 				temp[j++] = str[i++];
// 			if (str[i] != '\0')
// 				i++;
// 		}
// 		else
// 			temp[j++] = str[i++];
// 	}
// 	temp[j] = '\0';
// 	free(str);
// 	return (temp);
// }


void  replace_parse(t_data *data)
{
	int			i;
	int			j;
	char	*temp;
	char	charset;
	t_arg	*curr;

	i = 0;
	j = 0;
	temp = NULL;
	curr = data->cmd;
	while (curr != NULL)
	{
		j = get_temp_size(curr->ac);
		temp = malloc(sizeof(char) * (j + 1));
		j = 0;
		i = 0;
		while (curr->ac[i] != '\0')
		{
			if (curr->ac[i] == '\'' || curr->ac[i] == '\"')
			{
				charset = curr->ac[i];
				i++;
				while (curr->ac[i] != charset && curr->ac[i] != '\0')
					temp[j++] = curr->ac[i++];
				if (curr->ac[i] != '\0')
					i++;
			}
			else
				temp[j++] = curr->ac[i++];
		}
		temp[j] = '\0';
		free(curr->ac);
		curr->ac = temp;
		temp = NULL;
		curr = curr->next;
	}
}

int check_flag(int flag, char *str)
{
	int	i;

	i = flag;
	if (str[0] == '\"' && i != 2)
	{
		if (i == 1)
			i = 0;
		else
			i = 1;
	}
	if (str[0] == '\'' && i != 1)
	{
		if (i == 2)
			i = 0;
		else
			i = 2;
	}
	return (i);
}

int ft_charlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_find_red(char *str)
{
	int		i;
	int		j;
	int	flag;


	i = 0;
	j = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>' ) && flag == 0)
		{
			if (i > 0 && ((str[i - 1] == '<' && str[i] == '<') || (str[i - 1] == '>' && str[i] == '>')))
				i++;
			else
				j++;
		}
		i++;
	}
	return (j);
}

void before_parse(char *ch, t_data *data)
{
	int			i;
	int			j;
	int		flag;
	char	*temp;

	i = 0;
	j = 0;
	flag = 0;
	temp = malloc(sizeof(char) * (ft_charlen(ch) + ft_find_red(ch)) + 1);
	while (ch[i] != '\0')
	{
		flag = check_flag(flag, &ch[i]);
		if ((ch[i] == '|' || ch[i] == '<' || ch[i] == '>' || ch[i] == ';') && flag == 0)
		{		
			temp[j++] = ' ';
			if (ch[i + 1] != '\0' && ((ch[i] == '<' && ch[i + 1] == '<') || (ch[i] == '>' && ch[i + 1] == '>')))
			{
				temp[j++] = ch[++i];
				temp[j++] = ch[i++];
			}
		}
		temp[j++] = ch[i++];
	}
	temp[j] = '\0';
	parse(temp, data);
}

void parse(char *ch, t_data *data)
{
	int			i;
	t_arg	*head;
 
	i = 0;
	head = NULL;
	data->argc = ft_strlen(ch);
	while (ch[i] != '\0')
	{
		if ((ch[i] != '\'' && ch[i] != '\"') || (ch[i] == '\"' || ch[i] == '\''))
		{
			while (ch[i] == ' ')
				i++;
			add_back(&head, &ch[i]);
			i += (if_char(&ch[i], " "));
		}
	}
	data->cmd = head;
	free(ch);
	assign_parse (data);
}

void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
	g_exit_number = 0;
}

void	ft_set_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->prev = NULL;
	data->next = NULL;
}

void	clean_all(t_data *data)
{
	t_arg	*next;

	if (!data->cmd)
		return;
	while (data->cmd)
	{
		if (data->cmd->ac)
			free(data->cmd->ac);
		next = data->cmd->next;
		if (data->cmd)
			free(data->cmd);
		data->cmd = next;
	}
	ft_set_data(data);
}



char	**ft_malloc_envp(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while(envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * i);
	ret[i--] = NULL;
	while(envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		i--;
	}
	return (ret);
}

int	main(int argc, char *argv[], char **envp) 
{
	t_data			*data;
	struct termios	terminal;
	char			*ch;

	tcgetattr(STDIN_FILENO, &terminal);
	before_init();
	(void)argc;
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	ft_set_data(data);
	data->envp = ft_malloc_envp(envp);
	ft_signal();
	while(1)
	{
		ch = readline("MINISHELL./ ");
		if (ch)
		{
			before_parse(ch, data);
		//	printf ("AAAAAAA\n");
			if(!ft_redir(data))
				ft_cmd_start(data);
		}
		else if (!ch)
			exit_C_d();
		add_history(ch);
		clean_all(data);
		free(ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}
