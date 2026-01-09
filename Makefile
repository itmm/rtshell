PROJECTS := log lazy marked-files-in marked-files-out ta tac tals tacat
PROJECTS += tarm tamv csv ttsv csv2ttsv ttsv2csv md5 md5add md5chk

CLEAN_TARGETS := $(addsuffix .clean,$(PROJECTS))

.PHONY: all clean $(PROJECTS) $(CLEAN_TARGETS)

all: marked-files-out/base.mk marked-files-out/with-mdp.mk $(PROJECTS)

marked-files-out/%.mk: %.mk
	chmod a+w $@
	cp $< $@
	chmod a-w $@

define GEN
$(1)
	$$(MAKE) -C $$(basename $$@) $(2)
endef

$(foreach prj,$(addsuffix :,$(PROJECTS)),$(eval $(call GEN,$(prj),all)))
$(foreach cln,$(addsuffix :,$(CLEAN_TARGETS)),$(eval $(call GEN,$(cln),clean)))

clean: $(CLEAN_TARGETS)
