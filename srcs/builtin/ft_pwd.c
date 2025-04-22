#include "../../includes/minishell.h"

//Distinction cwd & pwd 
//cwd : pour obtenir value pour env
//pwd : print le wd 
/*
char	*ft_cwd_init(char *buff)
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
}
*/