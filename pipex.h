/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:50 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/24 15:00:50 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdarg.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct ss_list
{
	int		heredoc;
	int		**fd;
	int		ncomand;
	int		comand;
	int		pid;
	char	**paths;
}	t_tlist;

void	ft_place_comand(t_tlist *pipex, int argc, char **argv, char **envp);
int		final_child(t_tlist *pipex, int *file, char **argv, int argc);
int		first_child(t_tlist *pipex, int *file, char **argv);
int		middle_child(t_tlist *pipex, int argc);
int		ft_create_pipe(t_tlist *pipex);
int		ft_create_childs_fd(t_tlist *pipex);
int		ft_execute(t_tlist *pipex, char **argv, char **envp);
void	ft_heredoc(int *file, char *delimitador);
char	*ft_strjoinpip(char const *s1, char const *s2);
char	*ft_find_paths(char **large, char *small);

#endif
