# Makefile to ease trivial tasks for the project

DOC := final

all: latex

.PHONY: latex clean

latex:
	# compile LaTex file to PDF
	@xelatex ${DOC}
	@bibtex ${DOC}
	@xelatex ${DOC}
	@xelatex ${DOC}

clean:
	# clean out cache and temporary files
	rm -rf *.aux *.log *.out *.dvi
	rm -rf *.bbl *.blg
	rm -rf *.fls *.fdb_latexmk *.synctex.gz
