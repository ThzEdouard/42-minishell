/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:44:08 by eflaquet          #+#    #+#             */
/*   Updated: 2022/05/07 14:49:14 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_b;

	lst_b = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_b = ft_lstlast(*lst);
	lst_b->next = new;
}
