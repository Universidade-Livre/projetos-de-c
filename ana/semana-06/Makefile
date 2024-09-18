NAME = ex01

bin/$(NAME): bin/ src/$(NAME).c
	gcc src/$(NAME).c -o bin/$(NAME)

bin/:
	mkdir bin

run: bin/$(NAME)
	./bin/$(NAME)

.PHONY: clean
clean:
	rm -rf bin
