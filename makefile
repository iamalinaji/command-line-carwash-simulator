carwash : main.o carwash.o car.o stage.o worker.o commandparse.hpp
	g++ main.o carwash.o stage.o car.o worker.o -o carwash

main.o : main.cpp
	g++ -c main.cpp

carwash.o : carwash.cpp carwash.hpp
	g++ -c carwash.cpp
stage.o : stage.cpp stage.hpp 
	g++ -c stage.cpp
worker.o: worker.cpp worker.hpp
	g++ -c worker.cpp
car.o : car.cpp car.hpp
	g++ -c car.cpp 
clear: 
	rm *.o carwash 




