
#include "../../include/minishell.h"

void	ft_pwd()
{
	char	*path;
	int	nbr_child;

	nbr_child = fork();
	if (nbr_child == 0)
	{
		path = getcwd(NULL, 0);
		printf("%s\n", path);//Talvez não printf.
		free(path);
		exit(0);
	}
}
