# Makefile to ease trivial tasks for the project

TODAY = $(shell date +_%Y%m%d)
DOC := DOC.tex

all: convert

.PHONY: convert convert1 convert2 clean

convert: convert1 convert2
convert1 convert2:
	# convert LaTex file to PDF
	@xelatex ${DOC}

clean:
	# clean out cache and temporary files
	rm -rf *.aux *.log *.out
