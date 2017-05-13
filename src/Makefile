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
test:
	rm -f test
	$(CC) $(INC) $(CFLAGS) test.cpp -o test
exha:
	rm -f exha
	$(CC) $(INC) $(CFLAGS) exhaustiveDataStructuresAndAlgos.cpp -o exha
    
clean:
	rm -f ct
	rm -f hld
	rm -f test
	rm -f exha
