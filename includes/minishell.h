/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:10:14 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 20:45:20 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/// STD_HEADERS ///
# include <unistd.h>			// get
# include <errno.h>             // liste des erreurs errno.
# include <readline/history.h>  // gere l'historique des commandes (non vide)
# include <readline/readline.h> // declare la fonction readline.
# include <stdbool.h>           // boolien
# include <stdio.h>             // printf (pour la phase de dev.); dprintf
# include <stdlib.h>            // exit ; getenv ;
# include <sys/errno.h>         // meilleur portabilite avec cette librairie.
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>				// open;
# include <signal.h>

/// MSHELL_HEADERS ///
# include "./structs.h"
# include "./font_style.h"
# include "./libft/includes/libft.h"
# include "./printf/includes/ft_printf.h"

# define IN		1
# define OUT	0

extern int	g_exit_code; //variable glob.pour obtenir le dernier exit_code.

/// MAIN ///
int		main(int ac, char **av, char **env);

////////////////////////////////////////////////////////////////////////////////

/// LEXER ///
bool		ft_lexer(t_mshell *mshell);

/// LEXER_INITIALISATION ///
void	ft_init_lexer(t_mshell *mshell, t_lexer *lexer);

/// LEXER_BUILD_LIST_TOKEN ///
void	ft_define_token_elem(t_lexer *lexer);
void	ft_define_token_redir(t_lexer *lexer);
void	ft_init_head_list_token(t_mshell *mshell, t_token **list_t, char *elem);
void	ft_add(t_mshell *mshell, t_lexer *lexer, char *elem);
void	ft_build_list_token(t_mshell *mshell, t_lexer *lexer);

/// LEXER_CLEANING_INPUT ///
int		ft_count_char(char *line);
void	ft_make_clear_input(t_mshell *mshell, t_lexer *lexer, char *wild_input);
void	ft_put_redirection(t_lexer *lexer, char *input);
void	ft_put_pipe(t_lexer *lexer);
void	ft_cleaning_input(t_mshell *mshell, t_lexer *lexer);

/// LEXER_UTILITES ///
bool	ft_character_valid(t_mshell *mshell, char *input);
void	ft_init_wild_input(t_mshell *mshell, t_lexer *lexer);
bool	ft_invalid_character(char c);
t_type	ft_builtin_or_cmd(t_lexer *lexer, char *elem);

////////////////////////////////////////////////////////////////////////////////

/// PARSER ///
bool		ft_parser(t_mshell *mshell);

/// PARSER_INITIALISATION ///
void	ft_init_parser(t_parser *parser, t_token *list_token);

/// PARSER_VALID_SYNTAX ///
char	*ft_valid_pipes(t_parser *parser);
char	*ft_valid_cmds(t_parser *parser);
char	*ft_valid_redirs(t_parser *parser);
bool	ft_valid_syntax(t_mshell *mshell, t_parser *parser);

/// PARSER_INITIALISATION_LIST_CMD ///
void	ft_init_node_values(t_cmd *new_elem);
void	ft_init_head_list_cmd(t_mshell *mshell, t_cmd **list_cmd);
void	ft_add_node_cmd(t_mshell *mshell, t_parser *parser);
void	ft_init_list_cmd(t_mshell *mshell, t_parser *parser);

/// PARSER_CLEANUP_AND_EXPAND ///
void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser);

/// PARSER_CLEAN_ELEM ///
bool	ft_char_saved(t_mshell *mshell, t_parser *parser, char *str, int i);
char	*ft_remove(t_mshell *mshell, t_parser *parser, char *str);
void	ft_clear_elems(t_mshell *mshell, t_parser *parser);

/// PARSER_MARCKERS_EXPAND ///
int		ft_find_end_var(char *str, int i);
char	*ft_insert_marker(t_mshell *mshell, char *str, int i);
char	*ft_marker(t_mshell *mshell, t_token *tmp, t_parser *parser);
void	ft_mark_expand(t_mshell *mshell, t_parser *parser);

/// PARSER_EXPAND ///
char	*ft_inval(t_mshell *ms, char *str, char *ev_exp, t_parser *parser);
char	*ft_merge(t_mshell *ms, char *str, char *exp, t_parser *parser);
char	*ft_expand(t_mshell *mshell, char *elem, t_parser *parser);
void	ft_exp_elem(t_mshell *mshell, t_token *tmp, t_parser *parser);
void	ft_expand_list(t_mshell *mshell, t_parser *parser);

/// PARSER_FILL_LIST_CMD ///
bool	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser);

/// PARSER_HANDLE_REDIR ///
bool	ft_get_fd_outfile(t_mshell *mshell, t_cmd *lt_cmd, t_token *lt_token);
bool	ft_get_fd_infile(t_mshell *mshell, t_cmd *cmd, t_token *token);
bool	ft_handle_redir(t_mshell *mshell, t_parser *parser);

/// PARSER_HANDLE_HD ///
bool	ft_get_hd(t_mshell *mshell, t_cmd *cmd, t_token *token);
bool	ft_handle_hd(t_mshell *mshell, t_parser *parser);

/// PARSER_HANDLE_CMD ///
void	ft_make_cmd_tab(t_mshell *mshell, t_token *list_token, t_cmd *list_cmd);
void	ft_handle_cmd(t_mshell *mshell, t_parser *parser);

/// PARSER_UTILITIES ///
bool	ft_inside_brackets(t_parser *parser, char *str, int i);
int		ft_count_pipe(t_parser *parser);
bool	ft_srch_quotes(char *elem);
char	*ft_get_ev_name(t_mshell *mshell, char *elem, t_parser *parser);
bool	ft_effect_escape_hd(char *str, int i);
bool	ft_found_dollar_active(char *str);
bool	ft_escape_last_char(char *line);
int		ft_ispath(char *str);

////////////////////////////////////////////////////////////////////////////////

/// MALLOC ///
void	*ft_malloc_list(t_mshell *mshell, size_t size);
void	*ft_calloc_list(t_mshell *mshell, size_t nb, size_t size_type);
void	ft_init_head_list_ml(t_mshell *mshell, void *ptr, size_t size);
void	ft_add_ml(t_mshell *mshell, void *ptr, size_t size);
char	*ft_itoa_ml(t_mshell *mshell, int n);
char	**ft_split_ml(t_mshell *mshell, char *s, char c);
char	*ft_strdup_ml(t_mshell *mshell, char *s_src);
char	*ft_strjoin_ml(t_mshell *mshell, char *s1, char *s2);
char	*ft_substr_ml(t_mshell *mshell, char *s_src, int start, int len);
void	ft_exit_cleanly(t_mshell *mshell);
void	ft_free_one_node_ml(void *ptr, t_mnode **ml);
void	ft_free_ml(t_mshell *mshell);
void	ft_free_env(t_env *env_list);

////////////////////////////////////////////////////////////////////////////////

/// UTILITIES ///
void	ft_init_mshell(t_mshell **mshell, char **env);
bool	ft_empty_line(char *input);
int		ft_msspace(char c);

/// ERRORS ///
bool	ft_syntax_err(t_mshell *ms, char *elem, int exit_code);
void	ft_mem_err(t_mshell *mshell);
bool	ft_fd_err(t_mshell *mshell, char *file);
void	ft_hd_err(int *fd, char *delim);
void	ft_main_err(t_mshell *mshell);

/// HANDLE_INPUT ///
bool	ft_pipe_last(t_mshell *mshell, char *input);
bool	ft_open_quotes(t_mshell *mshell, char *input);
bool	ft_incomplete_cmd(t_mshell *mshell, char *input);
void	ft_handle_input(t_mshell *mshell);

/// HANDLE_QUOTES ///
bool	ft_effect_esc(t_qts *qts, char *str, int i);
void	ft_swipe(bool *quote, bool *status, bool *delay_in, bool *delay_out);
void	ft_delay(t_qts *qts);
bool	ft_status_qts(t_qts *qts, char *str, int i);

/// PRINT ///
void	ft_print_double_tab(char **tab);
void	ft_print_list_token(t_token *head);
char	*ft_get_name_type(t_type type);
void	ft_print_list_cmd(t_mshell *mshell);

////////////////////////////////////////////////////////////////////////////////

/// BUILTIN_UTILITIES ///
int		ft_count_node(t_env *env_list);
bool	ft_isequal(char *str);
void	ft_print_env_node(t_env *env);
char	*ft_get_key(char *var);
char	*ft_get_value(char *var);
void	ft_build_env_list(t_mshell *mshell, char **env);
int		ft_strlen_equal(char *str);
t_env	*ft_create_env_node(t_mshell *mshell);
t_env	*ft_init_env_node(t_env *new_node);
void	ft_up_value_var(t_env *env_list, char *key, char * value);
t_env	*ft_get_key_node(t_env *env, char *key);
char	*ft_found_value_key(t_mshell *mshell, char *key);
void	ft_init_ignore(t_env *env_list);

		// ||  ft_cd.c  ||
int		ft_cd(t_mshell *mshell);

/// BUILTIN_ECHO ///
int		ft_echo(t_mshell *mshell);

// ||  ft_env.c  ||
int		ft_env(t_mshell *mshell);
void	ft_env_minimal(t_mshell *mshell);

		// ||  ft_exit.c  ||
int		ft_exit(t_cmd *cmd);

		// ||  ft_exe_builtins.c  ||
void	ft_exe_built_in(t_mshell *mshell);

		// ||  ft_export_utilities.c  ||
void	ft_init_ignore(t_env *env_list);
void	ft_ignore_underscore(t_env *env_list, int *count);
void	ft_print_sorted_env(t_env *env_list);
bool	ft_valid_key(char *c_key);
void	ft_edit_var_env(t_mshell *mshell);

		// ||  ft_export.c  ||
int		ft_export(t_mshell *mshell);

		// ||  ft_pwd.c ||
int		ft_pwd(t_mshell *mshell);

		// ||  ft_unset.c ||
int		ft_unset(t_mshell *mshell);
void	ft_remove_env_node(t_env *env_list, char *key);
void	ft_free_env_node(t_env *env_node);


		/// EXEC ///
void	ft_executer(t_mshell *mshell, char **env);
t_cmd	*cmd_init(void);

		// redirections

void	ft_redir(t_mshell *mshell);
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



		/// PARSER_HEREDOC ///
char	*ft_merge_hd(t_mshell *mshell, char *line, char *ev_exp, t_hd *hd);
char	*ft_expand_ev_hd(t_mshell *mshell, char *line, t_hd *hd);
char	*ft_expand_hd(t_mshell *mshell, char *line, t_hd *hd);
void	ft_put_in_hd(t_mshell *mshell, char *line, t_cmd *cmd);
void	ft_heredoc(t_mshell *mshell, t_cmd *cmd);

		/// EXEC_UTILITIES ///
int		ft_check_path_access(char *cmd);

void	ft_build_path(t_mshell *mshell);
void	ft_build_cmd_path(t_mshell *mshell);
void	ft_path_makeur(t_mshell *mshell, char **path_tab);



		// signal

void	handle_sig_int(int num);
void	ft_handle_signals(void);

void	ft_child_signals(void);

void	ft_handle_eof(void);
void	handle_sig_quit(int num);


#endif