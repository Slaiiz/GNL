/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:29:03 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/27 13:29:03 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	load_next_chunk(t_buffer *buff)
{
	char	*data;
	char	*new;
	size_t	size;

	if ((new = malloc(sizeof(char) * (buff->size + BUFF_SIZE))) == NULL)
		return (-1);
	data = buff->data;
	buff->data = new;
	if (data != NULL)
	{
		size = buff->size;
		while (size--)
			new[size] = data[size];
		free(data);
	}
	if ((size = read(buff->fd, new + buff->size, BUFF_SIZE)) != (size_t)-1)
		buff->size += size;
	return (size);
}

static int	trim_buffer(t_buffer *buff, size_t offset)
{
	char	*data;
	char	*new;
	size_t	size;

	if (offset >= buff->size)
	{
		free(buff->data);
		buff->data = NULL;
		buff->size = 0;
		return (1);
	}
	size = buff->size - offset;
	buff->size = size;
	if ((new = malloc(sizeof(char) * size)) == NULL)
		return (-1);
	data = buff->data + offset;
	while (size--)
		new[size] = data[size];
	free(buff->data);
	buff->data = new;
	return (1);
}

static int	retrieve_line(t_buffer *buff, char **out, size_t size)
{
	char	*data;
	char	*new;
	size_t	trim;

	if (buff->size < 1)
		return (0);
	data = buff->data;
	if (size < 1)
	{
		while (size < buff->size && data[size] != '\n')
			size++;
		if (size == buff->size)
			return (0);
	}
	if ((new = malloc(sizeof(char) * (size + 1))) == NULL)
		return (0);
	*out = new;
	trim = size + 1;
	while (size--)
		*new++ = *data++;
	*new = '\0';
	return (trim_buffer(buff, trim));
}

static int	get_buffer(const int fd, t_buffer *root, t_buffer **out)
{
	t_buffer	*new;

	while (root->next != NULL)
	{
		if (root->fd == fd)
			break ;
		root = root->next;
	}
	new = root;
	if (root->fd != fd)
	{
		if (root->fd != 0)
		{
			if ((new = malloc(sizeof(t_buffer))) == NULL)
				return (0);
			root->next = new;
			new->next = NULL;
			new->data = NULL;
			new->size = 0;
		}
		new->fd = fd;
	}
	*out = new;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int				error;
	t_buffer		*buff;
	static t_buffer	root;

	*line = NULL;
	if (!get_buffer(fd, &root, &buff))
		return (-1);
	while (!(error = retrieve_line(buff, line, 0)))
		if ((error = load_next_chunk(buff)) < 1)
			break ;
	if (error == 0)
		return (retrieve_line(buff, line, buff->size));
	return (error);
}
