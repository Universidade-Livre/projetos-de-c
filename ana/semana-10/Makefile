bin/readpe: bin/libpetest.so src/readpe.c
	gcc src/readpe.c -o bin/readpe -L./bin -lpetest

bin/libpetest.so: bin/ lib/petest.c lib/petest.h
	gcc -shared -fPIC -o bin/libpetest.so lib/petest.c

bin/:
	mkdir bin

install_lib: bin/libpetest.so
	install -m 0644 bin/libpetest.so /usr/lib/libpetest.so

uninstall_lib:
	rm -f /usr/lib/libpetest.so

all: install_lib bin/readpe

clean:
	rm -rf bin

