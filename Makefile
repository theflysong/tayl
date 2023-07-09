global-env := ./script/env/global.mk

-include ./config.mk

architecture ?= x86_64

include $(global-env)
include $(path-script)/env/local.mk
include $(path-script)/helper.mk
include $(path-script)/tool.mk
include $(path-script)/util.mk

.PHONY: build gendoc

path-bin := $(path-e)/build/bin/
path-objects := $(path-e)/build/objects/

arg-basic := architecture=$(architecture) global-env=$(global-env) path-bin=$(path-bin) path-objects=$(path-objects)

build:
	$(q)$(MAKE) -f $(path-e)/tayir/Makefile $(arg-basic) $@

gendoc:
	$(q)$(MAKE) -f $(path-e)/tayir/Makefile $(arg-basic) $@