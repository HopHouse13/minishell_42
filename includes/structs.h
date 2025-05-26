/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:07:51 by pab               #+#    #+#             */
/*   Updated: 2025/05/26 19:17:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

#endif