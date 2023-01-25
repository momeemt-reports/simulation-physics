.PHONY: run
run: main.out
	./main.out

.PHONY: report1
report1: report/week1/main.saty
	satysfi ./report/week1/main.saty

main.out: src/main.c
	mkdir -p obj out
	gcc -c src/hit_miss.c -o obj/hit_miss.o
	gcc -c src/cell_automaton.c -o obj/cell_automaton.o
	gcc src/main.c obj/hit_miss.o obj/cell_automaton.o -o main.out -lm

.PHONY: clean
clean:
	rm -f *.out
	rm -f obj/*.o
	rm -f graph.jpg data.dat
	rm -f report/*/main.pdf
	rm -f report/*/main.satysfi-aux
	rm -f out/*