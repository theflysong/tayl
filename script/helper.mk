builder := -f $(path-script)/build/Makefile.build global-env=$(global-env) target

builder-e := -f $(path-script)/build/Makefile.build global-env=$(global-env) mode=e target
builder-s := -f $(path-script)/build/Makefile.build global-env=$(global-env) mode=s target
builder-l := -f $(path-script)/build/Makefile.build global-env=$(global-env) mode=l target

doc-generator := -f $(path-script)/gendoc/Makefile.doc global-env=$(global-env) config