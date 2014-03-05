all:
	+$(MAKE) -C src/utils
	+$(MAKE) -C src/fsm

clean:
	+$(MAKE) -C src/utils clean
	+$(MAKE) -C src/fsm clean
