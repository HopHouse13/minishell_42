/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/05/21 16:53:50 by pbret            ###   ########.fr       */
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
# include <unistd.h>			// get
# include <sys/errno.h>         // meilleur portabilite avec cette librairie.
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>				// open;	
# include <signal.h>

#define BLINK "\033[5m"			// a supp
# define RESET "\033[0m"		// a supprimer si non besoin
# define BLACK "\033[30m"		// a supprimer si non besoin
# define RED "\033[31m"			// a supprimer si non besoin
# define GREEN "\033[32m"		// a supprimer si non besoin
# define YELLOW "\033[33m"		// a supprimer si non besoin
# define BLUE "\033[34m"		// a supprimer si non besoin
# define MAGENTA "\033[35m"		// a supprimer si non besoin
# define CYAN "\033[36m"		// a supprimer si non besoin
# define WHITE "\033[37m"		// a supprimer si non besoin

# define IN 1
# define OUT 0

extern int		g_exit_code; //variable glob.pour obtenir le dernier exit_code.
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
	DELIM,		// delimiteur heredoc
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

typedef struct s_lexer
{
	char			*wild_input;
	char			*clear_input;
	t_token			*list_token;
	int				i;
	int				j;
	bool			cmd_in_pipe;
}					t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	bool			builtin;
	int				fd_in;
	int				fd_out;
	int				fd_hd;
	char			*delim_hd;
	bool			expand_hd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef	struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_parser // local
{
	int				i;
	t_token			*list_token;
	t_cmd			*list_cmd;
	int				srt;
	int				end;
	bool			mark_b;
}					t_parser;

typedef struct s_qts
{
	bool			spl_q;	// État des guillemets simples
	bool			dbl_q;	// État des guillemets doubles
	bool			in_q;		// Mark pour savoir si on est à l'intérieur des quotes
	bool			delay_in;	// retarde le chagement d'etat d'entree
	bool			delay_out;	// retarde le chagement d'etat de sortie
}					t_qts;

typedef struct s_mnode
{
	void			*ptr;
	size_t			size;
	struct s_mnode	*next;
}					t_mnode;

typedef struct s_hd
{
	int				start;
	int				end;
}					t_hd;

typedef struct s_mshell
{	
	char			*input;
	t_qts			*qts;
	t_token			*list_token;
	t_cmd			*list_cmd;
	t_env			*env_list;
	t_mnode			*ml;	
	int				count_pipe;
}					t_mshell;

/// main ///
int		main(int ac, char **av, char **env);

////////////////////////////////////////////////////////////////////////////////

/// lexer ///
int		ft_lexer(t_mshell *mshell);

/// lexer_initialisation ///
void 	ft_init_lexer(t_mshell *mshell, t_lexer *lexer);

/// lexer_build_list_token ///
void	ft_define_token_elem(t_lexer *lexer);
void	ft_define_token_redir(t_lexer *lexer);
void	ft_init_head_list_token( t_mshell *mshell, t_token **list_t, char *elem);
void	ft_add_node(t_mshell *mshell, t_lexer *lexer, char *elem);
void	ft_build_list_token(t_mshell *mshell, t_lexer *lexer);

/// lexer_cleaning_input ///
int		ft_count_char(char *line);
void	ft_make_clear_input(t_mshell *mshell, t_lexer *lexer, char *wild_input);
void	ft_put_redirection(t_lexer *lexer, char *input);
void	ft_put_pipe(t_lexer *lexer);
void	ft_cleaning_input(t_mshell *mshell, t_lexer *lexer);

/// lexer_utilities ///
bool	ft_character_valid(t_mshell *mshell, char *input);
void	ft_init_wild_input(t_mshell *mshell, t_lexer *lexer);
bool	ft_invalid_character(char c);
t_type	ft_builtin_or_cmd(t_lexer *lexer, char *elem);

////////////////////////////////////////////////////////////////////////////////

/// parser ///
int		ft_parser(t_mshell *mshell);

/// parser_initilisation ///
void	ft_init_parser(t_parser *parser, t_token *list_token);

/// parser_valid_syntax ///
bool	ft_valid_pipes(t_parser *parser);
bool	ft_valid_cmds(t_parser *parser);
bool	ft_valid_redirs(t_parser *parser);
bool	ft_valid_syntax(t_parser *parser);

/// parser_initialisation_list_cmd ///
void	ft_init_node_values(t_cmd *new_elem);
void	ft_init_head_list_cmd(t_mshell *mshell, t_cmd **list_cmd);
void	ft_add_node_cmd(t_mshell *mshell, t_parser *parser);
void	ft_init_list_cmd(t_mshell *mshell, t_parser *parser);

/// parser_expand_and_ckeanup ///
void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser);

/// parser_clear_elem ///
bool	ft_char_saved(t_mshell *mshell, t_parser *parser, char *str, int i);
char	*ft_remove(t_mshell *mshell, t_parser *parser, char *str);
void	ft_clear_elems(t_mshell *mshell, t_parser *parser);

/// parser_markers_expand ///
int		ft_find_end_var(char *str, int i);
char	*ft_insert_marker(t_mshell *mshell, char *str, int i);
char	*ft_marker(t_mshell *mshell, t_token *tmp, t_parser *parser);
void	ft_mark_expand(t_mshell *mshell, t_parser *parser);

/// parser_expand ///
char	*ft_inval(t_mshell *ms, char *str, char *ev_exp, t_parser *parser);
char	*ft_merge(t_mshell *ms, char *str, char *exp, t_parser *parser);
char	*ft_expand(t_mshell *mshell, char *elem, t_parser *parser);
void	ft_exp_elem(t_mshell *mshell, t_token *tmp, t_parser *parser);
void	ft_expand_list(t_mshell *mshell, t_parser *parser);

/// parser_fill_list_cmd ///
void	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser);

/// parser_handle_redir ///
void	ft_get_fd_outfile(t_cmd *lt_cmd, t_token *lt_token);
void	ft_get_fd_infile(t_cmd *cmd, t_token *token);
void	ft_handle_redir(t_parser *parser);

/// parser_handle_hd ///
void	ft_get_hd(t_cmd *cmd, t_token *token);
void	ft_handle_hd(t_mshell *mshell, t_parser *parser);

/// parser_handle_cmd ///
void	ft_make_cmd_tab(t_mshell *mshell, t_token *list_token, t_cmd *list_cmd);
void	ft_handle_cmd(t_mshell *mshell, t_parser *parser);

/// parser_utilities ///
bool	ft_inside_brackets(t_parser *parser, char *str, int i);
int		ft_count_pipe(t_parser *parser);

////////////////////////////////////////////////////////////////////////////////

/// malloc ///
void	*ft_malloc_list(t_mshell *mshell, size_t size);
void	*ft_calloc_list(t_mshell *mshell, size_t nb, size_t size_type);
void	ft_init_head_list_ml(t_mshell *mshell, void *ptr, size_t size);
void 	ft_add_ml(t_mshell *mshell, void *ptr, size_t size);
char	*ft_itoa_ml(t_mshell *mshell, int n);
char	**ft_split_ml(t_mshell *mshell, char *s, char c);
char	*ft_strdup_ml(t_mshell *mshell, char *s_src);
char	*ft_strjoin_ml(t_mshell *mshell, char *s1, char *s2);
char	*ft_substr_ml(t_mshell *mshell, char *s_src, int start, int len);
void	ft_free_one_node_ml(void *ptr, t_mnode **ml);
void	ft_free_ml(t_mshell *mshell);
void	ft_free_env(t_env **env_list);

////////////////////////////////////////////////////////////////////////////////

/// utilities ///
void	ft_init_mshell(t_mshell **mshell/* , char **env */);
bool	ft_empty_line(char *input);

/// errors ///
char	*ft_build_err_mess(t_mshell *ms, char *message, char *elem);
bool	ft_err(t_mshell *mshell, char *message, char *elem, int exit_code);

/// handle_input ///
bool	ft_open_input(t_mshell *mshell, char *input);
void	ft_handle_input(t_mshell *mshell);

/// handle_quotes ///
bool	ft_effect_esc(t_qts *qts, char *str, int i);
void	ft_swipe(bool *quote, bool *status, bool *delay_in, bool *delay_out);
void	ft_delay(t_qts *qts);
bool	ft_status_qts(t_qts *qts, char *str, int i);

/// print ///
void	ft_print_input_clean(char *line);
void	ft_print_double_tab(char **tab);
void	ft_print_list_token(t_token *head);
char	*ft_get_name_type(t_type type);
void	ft_print_list_cmd(t_mshell *mshell);

////////////////////////////////////////////////////////////////////////////////

// redirections

void	ft_redir(t_mshell *mshell);
//void	ft_redir_case(t_mshell *mshell);
void	ft_redir_out(t_mshell *mshell);
void	ft_redir_in(t_mshell *mshell);
void	ft_redir_hd(t_mshell *s_mshell);

void	ft_redir_pipe_read(t_mshell *mshell, int *pipe_fd);
void	ft_redir_pipe_write(t_mshell *mshell, int *pipe_fd);



// pipe.c
void	ft_forker(t_mshell *mshell, char **envp);
int		ft_piper(t_mshell *mshell, char **envp);
void	ft_pipe_read(t_mshell *mshell, int pipe_read);
void	ft_pipe_write(t_mshell *mshell, int pipe_write);

// exec
void	ft_executer(t_mshell *mshell, char **envp);

//t_mshell	*cmd_remplissage_test(t_mshell *mshell);

t_cmd			*cmd_init(void);
t_mshell		*cmd_remplissage(t_mshell *mshell);


// BUILTINS

// ft_env_utilities
char	*ft_get_env_value(t_mshell *mshell, char *key);
char	*ft_get_env(char *key, t_env *env);

void	ft_print_env_list(t_env *env_list);


// builtin_utilities




void	ft_exe_built_in(t_mshell *mshell);
// ft_cd
int		ft_cd(t_mshell *mshell);
	// ft_echo
int		ft_echo(t_mshell *mshell);

	// ft_env
int		ft_env(t_mshell *mshell);
void	ft_env_minimal(t_mshell *mshell);
void	ft_build_env_list(t_mshell   *mshell, char **env);

char	**ft_split_var(char *cmd);

//update_env();

	// ft_exit
int ft_exit(t_cmd *cmd);
	// ft_export
int		ft_export(t_mshell *mshell);

void	ft_add_var(t_mshell *mshell);
void	ft_add_node_env(t_mshell *mshell, char *cmd);
int		ft_isequal(char *str);
void	ft_free_tab(char **tab);

int		ft_check_env_key(t_env *env, char **key_value);
void	ft_change_env_value (t_env *env, char **key_value);
void	ft_create_env_node(t_mshell *mshell, char **key_value);	


void	ft_swap_env(t_env *a, t_env *b);
void	ft_print_sorted_env(t_env *env);


	// ft_pwd

int		ft_pwd(t_mshell *mshell);


	// ft_unset
int		ft_unset(t_mshell *mshell);
void	ft_remove_env_node(t_env *env_list, char *key);

/// exec_heredoc ///
char	*ft_merge_hd(t_mshell *mshell, char *line, char *ev_exp, t_hd *hd);
char	*ft_expand_ev_hd(t_mshell *mshell, char *line, t_hd *hd);
char	*ft_expand_hd(t_mshell *mshell, char *line, t_hd *hd);
void	ft_put_in_hd(t_mshell *mshell, char *line, t_cmd *cmd);
void	ft_heredoc(t_mshell *mshell, t_cmd *cmd);

/// exec_utilities ///
bool	ft_effect_escape_hd(char *str, int i);
bool	ft_found_dollar_active(char *str);
bool	ft_escape_last_char(char *line);

int		ft_ispath(char *str);
int		ft_check_path_access(char *cmd);

void	ft_build_path(t_mshell *mshell);
void	ft_build_cmd_path(t_mshell *mshell);
void	ft_path_makeur(t_mshell *mshell, char **path_tab);




// signals

void	ft_handle_signals(void);
void	handle_sig_int(int num);
void	setup_child_signals(void);


#endif