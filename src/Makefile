CPP             = c++
RM              = rm -f
CPP_FLAGS       = -Wall -c -g -O2 -std=c++11
LD              = c++
LD_FLAGS        = -Wall -shared -O2 -ljson-c
RESULT          = libvariant.so

SOURCES		= $(wildcard *.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)


all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} ${LD_LIBRARIES}

clean:
		${RM} *~* *.o ${RESULT}

${OBJECTS}:
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}
