/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosoph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:37:03 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/22 17:24:48 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void ft_philo_eat(t_ptr *filo)
{
    int status;

    filo->left_fork = filo->philo_id;
    filo->right_fork = filo->philo_id - 1;
    if(filo->right_fork < 0)
        filo->right_fork = filo->all->number_of_philosophers - 1;
    status = filo->philo_id % 2; // 0 - четный 1 - нечетный
    if(status == 1)
    {
        ft_write_text(" думает\n", filo);
        pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
        pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
        ft_write_text(" взял вилку\n", filo);
        ft_write_text(" начал кушать\n", filo);
        ft_usleep(filo->all->time_to_eat);
        ft_write_text(" покушал\n", filo);
        pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
        pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
        ft_write_text(" лег спать\n", filo);
        ft_usleep(filo->all->time_to_sleep);
    }
    if(status != 1)
    {
        ft_write_text(" думает\n", filo);
        pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
        pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
        ft_write_text(" взял вилку\n", filo);
        ft_write_text(" начал кушать\n", filo);
        ft_usleep(filo->all->time_to_eat);
        ft_write_text(" покушал\n", filo);
        pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
        pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
        ft_write_text(" лег спать\n", filo);
        ft_usleep(filo->all->time_to_sleep);
    }
}

static void *life_style(void *ptr)
{
    t_ptr *filo = ptr;

    // printf("Hello world!\n");
    // printf("Количество философов: = %d\n", filo->all->number_of_philosophers);
    // printf("Время до еды: = %ld\n", filo->all->time_to_eat);
    //printf("id философа = %d\n", filo->philo_id);
    while(1)
        ft_philo_eat(filo);
    return(NULL);
}

static void ft_init_struct(t_ptr *ptr, t_data *all, t_table *table)
{
    ptr->all = all;
    ptr->table = table;
}

int ft_philosoph(t_data *all)
{
    int i;
    int status;
    int status_addr;
    t_ptr *ptr;
    t_table table;

    all->start_time = my_get_time();
    if(!(table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->number_of_philosophers)))
        return(1);
    if(!(ptr = (t_ptr *)malloc(sizeof(t_ptr) * all->number_of_philosophers)))
        return(1);
    i = 0;
    pthread_mutex_init(&table.text, NULL); // init вывода текста
    while(i != all->number_of_philosophers)
    {
        pthread_mutex_init(&table.forks[i], NULL);
        i++;
    }
    i = 0;
    while(i != all->number_of_philosophers)
    {
        ptr[i].philo_id = i;
        ft_init_struct(&ptr[i], all, &table);
        ptr[i].status = pthread_create(&ptr[i].thread, NULL, life_style, &ptr[i]);
        if (ptr[i].status != 0) 
            return(1);
        i++;
    }
    i = 0;
    while(i != all->number_of_philosophers)
    {
        ptr[i].status = pthread_join(ptr[i].thread, (void**)&ptr[i].status_join);
        if (ptr[i].status != 0) 
            return(1);
        i++;
    }
    return(0);
}