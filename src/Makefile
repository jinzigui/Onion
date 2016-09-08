CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O

DIR=util
OBJ=util/string_op.o util/ip_address.o util/end_point.o util/socket.o

Onion:$(OBJ) Onion.cpp
	$(CPP) $(CPPFLAGS) -o Onion $(OBJ) Onion.cpp

tag:
	ctags -R --sort=yes -f .tags

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Onion
