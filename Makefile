.PHONY: run
run: main.out
	./main.out

main.out: src/main.c
	gcc src/main.c -o main.out

.PHONY: clean
clean:
	rm -f *.out
	rm graph.png data.dat