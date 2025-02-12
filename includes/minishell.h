/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/02/12 20:16:42 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "./printf/includes/ft_printf.h"

# include <stdio.h> // printf (pour la phase de dev.)
# include <errno.h> // liste des erreurs errno.
# include <sys/errno.h> // meilleur portabilite avec cette librairie.
# include <readline/readline.h> // declare la fonction readline.
# include <readline/history.h> // gere l'historique des commandes (non vide)
# include <stdlib.h> // exit ;

# define RESET "\033[0m" // a supprimer si non besoin
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef struct s_token
{
	char			*cmds;
	char			tokens;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_parser
{

}					t_parser;

typedef struct s_lexer
{
	t_token			*tokens;
}					t_lexer;

typedef struct s_exec
{

}					t_exec;

typedef struct s_mshell
{
	char			*input;
	t_list			*cmds_list;
	char			**env;
	char			**path;
	t_token			*tokens;
	t_parser		parser;
	t_exec			exec;
}					t_mshell;

/// main ///
int main(int ac, char **av, char **env);

#endif