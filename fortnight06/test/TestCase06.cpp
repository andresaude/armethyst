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
#include "Processor.h"
#include "Factory.h"

using namespace std;

int TestCase06::run() {
	
	// TODO aqui não é basic memory
	throw "not implemented";
	
	
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test06(cpu, memory, TEST_FILE_06);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}

/**
 * Testa a hierarquia de cache do Corei7Memory com o arquivo isummationLarge.o.
 * 
 * Simplesmente roda o processador para que possa ser verificado manualmente o log
 * de acesso à memória.
 */
void TestCase06::test06(BasicCPUTest* cpu, MemoryTest* memory, string fname)
{
	
	cout << "##################\n# " + fname + "\n##################\n\n\n";
	
	// (EN) create processor
	// (PT) cria processador
	Processor* processor = Factory::createProcessor(memory);
		
	// (EN) start processor
	// (PT) inicia processador
	processor->run(STARTADDRESS);
}

