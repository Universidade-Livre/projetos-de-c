all:
	gcc -shared -fPIC -o libpetest.so petest.c

clean:
	rm libpetest.so

install:
	install -m 0644 libpetest.so /usr/lib/libpetest.so

uninstall:
	rm -f /usr/lib/libpetest.so
