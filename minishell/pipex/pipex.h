/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:57:36 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/16 13:00:32 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipe
{
	int		file_in;
	int		file_out;
	char	*filename;
	char	**command;
	int		fd[2];

}t_pipe;

int		check(char const str, char *charset);
int		findsecond(char const *str, char *charset);
int		findfirst(char const *str, char *charset);
char	**malloc_free(char **all);
char	**ft_split(char const *s, char *c);
int		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*my_parsing_filename(int i, int j, char *command, char *envp[]);
void	infile_to_command(t_pipe *my_pipex, char **argv, char *envp[]);
void	command_to_outfile(t_pipe *my_pipex, char **argv, char *envp[]);
int		ft_strlen(char *s4);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_for_parsing(char *s1, char s2);
int		ft_strchr(char *s, char *c);
void	fork_error(void);
void	pipe_error(void);
void	execve_error(void);
int		search_path(int i, char *envp[]);
char	*search_filename(char *command, char *envp[]);
void	free_my_files(char *new_filename, char *temp);
void	free_my_pipex(t_pipe *my_pipex);
char	*ft_strdup(const char *s1);
void	file_number_error(void);
void	handle_infile_error(int file1, char *commands);
void	handle_outfile_error(int file2, char *commands);

#endif
