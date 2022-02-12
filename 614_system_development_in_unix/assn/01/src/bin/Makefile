# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src/bin

CXX ?= $(which $(CXX))

ROOT = $(CURDIR)
SUBDIRS := conv_to_fahr conv_to_cent

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# pass
it: $(SUBDIRS)

# pass
install: $(SUBDIRS)

# pass
depend: $(SUBDIRS)

clean: $(SUBDIRS)
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.out" \) -delete
