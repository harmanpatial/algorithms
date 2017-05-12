CC=g++
CFLAGS= -std=c++11
LDFLAGS= -shared -Wl
INC=-I/usr/local/include -I /usr/local/boost_1_63_0

MAKE = /usr/bin/make
RM = /bin/rm
CP = /bin/cp
ECHO = /bin/echo
PWD = /bin/pwd

.PHONY: exha exhaFromWeb

#project_code:
 #   $(CC) $(INC)  sortedArrayToBalancedBST.cpp -o sortedArrayToBalancedBST
#   $(CC) $(INC)  longestIncreasingSequence.cpp -o longestIncreasingSequence
#   $(CC) $(INC)  knapsackProblem.cpp -o knapsackProblem
#   $(CC) $(INC)  maxSumContCirArray.cpp -o maxSumContCirArray

ct:
	$(CC) $(INC) $(CFLAGS) centroidDecomposition.cpp -o ct
test:
	rm -f test
	$(CC) $(INC) $(CFLAGS) test.cpp -o test
exha:
	rm -f exha
	$(CC) $(INC) $(CFLAGS) exhaustiveDataStructuresAndAlgos.cpp -o exha
    
clean:
	rm -f ct
	rm -f test
	rm -f exha
