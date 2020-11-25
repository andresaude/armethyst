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

#include "BasicCPUTest.h"

/**
 * Start PC without executing machine cycles.
 */
BasicCPUTest::BasicCPUTest(Memory *memory)
	: BasicCPU(memory)
{
}
	
void BasicCPUTest::setSP(uint64_t address) {
	SP = address;
}

void BasicCPUTest::resetFlags() {
	ALUctrl = ALUctrlFlag::ALU_UNDEF;
	fpOp = FPOpFlag::FP_UNDEF;
	MEMctrl = MEMctrlFlag::MEM_UNDEF;
	WBctrl = WBctrlFlag::WB_UNDEF;
}
	
uint32_t BasicCPUTest::getIR() {
	return IR;
}

void BasicCPUTest::setW(int n, uint32_t value) {
	BasicCPU::setW(n,value);
}

void BasicCPUTest::setX(int n, uint64_t value) {
	BasicCPU::setX(n,value);
}

void BasicCPUTest::setS(int n, float value) {
	BasicCPU::setS(n,value);
}

uint64_t BasicCPUTest::getA() {
	return A;
}

uint64_t BasicCPUTest::getB() {
	return B;
}

ALUctrlFlag BasicCPUTest::getALUctrl() {
	return ALUctrl;
}
	
MEMctrlFlag BasicCPUTest::getMEMctrl() {
	return MEMctrl;
}
	
WBctrlFlag BasicCPUTest::getWBctrl() {
	return WBctrl;
}
	
uint64_t BasicCPUTest::getALUout() {
	return ALUout;
}

uint64_t BasicCPUTest::getMDR() {
	return MDR;
}

void BasicCPUTest::runIF() {
	IF();
}

int BasicCPUTest::runID() {
	return ID();
}

int BasicCPUTest::runEXF() {
	return EXF();
}

int BasicCPUTest::runEXI() {
	return EXI();
}

int BasicCPUTest::runMEM() {
	return MEM();
}

int BasicCPUTest::runWB() {
	return WB();
}

uint64_t BasicCPUTest::getRd() {
	return *Rd;
}
