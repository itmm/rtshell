DIR = ../ta
LIB = libta.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/ta.h $(DIR)/ta.cpp ../log/log.h \
		 ../marked-files-in/marked-files-in.h \
		 ../marked-files-out/marked-files-out.h
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
