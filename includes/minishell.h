/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/02/19 18:44:15 by pbret            ###   ########.fr       */
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

# define SIZE_LINE 80000
# define IN_Q 1
# define OUT_Q 0

typedef enum e_type
{
					WORD,
					PIPE, 		// "|"
					REDIR_IN,	// "<"
					REDIR_OUT_Q,	// ">"
					HD,			// "<<"
					END_HD,		// EOF
					APPEND,		// ">>"
					DOLLAR,		// "$"
					S_QUOTE,	// "'"
					D_QUOTE,	// """
					END,		// fin de input
					UNKNOWN		// inconnu
}					t_type;

typedef struct s_lexer
{
	int 			i;
	bool			intoken;
}					t_lexer;

typedef struct s_token
{
	char			*elem;
	t_type			token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_elem
{
	t_cmd			*cmd;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef struct s_parser
{
	char			line[SIZE_LINE];
	int				i;
	int				j;
	int				squote;
	int				dquote;
}					t_parser;

/* typedef struct s_exec
{

}					t_exec; */

typedef struct s_mshell
{
	char			*input;
	t_cmd			*cmds_list;
	char			**env;
	char			**paths;
	int				exit_status;
}					t_mshell;

/// main ///
int main(int ac, char **av, char **env);

/// parser ///
void	ft_parser(t_mshell *mshell, char *input);
bool	ft_check_quotes_input(t_parser *parser, char *input);
void	ft_check_quotes(t_parser *parser,char c);
void	ft_put_spaces(t_parser *parser, char *input);
void	ft_put_pipe(t_parser *parser, char *input);
void	ft_put_redirection(t_parser *parser, char *input);

/// parser-utils ///
void	ft_init_line(char *virgin_line);

/// lexer ///
void	ft_lexer(t_mshell mshell, char *input);

/// lexer-utils ///
void	ft_init_lexer(t_lexer *lexer);
void	ft_build_list_tokens(t_mshell *mshell, t_lexer *lexer, char *input);
bool	ft_isspace(char c);
bool	ft_ischevron(char c);
bool	ft_isnotchevron(char c);
bool	ft_ispipe(char c);

/// utils-error ///
void	ft_error_exit(char *message);

/// utils-free ///
void	ft_free_manag(t_mshell *mshell);

/// utils-init ///
void	ft_init_mshell(t_mshell *mshell, char **env);
void	ft_build_env(t_mshell *mshell, char  **env);
void	ft_build_path(t_mshell *mshell);

/// utils-print ///
void	ft_print_double_tab(char **tab);
#endif