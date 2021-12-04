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
#include "Util.h"

#include <iostream>

#include "BasicMemory.h"

using namespace std;

int TestCase02::run() {
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test02(cpu, memory, TEST_FILE_02);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}

/**
 * Testa as instruções fadd e fsub do arquivo fpops.S.
 */
void TestCase02::test02(BasicCPUTest* cpu, MemoryTest* memory, string fname)
{
	float fA = -0.7;
	float fB = 0.5;

	TEST_HEADER

	//
	// Test SUB
	//
	instruction = "sub sp, sp, #32";
	startAddress = 0x40; // endereço de 'sub sp, sp, #32'
	xpctdIR = 0xD10083FF;
	xpctdA = STARTSP; // SP deve ser lido para A
	xpctdB = 32; 	 // valor imediato da instrução sub
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA - xpctdB;
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test FSUB (linha 45)
	//
	fpOp = true;
	instruction = "fsub	s0, s1, s0";
	startAddress = 0x8C; // endereço de 'fsub	s0, s1, s0'
	xpctdIR = 0x1E203820;
	xpctdA = Util::floatAsUint64Low(fA);	// valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA-fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test FADD (linha 58)
	//
	fpOp = true;
	instruction = "fadd s1, s1, s0";
	startAddress = 0xBC; // endereço de 'fadd	s1, s1, s0'
	xpctdIR = 0x1E202821;
	xpctdA = Util::floatAsUint64Low(fA);	// valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA+fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
}

