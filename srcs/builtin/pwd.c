#include "minishell.h"

void	B_pwd(void)
{
	//printf() + getcwd()	
	//PATH_MAX = constante dans limits.h
	//4096 = Linux ; 1024 = MacOs

	char pwd[4096];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("PWD = %s\n", pwd);
	else
		perror("B_pwd failed !");
}