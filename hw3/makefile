main:main.cpp main2.cpp main3.cpp
	@g++ main.cpp -o p1
	@g++ main2.cpp -o p2
	@g++ main3.cpp -o p3 -fexec-charset=BIG5

p1:main.cpp
	@g++ main.cpp

p2:main2.cpp
	@g++ main2.cpp

p3:main3.cpp
	@g++ main3.cpp -fexec-charset=BIG5

.PHONY: clean
clean:
	@rm -f a.exe p1.exe p2.exe p3.exe
	@rm -f out*