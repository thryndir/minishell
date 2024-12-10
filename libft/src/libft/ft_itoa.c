/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:37:30 by lgalloux          #+#    #+#             */
/*   Updated: 2023/11/11 18:20:31 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_nbr_is_negative(char *str, int nbr2, int len)
{
	str[0] = '-';
	nbr2 *= -1;
	while (len > 0)
	{
		str[len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		len--;
	}
	return (str);
}

char	*ft_nbr_is_positive(char *str, int nbr2, int len)
{
	while (len > -1)
	{
		str[len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		len--;
	}
	return (str);
}

int	ft_nbr_count(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len = 1;
	}
	else
		len = 0;
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nbr_count(nbr);
	str = malloc(len + 2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nbr < 0)
		str = ft_nbr_is_negative(str, nbr, len);
	else
		str = ft_nbr_is_positive(str, nbr, len);
	str[len + 1] = '\0';
	return (str);
}

/*int	main(void)
{
	int test = 458;
	printf("%s\n", ft_itoa(test));
	return (0);
}*/