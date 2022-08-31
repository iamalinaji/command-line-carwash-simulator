carwash : main.o carwash.o 
	g++ main.o carwash.o -o carwash

main.o : main.cpp
	g++ -c main.cpp

carwash.o : carwash.cpp 
	g++ -c carwash.cpp
clear: 
	rm *.o carwash 




