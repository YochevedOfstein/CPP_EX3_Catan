CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wall -g
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = board.cpp tile.cpp intersection.cpp road.cpp resource.cpp player.cpp developmentCard.cpp catan.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: catan test

catan: demo
	./$^

demo: $(OBJECTS) demo.o
	$(CXX) $(CXXFLAGS) $(OBJECTS)  demo.o -o demo

test: $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) test.o -o test

tidy:
	clang-tidy $(SOURCES) $(TEST_SOURCES) demo.cpp -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o catan demo test