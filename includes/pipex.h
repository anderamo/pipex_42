/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:54:48 by aamorin-          #+#    #+#             */
/*   Updated: 2021/08/31 18:45:08 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../ft_printf/includes/ft_printf.h"

typedef struct s_pipe
{
	int		**pipes;
	int		*pid;
	int		procecess_num;
	char	**c_split;
	char	*bin;
}	t_pipe;

char	**ft_split_comma(char *s, char c);
char	*get_bin_path(char **envp, char *command);
char	**ft_frlloc(char **tab);
char	**ft_frlloc_int(int **tab, int size);

#endif
