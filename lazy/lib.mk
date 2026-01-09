DIR = ../lazy
LIB = liblazy.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
