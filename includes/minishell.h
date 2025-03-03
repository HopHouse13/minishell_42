/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/03 15:32:22 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "./printf/includes/ft_printf.h"
# include <errno.h>             // liste des erreurs errno.
# include <readline/history.h>  // gere l'historique des commandes (non vide)
# include <readline/readline.h> // declare la fonction readline.
# include <stdbool.h>           // boolien
# include <stdio.h>             // printf (pour la phase de dev.)
# include <stdlib.h>            // exit ;
# include <sys/errno.h>         // meilleur portabilite avec cette librairie.

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
	PIPE,        // "|"
	REDIR_IN,    // "<"
	REDIR_OUT_Q, // ">"
	HD,          // "<<"
	END_HD,      // EOF
	APPEND,      // ">>"
	DOLLAR,      // "$"
	S_QUOTE,     // "'"
	D_QUOTE,     // """
	END,         // fin de input
	UNKNOWN      // inconnu
}					t_type;

typedef struct s_parser
{
	int				i;
}					t_parser;

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
	char			**cmd;
	//liste chainee	**redir;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem; 

typedef struct s_lexer
{
	char			line[SIZE_LINE];
	int				i;
	int				j;
	int				squote;
	int				dquote;
	int				flag_quote;
}					t_lexer;

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
int		main(int ac, char **av, char **env);

/// lexer ///
void	ft_lexer(t_mshell *mshell, char *input);

/// lexer_init ///
void	ft_init_lexer(t_lexer *lexer);

///

/// lexer_operateurs_valid ///
bool	ft_validate_operators(t_lexer *lexer, char *input);
bool	ft_control_quotes_valid(t_lexer *lexer, char *input);
bool	ft_control_carac_valid(t_lexer *lexer, char *input);
bool	ft_control_pipe_valid(t_lexer *lexer, char *input);
bool	ft_control_redir_valid(t_lexer *lexer, char *input);

/// lexer_cleaning_input ///
void	ft_cleaning_input(t_lexer *lexer, char *input);
void	ft_put_pipe(t_lexer *lexer, char *input);
void	ft_put_redirection(t_lexer *lexer, char *input);

/// lexer_operateurs_utilities ///
void	ft_check_quotes(t_lexer *lexer, char c);
void	ft_init_line(char *virgin_line);
void	ft_handle_space(t_lexer *lexer, char *input);
bool	ft_valid_carac(char c);

/// parser-utils ///
void	ft_init_line(char *virgin_line);
void	ft_handle_space(t_lexer *lexer, char *input);
bool	ft_valid_carac(char c);

/// parser ///
void	ft_parser(t_mshell mshell, char *input);

/// parser-utils ///
void	ft_init_parser(t_parser *parser);
void	ft_build_list_tokens(t_mshell *mshell, t_parser *lexer, char *input);
bool	ft_isspace(char c);
bool	ft_ischevron(char c);
bool	ft_isnotchevron(char c);
bool	ft_ispipe(char c);

/// utilities ///
void	ft_error_exit(char *message);
void	ft_free_manag(t_mshell *mshell);
void	ft_init_mshell(t_mshell *mshell, char **env);
void	ft_build_env(t_mshell *mshell, char **env);
void	ft_build_path(t_mshell *mshell);
void	ft_print_double_tab(char **tab);

#endif