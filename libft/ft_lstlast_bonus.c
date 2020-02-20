/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:27:02 by jbennink       #+#    #+#                */
/*   Updated: 2019/11/01 17:03:12 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (lst);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
