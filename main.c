/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 13:22:51 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/27 12:19:36 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		error;
	char	*line;
	int		file;

	if (argc != 2)
	  return (1);
	file = open(argv[1], O_RDONLY);
	while ((error = get_next_line(file, &line)) > 0)
		printf("-> %s\n", line);
	printf("Error: %d\n", error);
	return (0);
}
