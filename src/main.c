/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:37 by fstaryk           #+#    #+#             */
/*   Updated: 2022/11/06 17:30:38 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *comnd_table;
	t_token_list *tokens;
	t_data *data;
	(void)envp;
    (void)argc;
	(void)argv;
	
	while (true)
	{
		comnd_table = read_input();
        tokens = lexer(comnd_table);
		if(!tokens)
			continue;
		// print_token(tokens);
		data = parse(&tokens, envp);
		//theExecutor();

		// free_data(data);
		// free();
		// free(data);
	}
	exit(1);
}
