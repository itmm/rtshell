DIR = ../csv
LIB = libcsv.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/csv.cpp $(DIR)/csv.h ../log/log.h
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
