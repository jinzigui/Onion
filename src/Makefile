CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O
DFLAGS   = $1

DIR=util tcp
OBJ=util/log.o util/string_op.o util/buffer.o util/ip_address.o util/end_point.o util/socket.o \
		tcp/connection_id.o tcp/tcp_option.o tcp/tcp_connection.o tcp/tcp_client.o tcp/tcp_server.o \
		tcp/event.o tcp/poller.o tcp/select_poller.o tcp/poll_poller.o\

Onion:$(OBJ) Onion.cpp
	$(CPP) $(CPPFLAGS) -o Onion $(OBJ) Onion.cpp

all:Onion log client server

log:$(OBJ) ../test/log.cpp
	$(CPP) $(CPPFLAGS) -o log $(OBJ) ../test/log.cpp

client:$(OBJ) ../test/client.cpp
	$(CPP) $(CPPFLAGS) -o client $(OBJ) ../test/client.cpp

server:$(OBJ) ../test/server.cpp
	$(CPP) $(CPPFLAGS) -o server $(OBJ) ../test/server.cpp $1

tag:
	cd .. && ctags -R --sort=yes -f .tags

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Onion log client server logging .tags
