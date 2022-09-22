#include "minishell.h"

int	exit_number;
//t_arg *set_cmd(char *ch)
//{
//	t_arg	*cmd;
//	int			i;
//
//	i = 0;
//	char	**ac;
//	int		type;
//	int		fd_in;
//	int		fd_out;
//	int		if_next;
//	return (cmd);
//}

//void addFirst(t_arg *target, int data)
//{
//   t_arg *newNode = malloc(sizeof(t_arg) * 1);
//    newNode->next = target->next;
//    newNode->data = data;

//    target->next = newNode;
//}

/*int	check(char const str, char *charset)
{
	if (str == charset[0])
		return (1);
	return (0);
}*/

// int	if_char(char const *str, char *charset)
// {
//	int	i;

//	i = 0;
//	while (str[i] != '\0' && !(check(str[i], charset)))
//		i++;
//	return (i);
// }

int	if_char(char const *str)
{
	int		i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	while(str[i] != '\0')
	{
		if (i > 1)
		{
			if ((str[i - 1] != '\\' && str[i] == '\"') || (str[i - 1] != '\\' && str[i] == '\''))
			{
				if (str[i] == '\"' && q_flag == 0)
				{
					if (dq_flag == 1)
						dq_flag = 0;
					else
						dq_flag = 1;
				}
				else if (str[i] == '\'' && dq_flag == 0)
				{
					if (q_flag == 1)
						q_flag = 0;
					else
						q_flag = 1;
				}
			}
		}
		if (q_flag == 0 && dq_flag == 0 && str[i] == ' ')
			break;
		i++;
	}
	return (i);
}

int add_back_1(t_arg **head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;
	int		i;

	i = 0;
	curr = *head;
	while (ch[i] != '\0')
	{
		i++;
		if ((ch[i] == ch[0] && ch[i - 1] != '\\'))
		{
			i++;
			break;
		}
	}
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(new->ac, ch, (i + 1));
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while(curr->next != NULL)
			curr = curr->next;
		curr = new;
	}
	return (i);
}

void add_back(t_arg **head, char *ch)
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
		while(curr->next != NULL)
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


int check_q(char *str)
{
	int			i;
	int dq_flag;

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

int check_dq(char *str)
{
	int			i;
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

int check_redirect(char *str)
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

int check_exitnumber(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (0);
	return (1);
}

int check_pipe(char *str)
{
	if (str[0] == '|')
		return (0);
	return (0);
}

void assign_q(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = SINQ;
}

void assign_dq(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = DOUQ;
}

void assign_redirect(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = RDRT;
}

void assign_pipe(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = PIPE;
}

void assign_norm(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = NORM;
}

void assign_parse (t_data *data)
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
	// t_arg *head = data->cmd;
	// while(head != NULL) 
	// {
	// 	printf("this is final :%d\n", head->type);
	// 	head = head->next;
	// }
	replace_parse (data);
}

char *get_path(char *str)
{
	int			i;
	int			j;
	int			k;
	char	*temp;

	temp = NULL;
	i = 0;
	j = 0;
	k = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i + j] != ' ' && str[i + j] != '\0' && str[i + j] != '\"')
				j++;
			temp = malloc(sizeof(char) * (j + 1));
			while (k != j)
			{
				temp[k] = str[i + k];
				k++;
			}
			temp[k] = '\0';
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

char *replace_dollar_sign(t_arg **head, int flag, t_data *data)
{
	t_arg	*curr;
	char	*temp;
	char	*temp2;
	char	*str;
	int			i;
	curr = *head;
	//flag 1 == $?
	// flag 2 == $
	temp = NULL; 
	temp2 = NULL;
	str = NULL;
	i = 0;
	if (flag == 1)
	{
		temp = ft_itoa(exit_number);
		str = malloc(sizeof(char) * ((ft_strlen(curr->ac) - 2) + ft_strlen(temp) + 1));
		while (curr->ac[i] != '\0')
		{
			if (curr->ac[i] == '$')
			{
				i += 2;
				temp2 = ft_strjoin_normal(str, temp);
				free(str);
				str = temp2;
			}
			else
			{
				temp2 = ft_strjoin(str, &curr->ac[i]);
				free(str);
				str = temp2;
				i++;
			}
		}
		free(curr->ac);
		return (temp2);
	}
	else if (flag == 0)
	{
		temp = get_path(curr->ac);
		while(data->envp[i] != NULL && search_mini_path(i, data->envp, temp))
			i++;
	//	printf("%s\n", data->envp[i]);
	//	exit(1);
	}
	return (NULL);
}

void replace_parse(t_data *data)
{
	int			i;
	int		flag;
	char	*str;
	char	*temp;
	t_arg	*curr;

	i = 0;
	flag = 0;
	str = NULL;
	temp = NULL;
	curr = data->cmd;

	while (curr != NULL)
	{
		flag = 0;
		i = 0;
		if (curr->type == SINQ)
		{
			while(curr->ac[i] != '\0')
			{
				if (curr->ac[i] == '\'')
					i++;
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
		}
		else if (curr->type == DOUQ)
		{
			// if (ft_strchr(curr->ac, '$') == 1)
			// {
			// 	if (curr->ac[i] == '$' && curr->ac[i + 1] == '?')
			// 		flag = 1; 
			// 	replace_dollar_sign(&curr, flag);
			// }
			while(curr->ac[i] != '\0')
			{
				if (curr->ac[i] == '\"')
					i++;
				if (curr->ac[i] == '$')
				{
					if (curr->ac[i] == '$' && curr->ac[i + 1] == '?')
						flag = 1;
					curr->ac = replace_dollar_sign(&curr, flag, data);
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
		}
		temp = NULL;
		str = NULL;
		curr = curr->next;
	}
/*	t_arg *head = data->cmd;
	while(head != NULL) 
	{
		printf("this is final : %s %d\n", head->ac, head->type);
		head = head->next;
	}
*/
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
			while ((ch[i] >= 9 && ch[i] <= 13) || ch[i] == ' ')
				i++;
			add_back(&head, &ch[i]);
			i += (if_char(&ch[i]));
		}
	}
	i = 0;
	// while(head != NULL) 
	// {
	// 	printf("this is final : %s %d\n", head->ac, i);
	// 	head = head->next;
	// 	i++;
	// }
	data->cmd = NULL;
	data->cmd = head;
	assign_parse (data);
}


void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
	exit_number = 127;
}

void	clean_all(t_data *data)
{
	t_arg	*next;

	data->fd_in = -1;
	data->fd_out = -1;
	while (data->cmd)
	{
		if (data->cmd->ac)
			free(data->cmd->ac);
		next = data->cmd->next;
		free(data->cmd);
		data->cmd = next;
	}
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
void	ft_set_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->prev = NULL;
	data->next = NULL;
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
			parse(ch, data);
			ft_redir(data);
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

