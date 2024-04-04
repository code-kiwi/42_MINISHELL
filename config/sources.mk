# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brappo <brappo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 20:47:09 by mhotting          #+#    #+#              #
#    Updated: 2024/04/04 10:38:29 by mhotting         ###   ########.fr        #
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
    endif
	ifeq ($(testChosen), prompt)
		MAIN_DIR		=	.test/
		MAIN_FILE		=	test_prompt.c
	endif
endif
MAIN					=	$(addprefix $(MAIN_DIR), $(MAIN_FILE))

# AST
AST_DIR					=	ast/
AST_FILES				=	t_node_command_utils.c		\
							t_node_pipe_utils.c			\
							t_node_utils.c				\
							t_redirection_list_utils.c	\
							t_redirection_utils.c
AST						=	$(addprefix $(AST_DIR), $(AST_FILES))

# TOKEN RECOGNITION
TOKENR_DIR				=	tokenRecognition/
TOKENR_FILES			=	handle_quote.c				\
							is_operator.c				\
							token_recognition_utils.c	\
							token_recognition.c
TOKENR					=	$(addprefix $(TOKENR_DIR), $(TOKENR_FILES))

# PROMPT
PROMPT_DIR				=	prompt/
PROMPT_FILES			=	prompt_handler.c \
							directory_utils.c
PROMPT					=	$(addprefix $(PROMPT_DIR), $(PROMPT_FILES))

# ENV
ENV_DIR					=	env/
ENV_FILES				=	env_utils.c					\
							t_env_element_utils.c
ENV						=	$(addprefix $(ENV_DIR), $(ENV_FILES))

# UTILS
UTILS_DIR				=	utils/
UTILS_FILES				=	list_utils.c				\
							t_minishell_utils.c			\
							close_file_descriptor.c		\
							string_utils.c				\
							ft_split_key_val.c			\
							array_utils.c				\
							error.c
UTILS					=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	$(MAIN)	$(AST) $(TOKENR) $(PROMPT) $(ENV) $(UTILS)
SRCS					=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS GENERAL
OBJS_MAIN_DIR			=	objs/
OBJS_FILES				=	$(SRCS_FILES:.c=.o)
OBJS					=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# DEPENDENCIES
DEPS_MAIN_DIR			=	deps/
DEPS_FILES				=	$(OBJS_FILES:.o=.d)
DEPS					=	$(addprefix $(DEPS_MAIN_DIR), $(DEPS_FILES))
