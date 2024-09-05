/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:09:52 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/01 14:19:31 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_posini(char const *s1, char const *set)
{
	size_t	start_position;
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	j = 0;
	start_position = 0;
	found = 1;
	while (i < ft_strlen(s1) && found == 1)
	{
		found = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				found = 1;
				start_position ++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (start_position);
}

size_t	ft_endpos(char const *s1, char const *set)
{
	size_t	endpos;
	size_t	i;
	size_t	j;
	int		found;

	i = ft_strlen(s1)-1;
	j = 0;
	endpos = ft_strlen(s1);
	found = 1;
	while (i > 0 && found == 1)
	{
		found = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				found = 1;
				endpos = i;
			}
			j++;
		}
		j = 0;
		i--;
	}
	return (endpos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!*s1)
		return (ft_strdup(""));
	if (ft_posini(s1, set) == ft_strlen(s1))
		return (ft_strdup(""));
	return (ft_substr(s1, ft_posini(s1, set), \
		ft_endpos(s1, set) - ft_posini(s1, set)));
}
