/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:23:39 by aamorin-          #+#    #+#             */
/*   Updated: 2021/08/31 18:48:00 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_pipe	init_pipex(int a)
{
	t_pipe	pipex;
	int		i;

	pipex.procecess_num = a - 3;
	pipex.pipes = (int **)malloc((pipex.procecess_num + 1) * sizeof(int *));
	pipex.pid = (int *)malloc((pipex.procecess_num) * sizeof(int));
	i = 0;
	while (i < pipex.procecess_num + 1)
	{
		pipex.pipes[i] = (int *)malloc((2) * sizeof(int));
		i++;
	}
	i = 0;
	while (i < pipex.procecess_num + 1)
	{
		if (pipe(pipex.pipes[i]) == -1)
			exit (0);
		i++;
	}
	return (pipex);
}

void	child(t_pipe pipex, char **argv, char **envp, int i)
{
	int		j;

	j = 0;
	while (j < pipex.procecess_num + 1)
	{
		if (j != i)
			close(pipex.pipes[j][0]);
		if (j != i + 1)
			close(pipex.pipes[j][1]);
		j++;
	}
	dup2(pipex.pipes[i][0], 0);
	close(pipex.pipes[i][0]);
	dup2(pipex.pipes[i + 1][1], 1);
	close(pipex.pipes[i + 1][1]);
	pipex.c_split = ft_split_comma(argv[i + 2], ' ');
	pipex.bin = get_bin_path(envp, pipex.c_split[0]);
	if (execve(pipex.bin, pipex.c_split, envp) == -1)
	{
		ft_frlloc(pipex.c_split);
		free(pipex.bin);
		perror("execve");
		exit (0);
	}
}

void	pipex(int a, char **argv, char **envp)
{
	t_pipe	pipex;
	int		i;

	i = 0;
	pipex = init_pipex(a);
	close(pipex.pipes[0][0]);
	pipex.pipes[0][0] = open(argv[1], O_RDONLY);
	if (pipex.pipes[0][0] < 0)
		exit (0);
	close(pipex.pipes[pipex.procecess_num][1]);
	pipex.pipes[pipex.procecess_num][1] = open(argv[a - 1], O_RDWR
			| O_TRUNC | O_CREAT, 0755);
	while (i < pipex.procecess_num)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
			exit (0);
		if (pipex.pid[i] == 0)
			child(pipex, argv, envp, i);
		i++;
	}
	free(pipex.pid);
	ft_frlloc_int(pipex.pipes, pipex.procecess_num + 1);
}

int	main(int a, char **argv, char **envp)
{
	if (a >= 5)
		pipex(a, argv, envp);
	else
		exit(0);
	return (0);
}
