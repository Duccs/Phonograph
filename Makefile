all: build

build:
	make -C library-application install
	make -C library-audiofiles install
	make -C library-commands install
	make -C program-hello all
	make -C program-questions3 all

clean:
	make -C library-application clean
	make -C library-audiofiles clean
	make -C library-commands clean
	make -C program-hello clean
	make -C program-questions3 clean
	-cd lib && rm -f *.a 
	-cd include && rm -f *.h