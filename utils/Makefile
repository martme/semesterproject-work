all: bin/x86_instructions bin/x86_cpuload
arm: bin/arm_instructions bin/arm_cpuload

benchmark: bin/benchmark

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/x86_instructions: src/x86_instructions/*.c | bin
	cc $+ -o $@

bin/arm_instructions: src/arm_instructions/*.c | bin
	cc $+ -o $@

bin/x86_cpuload: src/cpuload/main.sh | bin
	cp $+ $@
	chmod +x $@


bin/arm_cpuload: src/cpuload_raspberrypi/main.sh | bin
	cp $+ $@
	chmod +x $@

bin/benchmark: src/benchmark/*.c | bin
	cc src/benchmark/1k_cache_hit.c -o bin/1k_cache_hit
	cc src/benchmark/1k_cache_miss.c -o bin/1k_cache_miss

.PHONY: all
