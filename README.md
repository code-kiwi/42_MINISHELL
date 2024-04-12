# 42_MINISHELL
42 Cursus project: Minishell

# TODO (things easily forgotten)
- Check all getenv() calls in order to retrieve elements from our own env;
- Check error messages;
- Remove debug and print functions (or put them into seperate files, then add a rule to the Makefile for debugging);
- If we add $? as an env variable, we have to avoid putting it into the env str array because it should not appear when we call the env builtin
