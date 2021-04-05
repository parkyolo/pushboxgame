all:push_box

push_box:pushbox.o
	g++ -W -Wall -o push_box pushbox.o -lncursesw

soko.o:pushbox.cpp
	g++ -W -Wall -c -o pushbox.o pushbox.cpp

clean:
	rm -rf *.0
