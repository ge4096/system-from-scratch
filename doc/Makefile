LATEX := pdflatex

.PHONY: default all sfsasm clean

default: all
all: sfsasm
sfsasm: ./sfsasm.pdf

./%.pdf: ./%/main.tex
	$(LATEX) -jobname=$(patsubst %.pdf,./%/main,$@) $<
	mv $(patsubst %.pdf,./%/main.pdf,$@) $@

clean:
	-rm -f ./sfsasm/*.aux
	-rm -f ./sfsasm/*.log
	-rm -f ./sfsasm.pdf