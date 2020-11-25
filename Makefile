CPP = g++
CPPFLAGS = -Wall -g


frupal: *.cpp 
	$(CPP) $(CPPFLAGS) -o frupal *.cpp -lncurses

clean:
	rm -f frupal