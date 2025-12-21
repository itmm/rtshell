PROJECTS := lazy tac tals
CLEAN_TARGETS := $(addsuffix .clean, $(PROJECTS))

.PHONY: all clean $(PROJECTS)

all: $(PROJECTS)

define GEN_PRJ
$(1)
	@$$(MAKE) --directory=$$@
endef

define GEN_CLN
$(1)
	@$$(MAKE) --directory=$$(basename $$@) clean
endef

$(foreach prj,$(addsuffix :,$(PROJECTS)),$(eval $(call GEN_PRJ,$(prj))))
$(foreach cln,$(addsuffix :,$(CLEAN_TARGETS)),$(eval $(call GEN_CLN,$(cln))))

clean: $(CLEAN_TARGETS)

