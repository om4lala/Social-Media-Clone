CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = DynamicList.cpp User.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = social_media

all: $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(EXEC)

clean:
	rm -f *.o
	rm -f $(EXEC)

valgrind: all
	valgrind --leak-check=yes ./$(EXEC)
