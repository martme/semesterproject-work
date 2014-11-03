all: bin/x86_instructions bin/cpuload
arm: bin/arm_instructions bin/cpuload

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/x86_instructions: src/x86_instructions/*.c | bin
	cc $+ -o $@

bin/arm_instructions: src/arm_instructions/*.c | bin
	cc $+ -o $@

bin/cpuload: src/cpuload/main.sh | bin
	cp $+ $@

.PHONY: all
