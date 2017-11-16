LATEX := pdflatex

.PHONY: default all sfsasm sfsisa clean

default: all
all: sfsasm sfsisa
sfsasm: ./sfsasm.pdf
sfsisa: ./sfsisa.pdf

./%.pdf: ./%/main.tex ./common/preamble.tex
	$(LATEX) -jobname=$(patsubst %.pdf,./%/main,$@) -interaction=batchmode $<
	$(LATEX) -jobname=$(patsubst %.pdf,./%/main,$@) -interaction=batchmode $<
	mv $(patsubst %.pdf,./%/main.pdf,$@) $@

clean:
	for TARGET in "sfsasm" "sfsisa"; do
		-rm -f ./${TARGET}/*.aux
		-rm -f ./${TARGET}/*.log
		-rm -f ./${TARGET}.pdf
	done
