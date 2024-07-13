# tokiponacharachterencoding
Because 4 bytes per one symbol is ridiculous.

# How to use
Well, first of all, install Python if you haven't. Then download the scripts. 

Now you have two options: 
1. Open terminal (Win+R and type cmd), and run with command line arguments.
2. Run it directly.

If you chose the latter, you will be prompted with the data needed.

Command line syntax:

`python encode.py \[input .txt file] \[output .whatever_extension_you_want file]`

`python decode.py \[input .whatever file] \[output .txt file]`

# How it works
This section is unnecessary to read and I advise against it.

This script is compatible with [Under-ConScript Unicode Registry](https://www.kreativekorp.com/ucsur/charts/sitelen.html). It is used by several fonts to display the characters.

The algorithm iterates over the input file and saves bytes to a buffer. If it finds the defined block in the last bytes of the buffer, it first saves the length of non-defined string and adds 0xaf to it. That way, if you have string "hello", it will become "\xb4hello". If the length exceeds 80 (aka the sum is 0xff), the string is split in 80 character long blocks. Then 128 will be subtracted from the last byte of the block and two least significant bits of second-to-last byte will be added as the most significant bits.

So "hello\xf3\xb1\xa4\x80 world!" will become "\xb4hello\x00\xb6 world!" because 0xf3b1a580 is converted into \x00, and the lengths of other strings are added.

Of course there's not much compression here since we use only so little special characters, but the compression can theoretically approach 4x. In a normal test on an average-sized file written fully in Toki Pona with the spaces and newline characters, the compression was ~2.4x. 
