/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_extentions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:54:10 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/25 17:53:04 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*sub_extend(char *var, int len)
{
	int		i;
	char	*ret;
	int		var_len;

	i = 0;
	var_len = 0;
	ret = NULL;
	while (var_len < len)
	{
		if (var[var_len] == '$')
			break ;
		var_len++;
	}
	while (g_env[i])
	{
		if (ft_strncmp(var, g_env[i], var_len) == 0)
		{
			return (ft_strdup(&g_env[i][var_len + 1]));
		}
		i++;
	}
	return (ft_strndup(var - 1, var_len + 1));
}

char	*extend(char *var, int len, int last_ret)
{
	char	*ext;
	char	*ret;
	char	*to_free;
	int		i;

	i = 0;
	ret = NULL;
	while (i < len)
	{
		if (var[i] == '$')
		{
			if (len <= 1)
				return (ft_strdup("$"));
			if (var[i + 1] == '?')
				ext = ft_itoa(last_ret);
			else
				ext = sub_extend(&var[i + 1], len - i - 1);
			to_free = ret;
			ret = ft_strnnjoin(ret, ft_strlen(ret), ext, ft_strlen(ext));
			free(to_free);
			free(ext);
		}
		i++;
	}
	return (ret);
}

void	sub_open_extentions(t_token_list *temp, int i, int last_ret)
{
	char			*to_free;
	char			*ext;

	to_free = temp->tok;
	ext = extend(&temp->tok[i], temp->len - i, last_ret);
	temp->tok = ft_strnnjoin(temp->tok, i, ext, ft_strlen(ext));
	if (temp->type == EXTENDED)
		free(to_free);
	temp->len = ft_strlen(temp->tok);
	if (temp->type == TEXT)
		temp->type = EXTENDED;
	if (ext)
		free(ext);
}

void	open_extentions(t_token_list **tok_list, int tok_len, int last_ret)
{
	t_token_list	*temp;
	int				i;
	int				count;

	count = 0;
	temp = *tok_list;
	while (temp && count < tok_len)
	{
		i = 0;
		while (i < temp->len && (temp->type == TEXT || \
		temp->type == DUP_QUOTES || temp->type == EXTENDED))
		{
			if (temp->tok[i] == '$')
				sub_open_extentions(temp, i, last_ret);
			i++;
		}
		count++;
		temp = temp->next;
	}
}