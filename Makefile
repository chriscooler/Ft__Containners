
NAMEFT = ft

NAMESTL = std

CC = clang++

FLAGS = -Wall -Wextra -Werror -std=c++98

OUTPUTFT = $(NAMEFT:=.output)

OUTPUTSTL = $(NAMESTL:=.output)

RM		  = rm -rf

all: $(NAMEFT) $(NAMESTL) diff clean

$(NAMEFT):
	${CC} ${FLAGS} -D$(NAMEFT)_D *.cpp -o $(NAMEFT)
	time ./$(NAMEFT) 42 > $(OUTPUTFT)

$(NAMESTL):
	${CC} ${FLAGS} -D$(NAMESTL)_D *.cpp -o $(NAMESTL)
	time ./$(NAMESTL) 42 > $(OUTPUTSTL)

diff: $(NAMEFT) $(NAMESTL)
	diff $(OUTPUTFT) $(OUTPUTSTL)

clean:
	$(RM) $(NAMEFT) $(NAMESTL) $(OUTPUTFT) $(OUTPUTSTL)


fclean: clean
	$(RM) $(OUTPUTFT) $(OUTPUTSTL)

re: fclean all

.PHONY: all $(NAMEFT) $(NAMESTL) diff clean fclean
