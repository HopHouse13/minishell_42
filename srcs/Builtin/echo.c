#include "minishell.h"

/*

    - equivalent a un putstr
    - sauf en cas d'expand de la variable d'env '$'; 
        utiliser getenv et le nom de la variable voulue pour obtenir bon comportement de fonction

void    BI_echo(char *env_var)
{

    if ("$")
    {
        //recupére le reste après dollard. -> var env.
        var_decla = string après "$";
        var_env = getenv(var_decla);
        if (var_env == NULL)
        {
            perror("variable n'existe pas dans l'environnement en cours");
            exit(EXIT_STATUS); // definir le code erreur
        }
        else 
            print_var(var_decla);
    }
}

*/