/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auskola- <auskola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:26:58 by auskola-          #+#    #+#             */
/*   Updated: 2024/02/02 13:45:37 by auskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while (n > counter && (s1[counter] != '\0'))
	{
		if (s1[counter] != s2[counter])
		{
			return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
		}
		counter++;
	}
	if (s2[counter] == '\0' || counter == n)
		return (0);
	else
		return (-1);
}

char	*ft_strdup_trim(const char *str)
{
	char	*pointer;
	size_t	counter;
	size_t	len;

	counter = 0;
	len = ft_strlen(str) - 2;
	(pointer = (char *)malloc(sizeof(char) * (len + 1)));
	if (pointer == NULL)
		return (NULL);
	while (counter < len)
	{
		pointer[counter] = str[counter + 1];
		counter++;
	}
	pointer[counter] = '\0';
	return (pointer);
}

/* 	if (!(new = malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
 */		
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	if (!s)
		return (0);
	counter = 0;
	while (s[counter] != '\0')
		counter++;
	return (counter);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}
