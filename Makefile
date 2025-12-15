include vars.mk
include color.mk

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(BLUE)[LINK] Linking executable: $@$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(GREEN)[LINK] Done -> $@$(RESET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[CC] Compiling C++ file: $<$(RESET)"
	@$(CC) $(CFLAGS) ${INCLUDES} -c $< -o $@
	@echo "$(GREEN)[CC] OK -> $@$(RESET)"

clean:
	@echo "$(RED)[RM] Cleaning object files in $(OBJDIR)...$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)[RM] Objects cleaned$(RESET)"

fclean: clean
	@echo "$(RED)[RM] Cleaning executable: $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)[RM] All cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re
