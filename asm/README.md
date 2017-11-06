# The System from Scratch Cross Assembler (sfsasm)

sfsasm is a cross assembler targeting the SfS ISA desribed elsewhere in this project. For full documentation of the SfS assembly language, refer to the documentation (coming soon). As with the other projects in this repository, it is part of an entirely non-practical exercise in system programming.

## Getting Started

To build the assembler, run the following from inside this directory:
```shell
$ make
```

Once you have built the assembler, you can run it with the following command:
```shell
$ ./bin/sfsasm infile outfile
```

To run the automated unit and validation testing suite, run the following from inside this directory:
```shell
$ ./test/test.sh
```
