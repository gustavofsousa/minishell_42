/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:54:17 by parnaldo          #+#    #+#             */
/*   Updated: 2023/01/30 23:02:33 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int flag_echo(char c)
{
    if (c == 'n')
        return (1);
    return (0);
}

void    ft_echo(char *str)
{
    int n_option;

    n_option = 0;
    if (*str == '-' && *(str+1) == 'n')
    {
        *str++;
        if(flag_echo(*str))
            *str++;
        n_option = 1;
    }
    printf("%s", str);
    if (n_option)
        printf("\n");
}