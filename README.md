# Huffman
Files to perform Huffman compression and decompression using a priority queue algorithm based on a min-heap structure.

The included files are: 
- a linked list library
- a hashtable library
- a heap library
- a buffer function and file manipulation library
- the project's main file

The .DS_Store file can be ignored.

Currently, a user has to input a compressed file along with an uncompressed version of that file to perform decompression:
this is because no function has been created to reconstruct a Huffman tree only with the binary data provided by a 
compressed (binary) file, due to time constraints. Otherwise, the code works as expected.

At the moment, no special functions to free allocated memory during the execution of the project's various functions have been
created for simplicity's sake: the exit() function used in the Huffmain_main file's main() function serves that purpose. Users
are free to create their own functions as they see fit.
