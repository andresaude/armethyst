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
#include "Util.h"

using namespace std;

int TestCase04::run() {
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test04(cpu, memory, TEST_FILE_04);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}


/**
 * Testa as instruções aritméticas de float de fpops.S.
 */
void TestCase04::test04(BasicCPUTest* cpu, MemoryTest* memory, string fname)
{
	TEST_HEADER
	
	float fA = -0.7;
	float fB = 0.5;

	//
	// Test fneg s1, s0 (linha 40)
	// implementado como s1 = 0 - s0
	//
	fpOp = true;
	instruction = "fneg s1, s0";
	startAddress = 0x78; // endereço da instrução
	xpctdIR = 0x1E214001;
	xpctdA = 0;
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(-fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
	
	
	//
	// Test fdiv s1, s1, s0 (linha 43)
	//
	fpOp = true;
	instruction = "fdiv s1, s1, s0";
	startAddress = 0x84; // endereço da instrução
	xpctdIR = 0x1E201821;
	xpctdA = Util::floatAsUint64Low(fA); // valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::DIV;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA/fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
	
	//
	// Test fmul s1, s1, s0 (linha 52)
	//
	fpOp = true;
	instruction = "fmul s1, s1, s0";
	startAddress = 0xA4; // endereço da instrução
	xpctdIR = 0x1E200821;
	xpctdA = Util::floatAsUint64Low(fA); // valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::MUL;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA*fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();

}
