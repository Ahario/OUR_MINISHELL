 #include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

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

int	if_char(char const *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(check(str[i], charset)))
		i++;
	return (i);
}

int add_back_1(t_arg *head, char *ch, char *charset)
{
	t_arg	*curr;
	t_arg	*new;
	int			i;
	char		checking;

	i = 0;
	checking = charset[0];
	curr = head;
	new = malloc(sizeof(t_arg) * 1);
	while (ch[i] != '\0')
	{
		i++;
		if ((ch[i] == checking && ch[i - 1] != '\\'))
		{
			i++;
			break;
		}
	}
	new->ac = malloc(sizeof(char) * (i + 1));
	while(curr->next != NULL)
		curr = curr->next;
	ft_strlcpy(new->ac, ch, (i + 1));
	curr->next = new;
	new->next = NULL;
	return (i);
}

void add_back(t_arg *head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;

	curr = head;
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (if_char(ch, " ") + 1));
	while(curr->next != NULL)
		curr = curr->next;
	ft_strlcpy(new->ac, ch, (if_char(ch, " ") + 1));
	curr->next = new;
	new->next = NULL;
}

int	parse(char *ch, t_data *data)
{
	int			i;
	t_arg	*head;
//	t_arg	*curr;

	i = 0;
	head = malloc(sizeof(t_arg) * 1);
	head->next = NULL;
//	curr = head;
	data->argc = ft_strlen(ch);
	while (ch[i] != '\0')
	{
		if (ch[i] != '\'' && ch[i] != '\"')
		{
			while ((ch[i] >= 9 && ch[i] <= 13) || ch[i] == ' ')
				i++;
//			curr->ac = malloc(sizeof(char) * (if_char(ch, " ") + 1));
			add_back(head, &ch[i]);
//			ft_strlcpy(curr->ac, &ch[i], (if_char(&ch[i], " ") + 1));
			i += (if_char(&ch[i], " ") + 1);
		}
		else if (ch[i] == '\"' || ch[i] == '\'')
			i += (add_back_1(head, &ch[i], &ch[i]) + 1);
	}
/*	while(head->next != NULL)
	{
		head = head->next;
		if (!exitcheck(head))
			exit2();
		printf("%s\n", head->ac);
	}*/
	head = head->next;
	data->cmd = head;
	return (1);
}

void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
}

void	ft_start(t_data *data)
{
	t_arg *check;

	data->cmd->type = 0;
	check = data->cmd;
	if (!(ft_strncmp(check->ac, "exit", 5)))
		ft_exit(check);
	if (!(ft_strncmp(check->ac, "env", 4)))
		ft_env(data->envp);
	if (!(ft_strncmp(check->ac, "export", 6)))
		ft_export(data);
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
		if (!ch)
			exit_C_d();
		add_history(ch);
		if (parse(ch, &data))
			ft_start(&data);
		free(ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}

