/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:22:16 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:14:15 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	p;

	i = 0;
	p = (char)c;
	while (s[i] != '\0')
		i++;
	while (i != 0)
	{
		if (s[i] == p)
			return (&((char *)s)[i]);
		i--;
	}
	if (s[i] == p)
		return (&((char *)s)[i]);
	return (0);
}
