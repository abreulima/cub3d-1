/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:42:29 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/16 20:04:17 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_nbrlen(int n, int *neg)
{
	int	i;

	i = 0;
	*neg = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		*neg *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i <= ((len - 1) / 2))
	{
		tmp = str[len - i];
		str[len - i] = str[i];
		str[i] = tmp;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	i = 0;
	str = malloc(sizeof(char) * (ft_nbrlen(n, &neg) + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = ((n % 10) * neg) + '0';
		n /= 10;
	}
	if (neg == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
