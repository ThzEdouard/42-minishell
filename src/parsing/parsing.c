/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/08 14:32:06 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_sep(char line)
{
	if (line == '|' || line == '<' || line == '>' )
		return (SUCCESS);
	return (FAIL);
}

char	*ft_join_realloc(char *s, int i, int len, char *s2)
{
	char	*value;
	char	*name;

	value = malloc(sizeof(char *) * (i + ft_strlen(s2) - (i - len + 1) + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, s, len);
	value[len] = 0;
	s += len;
	while (s && *s != 36)
		s++;
	if (*s == 36)
		s++;
	while (s2 && *s2 != '=' && *s2 == *s)
	{
		s2++;
		s++;
	}
	name = ft_strdup(s2 + 1);
	if (name)
	{
		value = ft_free_strjoin(value, name);
		free(name);
	}
	value = ft_free_strjoin(value, s);
	return (value);
}
int	ft_sep_ex(char line)
{
	if (line != 36 && line != 34 && line != 39)
		return(SUCCESS);
	return (FAIL);
}
void	expand(t_token *t, t_env *env)
{
	t_env	*tmp_env;
	t_token	*tmp_token;
	int		i;
	int		y;
	char	*tmp_line_env;
	char	*tmp_str;

	tmp_token = t;
	tmp_env = env;
	i = 0;
	while (tmp_token)
	{
		if (tmp_token->type == WORD)
		{
			while (tmp_token->str[i] && !ft_sep_ex(tmp_token->str[i]))
				i++;
			if (tmp_token->str[i] && tmp_token->str[i] == 39)
			{
				if (tmp_token->str[i] && tmp_token->str[i] == 39)
					i++;
				while (tmp_token->str[i] && tmp_token->str[i] != 39)
					i++;
				if (tmp_token->str[i] && tmp_token->str[i] == 39)
					i++;
			}
			else if (tmp_token->str[i] && tmp_token->str[i] == 34)
			{
				if (tmp_token->str[i] && tmp_token->str[i] == 34)
					i++;
				while (tmp_token->str[i] && tmp_token->str[i] != 36 && tmp_token->str[i] != 34)
					i++;
				if (tmp_token->str[i] && tmp_token->str[i + 1] && tmp_token->str[i - 1] &&  tmp_token->str[i] == 36 && tmp_token->str[i + 1] == '"' && tmp_token->str[i - 1] == '"')
					i++;
				if (tmp_token->str[i] && tmp_token->str[i] == 34)
					i++;
			}
			if (tmp_token->str[i] && tmp_token->str[i] == 36)
			{
				if (tmp_token->str[i + 1] && !ft_isalpha(tmp_token->str[i + 1]) && tmp_token->str[i + 1] == '$' && (tmp_token->str[i + 1] != '_' || tmp_token->str[i + 1] != '?'))
				{
					y = i;
					i++;
					if (tmp_token->str[i] && (!ft_isalpha(tmp_token->str[i]) || tmp_token->str[i] != '$' || tmp_token->str[i] != '"' || tmp_token->str[i] != '\''))
						i++;
					while (tmp_token->str[i])
					{
						tmp_token->str[y] = tmp_token->str[i];
						i++;
						y++;
					}
					tmp_token->str[y] = 0;
					i = 0;
				}
				else if (tmp_token->str[i + 1])
				{
					y = i;
					i++;
					if (tmp_token->str[i] != '?')
						while (tmp_token->str[i] && (ft_isalpha(tmp_token->str[i]) || ft_isalnum(tmp_token->str[i]) || tmp_token->str[i] == '_'))
							i++;
					else
						i++;
					tmp_line_env = get_name(tmp_env, tmp_token->str + (y + 1), i - (y + 1));
					if (!tmp_line_env)
					{
							while (tmp_token->str[i])
						{
							tmp_token->str[y] = tmp_token->str[i];
							i++;
							y++;
						}
						tmp_token->str[y] = 0;
					}
					else
					{
						tmp_str = ft_join_realloc(tmp_token->str, (y - i), y, tmp_line_env);
						if (!ft_strncmp(tmp_line_env, "?=", 2))
							free(tmp_line_env);
						free(tmp_token->str);
						tmp_token->str = tmp_str;
					}
					i = 0;
				}
			}
		}
		if (!tmp_token->str[i] || !tmp_token->str[i + 1])
        {
			tmp_token = tmp_token->next;
			i = 0;
		}

	}
}

void	extand(t_token *t)
{
	t_token	*tmp;
	int		i;
    int     x;
	int		y;
	char	c;

	tmp = t;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			c = 0;
			while (tmp->str[i] && (tmp->str[i] != 34 && tmp->str[i] != 39))
				i++;
			if (tmp->str[i] && (tmp->str[i] == 34 || tmp->str[i] == 39))
			{
				c = tmp->str[i];
				y = i;
				if (tmp->str[i] && tmp->str[i] == c)
					i++;
				while (tmp->str[i] && tmp->str[i] != c)
				{
					tmp->str[y] = tmp->str[i];
					y++;
					i++;
				}
                if (tmp->str[i] && tmp->str[i] == c)
                    i++;
                x = i;
                while (tmp->str[x])
                {
                    tmp->str[y] = tmp->str[x];
                    y++;
                    x++;
                }
                tmp->str[y] = tmp->str[x];
                i -= 2;
			}
		}
		tmp = tmp->next;
	}
}

void	add_token(t_token *t)
{
	if (!ft_strncmp(t->str, "|", 1))
		t->type = PIPE;
	else if (!ft_strcmp(t->str, ">"))
		t->type = WRITE;
	else if (!ft_strcmp(t->str, "<"))
		t->type = READ;
	else if (!ft_strncmp(t->str, ">>", 2))
		t->type = APPEND;
	else if (!ft_strncmp(t->str, "<<", 2))
		t->type = HEREDOC;
	else if (!ft_strncmp(t->str, "&", 1))
		t->type = COUNT;
	else
		t->type = WORD;
	t = t->next;
	if (t)
		add_token(t);
}

t_list_token	parsin(char *line)
{
	t_list_token	tmp;
	int				i;
	char			c;

	token_init(&tmp);
	while (*line)
	{
		while (*line && *line == 32)
			line ++;
		c = 0;
		i = 0;
		while (line[i] && line[i] != 32 && ft_sep(line[i]))
		{
			if (line[i] == 34 || line[i] == 39)
			{
				c = line[i];
				i++;
				while (line[i] && line[i] != c)
					i++;
				c = 0;
			}
			if (line[i] && line[i] != 32)
				i++;
		}
		if (!i)
			while (line[i] && !ft_sep(line[i]))
				i++;
		if (i && add_list(&tmp, line, i))
			return (token_clear(&tmp), tmp);
		line += i;
	}
	return (tmp);
}

int	parsing(char *line, t_list_token *t, t_env *env)
{
	t_list_token	l;

	token_init(&l);
	l = parsin(line);
	add_token(l.first);
	expand(l.first, env);
	extand(l.first);
	View(l);
	t->first = l.first;
	return (SUCCESS);
}
