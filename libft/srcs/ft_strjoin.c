/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:32:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/27 14:10:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	if (!(str = (char *)(ft_memalloc_lt(sizeof(char)
	* (ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (0);
	str = ft_strcat(str, (char *)s1);
	str = ft_strcat(str, s2);
	return (str);
}
