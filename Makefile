.PHONY: project run doxygen clean pack

project:
	@mkdir -p obj
	@$(MAKE) -C src

run:
	./icp examples/streets.txt examples/stations.txt examples/lines.txt

doxygen:
	@mkdir -p doc

clean:
	@rm -rf icp obj

pack:
	@zip -r xbayer09-xszymi00.zip src examples doc Makefile README.txt
