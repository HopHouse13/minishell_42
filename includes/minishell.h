/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/06 17:46:15 by pbret            ###   ########.fr       */
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

# define RESET "\033[0m"		// a supprimer si non besoin
# define BLACK "\033[30m"		// a supprimer si non besoin
# define RED "\033[31m"			// a supprimer si non besoin
# define GREEN "\033[32m"		// a supprimer si non besoin
# define YELLOW "\033[33m"		// a supprimer si non besoin
# define BLUE "\033[34m"		// a supprimer si non besoin
# define MAGENTA "\033[35m"		// a supprimer si non besoin
# define CYAN "\033[36m"		// a supprimer si non besoin
# define WHITE "\033[37m"		// a supprimer si non besoin

# define SIZE_LINE 80000
# define IN_Q 1
# define OUT_Q 0

typedef enum e_type
{
	ELEM,
	PIPE,       // "|"
	REDIR_IN,   // "<"
	REDIR_OUT,	// ">"
	HD,         // "<<"
	END_HD,     // EOF
	APPEND,     // ">>"
	DOLLAR,     // "$"
	END,        // fin de input
	UNKNOWN     // inconnu
}					t_type;
typedef struct s_token
{
	char			*elem;
	t_type			token;			
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;
typedef struct s_lexer
{
	char			line[SIZE_LINE];
	t_token			*list_token;
	int				i;
	int				j;
	int				squote;
	int				dquote;
	int				flag_quote;
}					t_lexer;
typedef struct s_cmd
{
	char			**cmd;
	//liste chainee	**redir;
	bool			squote;
	bool			dquote;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_parser
{
	int				i;
	t_token			*list_token;
}					t_parser;


/* typedef struct s_exec
{

}					t_exec; */

typedef struct s_mshell
{
	char			*input;
	t_token			*list_token;
	t_cmd			*list_cmd;
	char			**env;
	char			**paths;
	int				exit_status;
}					t_mshell;

/// main ///
int			main(int ac, char **av, char **env);

/// lexer ///
t_token		*ft_lexer(char *input);

/// lexer_init ///
void		ft_init_lexer(t_lexer *lexer);

/// lexer_build_list_token ///
void		ft_define_token(t_lexer *lexer);
void		ft_build_list_token(t_lexer *lexer);
void		ft_add_node_token(t_lexer *lexer, char *elem);
void		ft_init_list_head(t_token **list, char *elem);

/// lexer_operateurs_valid ///
bool		ft_validate_operators(t_lexer *lexer, char *input);
bool		ft_control_quotes_valid(t_lexer *lexer, char *input);
bool		ft_control_carac_valid(t_lexer *lexer, char *input);
bool		ft_control_pipe_valid(t_lexer *lexer, char *input);
bool		ft_control_redir_valid(t_lexer *lexer, char *input);

/// lexer_cleaning_input ///
void		ft_input_one_space(t_lexer *lexer, char *input);
void		ft_put_pipe(t_lexer *lexer, char *input);
void		ft_put_redirection(t_lexer *lexer, char *input);

/// lexer_operateurs_utilities ///
void		ft_check_quotes(t_lexer *lexer, char c);
void		ft_init_line(char *virgin_line);
void		ft_handle_space(t_lexer *lexer, char *input);
bool		ft_valid_carac(char c);

/// parser_utils ///
void		ft_init_line(char *virgin_line);
void		ft_handle_space(t_lexer *lexer, char *input);
bool		ft_valid_carac(char c);

/// parser ///
t_cmd		*ft_parser(t_token *token);

/// parser_utils ///
void		ft_init_parser(t_parser *parser, t_token *token);
bool		ft_isspace(char c);
bool		ft_ischevron(char c);
bool		ft_isnotchevron(char c);
bool		ft_ispipe(char c);

/// utilities ///
void		ft_error_exit(char *message);
void		ft_init_mshell(t_mshell *mshell, char **env);
void		ft_build_env(t_mshell *mshell, char **env);
void		ft_build_path(t_mshell *mshell);

/// utilities_free ///
void		ft_free_manag(t_mshell *mshell);
void		ft_free_list_token(t_token *lexer);

/// utilities_print ///
void		ft_print_double_tab(char **tab);
void		ft_print_list_token(t_token *head);
const char	*ft_get_name_type(t_type type);

#endif	