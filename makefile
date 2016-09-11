OBJ=obj/ProtocolHandler.o obj/OrderPackage.o obj/ioFunc.o obj/TcpServer.o obj/main.o
DEBUG=-g
PTHREAD=-lpthread

Server:$(OBJ)
	g++ -o Server $(OBJ) $(PTHREAD) $(DEBUG)

obj/OrderPackage.o:src/OrderPackage.cpp
	g++ -c src/OrderPackage.cpp -o obj/OrderPackage.o $(DEBUG)

obj/ProtocolHandler.o:src/ProtocolHandler.cpp
	g++ -c src/ProtocolHandler.cpp -o obj/ProtocolHandler.o $(DEBUG)
	
obj/ioFunc.o:src/ioFunc.cpp
	g++ -c src/ioFunc.cpp -o obj/ioFunc.o $(DEBUG)
	
obj/TcpServer.o:src/TcpServer.cpp
	g++ -c src/TcpServer.cpp -o obj/TcpServer.o $(DEBUG)

obj/main.o:src/main.cpp
	g++ -c src/main.cpp -o obj/main.o $(DEBUG)

clean:
	rm $(OBJ)