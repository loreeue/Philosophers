/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:15:24 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/06 18:15:26 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Returns the current time in different units.

Use gettimeofday() to get the current time.

	- If time == SECOND, returns the current seconds (tv.tv_sec).
	- If time == MILISECOND, converts seconds to milliseconds and sums the
		microseconds converted to milliseconds.
	- If time == MICROSECOND, converts seconds to microseconds and sums the
		microseconds.
*/
long	get_time(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time == MILISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (0);
}

static bool	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_onlydigits(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

/*
Validates that the input string is a valid positive number and does not exceed
INT_MAX.

Ignores leading spaces.
Allows a + sign at the beginning, but not - (returns NULL if a negative number
is found).
Checks that the first character after the spaces and the sign is a digit.
If the length exceeds 10 characters (possible INT_MAX exceeded) also returns
NULL.

If everything is valid, returns the pointer to the position where the number
begins
in the string.
*/
static const char	*valid_input(const char *str)
{
	int	len;

	len = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (printf("Negative numbers are not accepted"), NULL);
	if (ft_onlydigits(str) == 1)
		return (printf("Invalid input: not a number"), NULL);
	while (str[len])
		len++;
	if (len > 10)
		return (printf("The value surpasses INT_MAX"), NULL);
	return (str);
}

/*
Converts a string to an integer (long).

First, validates the input by making sure it is a valid positive number.

Then, converts the string to a long.

Checks that it does not exceed INT_MAX.

Returns the converted number if it is valid.
*/
long	ft_atol(const char *s)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	s = valid_input(s);
	if (s == NULL)
		return (-2);
	while (s[i] >= 48 && s[i] <= 57)
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return (-2);
	return (res);
}
