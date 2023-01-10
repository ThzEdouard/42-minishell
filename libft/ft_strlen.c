/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:59:09 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/10 17:23:23 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *thestring)
{
	int	i;

	if (!thestring)
		return (0);
	i = 0;
	while (thestring[i])
		i++;
	return (i);
}
