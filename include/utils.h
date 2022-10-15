/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:38:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/13 20:51:43 by eflaquet         ###   ########.fr       */
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
char	**ft_split(char *s1, char c);
char	*ft_strncpy(char *s1, char *s2, unsigned int n);
char	*ft_strcat(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif