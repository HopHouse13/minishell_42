/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/12 18:33:12 by ubuntu           ###   ########.fr       */
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

typedef struct s_HD
{
	char			*delim;
	bool			expand;
}					t_HD;

typedef struct s_parser
{
	int				i;
	t_token			*list_token;
	t_cmd			*list_cmd;
}					t_parser;

/* typedef struct s_exec
{

}					t_exec; */

typedef struct s_mnode  		// noeud par malloc
{
	void			*ptr;
	size_t			size;
	struct s_mnode	*next;
}					t_mnode;

/* typedef struct s_ml				// head de la liste de malloc (init dans le main)
{
	void			*head_ml;
}					t_ml; */

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
void		ft_loop_mshell(t_mshell *mshell, t_mnode **ml);

/// lexer ///
t_token		*ft_lexer(char *input, t_mnode **ml);

/// lexer_init ///
void		ft_init_lexer(t_lexer *lexer);

/// lexer_build_list_token ///
void		ft_define_token(t_lexer *lexer);
void		ft_build_list_token(t_lexer *lexer, t_mnode **ml);
void		ft_add_node_token(t_lexer *lexer, char *elem, t_mnode **ml);
void		ft_init_head_list_token(t_token **list, char *elem, t_mnode **ml);

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
t_cmd		*ft_parser(t_token *list_token, t_mnode **ml);
void		ft_init_list_cmd(t_parser *parser, t_mnode **ml);
void		ft_add_node_cmd(t_parser *parser, t_mnode **ml);
void		ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml);

/// parser_utils ///
void		ft_init_parser(t_parser *parser, t_token *token);

/// malloc ///
void		*ft_malloc_list(size_t size, t_mnode **ml);
void		*ft_calloc_list(size_t nb, size_t size_type, t_mnode **ml);
void 		ft_add_ml(void *ptr, size_t size, t_mnode **ml);
void		ft_init_head_list_ml(void *ptr, size_t size, t_mnode **ml);
char		**ft_split_ml(char const *s, char c, t_mnode **ml);
char		*ft_strdup_ml(const char *s_src, t_mnode **ml);
char		*ft_substr_ml(char const *s_src, int start, int len, t_mnode **ml);
void		ft_free_one_node_ml(void *ptr, t_mnode **ml);
void		ft_free_ml(t_mnode **ml);

/// utilities ///
void		ft_error_exit(char *message);
void		ft_init_mshell(t_mshell *mshell, char **env, t_mnode **ml);
void		ft_build_env(t_mshell *mshell, char **env,  t_mnode **ml);
void		ft_build_path(t_mshell *mshell,  t_mnode **ml);

/// utilities_print ///
void		ft_print_input_clean(char *line);
void		ft_print_double_tab(char **tab);
void		ft_print_list_token(t_token *head);
const char	*ft_get_name_type(t_type type);
void		ft_print_list_cmd(t_cmd *head);


	// * EXEC * //

//redirect.c

void	redirect(t_mshell instructions);
void	redirect_case(void fd, void tokken);
void	redirect_in(void fd, char *infile);
void	redirect_out_trunc(char *outfile);
void	redirect_out_app(char *outfile);
void	redirect_hd(src, dest);

// execution_cmd.c
void	ft_executer(t_mshell instructions);
void	execution_cmd(char *cmd, char **cmd_args);




	// * Built - In * //
void	BI_echo(char *env_var);

#endif	