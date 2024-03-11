COLOR = \033[0;32m
COLOR2 = \033[0;33m
RESET = \033[0m
#######################

FT 			= ft_container
STL 		= stl_container

CC 			= clang++
CFLAGS 		= -Wall -Wextra -Werror -std=c++98

FT_SRCS 	= $(wildcard FT/*.cpp)
STL_SRCS 	= $(wildcard STL/*.cpp)

FT_OBJS 	= $(FT_SRCS:.cpp=.o)
STL_OBJS 	= $(STL_SRCS:.cpp=.o)

OUTPUT_DIR 	= Output

FT_OUTPUT 	= $(OUTPUT_DIR)/$(FT)
STL_OUTPUT 	= $(OUTPUT_DIR)/$(STL)

RM			= rm -rf

all: $(FT_OUTPUT) $(STL_OUTPUT)

$(OUTPUT_DIR):
	@echo "$(COLOR2)>>>>>> Output directory created...$(RESET)"
	mkdir -p $(OUTPUT_DIR)

$(FT_OUTPUT): $(FT_OBJS) | $(OUTPUT_DIR)
	@echo "$(COLOR)>>>>>> Building $(FT)...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(COLOR2)>>>>>> $(FT) is ready to be used ! $(RESET)"

$(STL_OUTPUT): $(STL_OBJS) | $(OUTPUT_DIR)
	@echo "$(COLOR)>>>>>> Building $(STL)...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(COLOR2)>>>>>> $(STL) is ready to be used ! $(RESET)"

%.o:%.cpp
	@echo "$(COLOR)>>>>>> Building $<...$(RESET)"
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "$(COLOR)>>>>>> Cleaning ...$(RESET)"
	$(RM) $(FT_OBJS) $(STL_OBJS) 

fclean: clean
	$(RM) $(FT_OUTPUT) $(STL_OUTPUT) $(OUTPUT_DIR)

re: fclean all

.PHONY: all clean fclean re