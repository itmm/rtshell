PROJECTS := log lazy marked-files-in marked-files-out ta tac tals tacat
PROJECTS += tarm tamv csv ttsv csv2ttsv ttsv2csv md5 md5add md5chk

CLEAN_TARGETS := $(addsuffix .clean,$(PROJECTS))

.PHONY: all clean $(PROJECTS) $(CLEAN_TARGETS)

all: marked-files-out/base.mk marked-files-out/with-mdp.mk $(PROJECTS)

marked-files-out/base.mk: base.mk
	chmod a+w $@
	cp $< $@
	chmod a-w $@

marked-files-out/with-mdp.mk: with-mdp.mk
	chmod a+w $@
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
