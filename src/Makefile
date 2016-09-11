CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O

DIR=util tcp test
OBJ=util/log.o util/string_op.o util/ip_address.o util/end_point.o util/socket.o \
		tcp/tcp_option.o tcp_client.o \
		test/log_test.o test/socket_test.o \

Onion:$(OBJ) Onion.cpp
	$(CPP) $(CPPFLAGS) -o Onion $(OBJ) Onion.cpp

server:$(OBJ) server.cpp
	$(CPP) $(CPPFLAGS) -o server $(OBJ) server.cpp

client:$(OBJ) client.cpp
	$(CPP) $(CPPFLAGS) -o client $(OBJ) client.cpp

tag:
	ctags -R --sort=yes -f .tags

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Onion log .tags
