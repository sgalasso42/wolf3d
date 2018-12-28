/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 21:44:23 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/27 14:10:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;

	if (!(cpy = (char *)ft_memalloc_lt(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	return (ft_strcpy(cpy, s));
}
