DIR = ../md5
LIB = libmd5.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/md5.cpp $(DIR)/md5.h
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
