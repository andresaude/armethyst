/* ----------------------------------------------------------------------------
	
	(EN) Processor - A single core processor with a basic CPU. Part or armethyst
	project.
	
    armethyst - A simple ARM Simulator written in C++ for Computer Architecture
    teaching purposes. Free software licensed under the MIT License (see license
    below).

	(PT) Processor - Um processador de núcleo único com uma CPU básica. Parte do
	projeto armethyst.
	
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

#include "MemoryLoader.h"

#include "BasicCPUTest.h"
#include "MemoryTest.h"

#define STARTSP 0x1000 // endereço inicial da pilha: 4096
#define TEST_FILE_01 "isummation.o"
#define TEST_FILE_02 "fpops.o"
#define TEST_FILE_03 "isummation.o"
#define TEST_FILE_04 "fpops.o"
#define TEST_FILE_05 "isummation.o"
#define TEST_FILE_06 "isummationLarge.o"

/*
 * Macros
 */
#define CALLTEST() test(fpOp,instruction,cpu,memory,startAddress,startSP,xpctdIR,xpctdA,xpctdB,xpctdALUctrl,xpctdMEMctrl,xpctdWBctrl,xpctdALUout,xpctdMDR,xpctdRd)

#define RESETTEST()	fpOp=false;startAddress=-1;xpctdIR=-1;xpctdA=-1;xpctdB=-1;xpctdALUctrl=ALUctrlFlag::ALU_UNDEF;xpctdALUout=-1;xpctdMEMctrl=MEMctrlFlag::MEM_UNDEF;xpctdMDR=-1;xpctdWBctrl=WBctrlFlag::WB_UNDEF;xpctdRd=-1;cpu->resetFlags();memory->resetLastDataMemAccess();

#define TEST_HEADER bool fpOp;\
		string instruction;\
		uint64_t startAddress;\
		uint64_t startSP = STARTSP;\
		uint32_t xpctdIR;\
		uint64_t xpctdA;\
		uint64_t xpctdB;\
		ALUctrlFlag xpctdALUctrl;\
		MEMctrlFlag xpctdMEMctrl;\
		WBctrlFlag xpctdWBctrl;\
		uint64_t xpctdALUout;\
		uint64_t xpctdMDR;\
		uint64_t xpctdRd;\
		RESETTEST();\
		memoryLoadReloc(memory, fname);\
		cout << "##################\n# " + fname + "\n##################\n\n\n";

/**
 * Classe básica de casos de teste. Cada caso de teste é implementado por uma
 * subclasse de nome TestCaseXX.
 */
class TestCase
{
	public:
		virtual int run() = 0;

	protected:
		void memoryLoadReloc (MemoryTest* memory, string fname);

		void test(
					bool fpOp,
					string instruction,
					BasicCPUTest* cpu,
					MemoryTest* memory,
					uint64_t startAddress,
					uint64_t startSP,
					uint32_t xpctdIR,
					uint64_t xpctdA,
					uint64_t xpctdB,
					ALUctrlFlag xpctdALUctrl,
					MEMctrlFlag xpctdMEMctrl,
					WBctrlFlag xpctdWBctrl,
					uint64_t xpctdALUout,
					uint64_t xpctdMDR,
					uint64_t xpctdRd);

		/**
		 * Testa o estágio IF.
		 */
		void testIF(BasicCPUTest* cpu, uint32_t xpctdIR);

		/**
		 * Testa o estágio ID.
		 */
		void testID(BasicCPUTest* cpu,
					uint32_t xpctdIR,
					uint64_t xpctdA,
					uint64_t xpctdB,
					ALUctrlFlag xpctdALUctrl,
					MEMctrlFlag xpctdMEMctrl,
					WBctrlFlag xpctdWBctrl);

		/**
		 * Testa o estágio EX.
		 */
		void testEX(BasicCPUTest* cpu, bool fpOp, uint64_t xpctdALUout);

		/**
		 * Testa o estágio MEM - NAO IMPLEMENTADO.
		 */
		void testMEM(BasicCPUTest* cpu,
						MemoryTest* memory,
						MEMctrlFlag xpctdMEMctrl,
						uint64_t xpctdALUout,
						uint64_t xpctdRd);

		/**
		 * Testa o estágio WB.
		 */
		void testWB(BasicCPUTest* cpu,
				WBctrlFlag xpctdWBctrl,
				uint64_t xpctdRd);

};

/**
 * Testa as instruções 'sub sp, sp, #16' e 'add w1, w1, w0' do
 * arquivo isummation.S.
 */
class TestCase01 : public TestCase
{
	public:
		int run();
	private:
		void test01(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};


/**
 * Testa as instruções fadd e fsub do arquivo fpops.S.
 */
class TestCase02 : public TestCase
{
	public:
		int run();
	private:
		void test02(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};

/**
 * Testa as instruções de load e store e instruções de branch do
 * arquivo isummation.S.
 */
class TestCase03 : public TestCase
{
	public:
		int run();
	private:
		void test03(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};

/**
 * Testa as instruções aritméticas de float de fpops.S.
 */
class TestCase04 : public TestCase
{
	public:
		int run();
	private:
		void test04(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};

/**
 * Testa apenas duas instruções de load e store do arquivo isummation.S.
 */
class TestCase05 : public TestCase
{
	public:
		int run();
	private:
		void test05(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};

/**
 * Testa a hierarquia de cache do Corei7Memory com o arquivo isummationLarge.o.
 * 
 * Simplesmente roda o processador para que possa ser verificado manualmente o log
 * de acesso à memória.
 */
class TestCase06 : public TestCase
{
	public:
		int run();
	private:
		void test06(BasicCPUTest* cpu, MemoryTest* memory, string fname);
};
