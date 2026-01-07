include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

t_csv: t_csv.o $(LIBS_O)

test: t_csv
	./t_csv

clean:
	$(RM) libcsv.a csv.o t_csv.o t_csv
