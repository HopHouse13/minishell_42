#include "../../includes/minishell.h"

// #include <signal.h>

void handle_sig_int(int num)
{
	(void)num;
	write(STDOUT_FILENO,"\n",1);
    rl_replace_line("", 0); // Efface le contenu de la ligne actuelle
	rl_on_new_line(); // Informe readline qu'on est sur une nouvelle ligne
    rl_redisplay(); // Affiche le nouveau prompt
	//write(STDOUT_FILENO,"^C",2);
	//glob error a 130;
}

void	ft_handle_signals(void)
{
	// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	
	// ^C --> SIGINT
	struct sigaction sigint;

	sigint.sa_handler = &handle_sig_int;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0; // No special flags

	sigaction (SIGINT, &sigint, NULL);  // Ctrl+C
	
	// ^/ --> SIGQUIT
    struct sigaction sa_quit;
    
	sa_quit.sa_handler = SIG_IGN;            // Set handler to ignore the signal
    sigemptyset(&sa_quit.sa_mask);           // Initialize and clear the signal mask
    sa_quit.sa_flags = 0;                    // No special flags needed for ignoring

	sigaction(SIGQUIT, &sa_quit, NULL);
	
	// ^D --> EOF

}

/*
//reinit avance execve
void	setup_child_signals(void)
{
	struct sigaction sa_quit;
	struct sigaction sigint;

	//sigint.sa_handler = &handle_sig_int;
	//sigemptyset(&sigint.sa_mask);
	//sigint.sa_flags = 0; // No special flags
    
	//sigaction(SIGINT, &sigint, NULL);  // Réinitialiser à comportement par défaut
    //sigaction(SIGQUIT, SIG_DFL); // Réinitialiser à comportement par défaut
    // SIG_IGN

}
*/
