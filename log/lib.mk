DIR = ../log
LIB = liblog.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
