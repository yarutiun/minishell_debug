/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:35:57 by fstaryk           #+#    #+#             */
/*   Updated: 2022/10/13 16:46:52 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_token_list *create_token(int length, char *start, int type)
{
	t_token_list *token;
	token = (t_token_list*)malloc(sizeof(t_token_list));
// ft_strtrim(start, "\"\'");
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->tok = start;
	token->type = type;
	return token;
}

void add_token(t_token_list **first, t_token_list * to_add)
{
	t_token_list *temp;

	if(!to_add)
	{
		perror("sho? ti sho tworish");	
		return;
	}
	if(!(*first))
	{
		*first = to_add;
		return;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}

t_token_list *token_delim_logic(t_token_list **global, int *len)
{
	t_token_list *temp;
	temp = *global;
	int i;

	i = 0;
	if((*global)->next == NULL)
		return NULL;
	while((*global)->type != LOGICAL_OR && (*global)->type != LOGICAL_AND)
	{
		// printf("%s\n",(*global)->tok);
		if ((*global)->next == NULL)
		{
			i++;
			*len = i;
			return temp;
		}
		i++;
		*global = (*global)->next;
	}
	*len = i;
	//printf("len is asigning to %d\n", i);
	if(!(*global)->next)
		{
			perror ("syntax error");
			return 0;
		}
	*global = (*global)->next;
	// printf("\n");
	return temp;
}

t_token_list *token_delim_pipe(t_token_list *global, int log_len, int *pipe_len)
{
	t_token_list *temp;
	temp = global;
	int i;
	//static int j;

	i = 0;
	if(global->next == NULL)
		return NULL;
	while(global->type != PIPE)
	{
		fprintf(stderr, "%s\n", global->tok);
		if (i == log_len)
		{
			*pipe_len = i;
			return temp;
		}
		i++;
		global = global->next;
	}
	*pipe_len = i;
	global = global->next;
	return temp;
}

void restore_tok_list(t_token_list **global)
{
	while ((*global)->prev)
		(*global) = (*global)->prev;
}
