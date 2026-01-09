include ../base.mk
include ../log/lib.mk
include lib.mk

t_csv: t_csv.o $(LIBS)

test: t_csv
	./t_csv

include t_csv.d
include csv.d

$(LIB): $(LIB)(csv.o)

clean:
	$(RM) libcsv.a csv.o t_csv.o t_csv
