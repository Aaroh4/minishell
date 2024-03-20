/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:12 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/06 16:49:43 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*t;
	unsigned int	i;

	if (!s || !*f)
		return (NULL);
	len = ft_strlen((char *)s);
	t = (char *)malloc(sizeof(char) * len + 1);
	if (t == NULL)
		return (NULL);
	t[len] = '\0';
	i = 0;
	while (s[i])
	{
		t[i] = (*f)(i, s[i]);
		i++;
	}
	return (t);
}
