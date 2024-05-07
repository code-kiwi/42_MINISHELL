# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 20:47:09 by mhotting          #+#    #+#              #
#    Updated: 2024/05/07 16:31:38 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################
#              Variable definitions             #
#################################################

# GENERAL
NAME					=	minishell
CC						=	cc
ifndef NOFLAGS
	CFLAGS				=	-Wall -Werror -Wextra -g
endif
HFLAGS					=	-I$(HEADERS_DIR) -I$(LIBFT_HEADERS_DIR)
FSFLAGS					=	-fsanitize=address
EXT_LIB_FLAGS			=	-lreadline

# HEADERS
HEADERS_DIR				=	includes/
HEADERS_FILES			=	minishell.h
HEADERS					=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# LIBFT
LIBFT_DIR				=	libft/
LIBFT_FILE				=	libft.a
LIBFT					=	$(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
LIBFT_HEADERS_SUBDIR	=	includes/
LIBFT_HEADERS_DIR		=	$(addprefix $(LIBFT_DIR), $(LIBFT_HEADERS_SUBDIR))
LIBFT_HEADERS_FILE		=	libft.h
LIBFT_HEADERS			=	$(addprefix $(LIBFT_HEADERS_DIR), $(LIBFT_HEADERS_FILE))
LIBFT_FLAGS				=	-L$(LIBFT_DIR) -lft 

# SCRIPT HEADERS SYMLINKS CREATION
HEADER_LINK_SCRIPT		=	config/create_sym_limk.sh
HEADER_LINK_SCRIPT_CLS	=	config/remove_sym_limk.sh

# MAIN
MAIN_DIR				=	main/
MAIN_FILE				=	minishell.c
ifdef testChosen
    ifeq ($(testChosen), token)
		MAIN_DIR		=	.test/
		MAIN_FILE		= 	test_token_recognition.c
	else ifeq ($(testChosen), env)
		MAIN_DIR		=	.test/
		MAIN_FILE		= 	test_env.c
	else ifeq ($(testChosen), prompt)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_prompt.c
	else ifeq ($(testChosen), execution)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_execution1.c test_execution2.c
	else ifeq ($(testChosen), ast)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_ast_creation.c
	else ifeq ($(testChosen), expansion)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_expansion.c echo_string.c
	else ifeq ($(testChosen), ast_building)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_ast_building.c	ast_printing.c
	else ifeq ($(testChosen), signals)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	signals_tests.c
	else ifeq ($(testChosen), wildcard)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	wildcard_test.c echo_string.c
	endif
	MAIN_FILE			+=	temp.c
endif
MAIN					=	$(addprefix $(MAIN_DIR), $(MAIN_FILE))

# AST
AST_DIR					=	ast/
AST_FILES				=	t_node_command_utils.c		\
							t_node_pipe_utils.c			\
							t_node_logical_utils.c		\
							t_node_and_utils.c			\
							t_node_or_utils.c			\
							t_node_subshell_utils.c		\
							t_node_utils.c				\
							t_redirection_list_utils.c	\
							t_redirection_utils.c
AST						=	$(addprefix $(AST_DIR), $(AST_FILES))

# TOKEN RECOGNITION
TOKENR_DIR				=	tokenRecognition/
TOKENR_FILES			=	handle_quote.c				\
							is_operator.c				\
							token_recognition_utils.c	\
							token_recognition.c			\
							tokenize_str.c				\
							token_list_merge.c
TOKENR					=	$(addprefix $(TOKENR_DIR), $(TOKENR_FILES))

# PROMPT
PROMPT_DIR				=	prompt/
PROMPT_FILES			=	prompt_handler.c 			\
							directory_utils.c
PROMPT					=	$(addprefix $(PROMPT_DIR), $(PROMPT_FILES))

# VARIABLE EXPANSION
EXPANSION_DIR			=	expansion/
EXPANSION_FILES			=	get_variable_key.c			\
							word_expansion.c			\
							expand_string.c				\
							expand_wildcard.c			\
							string_equal_wildcard.c		\
							expand_argv.c
EXPANSION				=	$(addprefix $(EXPANSION_DIR), $(EXPANSION_FILES))
# ENV
ENV_DIR					=	env/
ENV_FILES				=	env_utils1.c				\
							env_utils2.c				\
							t_env_element_utils.c
ENV						=	$(addprefix $(ENV_DIR), $(ENV_FILES))

# EXECUTION
EXECUTION_DIR			=	execution/
EXECUTION_FILES			=	exec.c						\
							exec_node_pipe.c			\
							exec_node_logical.c			\
							exec_node_subshell.c		\
							exec_node_command.c			\
							exec_cmd.c					\
							exec_cmd_get_path.c			\
							exec_builtin.c				\
							exec_redirection_list.c		\
							exec_ast_heredocs.c			\
							t_heredoc_exec_info_utils.c	\
							exec_redirection_list_hdcs.c
EXECUTION				=	$(addprefix $(EXECUTION_DIR), $(EXECUTION_FILES))

# BUILT_IN
BUILT_IN_DIR			=	built_in/
BUILT_IN_FILES			=	built_in_utils.c			\
							echo.c						\
							cd1.c						\
							cd2.c						\
							pwd.c						\
							export.c					\
							unset.c						\
							env.c						\
							exit.c
BUILT_IN				=	$(addprefix $(BUILT_IN_DIR), $(BUILT_IN_FILES))

#AST BUILDING
AST_BUILDING_DIR		=	ast_building/
AST_BUILDING_FILES		=	add_command.c				\
							add_operator_node.c			\
							add_subshell.c				\
							build_ast_utils.c			\
							build_ast.c					\
							get_argv.c
AST_BUILDING			=	$(addprefix $(AST_BUILDING_DIR), $(AST_BUILDING_FILES))

SIGNALS_DIR				=	signals/
SIGNALS_FILES			=	signals.c
SIGNALS					=	$(addprefix $(SIGNALS_DIR), $(SIGNALS_FILES))

# UTILS
UTILS_DIR				=	utils/
UTILS_FILES				=	list_utils.c				\
							t_minishell_utils1.c		\
							t_minishell_utils2.c		\
							t_pid_list_utils.c			\
							file_descriptors_utils.c	\
							string_utils1.c				\
							string_utils2.c				\
							is_empty_cmd.c				\
							ft_split_key_val.c			\
							ft_print_str_array.c		\
							array_utils.c				\
							error.c	
UTILS					=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	$(MAIN)	$(AST) $(TOKENR) $(PROMPT) $(ENV)			\
							$(EXPANSION) $(EXECUTION) $(BUILT_IN)				\
							$(AST_BUILDING) $(UTILS) $(SIGNALS)
SRCS					=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS GENERAL
OBJS_MAIN_DIR			=	objs/
OBJS_FILES				=	$(SRCS_FILES:.c=.o)
OBJS					=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# DEPENDENCIES
DEPS_MAIN_DIR			=	deps/
DEPS_FILES				=	$(OBJS_FILES:.o=.d)
DEPS					=	$(addprefix $(DEPS_MAIN_DIR), $(DEPS_FILES))
