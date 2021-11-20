/* ----------------------------------------------------------------------------

    (EN) armethyst - A simple ARM Simulator written in C++ for Computer Architecture
    teaching purposes. Free software licensed under the MIT License (see license
    below).

    (PT) armethyst - Um simulador ARM simples escrito em C++ para o ensino de
    Arquitetura de Computadores. Software livre licenciado pela MIT License
    (veja a licença, em inglês, abaixo).

    (EN) MIT LICENSE:

    Copyright 2020 André Vital Saúde

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

   ----------------------------------------------------------------------------
*/

#include "MemoryLoader.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

/**
 * Creates a MemoryLoader for 'memory' and loads binary file 'filename'.
 */
MemoryLoader::MemoryLoader(Memory *memory, string filename) {
	this->memory = memory;
	this->filename = filename;
	loadBinary();
}

/*
 * Methods for loading binary files into the memory.
 */
void MemoryLoader::loadBinary() {
    streampos size;

    ifstream file(filename, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        filesize = file.tellg();
        file.seekg (0, ios::beg);
        file.read (memory->getData(), filesize);
        file.close();
    }
    else {
		string msg = "Unable to open file " + filename + "\nAborting...\n";
		throw msg;
    }
}

/*
 * Methods for writing memory content to human readable text files.
 */
/**
 * Escreve arquivo binario em um arquivo legível
 */
#define LINE_SIZE 4
void MemoryLoader::writeBinaryAsText (string basename) {
    string filename = "txt_" + basename + ".txt";
    ofstream ofp;
    int i,j;
    unsigned int *data = (unsigned int *)memory->getData();

    cout << "Gerado arquivo " << filename << endl << endl;
    ofp.open(filename);

    ofp << uppercase << hex;

    // caption
    ofp << "ADDR    ";
    for (j=0; j<LINE_SIZE; j++) {
        ofp << "ADDR+" << setfill('0') << setw(2) << 4*j << "  ";
    }
    ofp << endl << "----------------------------------------------------------------------------" << endl;


    // binary
    i=0;
    for (i = 0; i < filesize / 4; i+=LINE_SIZE) {
        ofp << setw(4) << 4*i << "    ";
        for (j=0; j<LINE_SIZE; j++) {
            ofp << setw(8) << data[i+j] << " ";
        }
        ofp << endl;
    }
    ofp.close();
}

/**
 * Escreve arquivo binario byte a byte
 */
#define ADDR_SIZE 2
#define ADDR_OFFSET_SIZE 1
#define ADDR_COL_SPACE 4
#define WORD_SIZE 4
#define WORDS_PER_LINE 4
void MemoryLoader::writeBinaryAsTextELF (string basename) {
    string filename = "elf_" + basename + ".txt";
    ofstream ofp;
    int i,j;
    unsigned char *uData = (unsigned char *)memory->getData();

    ofp.open(filename);

    ofp << uppercase << hex;

    // caption
    ofp << "ADDR";
	// acrescenta ADDR_COL_SPACE espaços após o endereço a cada linha, cujo tamanho é 2*ADDR_SIZE
	// após ADDR deve acrescentar 2*ADDR_SIZE + ADDR_COL_SPACE - 4 espaços,
	// 		onde 4 é o tamanho de "ADDR"
	ofp << string(2*ADDR_SIZE + ADDR_COL_SPACE - 4, ' ');

    for (j=0; j<WORDS_PER_LINE; j++) {
        ofp << "ADDR+" << setfill('0') << setw(2*ADDR_OFFSET_SIZE) << WORD_SIZE*j;
		// acrescenta 1 espaço após cada palavra
		// após ADDR+OFFSET deve acrescentar
		//		2*WORD_SIZE+1-2*ADDR_OFFSET_SIZE-5 (5 é o tamanho de "ADDR+")
		ofp << string(2*WORD_SIZE+1-2*ADDR_OFFSET_SIZE-5,' ');
    }
    ofp << endl;
	ofp << string(2*ADDR_SIZE + ADDR_COL_SPACE-1+WORDS_PER_LINE*(2*WORD_SIZE+1),'-');
	ofp	<< endl;

    // data
#define ELF_LINE_SIZE (WORD_SIZE*WORDS_PER_LINE)
    i=0;
	unsigned short us = 0;
	//~ unsigned char *uData = (unsigned char*)memImpl->getData();
	string addrcolSpace = string(ADDR_COL_SPACE,' ');
	
	cout << hex;
    for (i = 0; i < filesize; i+=ELF_LINE_SIZE) {
        ofp << setw(2*ADDR_SIZE) << i << addrcolSpace;
        for (j=0; j<WORDS_PER_LINE; j++) {
			for (int k=0; k<WORD_SIZE; k+=2) {
					
				us = ((unsigned short)uData[i+(WORD_SIZE*j)+k]) << 8;
/* 				if (i == 0x40) {
					cout << "us = " << us << endl;
				}
 */				us = us | ((unsigned short)uData[i+(WORD_SIZE*j)+k+1]);
/* 				if (i == 0x40) {
					cout << "us2 = " << us << endl;
				}
 */				ofp << setw(4) << us;
			}
			ofp << " ";
        }
        ofp << endl;
    }
	
    cout << "Gerado arquivo " << filename << endl << endl;
    ofp.close();
}
