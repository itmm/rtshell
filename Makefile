PROJECTS := log lazy tac marked-files ta tals tacat tarm tamv csv ttsv \
	csv2ttsv ttsv2csv md5 md5add md5chk

CLEAN_TARGETS := $(addsuffix .clean,$(PROJECTS))

.PHONY: all clean $(PROJECTS) $(CLEAN_TARGETS)

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
