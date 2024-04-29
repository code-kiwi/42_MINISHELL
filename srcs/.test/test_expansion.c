#include "minishell.h"
#include "expansion.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>

char	**dup_args(char **argv)
{
	char	**result;
	size_t	argv_length;
	size_t	index;

	argv_length = array_size((void **)argv);
	result = ft_calloc(argv_length + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (index < argv_length)
	{
		result[index] = ft_strdup(argv[index]);
		if (result[index] == NULL)
		{
			ft_free_str_array(&argv);
			return (NULL);
		}
		index++;
	}
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char		**new_argv;
	t_minishell	shell;
	bool		result;

	t_minishell_init(&shell, argc, argv, envp);
	new_argv = dup_args(argv + 1);
	if (new_argv == NULL)
		return (1);
	result = expand_argv(&new_argv, O_VAR | O_PATH | O_QUOTE, &shell, false);
	if (result == false && errno != 0)
	{
		printf("error");
		return (1);

	}
	ft_print_str_array(new_argv);
	ft_free_str_array(&new_argv);
	t_minishell_free(&shell);
	return (0);
}