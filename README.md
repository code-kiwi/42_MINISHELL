# 42_MINISHELL
42 Cursus project: Minishell

# TODO (things easily forgotten)
- Check all `getenv()` calls in order to retrieve elements from our own env (**WARNING**: our `env_get()` function returns an allocated string);
- ✔️ ~~Check error messages;~~
- Remove debug and print functions (or put them into seperate files, then add a rule to the Makefile for debugging);
- ✔️ ~~We need to expand the content of the heredoc~~
- ✔️ ~~lorsque l'on fait `$test` alors que test n'est pas une variable définie, il affiche juste une string vide, tu préfères que je teste si le résultat est null pour le remplacer par une string vide dans mon code ou alors dans `env_get` `env-get()` retournera NULL avec errno à 0 lorsque la variable n'existe pas et c'est l'expansion qui gèrera le fait de mettre un chaîne vide;~~
- ✔️ ~~**ALL** here_docs are performed before any command execution! (`echo "test" && << LIM cat`)~~
- Check calls to `ft_printf()` and see if it is relevant to replace them by calls to `printf()`
- ✔️ ~~There is a problem with the token type `ASSIGNEMENT WORD`, when typing the command `export TESTS=12` the token is not recognized as an argument for the command and `build_ast()` function fails (I can comment lines into `srcs/tokenRecognition/tokenize_str.c` in order to disable the creation of token of this type)~~
- ✔️ ~~We need to check every call to `handle_error()` function in order to avoid the shell to stop its execution when an error occurs (we should probably comme back to the prompt when an error occurs)~~
- Control binary input (non printable chars)
- ✔️ ~~We could optimize the environment by "caching" the env string. When the env. would be changed, we would generate a new string array or set a flag to indicate that the environment has evolved (this avoids the fact to create an array string each time we call `env` while also avoiding us to access directly the env. strings)~~
- ✔️ ~~We need to check if the environment creation failed into `t_minishell_init()` (NB: the env can be NULL if it is empty like when `env -i ./minishell` was called => check `errno`)~~
- ✔️ ~~Variable "_" in the env~~
- ✔️ ~~On shell start: create basic ENV with: PATH, HOME, SHLLVL, PWD, OLDPWD~~
- ✔️ ~~Segfault when pressing enter with nothing to parse~~
- ✔️ ~~Tokenization error when giving a command composed of spaces~~
- ✔️ ~~`echo -n -n -n ...` does not work as expected~~
