#include "minishell.h"


void    BI_env_init(void)
{
    char    cwd;

    cwd = malloc(char * 4096);
    printf("CWD = %s\n", BI_init_cwd(cwd));

}



char	*BI_init_pwd(char *buff)
{
	//printf() + getcwd()	
	//PATH_MAX = constante dans limits.h
	//4096 = Linux ; 1024 = MacOs

    if (getcwd(buff,sizeof(buff)== NULL))
    {
        printf("sizeof cwd : %lu\nlen cwd : %lu\n", sizeof(buff),strlen(buff));
        perror("PWD = NULL\n");
        return (NULL);
    }
    else
        return (buff);

	//char pwd[4096];

/*
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("PWD = %s\n", pwd);
	else
		perror("B_pwd failed !");


    */
}

