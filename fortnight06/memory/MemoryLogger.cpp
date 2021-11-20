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

//~ #pragma once

#include "MemoryLogger.h"

#include <iomanip>

using namespace std;

/**
 * Creates a MemoryLogger that writs do file MEMORY_LOG_FILE defined in config.h.
 */
MemoryLogger::MemoryLogger() : MemoryLogger(MEMORY_LOG_FILE) {}
	
/**
 * Creates a MemoryLogger that writs do 'filename'.
 */
MemoryLogger::MemoryLogger(string logfilename) {
    memLogStream.open(logfilename);
    
    // header
    memLogStream << left << setfill(' ') << setw(16)  << "ACCESS_TYPE ";
    memLogStream << setw(16)  << "ADDRESS ";
    memLogStream << right << setw(12)  << " HIT_LEVEL" << endl;
}

MemoryLogger::~MemoryLogger() {
	memLogStream.close();
}	
	

void MemoryLogger::memlog(AccessType type, uint64_t address, int hitLevel) {
	string strAccessType[5] = {"READI", "READ32", "READ64", "WRITE32", "WRITE64"};
    memLogStream << left << setfill(' ') << setw(16)  << strAccessType[type];
    memLogStream << hex << right << setfill('0') << setw(16) << address << " ";
    memLogStream << setfill(' ') << setw(11) << hitLevel << endl;
}
