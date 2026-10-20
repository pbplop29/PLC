MATIEC = $(HOME)/tools/matiec

.PHONY: all generate build run plot clean

# the whole pipeline, fresh, every time
all: clean generate build run plot

plc/build:
	mkdir -p plc/build

# ST -> C
generate: plc/build
	$(MATIEC)/iec2c -I $(MATIEC)/lib -T plc/build plc/main.st

# C -> executable
build: generate
	gcc -I $(MATIEC)/lib/C -I plc/build -o plc/build/run_test plc/driver.c

# run the 10 scan cycles, writes plc/build/run_log.csv
run: build
	./plc/build/run_test

# plot plc/build/run_log.csv -> plc/build/waveform.png
plot: run
	python plc/plot_cycles.py

clean:
	rm -rf plc/build
