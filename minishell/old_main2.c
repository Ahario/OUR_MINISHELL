 #include "minishell.h"

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

int	check(char const str, char *charset)
{
	if (str == charset[0])
		return (1);
	return (0);
}

// int	if_char(char const *str, char *charset)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0' && !(check(str[i], charset)))
// 		i++;
// 	return (i);
// }

int	if_char(char const *str, char *charset)
{
	int		i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	(void)charset;
	while(str[i] != '\0')
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
		curr->next = new;
	}
	return (i);
}

void add_back(t_arg **head, char *ch)
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
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

int check_built(t_data	*data, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		ft_echo(data);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(data);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(data);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(data);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(data->envp);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(data);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		ft_exit(data->cmd);
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
			dq_flag = 0;
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
			q_flag = 0;
		if (str[i] == '\"' && q_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int check_redirect(char *str)
{
	if (str[0] == '>')
		return (0);
	else if (str[0] == '<')
		return (0);
	else if (str[0] == '<' && str[1] == '<')
		return (0);
	else if (str[0] == '>' && str[1] == '>')
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

void asssign_norm(t_arg **head)
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
	//	else
	//		assign_norm(&curr);
		curr = curr->next;
	}
}

void parse(char *ch, t_data *data)
{
	int			i;
	t_arg	*head;

	i = 0;
	head = NULL;
	data->argc = ft_strlen(ch);
	// printf("%s\n", ch);
	while (ch[i] != '\0')
	{
		if ((ch[i] != '\'' && ch[i] != '\"') || (ch[i] == '\"' || ch[i] == '\''))
		{
			while ((ch[i] >= 9 && ch[i] <= 13) || ch[i] == ' ')
				i++;
			add_back(&head, &ch[i]);
			i += (if_char(&ch[i], " "));
		}
		else if (ch[i] == '\"' || ch[i] == '\'')
			i += (add_back_1(&head, &ch[i]));
	}
	i = 0;
	// while(head != NULL) 
	// {
	// 	printf("this is final : %s %d\n", head->ac, i);
	// 	head = head->next;
	// 	i++;
	// }
	// free(head);
	data->cmd = head;
	assign_parse (data);
}


void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
}

int	main(int argc, char *argv[], char **envp) 
{
	t_data			data;
	struct termios	terminal;
	char			*ch;

	tcgetattr(STDIN_FILENO, &terminal);
	before_init();
	(void)argc;
	(void)argv;
	data.envp = envp;
	ft_signal();
	while(1)
	{
		ch = readline("MINISHELL./ ");
//		sunglee_signal_here;
		if (ch)
		{
			parse(ch, &data);
			check_built(&data, data.cmd->ac);
		}
		else if (!ch)
			exit_C_d();
		add_history(ch);
		free(ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}

