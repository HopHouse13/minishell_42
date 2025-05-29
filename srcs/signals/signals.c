#include "../../includes/minishell.h"

void	ft_handle_signals(void)
{// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	
	struct sigaction sigint; // ^C --> SIGINT

	sigint.sa_handler = &handle_sig_int;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0; // No special flags

	sigaction (SIGINT, &sigint, NULL);  // Ctrl+C
	
    struct sigaction sa_quit; // ^/ --> SIGQUIT
    
	sa_quit.sa_handler = SIG_IGN;            // Set handler to ignore the signal
    sigemptyset(&sa_quit.sa_mask);           // Initialize and clear the signal mask
    sa_quit.sa_flags = 0;                    // No special flags needed for ignoring

	sigaction(SIGQUIT, &sa_quit, NULL);
	
	// ^D --> EOF
	// Signal HD

}

void	ft_child_signals(void)
{
	struct sigaction reinit_dfl;

	reinit_dfl.sa_handler = SIG_DFL; // Default behavior
	sigemptyset(&reinit_dfl.sa_mask);
	reinit_dfl.sa_flags = 0;

	// Apply default behavior for SIGINT
	if (sigaction(SIGINT, &reinit_dfl, NULL) == -1)
		perror(RED"SIGINT child failed"RESET".");

	// Apply default behavior for SIGQUIT
	if (sigaction(SIGQUIT, &reinit_dfl, NULL) == -1)
		perror(RED"sigaction SIGQUIT child failed"RESET".");
}

void handle_sig_int(int num)
{/*    ^C    */
	(void)num;
	write(STDOUT_FILENO,"\n", 1);
	rl_replace_line("", 0); // Efface ligne actuelle
	rl_on_new_line(); // nouvelle ligne pour readline
	rl_redisplay(); // Affiche le nouveau prompt
	//write(STDOUT_FILENO,"^C",2);
	g_exit_code = 130;
}

/*
void	handle_sig_quit(int num)
{   ^\   

	(void)num;


	g_exit_code = 131;
}
*/

/*
void	ft_handle_eof(void)
{ // ^D

	// si readline == NULL --> EOF a ete presse sur ligne vide
	if (!readline)
	{
		printf("exit"); // + quitter proprement
		//break ; // si dans loop
	}
	// si ligne non vide ajoute a l'historique ?
	add_history(readline);

}
*/
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
