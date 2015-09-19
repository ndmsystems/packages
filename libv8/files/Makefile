all:
	$(MAKE) -C v8 dependencies
	LINK=$(CXX) LD=$(CXX) $(MAKE) -C v8 $(V8_ARGS)

clean:
	$(MAKE) -C v8 clean
