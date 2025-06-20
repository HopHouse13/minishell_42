/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:07:51 by pab               #+#    #+#             */
/*   Updated: 2025/06/20 11:49:31 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	ELEM,
	PIPE,
	R_IN,
	R_OUT,
	HD,
	APPEND,
	F_IN,
	F_OUT,
	F_APP,
	DELIM,
	CMD,
	BI,
	ARG,
	END,
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
	char			*path;
	bool			builtin;
	int				fd_in;
	int				fd_out;
	int				fd_hd;
	char			*delim_hd;
	bool			expand_hd;
	bool			no_cmd;
	int				pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	bool			equal;
	char			*value;
	bool			ignore;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_parser
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
	bool			spl_q;
	bool			dbl_q;
	bool			in_q;
	bool			delay_in;
	bool			delay_out;
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
	t_qts			qts;
	t_token			*list_token;
	t_cmd			*list_cmd;
	t_env			*env_list;
	t_mnode			*ml;
	int				count_pipe;
	int				shlvl;
	char			*pwd;
	char			**envp;
}					t_mshell;
#endif
