/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_lt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:41:36 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/28 11:54:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc_lt(size_t size)
{
	void	*mem;

	if (!(mem = lt_push(malloc(size), ft_memdel)))
		return (0);
	ft_memset(mem, 0, size);
	return (mem);
}
