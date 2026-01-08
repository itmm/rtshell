include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

t_csv: t_csv.o $(LIBS)

test: t_csv
	./t_csv

include t_csv.d
include csv.d

library: $(LIB)

$(LIB): $(LIB)(csv.o)

clean:
	$(RM) libcsv.a csv.o t_csv.o t_csv
