//
// This is a test input file for asm.
//

my_define = 1; my_define_2 = my_define // This is a trailing comment.
My_Define = 2

my_alignment_size = 4

	my_large_define = 1000
	my_negative_define = -42
	my_hex_define = 0x42
	my_octal_define = 042

// This is a mid-file comment.

.word	my_define, my_define_2, My_Define, my_large_define, my_negative_define,
		my_hex_define, my_octal_define, my_label;

my_label:
.byte my_define
.align my_alignment_size
.byte my_large_define
.align 2
.align 2
.byte my_negative_define

    .string	""
    .string	"abc"
    .string "\"Escape\ncharacters!\""