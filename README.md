# 42_MINISHELL
42 Cursus project: Minishell

# TODO (things easily forgotten)
- Check all getenv() calls in order to retrieve elements from our own env;
- Check error messages;
- Remove debug and print functions (or put them into seperate files, then add a rule to the Makefile for debugging);
- If we add $? as an env variable, we have to avoid putting it into the env str array because it should not appear when we call the env builtin
- We need to check if the environment creation failed into `t_minishell_init()` (NB: the env can be NULL if it is empty like when `env -i ./minishell` was called => check `errno`)

We have to discuss the env implementation (do we rebuild the env string array every time we need or do we store it into shell main structure?)
Idem for path: should we save the path into a variable of the shell and modify it only when the PATH has evolved?
