/* ----------------------------------------------------------------------------

    (EN) BasicCPUTest - test class for BasicCPU. Allows access to registers
	and protected methods.
		
	armethyst - A simple ARM Simulator written in C++ for Computer Architecture
    teaching purposes. Free software licensed under the MIT License (see license
    below).

    (PT) BasicCPUTest - classe de teste de BasicCPU. Permite acesso aos
	registradores e métodos protegidos.
    
	armethyst - Um simulador ARM simples escrito em C++ para o ensino de
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

#pragma once

#include "BasicCPU.h"
#include "Memory.h"

class BasicCPUTest: public BasicCPU
{
	public:
		BasicCPUTest(Memory *memory);
		
		// registers
		void setSP(uint64_t address);
		void setW(int n, uint32_t value);
		void setX(int n, uint64_t value);
		void setS(int n, float value);

		// flags
		void resetFlags();

		// IF
		uint32_t getIR();
		void runIF();
		
		// ID
		int runID();
		ALUctrlFlag getALUctrl();
		MEMctrlFlag getMEMctrl();
		WBctrlFlag getWBctrl();
		uint64_t getA();
		uint64_t getB();

		// EX
		int runEXF();
		int runEXI();
		uint64_t getALUout();
		
		// MEM
		int runMEM();
 		uint64_t getMDR();
		
		// WB
		int runWB();
		uint64_t getRd();
		
};
