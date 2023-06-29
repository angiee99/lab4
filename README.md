# LZW Compressor
The purpose of the provided code is to develop a simple archiver. 
The program is given the names of the input and output files and the parameter 
that indicates whether to pack or unpack the input file. 

To perform this task, the **Lempel-Ziv (LZW) compression** algorithm is implemented.

The difficulty is that in this task there is need to work with a large number of bitwise operations to work with numbers, 
that have 9, 10, 11 bits, etc., rather than the usual 8-, 16-, and 32-bit numbers. 

To write to a compressed file, the given code is converted to bytes: each 8 bits – into one byte, and only then bytes are written to the file. 
BitPacker is used for this purpose. Similarly, BitReader is used for bit-by-bit reading. 

Decoding requires only the encoded file, and the code dictionary is created both during compression and decompression. 
The dictionary is not passed with the encoded file, which is an advantage of the algorithm used. 

### Input and output data

For compression, the input is a single file in an arbitrary format (you don't know in advance which files the user will compress), 
the output is an archive. For example, if your program is compiled into megazip.exe:

> megazip.exe --compress output.mgzip input.bmp
> Compressing file input.bmp... Done.
> Result written to output.mgzip

To uncompress, the input file name is passed as input. The name of the output files is usually saved inside the archive.

> megazip.exe --decompress output.mgzip
> Getting out file input.bmp... Done.
