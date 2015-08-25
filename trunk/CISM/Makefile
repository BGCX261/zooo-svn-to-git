



SEOBJS =		server.o tcpserver.o

CLOBJS =		server.o tcpserver.o

DEOBJS =		server.o tcpserver.o

LIBS =

SERVTARGET =	cisserver.exe
CLIENTTARGET =	cismanager.exe
DEALSERVTARGET =	dealserver.exe

server.o:	src/server.c ${PWD}/include/server.h
	gcc -c	-I"${PWD}/include" src/server.c	server.o
	
tcpserver.o:	src/tcpserver.c	${PWD}/include/server.h
	gcc -c	-I"${PWD}/include" src/tcpserver.c	tcpserver.o
	
$(SERVTARGET):	$(SEOBJS)
	$(CXX) -o $(SERVTARGET) $(SEOBJS) $(LIBS)
	


all:	$(SERVTARGET) 

clean:
	rm -f $(SEOBJS) $(SERVTARGET) 
