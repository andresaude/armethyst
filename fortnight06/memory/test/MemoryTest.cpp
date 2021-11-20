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
#include "MemoryTest.h"
#include "BasicMemory.h"

#include <iostream>
#include <iomanip>

using namespace std;

MemoryTest::MemoryTest(Memory *mem)
{
	memImpl = mem;
    memLogStream.open(MEMORY_LOG_FILE);
}

MemoryTest::~MemoryTest()
{
	delete[] memImpl;
	memLogStream.close();
}

/**
 * Retorna o ponteiro para o início da memória.
 */
char *MemoryTest::getData() {
	return memImpl->getData();
}

/**
 * Log de memImpl->readInstruction32(long address)
 */
uint32_t MemoryTest::readInstruction32(uint64_t address)
{
    memLogStream << hex << "ri " << setfill('0') << setw(16) << address << endl;
 	return memImpl->readInstruction32(address);
}

/**
 * Log de memImpl->readData32(uint64_t address)
 */
uint32_t MemoryTest::readData32(uint64_t address)
{
    memLogStream << hex << "rd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_READ32;
 	return memImpl->readData32(address);
}

/**
 * Log de memImpl->readData64(uint64_t address)
 */
uint64_t MemoryTest::readData64(uint64_t address)
{
    memLogStream << hex << "rd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_READ64;
 	return memImpl->readData64(address);
}

/**
 * Log de memImpl->writeInstruction32(uint64_t address)
 */
void MemoryTest::writeInstruction32(uint64_t address, uint32_t value)
{
    memLogStream << hex << "wi " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_WRITE32;
 	memImpl->writeInstruction32(address, value);
}

/**
 * Log de memImpl->writeData32(uint64_t address)
 */
void MemoryTest::writeData32(uint64_t address, uint32_t value)
{
    memLogStream << hex << "wd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_WRITE32;
 	memImpl->writeData32(address, value);
}

/**
 * Log de memImpl->writeData64(uint64_t address)
 */
void MemoryTest::writeData64(uint64_t address, uint64_t value)
{
    memLogStream << hex << "wd " << setfill('0') << setw(16) << address << endl;
	lastDataMemAccess = MemAccessType::MAT_WRITE64;
 	memImpl->writeData64(address, value);
}

MemoryTest::MemAccessType MemoryTest::getLastDataMemAccess() {
	return lastDataMemAccess;
}

void MemoryTest::resetLastDataMemAccess() {
	lastDataMemAccess = MemAccessType::MAT_NONE;
}

/**
 * Realoca endereços das variáveis.
 * 
 * Específico para o arquivo de teste usado.
 */
void MemoryTest::relocateManual() {
	unsigned int *uiData = (unsigned int *)memImpl->getData();
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

 
