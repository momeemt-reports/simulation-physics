SOURCES=$(wildcard src/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

.PHONY: run
run: main.out
	./main.out

.PHONY: report1
report1: report/week1/main.saty
	satysfi ./report/week1/main.saty

.PHONY: report2
report2: report/week2/main.saty
	satysfi ./report/week2/main.saty
	pdfunite ./report/week2/hyoshi.pdf ./report/week2/main.pdf week2.pdf

.PHONY: report3
report3: report/week3/main.saty
	satysfi ./report/week3/main.saty
	pdfunite ./report/week3/hyoshi.pdf ./report/week3/main.pdf week3.pdf

.PHONY: report4
report4: report/week4/main.saty
	satysfi ./report/week4/main.saty
	pdfunite ./report/week4/hyoshi.pdf ./report/week4/main.pdf week4.pdf

main.out: $(OBJECTS)
	gcc $^ -g -o $@ -lm

obj/%.o: src/%.c
	mkdir -p obj out
	gcc -g -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.out
	rm -f obj/*.o
	rm -f report/*/main.pdf
	rm -f report/*/main.satysfi-aux
	rm -f out/*