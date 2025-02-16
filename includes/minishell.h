/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/02/16 16:32:09 by pbret            ###   ########.fr       */
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
# include <stdbool.h> // boolien

# define RESET "\033[0m" // a supprimer si non besoin
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef enum e_type
{
					WORD,
					PIPE, 		// "|"
					REDIR_IN,	// "<"
					REDIR_OUT,	// ">"
					HD,			// "<<"
					SIN_HD,		// EOF
					APPEND,		// ">>"
					DOLLAR,		// "$"
					S_QUOTE,	// "'"
					D_QUOTE,	// """
					END,		// fin de imput
					UNKNOWN		// inconnu
}					t_type;

typedef struct s_cmds_list
{
	char				**cmds;
	char				*path;
	t_type				token;
	struct s_cmds_list	*prev;
	struct s_cmds_list	*next;
}						t_cmds_list;

typedef struct s_lexer
{
	int 				i;
}						t_lexer;

/* typedef struct s_parser
{

}					t_parser;

typedef struct s_exec
{

}					t_exec; */

typedef struct s_mshell
{
	char				*input;
	t_cmds_list			*cmds_list;
	char				**env;
	char				**paths;
}						t_mshell;

/// main ///
int main(int ac, char **av, char **env);

/// lexer ///
void	ft_lexer(t_mshell mshell, char *input);

/// lexer- ///
void	ft_init_lexer(t_lexer *lexer);
bool	ft_isspace(char c);
bool	ft_isredirection(char c);

/// utils-error ///
void	ft_error_exit(char *message);

/// utils-free ///
void	ft_free_manag(t_mshell *mshell);

/// utils-init ///
void	ft_init_mshell(t_mshell *mshell, char **env);
void	ft_build_env(t_mshell *mshell, char  **env);
void	ft_build_paths(t_mshell *mshell);

#endif