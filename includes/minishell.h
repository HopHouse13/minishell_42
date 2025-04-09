/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/09 18:14:42 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "./printf/includes/ft_printf.h"
# include <unistd.h>			// get
# include <errno.h>             // liste des erreurs errno.
# include <readline/history.h>  // gere l'historique des commandes (non vide)
# include <readline/readline.h> // declare la fonction readline.
# include <stdbool.h>           // boolien
# include <stdio.h>             // printf (pour la phase de dev.); dprintf
# include <stdlib.h>            // exit ; getenv ;
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
# define IN 1
# define OUT 0

typedef enum e_type
{
	ELEM,
	PIPE,       // "|"
	R_IN,   	// "<"
	R_OUT,		// ">"
	HD,         // "<<"
	APPEND,     // ">>"
	F_IN,		// fichier d'entree
	F_OUT,		// ecrasement dans fichier
	F_APP,		// rajout dans fichier
	DELIM,	// delimiteur heredoc
	CMD,		// commande
	BI,			// builtin
	ARG,		// argument de la precedente commande
	END,		// fin de input
}					t_type;

typedef struct s_token
{
	char			*elem;
	t_type			token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer // local
{
	char			line[SIZE_LINE];
	t_token			*list_token;
	int				i;
	int				j;
	bool			simple_q;
	bool			double_q;
	bool			flag_q;
	bool			mark_q;
	bool			APP_HD; // uniquement pour ft_control_redir_valid
}					t_lexer;

typedef struct s_hd
{
	char			*delim; // pab
	char			**buff_doc; // emir
	bool			expand; // pab
}					t_hd;

typedef struct s_redir
{
	t_type			token; // pab
	char			*file; // pab
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd; //ELEM
	t_redir			*redir;
	t_hd			*hd;
	int				count_hd; // 0 -> pas de hd, autre hd | Pab
	bool			simple_q; //ELEM
	bool			double_q; //ELEM
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_parser // local
{
	int				i;
	t_token			*list_token;
	t_cmd			*list_cmd;
	char			**env;
	bool			simple_q;
	bool			double_q;
	bool			flag_q;
	bool			mark_q;
	int				start;
	int				end;
	bool			mark_b;
	int				exit_status;
}					t_parser;

typedef struct s_exec // local
{
	int				i;
//	int				exit_status;
}					t_exec;

typedef struct s_mnode  		// noeud par la liste de malloc
{
	void			*ptr;
	size_t			size;
	struct s_mnode	*next;
}					t_mnode;

typedef struct s_mshell
{
	char			*input;
	t_token			*list_token;
	t_cmd			*list_cmd;
	int				count_pipe; // pab
	char			**env;
	char			**paths;
	int				exit_status;
}					t_mshell;

/// main ///
int			main(int ac, char **av, char **env);
void		ft_loop_mshell(t_mshell *mshell, t_mnode **ml);

////////////////////////////////////////////////////////////////////////////////

/// lexer ///
t_token		*ft_lexer(char *input, t_mnode **ml);

/// lexer_initialisation ///
void		ft_init_lexer(t_lexer *lexer);

/// lexer_build_list_token ///
void		ft_define_token_redir(t_lexer *lexer);
void		ft_build_list_token(t_lexer *lexer, t_mnode **ml);
void		ft_add_node(t_lexer *lexer, char *elem, t_mnode **ml);
void		ft_init_head_list_token(t_token **list, char *elem, t_mnode **ml);

/// lexer_operateurs_valid ///
bool		ft_validate_operators(t_lexer *lexer, char *input);
bool		ft_control_quotes_valid(t_lexer *lexer, char *input);
bool		ft_control_character_valid(t_lexer *lexer, char *input);
bool		ft_control_pipe_valid(t_lexer *lexer, char *input);
bool		ft_control_redir_valid(t_lexer *lexer, char *input);

/// lexer_cleaning_input ///
void		ft_handle_space(t_lexer *lexer, char *input);
void		ft_input_one_space(t_lexer *lexer, char *input);
void		ft_put_pipe(t_lexer *lexer, char *input);
void		ft_put_redirection(t_lexer *lexer, char *input);

/// lexer_handle_quotes ///
bool		ft_inside_quotes_lexer(t_lexer *lexer, char *str, int i);
void		ft_status_update_lexer(bool *quote, bool *mark, bool *flag);

/// lexer_utilities ///
bool		ft_effect_escape_lexer(t_lexer *lexer, char *str, int i);
void		ft_init_line(char *virgin_line);
bool		ft_valid_character(char c);
t_type		ft_builtin_or_cmd(char *elem);

////////////////////////////////////////////////////////////////////////////////

/// parser ///
t_cmd		*ft_parser(t_mshell *mshell, t_token *list_token, t_mnode **ml);

/// parser_initilisation ///
void		ft_init_parser(t_mshell *mshell, t_parser *parser, t_token *list_token);

/// parser_valid_syntax ///
bool		ft_valid_pipes(t_parser *parser);
bool		ft_valid_cmds(t_parser *parser);
bool		ft_valid_redirs(t_parser *parser, t_mnode **ml);
bool		ft_valid_syntax(t_parser *parser, t_mnode **ml);


/// parser_initialisation_list_cmd ///
void		ft_init_list_cmd(t_parser *parser, t_mnode **ml);
void		ft_add_node_cmd(t_parser *parser, t_mnode **ml);
void		ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml);
void		ft_init_node_values(t_cmd *new_elem);

/// parser_expand_and_ckeanup ///
void		ft_expand_list_and_cleanup(t_parser *parser, t_mnode **ml);
void		ft_delete_quotes(t_parser *parser, t_mnode **ml);
void		ft_clear_escape_character(t_parser *parser, t_mnode **ml);

/// parser_expand ///
void		ft_expand_list(t_parser *parser, t_mnode **ml);
char		*ft_expand(char *elem, int i, t_parser *parser, t_mnode **ml);
char		*ft_merge(char *str, char *exp, int i, t_parser *parser, t_mnode **ml);

/// parser_fill_list_cmd ///
void		ft_fill_list_cmd(t_parser *parser, t_mnode **ml);

/// parser_handle_quotes ///
void		ft_status_update_parser(bool *quote, bool *mark, bool *flag);
bool		ft_inside_quotes_parser(t_parser *parser, char *str, int i);

/// parser_utilities ///
bool		ft_cmds(char *cmd);
char		*ft_find_next_cmd(t_parser *parser, t_token *tmp, t_mnode **ml);
char		*ft_remove_quotes(t_parser *parser, char *str, t_mnode **ml);
bool		ft_effect_escape_parser(t_parser *parser, char *str, int i);

////////////////////////////////////////////////////////////////////////////////

/// malloc ///
void		*ft_malloc_list(size_t size, t_mnode **ml);
void		*ft_calloc_list(size_t nb, size_t size_type, t_mnode **ml);
void 		ft_add_ml(void *ptr, size_t size, t_mnode **ml);
void		ft_init_head_list_ml(void *ptr, size_t size, t_mnode **ml);
char		**ft_split_ml(char const *s, char c, t_mnode **ml);
char		*ft_strdup_ml(const char *s_src, t_mnode **ml);
char		*ft_strjoin_ml(char const *s1, char const *s2, t_mnode **ml);
char		*ft_substr_ml(char const *s_src, int start, int len, t_mnode **ml);
void		ft_free_one_node_ml(void *ptr, t_mnode **ml);
void		ft_free_ml(t_mnode **ml);

////////////////////////////////////////////////////////////////////////////////

/// utilities ///
void		ft_error_exit(char *message);
void		ft_init_mshell(t_mshell *mshell, char **env, t_mnode **ml);
void		ft_build_env(t_mshell *mshell, char **env,  t_mnode **ml);
void		ft_build_path(t_mshell *mshell,  t_mnode **ml);
void		ft_init_exec(t_exec *exec);

/// utilities_print ///
void		ft_print_input_clean(char *line);
void		ft_print_double_tab(char **tab);
void		ft_print_list_token(t_token *head);
const char	*ft_get_name_type(t_type type);
void		ft_print_list_cmd(t_cmd *head);

#endif	