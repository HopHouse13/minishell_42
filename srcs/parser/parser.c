/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/02/19 18:44:41 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parcer(t_parser *parser)
{
	ft_init_line(parser->line);
	parser->i = -1;
	parser->j = -1;
	parser->squote = OUT_Q;
	parser->dquote = OUT_Q;
}
// true(1) = exterieur de quote
// false(0) = interieur de quote
/* bool	ft_check_quotes_input(t_parser *parser, char *input)
{
	while (input[++parser->i])
	{
		if (input[parser->i] == '\'' && parser->dquote == true && parser->squote == true)
			parser->squote = false;
		else if (input[parser->i] == '\'' && parser->squote == false && parser->dquote == true)
			parser->squote = true;
		else if (input[parser->i] == '\"' && parser->squote == true && parser->dquote == true)
			parser->dquote = false;
		else if (input[parser->i] == '\"' && parser->dquote == false && parser->squote == true)
			parser->dquote = true;
	}
	if (parser->squote == true && parser->dquote == true)
		return (true);
	return (false);
} */
bool	ft_check_quotes_input(t_parser *parser, char *input)
{
	while (input[++parser->i])
		ft_check_quotes(parser, input[parser->i]);
	if (parser->squote == OUT_Q && parser->dquote == OUT_Q)
		return (OUT_Q);
	return (IN_Q);
}

void	ft_check_quotes(t_parser *parser, char c)
{
	if (c == '\'' && parser->dquote == OUT_Q && parser->squote == OUT_Q)
		parser->squote = IN_Q;
	else if (c == '\'' && parser->squote == IN_Q && parser->dquote == OUT_Q)
		parser->squote = OUT_Q;
	else if (c == '\"' && parser->squote == OUT_Q && parser->dquote == OUT_Q)
		parser->dquote = IN_Q;
	else if (c == '\"' && parser->dquote == IN_Q && parser->squote == OUT_Q)
		parser->dquote = OUT_Q;
}

void	ft_put_pipe(t_parser *parser, char *input)
{
	if (input[parser->i - 1] != ' ')
	{
		//parser->j++;
		parser->line[++parser->j] = ' ';
		parser->line[++parser->j] = '|';
		parser->line[++parser->j] = ' ';
	}
}
void	ft_put_redirection(t_parser *parser, char *input)
{
	
}

void	ft_put_spaces(t_parser *parser, char *input)
{
	int	flag_quote;
	
	parser->i = 0;
	flag_quote == OUT_Q;
	while (input[parser->i])
	{
		ft_check_quotes(parser, input[parser->i]);
		if (parser->squote == IN_Q || parser->dquote == IN_Q)
			flag_quote = IN_Q;
		else
			flag_quote = OUT_Q;
		if (input[parser->i] == '|' && flag_quote == OUT_Q)
			ft_put_pipe(parser, input);
		else if ((input[parser->i] == '<' || input[parser->i] == '>') && flag_quote == OUT_Q)
			ft_put_redirection(parser, input);
		else if (input[parser->i] != ' ')
			parser->line[++parser->j] = input[parser->i];
	}
	ft_printf("\nline : [%s]\n\n", parser->line);
}

void	ft_parser(t_mshell *mshell, char *input)
{
	t_parser	parser;

	ft_init_parcer(&parser);
	ft_check_quotes_input(&parser, input); // gerer l'erreur lorsque on est endehors de quotes
	ft_put_spaces(&parser, input);
	(void)mshell->input;
}

// 	"bonjour'je'suis'" 'hello"i"am"'
// "bonjourjesuis" 'helloiam'