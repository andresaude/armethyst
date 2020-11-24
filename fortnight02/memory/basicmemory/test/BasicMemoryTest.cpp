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
#include "BasicMemoryTest.h"

#include <iostream>
#include <iomanip>

using namespace std;

BasicMemoryTest::BasicMemoryTest(int size) : BasicMemory{size}
{
    memLogStream.open(MEMORY_LOG_FILE);
}
BasicMemoryTest::~BasicMemoryTest()
{
	memLogStream.close();
}

/**
 * Log de Memory::readInstruction32(long address)
 */
uint32_t BasicMemoryTest::readInstruction32(uint64_t address)
{
    memLogStream << hex << "ri " << setfill('0') << setw(16) << address << endl;
 	return BasicMemory::readInstruction32(address);
}

/**
 * Log de Memory::readData32(long address)
 */
int BasicMemoryTest::readData32(unsigned long address)
{
    memLogStream << hex << "rd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_READ32;
 	return BasicMemory::readData32(address);
}

/**
 * Log de Memory::readData64(long address)
 */
long BasicMemoryTest::readData64(unsigned long address)
{
    memLogStream << hex << "rd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_READ64;
 	return BasicMemory::readData64(address);
}

/**
 * Log de Memory::writeData32(long address)
 */
void BasicMemoryTest::writeData32(unsigned long address, int value)
{
    memLogStream << hex << "wd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_WRITE32;
 	BasicMemory::writeData32(address, value);
}

/**
 * Log de Memory::writeData64(long address)
 */
void BasicMemoryTest::writeData64(unsigned long address, long value)
{
    memLogStream << hex << "wd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_WRITE64;
 	BasicMemory::writeData64(address, value);
}

BasicMemoryTest::MemAccessType BasicMemoryTest::getLastDataMemAccess() {
	return lastDataMemAccess;
}

void BasicMemoryTest::resetLastDataMemAccess() {
	lastDataMemAccess = MemAccessType::MAT_NONE;
}

/**
 * Escreve arquivo binario byte a byte
 */
#define ADDR_SIZE 2
#define ADDR_OFFSET_SIZE 1
#define ADDR_COL_SPACE 4
#define WORD_SIZE 4
#define WORDS_PER_LINE 4
void BasicMemoryTest::writeBinaryAsTextELF (string basename) {
    string filename = "elf_" + basename + ".txt";
    ofstream ofp;
    int i,j;

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
	unsigned char *uData = (unsigned char*)data;
	string addrcolSpace = string(ADDR_COL_SPACE,' ');
	
	cout << hex;
    for (i = 0; i < fileSize; i+=ELF_LINE_SIZE) {
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

/**
 * Realoca endereços das variáveis.
 * 
 * Específico para o arquivo de teste usado.
 */
void BasicMemoryTest::relocateManual() {
	unsigned int *uiData = (unsigned int *)data;
	long address;
	unsigned int instruction;
	
	//0x0050		91000000		fazer | 0x00028000
	address = 0x50>>2;
	instruction = uiData[address];
	uiData[address] = instruction | 0x00027000;
	
	//0x0060		91000000		fazer | 0x00027000
	address = 0x60>>2;
	instruction = uiData[address];
	uiData[address] = instruction | 0x00028000;

	//0x0070		91000000		fazer | 0x00027000
	address = 0x70>>2;
	instruction = uiData[address];
	uiData[address] = instruction | 0x00028000;
}

 
