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
#include "TestCase.h"

#include <iostream>

#include "BasicMemory.h"

using namespace std;

int TestCase01::run() {
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test01(cpu, memory, TEST_FILE_01);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}

/**
 * Testa as instruções 'sub sp, sp, #16' e 'add w1, w1, w0' do
 * arquivo isummation.S.
 */
void TestCase01::test01(BasicCPUTest* cpu, MemoryTest* memory, string fname)
{

	TEST_HEADER
	
	//
	// Test SUB
	//
	instruction = "sub sp, sp, #16";
	startAddress = 0x40; // endereço de 'sub sp, sp, #16'
	xpctdIR = 0xD10043FF;
	xpctdA = STARTSP; // SP deve ser lido para A
	xpctdB = 16; 	 // valor imediato da instrução sub
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA - xpctdB;
	
	xpctdRd = xpctdALUout;
	
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test ADD (linha 43)
	//
	instruction = "add w1, w1, w0";
	startAddress = 0x68; // endereço de 'add w1, w1, w0'
	xpctdIR = 0x0B000021;
	xpctdA = 7; 			// valor arbitrário para w1
	xpctdB = 16; 		// valor arbitrário para w0
	cpu->setW(1,xpctdA); // temos que fazer w1 valer xpctdA
	cpu->setW(0,xpctdB); // temos que fazer w0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = xpctdALUout;

	CALLTEST();
	RESETTEST();
}

