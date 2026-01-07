PROJECTS := log lazy marked-files-in marked-files-out ta tac tals tacat
PROJECTS += tarm tamv csv ttsv csv2ttsv ttsv2csv md5 md5add
#PROJECTS += md5add md5chk

CLEAN_TARGETS := $(addsuffix .clean,$(PROJECTS))

.PHONY: all clean $(PROJECTS) $(CLEAN_TARGETS)

all: marked-files-out/Makefile.base $(PROJECTS)

marked-files-out/Makefile.base: Makefile.base
	cp $< $@
	chmod a-w $@

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
