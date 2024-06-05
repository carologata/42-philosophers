/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:04:26 by cogata            #+#    #+#             */
/*   Updated: 2024/06/05 17:53:22 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t get_time_in_ms(void)
{
    struct timeval tv;
    size_t time;
    
    if(gettimeofday(&tv, NULL) == -1)
        error_exit("gettimeofday failed.");
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

size_t get_current_time(size_t start_time)
{
    size_t current_time;

    current_time = get_time_in_ms() - start_time;
    return (current_time);
}