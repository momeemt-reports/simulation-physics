.PHONY: run
run: main.out
	./main.out

.PHONY: report1
report1: report/week1/main.saty
	satysfi report/week1/main.saty

main.out: src/main.c
	gcc src/main.c -o main.out -lm

.PHONY: clean
clean:
	rm -f *.out
	rm -f graph.png data.dat
	rm -f report/*/main.pdf
	rm -f report/*/main.satysfi-aux