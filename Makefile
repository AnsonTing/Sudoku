all: main.exe

main.exe: main.o helper.o todo.o
	g++ -o main.exe main.o helper.o todo.o

main.o: main.cpp helper.h todo.h
	g++ -c main.cpp

helper.o: helper.cpp helper.h todo.h
	g++ -c helper.cpp

todo.o: todo.cpp helper.h todo.h
	g++ -c todo.cpp

clean:
	rm -rf *.o
	rm -rf *.exe
