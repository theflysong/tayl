include $(global-env)

include $(path-script)/env/local.mk
include $(path-script)/helper.mk

.PHONY: build gendoc

target := $(path-bin)/tayir/tayir

objects := main.o

subdirs := ir/

include $(foreach subdir, $(subdirs), $(path-d)/$(subdir)/include.mk)

flags-cpp := -Wall -Os -std=c++17

include-cpp := -I$(path-include) -I$(path-include)/std/ -I$(path-include)/libs/ -I$(path-d) -I./third_party/include/

defs-cpp :=

args-cpp := defs-cpp="$(defs-cpp)" include-cpp="$(include-cpp)" flags-cpp="$(flags-cpp)"

args := $(args-cpp) libraries=

dir := dir-obj="$(path-objects)/tayir/" dir-src="$(path-d)"

build:
	$(q)$(MAKE) $(builder-e)=$(target) objects="$(objects)" $(dir) $(args) $(target)

gendoc:
	$(q)$(MAKE) $(doc-generator)=$(path-d)/DoxygenFile $@