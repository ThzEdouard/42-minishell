/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:38:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 21:35:00 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_free_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strncpy(char *s1, char *s2, unsigned int n);
char	*ft_strcat(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_free_substr(char *s, unsigned int start, size_t len);

#endif