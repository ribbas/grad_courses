# Makefile to ease trivial tasks for the project

TODAY = $(shell date +_%Y%m%d)
DOC := DOC.tex

all: convert

.PHONY: convert convert1 convert2 clean

convert: convert1 convert2
convert1 convert2:
	# convert LaTex file to PDF
	xelatex -output-directory=$(dir ${DOC}) ${DOC}

clean:
	# clean out cache and temporary files
	find . \( -name *.aux -o -name *.log -o -name *.out \) -delete
