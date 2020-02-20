/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:28:15 by jbennink       #+#    #+#                */
/*   Updated: 2019/11/01 09:34:04 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*srcstr;
	char	*dststr;

	if (dst == NULL && src == NULL)
		return (dst);
	srcstr = (char*)src;
	dststr = (char*)dst;
	i = 0;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		i++;
	}
	return (dst);
}
