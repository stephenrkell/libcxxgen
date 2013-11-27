default: src lib #test

.PHONY: src
src:
	$(MAKE) -C src

.PHONY: lib
lib: src
	mkdir -p lib && cd lib && ln -sf ../src/libcxxgen.so .

.PHONY: clean
clean:
	$(MAKE) -C src clean
	rm -f lib/*.{o,so,a} 
	#$(MAKE) -C test clean
