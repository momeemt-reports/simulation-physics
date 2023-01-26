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

main.out: $(OBJECTS)
	mkdir -p obj out
	gcc $^ -o $@ -lm

obj/%.o: src/%.c
	gcc -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.out
	rm -f obj/*.o
	rm -f report/*/main.pdf
	rm -f report/*/main.satysfi-aux
	rm -f out/*