include ../Makefile.base
include ../log/Makefile.lib
include Makefile.deps

../csv/libcsv.a: ../csv/csv.o
	@echo building $@
	@$(AR) -rc $@ $^

t_csv: ../csv/libcsv.a ../log/liblog.a

test: t_csv
	@echo "testing csv ... \c";
	@./t_csv
	@echo "ok"

clean:
	@rm -f libcsv.a csv.o
