/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:06:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/22 15:24:51 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSENV_H
# define MSENV_H

typedef struct s_env_tdata
{
	char	*start;
	char	*end;
	char	*env_val;
	char	*temp;
	int		total_len;
}	t_env_tdata;

#endif