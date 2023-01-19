.PHONY: run
run: main.out
	./main.out

.PHONY: report1
report1: report/week1/main.saty
	satysfi ./report/week1/main.saty

main.out: src/main.c
	mkdir -p obj
	gcc -c src/hit_miss.c -o obj/hit_miss.o
	gcc src/main.c obj/hit_miss.o -o main.out -lm

.PHONY: clean
clean:
	rm -f *.out
	rm -f graph.jpg data.dat
	rm -f report/*/main.pdf
	rm -f report/*/main.satysfi-aux