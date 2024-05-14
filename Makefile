# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brappo <brappo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 12:21:10 by mhotting          #+#    #+#              #
#    Updated: 2024/05/14 13:24:56 by mhotting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config/sources.mk

#################################################
#               Rule definitions                #
#################################################

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(OBJS) $(LIBFT_FLAGS) $(EXT_LIB_FLAGS) -o $@

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.c $(HEADERS) $(LIBFT_HEADERS)
	@mkdir -p $(@D)
	@mkdir -p $(DEPS_MAIN_DIR)$(dir $*)
	$(CC) $(CFLAGS) $(HFLAGS) -MP -MMD -MF $(DEPS_MAIN_DIR)$*.d -c $< -o $@ 

$(LIBFT): init_submodule FORCE
	$(MAKE) -sC $(LIBFT_DIR)

FORCE:

bonus: all

fsanitize: fclean $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(FSFLAGS) $(OBJS) $(LIBFT_FLAGS) $(EXT_LIB_FLAGS) -o $(NAME)

init_submodule:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "*Info: Need to initialize git submodules"; \
		git submodule update --init; \
	fi

-include $(DEPS)

clean:
	rm -rf $(OBJS_MAIN_DIR)
	rm -rf $(DEPS_MAIN_DIR)

clean-libft:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)

fclean-libft:
	$(MAKE) -sC $(LIBFT_DIR) fclean

ffclean: fclean fclean-libft

re: fclean all

rre: ffclean re

header_symlink: $(LIBFT)
	@sh $(HEADER_LINK_SCRIPT)
	@printf "Creating symlinks for .h files into srcs sub directories...\n"

header_symlink_clean:
	@sh $(HEADER_LINK_SCRIPT_CLS)
	@printf "Removing symlinks for .h files into srcs sub directories...\n"

.PHONY: all clean fclean re clean-libft fclean-libft ffclean rre bonus FORCE fsanitize header_symlink header_symlink_clean init_submodule
