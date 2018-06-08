MODULES = x11 arm
clean_MODULES = $(patsubst %,clean_%, $(MODULES))

all: $(MODULES)
clean: $(clean_MODULES)

$(MODULES):
	@cd build \
	&& make -f Makefile.$@

$(clean_MODULES):
	@cd build \
	&& make -f Makefile.$(subst clean_,,$@) clean
