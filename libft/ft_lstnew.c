/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:17:56 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 14:58:28 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nv;

	nv = malloc(sizeof(t_list));
	if (!nv)
		return (NULL);
	nv -> content = content;
	nv -> next = NULL;
	return (nv);
}
