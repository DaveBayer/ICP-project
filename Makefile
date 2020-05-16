#	file: Makefile
#	autor: David Bayer (xbayer09)
#	autor: Michal Szymik (xszymi00)
#	date: 15.5.2020

.PHONY: icp run doxygen clean pack

icp:
	@qmake -makefile -o src/Makefile src/icp.pro
	@mkdir -p obj
	@$(MAKE) -C src

run: icp
	./icp examples/streets.txt examples/stations.txt examples/lines.txt

doxygen:
	@doxygen doxyfile

clean:
	@rm -rf icp obj src/moc_* doc/*

pack: clean
	@zip -r xbayer09-xszymi00.zip src examples doc Makefile README.txt
