# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 12:27:53 by lilefebv          #+#    #+#              #
#    Updated: 2025/02/18 10:46:24 by lilefebv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


# Program name
NAME     = minishell

# Style
GREY     = \033[0;30m
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m

BOLD     = \033[1m
UNDER    = \033[4m
REV      = \033[7m
BLINK    = \033[5m

NC       = \033[0;0m
ERASE    = \033[2K\r
ERASE2   = $(ERASE)\033[F$(ERASE)

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g3
LDFLAGS  = -lreadline

# libs
LIBFTDIR = libft/
LIBFT    = $(LIBFTDIR)libft.a

# Includes
INCLUDES = -I includes/ -I $(LIBFTDIR)includes/

# Source files
SRC_DIR  = src/
SRCS     = parsing/tokenization/expand_vars.c parsing/tokenization/expand_vars_utils.c parsing/tokenization/valid_command.c \
           shell/user_input.c  \
		   main.c

# Object files directory
OBJ_DIR   = .obj/
OBJ       = $(SRCS:%.c=$(OBJ_DIR)%.o)

# Remake all if modified
REMAKE   = libft/includes/libft.h libft/includes/ft_printf.h libft/includes/get_next_line.h libft/Makefile  \
           Makefile includes/ast.h includes/minishell.h includes/tokenization.h includes/tokens.h

# NORMINETTE
NORM_RET = $(RED)[ERROR]$(BOLD) Norminette Disable$(NC)
# NORM	 = $(shell norminette srcs includes | grep -c 'Error!')
# ifeq ($(NORM), 0)
# 	NORM_RET = $(GREEN)[DONE] $(BOLD)$(YELLOW)Norminette.$(NC)
# else
# 	NORM_RET = $(RED)[ERROR] $(BOLD)$(YELLOW)Norminette.$(NC)
# endif

COMPILED_FILES := 0

# Pattern rule for object files
$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(REMAKE)
	@if [ $(COMPILED_FILES) -eq 0 ]; then \
		echo "\n$(YELLOW)╔══════════════════════════════════════════════╗$(NC)";                          \
		echo "$(YELLOW)║      Starting $(YELLOW2)$(NAME)$(YELLOW) compilation...       ║$(NC)";           \
		echo "$(YELLOW)╚══════════════════════════════════════════════╝$(NC)";                        \
	fi
	@$(eval COMPILED_FILES := 1)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)
	@printf "\n$(GREEN)[Compiling] $(NC)$(shell echo $< | sed 's|^srcs/||')";

all : libft_make $(NAME) nothing_to_be_done

nothing_to_be_done:
	@if [ $(COMPILED_FILES) -eq 0 ]; then \
		echo "\n$(YELLOW)╔══════════════════════════════════════════════╗$(NC)";                          \
		echo "$(YELLOW)║      Nothing to be done for $(YELLOW2)$(NAME)$(YELLOW).       ║$(NC)";           \
		echo "$(YELLOW)╚══════════════════════════════════════════════╝$(NC)\n";                          \
	fi

end_message:
	@echo "$(WHITE)\n╔══════════════════════════════════════════════╗$(NC)"
	@echo "$(WHITE)║ $(GREEN)> make all                                   $(WHITE)║$(NC)"
	@echo "$(WHITE)║ $(GREEN)Minishell compiled !                         $(WHITE)║$(NC)"
	@echo "$(WHITE)║ $(GREEN)> $(BLINK)_                                          $(WHITE)║$(NC)"
	@echo "$(WHITE)╚══════════════════════════════════════════════╝$(NC)"
	@echo "\n$(NORM_RET)";

$(NAME) : $(LIBFT) $(OBJ)
	@if [ $(COMPILED_FILES) -eq 0 ]; then \
		echo "\n$(YELLOW)╔══════════════════════════════════════════════╗$(NC)";                          \
		echo "$(YELLOW)║      Starting $(YELLOW2)$(NAME)$(YELLOW) compilation...       ║$(NC)";           \
		echo "$(YELLOW)╚══════════════════════════════════════════════╝$(NC)";                        \
	fi
	@$(eval COMPILED_FILES := 1)
	@echo "\n\n$(GREEN)[Compiling program] $(NC)$(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MINILIBX) $(LDFLAGS)
	@make --no-print-directory end_message

libft_make:
	@make --no-print-directory -C $(LIBFTDIR) all

clean :
	@make --no-print-directory -C $(LIBFTDIR) clean
	@echo "$(RED)[Removing] $(NC)object files"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make --no-print-directory -C $(LIBFTDIR) fclean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)[Removing] $(NC)program $(NAME)"; \
		rm -f $(NAME); \
	fi

re : fclean
	@make --no-print-directory all

norminette:
	@norminette srcs/ libft/ includes/


.PHONY: all clean fclean fclean_fdf_only re end_message libft_make norminette