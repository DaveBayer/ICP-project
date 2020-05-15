

project:
	$(MAKE) -C src

run:
	./icp examples/streets.txt examples/stations.txt examples/lines.txt

pack: