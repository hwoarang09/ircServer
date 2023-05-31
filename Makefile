CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra
TARGET		= ircserv
OBJS		= ./src/$(SRCS:.cpp=.o)
SRCS 		= IrcServ.cpp

.PHONY : all clean fclean re

%.o : %.c
	$(CXX) $(CXXFLAGS) $^ -c $(TARGET) 

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET) 

all : 
	$(TARGET)

clean : 
	@rm -f *.o

fclean : 
	@make clean
	@rm -f $(TARGET)
	@rm -rf *.dSYM

re :
	@make fclean
	@make 
	