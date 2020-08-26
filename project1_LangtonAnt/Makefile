CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -Wall
#CXXFLAGS += -pedantic-errors

OBJS = main.o menu.o Ant.o validateInt.o

SRCS = main.cpp menu.cpp Ant.cpp validateInt.cpp

HEADERS = menu.hpp Ant.hpp validateInt.hpp

Langton_Ant: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS}  -o Langton_Ant

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o Langton_Ant
