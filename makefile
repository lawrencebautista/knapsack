all: ksdp ksbb

ksdp: ksdp.o dpclass.o
	g++ ksdp.o dpclass.o -o ksdp

ksdp.o: ksdp.cpp
	g++ -c ksdp.cpp

dpclass.o: dpclass.cpp dpclass.h
	g++ -c dpclass.cpp

ksbb: ksbb.o bbclass.o
	g++ ksbb.o bbclass.o -o ksbb

ksbb.o: ksbb.cpp
	g++ -c ksbb.cpp -std=c++11

bbclass.o: bbclass.cpp bbclass.h
	g++ -c bbclass.cpp -std=c++11

clean:
	rm -rf *.o ksdp ksbb
