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

#include "BasicMemory.h"

#include <iostream>
#include <iomanip>

using namespace std;

BasicMemory::BasicMemory(int size)
{
	data = new char[size];
}

BasicMemory::~BasicMemory()
{
	delete[] data;
}

/**
 * Lê uma instrução de 32 bits considerando um endereçamento em bytes.
 *
 * BasicMemory.cpp implementa a arquitetura de Von Neumman, com apenas uma
 * memória, que armazena instruções e dados.
 */
uint32_t BasicMemory::readInstruction32(uint64_t address)
{
	return ((uint32_t*)data)[address >> 2];
}

/**
 * Lê um dado de 32 bits considerando um endereçamento em bytes.
 */
int BasicMemory::readData32(unsigned long address)
{
	return ((int*)data)[address >> 2];
}

/**
 * Lê um dado de 64 bits considerando um endereçamento em bytes.
 */
long BasicMemory::readData64(unsigned long address)
{
	return ((long*)data)[address >> 3];
}

/**
 * Escreve um dado (value) de 32 bits considerando um endereçamento em bytes.
 */
void BasicMemory::writeData32(unsigned long address, int value)
{
	((int*)data)[address >> 2] = value;
}

/**
 * Escreve um dado (value) de 64 bits considerando um endereçamento em bytes.
 */
void BasicMemory::writeData64(unsigned long address, long value)
{
	((long*)data)[address >> 3] = value;
}

/**
 * carrega arquivo binário na memória
 */
void BasicMemory::loadBinary(string filename)
{
    streampos size;

    ifstream file(filename, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        fileSize = file.tellg();
        file.seekg (0, ios::beg);
        file.read (data, fileSize);
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
		cout << "Aborting... " << endl;
		exit(1);
    }

}


/**
 * Escreve arquivo binario em um arquivo legível
 */
#define LINE_SIZE 4
void BasicMemory::writeBinaryAsText (string basename) {
    string filename = "txt_" + basename + ".txt";
    ofstream ofp;
    int i,j;

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
    for (i = 0; i < fileSize / 4; i+=LINE_SIZE) {
        ofp << setw(4) << 4*i << "    ";
        for (j=0; j<LINE_SIZE; j++) {
            ofp << setw(8) << ((unsigned int *)data)[i+j] << " ";
        }
        ofp << endl;
    }
    ofp.close();
}
