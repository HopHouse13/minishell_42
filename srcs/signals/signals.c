#include "../../includes/minishell.h"


void handle_sig_int(int num)
{
	(void)num;
	write(STDOUT_FILENO,"^CC\n",4);
	rl_on_new_line(); // Informe readline qu'on est sur une nouvelle ligne
    rl_replace_line("", 0); // Efface le contenu de la ligne actuelle
    rl_redisplay(); // Affiche le nouveau prompt

}

void	ft_handle_signals(void)
{
	// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	// ^C --> SIGINT
	struct sigaction sa_int;
	sa_int.sa_handler = &handle_sig_int;

	sigaction (SIGINT, handle_sig_int);  // Ctrl+C
	//sigaction(SIGINT, &sa_int, NULL);
	
	
	// ^/ --> SIGQUIT
    struct sigaction sa_quit;
    
	sigaction(SIGQUIT, SIG_IGN);       // Ctrl+\ (Ignorer)v
	//sigaction(SIGQUIT, &sa_quit, NULL);
	// ^D --> EOF

}



void	setup_child_signals(void)
{
    sigaction(SIGINT, SIG_DFL);  // Réinitialiser à comportement par défaut
    sigaction(SIGQUIT, SIG_DFL); // Réinitialiser à comportement par défaut
}

