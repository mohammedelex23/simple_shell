#include "shell.h"

/**
 * _atoi - converts string to integer
 * @s: string to convert
 * Description: copy of atoi
 * Return: converted integer
 */
double _atoi(char *s)
{
	int i = 0;
	double n = 0;

	if (s[i] == '+' && (!(s[i++])))
		return (-1);

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (-1);
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			n = 10 * n + s[i] - '0';
		}
		i++;
	}
	return (n);
}

/**
 * _itoa - converts integer to string
 * @n: integer to convert
 * @s: string
 * Description: version of itoa
 * Return: void
 */

char *_itoa(int n, char *s)
{
	int i = 0;
	int sign = n;

	/* absolute value */
	if (n < 0)
		n = -n;

	for (sign = 1; sign <= n; sign *= 10)
		;
	sign /= 10;
	/* loop through int and set to string */
	while (sign > 0)
	{
		s[i] = (n / sign + '0');
		n %= sign;
		i++;
		sign /= 10;
	}
	s[i] = '\0';
	return (s);
}
