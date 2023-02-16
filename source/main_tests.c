
#include "../include/minishell.h"

void	echo_test(void)
{
	char	str[] = "-n -nnnn -nnnnnnn It's gonna be a long long time";
	ft_echo(str);
	char	str2[] = "-ntnnn you can't just leave me breath?";
	ft_echo(str2);
	char	str1[] = "";
	ft_echo(str1);
}

void	exit_test(char *str)
{
	(void)str;
	ft_exit("");
	ft_exit("42");
	ft_exit("42 53 68");
	ft_exit("259");
	ft_exit("9223372036854775807");
	ft_exit("-9223372036854775808");
	ft_exit("9223372036854775808");
	ft_exit("-9223372036854775810");
	ft_exit("-4");
	ft_exit("wrong");
	ft_exit("exit wrong_command");
	ft_exit("gdagadgag");
	ft_exit("ls -Z");
	ft_exit("cd gdhahahad");
	ft_exit("ls -la | wtf");
}


void env_test(char *str, struct s_info info)
{
	if(ft_strncmp(str, "env", 4))
		ft_env(info.env_cpy);
}
void unset_test(char *str, struct s_info *info)
{
	if(ft_strncmp(str, "unset", 6))
		ft_unset(str, info);
}

int	main(int ac, char **av, char *envp[])
{
	char	*prompt;
	//int		i;
	struct s_info	info;

	(void) ac;
	(void) av;
	//i = 0;
	info.env_cpy = ft_cpy_env(envp);
	while (42)
	{
		prompt = readline("🔩 Setor de testes> ");

		//echo_test();
		//exit_test(prompt);
		//env_test(prompt, info);
		unset_test(prompt, &info);
		free(prompt);
	}
	return (0);
}
