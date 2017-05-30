CC=g++
CFLAGS= -std=c++11
LDFLAGS= -shared -Wl
#INC=-I/usr/local/include -I /usr/local/boost_1_63_0
INC=-I/usr/local/include

MAKE = /usr/bin/make
RM = /bin/rm
CP = /bin/cp
ECHO = /bin/echo
PWD = /bin/pwd

.PHONY: exha exhaFromWeb

ct:
	rm -f ct
	$(CC) $(INC) $(CFLAGS) centroidDecomposition.cpp -o ct
hld:
	rm -f hld
	$(CC) $(INC) $(CFLAGS) HLD.cpp -o hld
st:
	rm -f st
	$(CC) $(INC) $(CFLAGS) segmentTree.cpp -o st
mf:
	rm -f mf
	$(CC) $(INC) $(CFLAGS) maxFlow.cpp -o mf
mst:
	rm -f mst
	$(CC) $(INC) $(CFLAGS) mst.cpp -o mst
    
clean:
	rm -f ct
	rm -f hld
	rm -f st
	rm -f mf
	rm -f mst