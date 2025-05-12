/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/05/12 03:40:55 by pab              ###   ########.fr       */
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

typedef struct s_lexer // local
{
	char			wild_input[SIZE_LINE];
	char			*input_clear;
	t_token			*list_token;
	int				i;
	int				j;
	bool			simple_q;
	bool			double_q;
	bool			flag_q;
	bool			mark_q;
	bool			cmd_in_pipe;
}					t_lexer;

typedef struct s_cmd
{
	char			**cmd; //ELEM
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
	bool			simple_q;
	bool			double_q;
	bool			flag_q;
	bool			mark_q;
	int				start;
	int				end;
	bool			mark_b;
}					t_parser;

typedef struct s_qts
{
	bool			simple_q;	// État des guillemets simples
	bool			double_q;	// État des guillemets doubles
	bool			flag_q;		// Flag indiquant si une quote est ouvert
	bool			mark_q;		// Mark pour savoir si on est à l'intérieur des quotes
	bool			delay_sq;	// retarde le chagement d'etat simple quote
	bool			delay_dq;	// retarde le chagement d'etat double quote
}   t_qts;

typedef struct s_mnode  		// noeud par la liste de malloc
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
	int				count_pipe;
}					t_mshell;

/// main ///
int		main(int ac, char **av, char **env);
// void	ft_loop_mshell(t_mshell *mshell, t_mnode **ml);

////////////////////////////////////////////////////////////////////////////////

/// lexer ///
int		ft_lexer(t_mshell *mshell, t_mnode **ml);

/// lexer_initialisation ///
void	ft_init_lexer(t_lexer *lexer);

/// lexer_build_list_token ///
void	ft_define_token_redir(t_lexer *lexer);
void	ft_build_list_token(t_mshell *mshell, t_lexer *lexer, t_mnode **ml);
void	ft_add_node(t_lexer *lexer, char *elem, t_mnode **ml);
void	ft_init_head_list_token(t_token **list, char *elem, t_mnode **ml);

/// lexer_operateurs_valid ///
// bool	ft_quotes_valid(t_lexer *lexer, char *input);
bool	ft_validate_operators(t_mshell *mshell, t_lexer *lexer, char *input);
bool	ft_character_valid(t_mshell *mshell, t_lexer *lexer, char *input);
bool	ft_redir_valid(t_mshell *mshell, t_lexer *lexer, char *input);

/// lexer_cleaning_input ///
void	ft_handle_space(t_lexer *lexer, char *input, t_mnode **ml);
void	ft_put_redirection(t_lexer *lexer, char *input);
void	ft_put_pipe(t_lexer *lexer);
void	ft_input_one_space(t_mshell *mshell, t_lexer *lexer, t_mnode **ml);

// /// lexer_handle_quotes ///
// bool	ft_inside_quotes_lexer(t_lexer *lexer, char *str, int i);
// void	ft_status_update_lexer(bool *quote, bool *mark, bool *flag);

/// lexer_utilities ///
bool	ft_effect_escape_lexer(t_lexer *lexer, char *str, int i);
void	ft_init_line(char *virgin_line);
bool	ft_valid_character(char c);
t_type	ft_builtin_or_cmd(t_lexer *lexer, char *elem);

////////////////////////////////////////////////////////////////////////////////

/// parser ///
int		ft_parser(t_mshell *mshell, t_mnode **ml);

/// parser_initilisation ///
void	ft_init_parser(t_parser *parser, t_token *list_token);

/// parser_valid_syntax ///
bool	ft_valid_pipes(t_parser *parser);
bool	ft_valid_cmds(t_parser *parser);
bool	ft_valid_redirs(t_parser *parser);
bool	ft_valid_syntax(t_parser *parser);

/// parser_initialisation_list_cmd ///
void	ft_init_list_cmd(t_parser *parser, t_mnode **ml);
void	ft_add_node_cmd(t_parser *parser, t_mnode **ml);
void	ft_init_head_list_cmd(t_cmd **list_cmd, t_mnode **ml);
void	ft_init_node_values(t_cmd *new_elem);

/// parser_expand_and_ckeanup ///
void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser, t_mnode **ml);

/// parser_clear_elem ///
bool	ft_char_saved(t_mshell *mshell, t_parser *parser, char *str, int i);
void	ft_clear_elems(t_mshell *mshell, t_parser *parser, t_mnode **ml);
char	*ft_remove(t_mshell *mshell, t_parser *parser, char *str, t_mnode **ml);

/// parser_markers_expand ///
int		ft_find_end_var(char *str, int i);
char	*ft_insert_marker(char *str, int i, t_mnode **ml);
char	*ft_marker(t_mshell *msh, t_token *tmp, t_parser *parser, t_mnode **ml);
void	ft_mark_expand(t_mshell *mshell, t_parser *parser, t_mnode **ml);

/// parser_expand ///
char	*ft_invalid(char *str, char *ev_exp, t_parser *parser, t_mnode **ml);
char	*ft_merge(char *str, char *exp, t_parser *parser, t_mnode **ml);
char	*ft_expand(t_mshell *ms, char *elem, t_parser *parser, t_mnode **ml);
void	ft_exp_elem(t_mshell *ms, t_token *tmp, t_parser *parser, t_mnode **ml);
void	ft_expand_list(t_mshell *mshell, t_parser *parser, t_mnode **ml);

/// parser_fill_list_cmd ///
void	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser, t_mnode **ml);

/// parser_handle_redir ///
void	ft_get_outfile(t_cmd *cmd, t_token *token);
void	ft_get_infile(t_cmd *cmd, t_token *token);
void	ft_handle_redir(t_parser *parser);

/// parser_handle_hd ///
void	ft_get_hd(t_cmd *cmd, t_token *token);
void	ft_handle_hd(t_mshell *mshell, t_parser *parser, t_mnode **ml);

/// parser_handle_cmd ///
void	ft_build_cmd_tab(t_token *list_toke, t_cmd *list_cmd, t_mnode **ml);
void	ft_handle_cmd(t_parser *parser, t_mnode **ml);

/// parser_handle_quotes ///
void	ft_status_update_parser(bool *quote, bool *mark, bool *flag);
bool	ft_inside_quotes_parser(t_parser *parser, char *str, int i);

/// parser_utilities ///
bool	ft_effect_escape_parser(t_parser *parser, char *str, int i);
bool	ft_inside_brackets(t_parser *parser, char *str, int i);
int		ft_count_pipe(t_parser *parser);

////////////////////////////////////////////////////////////////////////////////

/// malloc ///
void	*ft_malloc_list(size_t size, t_mnode **ml);
void	*ft_calloc_list(size_t nb, size_t size_type, t_mnode **ml);
void 	ft_add_ml(void *ptr, size_t size, t_mnode **ml);
void	ft_init_head_list_ml(void *ptr, size_t size, t_mnode **ml);
char	*ft_itoa_ml(int n, t_mnode **ml);
char	**ft_split_ml(char const *s, char c, t_mnode **ml);
char	*ft_strdup_ml(const char *s_src, t_mnode **ml);
char	*ft_strjoin_ml(char const *s1, char const *s2, t_mnode **ml);
char	*ft_substr_ml(char const *s_src, int start, int len, t_mnode **ml);
void	ft_free_one_node_ml(void *ptr, t_mnode **ml);
void	ft_free_ml(t_mnode **ml);
void	ft_free_env(t_env **env_list);

////////////////////////////////////////////////////////////////////////////////

/// utilities ///
void	ft_error_exit(char *message);
void	ft_init_mshell(t_mshell **mshell, char **env, t_mnode **ml);
bool	ft_empty_line(char *input);

/// handle_input ///
bool	ft_open_input(t_mshell *mshell, char *input);
void	ft_handle_input(t_mshell *mshell, t_mnode **ml);

/// handle_quotes ///
void	ft_stt_up(bool *quote, bool *mark, bool *flag, bool *delay);
bool	ft_status_qts(t_qts *qts, char *str, int i);
bool	ft_effect_esc(t_qts *qts, char *str, int i);

/// print ///
void	ft_print_input_clean(char *line);
void	ft_print_double_tab(char **tab);
void	ft_print_list_token(t_token *head);
char	*ft_get_name_type(t_type type);
void	ft_print_list_cmd(t_mshell *mshell);

////////////////////////////////////////////////////////////////////////////////

// redirections

void	ft_redir(t_mshell *mshell);
void	ft_redir_case(t_mshell *mshell);
void	ft_redir_out(t_mshell *mshell);


// exec
void	ft_executer(t_mshell *mshell, char **envp, t_mnode **ml);



//void    ft_forker_test(t_mshell *mshell);


void    ft_exe_built_in(t_mshell *mshell);

//t_mshell    	*cmd_remplissage_test(t_mshell *mshell);

t_cmd    		*cmd_init(void);
t_mshell    	*cmd_remplissage(t_mshell *mshell);


// pipe.c
int		ft_piper(t_mshell *mshell, char **envp);
void	ft_forker(t_mshell *mshell, char **envp);

// BUILTINS

// ft_cd
int		ft_cd(t_mshell *mshell);
// ft_echo

// ft_env
int		ft_env(t_mshell *mshell);
void	ft_print_env_list(t_env *env_list);
void    ft_env_minimal(t_mshell *mshell);
char	*ft_get_env(char *key, t_env *env);
void    ft_build_env_list(t_mshell   *mshell, char **env);

char	**ft_split_var(char *cmd);

// ft_exit

// ft_export
int		ft_export(t_mshell *mshell);
//char	*get_env_list(t_mshell *mshell);
void	ft_add_var(t_mshell *mshell);
void	ft_add_node_env(t_mshell *mshell, char *cmd);
int		ft_isequal(char *str);
void	ft_free_tab(char **tab);

// ft_pwd

// ft_unset

/// exec_heredoc ///
char	*ft_merge_hd(char *line, char *ev_exp, t_hd *hd, t_mnode **ml);
char	*ft_expand_ev_hd(t_mshell *mshell, char *line, t_hd *hd, t_mnode **ml);
char	*ft_expand_hd(t_mshell *mshell, char *line, t_hd *hd, t_mnode **ml);
void	ft_put_in_hd(char *line, t_cmd *cmd, t_mnode **ml);
void	ft_heredoc(t_mshell *mshell, t_cmd *cmd, t_mnode **ml);

/// exec_utilities ///
bool	ft_effect_escape_hd(char *str, int i);
bool	ft_found_dollar_active(char *str);
bool	ft_escape_last_char(char *line);


int		ft_ispath(char *str);
int		ft_check_path_access(char *cmd);

void	ft_build_path(t_mshell *mshell, t_mnode **ml);
void	ft_build_cmd_path(t_mshell *mshell, t_mnode **ml);


// exp
	// modif 
// ft_loop_mshell(mshell,&ml);
// ft_executer (mshell)

void	ft_path_makeur(t_mshell *mshell, char **path_tab, t_mnode **ml);



#endif