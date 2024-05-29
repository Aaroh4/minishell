/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:35:56 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/28 13:34:25 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freestr(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
}

char	*ft_sub(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == 0 || str[1] == 0)
		return (NULL);
	temp = ft_substr(str, i + 1, ft_strrlen(str) - (i + 1));
	if (!*temp)
		freestr(&temp);
	str[i + 1] = '\0';
	return (temp);
}

char	*ft_read(int fd, char *str, char *buf)
{
	int		read_size;
	char	*temp;

	read_size = 1;
	while (read_size)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		if (read_size == 0)
			break ;
		buf[read_size] = 0;
		if (!str)
			str = ft_strrdup("");
		if (!str)
			return (NULL);
		temp = str;
		str = ft_strrjoin(temp, buf);
		freestr(&temp);
		if (ft_str_chr(buf))
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*ret;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		freestr(&str);
		return (NULL);
	}
	buf = malloc(BUFFER_SIZE + 1);
	ret = ft_read(fd, str, buf);
	freestr(&buf);
	if (!ret)
		return (NULL);
	str = ft_sub(ret);
	return (ret);
}
