/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:20:35 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/11 10:30:00 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strdup(char *str)
{
	char	*r;

	r = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!r)
		return (NULL);
	r = ft_strcpy(r, str);
	return (r);
}