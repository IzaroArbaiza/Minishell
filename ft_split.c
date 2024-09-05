/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:22:19 by auskola-          #+#    #+#             */
/*   Updated: 2023/12/15 11:23:06 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*pointer;
	size_t	counter;
	size_t	len;

	counter = 0;
	len = ft_strlen(str);
	(pointer = (char *)malloc(sizeof(char) * (len + 1)));
	if (pointer == NULL)
		return (NULL);
	while (counter < len)
	{
		pointer[counter] = str[counter];
		counter++;
	}
	pointer[counter] = '\0';
	return (pointer);
}

size_t	ft_count_strings(const char *s, char c)
{
	size_t	strings;
	size_t	counter;

	if (!*s)
		return (0);
	strings = 0;
	counter = 1;
	if (!s)
		return (0);
	if (s[0] != c)
		strings = 1;
	while (s[counter] != '\0')
	{
		if ((s[counter] != c) && (s[counter - 1] == c))
			strings++;
		counter++;
	}
	return (strings);
}

char	*ft_get_line(char const *s, char c, int *mem_pos)
{
	int		characters;
	int		position;

	if (!*s)
		return (ft_strdup(""));
	position = *mem_pos;
	characters = 0;
	while (s[position] == c)
	{
		position++;
	}
	while (s[position] != c && s[position] != '\0')
	{
		position++;
		characters ++;
	}
	while (s[position] != '\0' && s[position] != c)
	{
		if (s[position] != c)
			characters++;
		position++;
	}
	*mem_pos = position;
	return (ft_substr(s, (position - characters), characters));
}

char	**ft_split(char const *s, char c)
{
	char	**substrings;
	int		strings;
	int		counter;
	int		mem_pos;

	counter = 0;
	mem_pos = 0;
	strings = ft_count_strings(s, c);
	substrings = (char **) malloc ((strings + 1) * sizeof(char *));
	if (!substrings)
	{
		return (NULL);
	}
	while (counter < strings)
	{
		substrings[counter] = ft_get_line(s, c, &mem_pos);
		counter ++;
	}
	substrings[counter] = NULL;
	return (substrings);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*return_s;
	size_t	counter;

	if (!*s || (ft_strlen(s) < start))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		return_s = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		return_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!return_s)
		return (0);
	if ((ft_strlen(s) < start) || (len == 0))
	{
		return_s[0] = '\0';
		return (return_s);
	}
	counter = 0;
	while (counter < len && counter < ft_strlen(s) - start)
	{
		return_s[counter] = s[start + counter];
		counter++;
	}
	return_s[counter] = '\0';
	return (return_s);
}
