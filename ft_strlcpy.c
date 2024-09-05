/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:08:08 by auskola-          #+#    #+#             */
/*   Updated: 2024/01/08 14:35:45 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//size - 1.> need to get one space for \0 (end line).

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	pos;

	src_len = ft_strlen(src);
	pos = 0;
	if (size == 0)
	{
		dst = NULL;
		return (src_len);
	}
	while (src_len > pos && pos < size -1)
	{
		dst[pos] = src[pos];
		pos++;
	}
	dst[pos] = '\0';
	return (src_len);
}
