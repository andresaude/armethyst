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

#include "config.h"

#include "Memory.h"
#include "BasicCPUTest.h"

#include <iostream>
#include <iomanip>

using namespace std;

#define STARTSP 0x10000000 // endereço inicial da pilha

void test(BasicCPUTest* cpu);
void test(BasicCPUTest* cpu,
			long startAddress,
			long startSP,
			int expectedIR,
			int expectedA,
			int expectedB,
			ALUctrlFlag expectedALUctrl,
			long expectedALUout);

int main()
{	
	// (EN) create memory
	// (PT) cria memória
	Memory* memory = new Memory(MEMORY_SIZE);
	
	// (EN) create CPU
	// (PT) cria CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
		
	// (EN) load executable binary
	// (PT) carrega binário executável
	memory->loadBinary(FILENAME);
	
	// (EN) create human readable representation of the binary file
	// (PT) cria representação legível do arquivo binário
	memory->writeBinaryAsText(FILENAME);

	// Teste:
	//		Como não temos o caminho de dados completo, faremos apenas testes.
	test(cpu);
	
	return 0;
}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para as instruções 'sub sp, sp, #16' e 'add w1, w1, w0'.
 */
void test(BasicCPUTest* cpu)
{
	long startAddress;
	long startSP = STARTSP;
	int expectedIR;
	long expectedA;
	long expectedB;
	ALUctrlFlag expectedALUctrl;
	long expectedALUout;
	
	//
	// Test SUB
	//
	cout << "#\n#\n#\n# Testando 'sub sp, sp, #16'...\n#\n#\n#\n" << endl;
	startAddress = 0x40; // endereço de 'sub sp, sp, #16'
	expectedIR = 0xD10043FF;
	expectedA = STARTSP; // SP deve ser lido para A
	expectedB = 16; 	 // valor imediato da instrução sub
	expectedALUctrl = ALUctrlFlag::SUB;
	expectedALUout = expectedA - expectedB;
	test(cpu,startAddress,startSP,
		expectedIR,expectedA,expectedB,expectedALUctrl,expectedALUout);
	cout << "Fim 'sub sp, sp, #16'." << endl << endl << endl;

	//
	// Test ADD
	//
	cout << "#\n#\n#\n# Testando 'add w1, w1, w0'...\n#\n#\n#\n" << endl;
	startAddress = 0x74; // endereço de 'add w1, w1, w0'
	expectedIR = 0x0B000021;
	expectedA = 7; 			// valor arbitrário para w1
	cpu->setW(1,expectedA); // temos que fazer w1 valer expectedA
	expectedB = 16; 		// valor arbitrário para w0
	cpu->setW(0,expectedB); // temos que fazer w1 valer expectedB
	expectedALUctrl = ALUctrlFlag::ADD;
	expectedALUout = expectedA + expectedB;
	test(cpu,startAddress,startSP,
		expectedIR,expectedA,expectedB,expectedALUctrl,expectedALUout);
	cout << "Fim 'add w1, w1, w0'." << endl << endl << endl;


}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para a instrução 'sub sp, sp, #16'.
 */
void test(BasicCPUTest* cpu,
			long startAddress,
			long startSP,
			int expectedIR,
			int expectedA,
			int expectedB,
			ALUctrlFlag expectedALUctrl,
			long expectedALUout)
{
	
	// saídas em hexadecimal
	cout << hex;	
	
	cout << "Iniciando processador..." << endl;
	cout << "	PC: 0x" << startAddress << endl;
	cout << "	SP: 0x" << startSP << endl;
	cpu->run(startAddress);
	cpu->setSP(startSP);
	cout << "processor iniciado." << endl << endl;
	
	//
	// Testa IF
	//
	cout << "Testando IF..." << endl;
	
	// executa
	cpu->runIF();
	cout << "	IR=0x" << cpu->getIR()
			<< ";  Esperado IR=0x" << expectedIR << endl;
	
	// verifica
	if (cpu->getIR() != expectedIR) {
		cout << "IF() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "IF() passou no teste!" << endl << endl;

	//
	// Testa ID (depende do sucesso no teste de IF)
	//
	cout << "Testando ID..." << endl;
	
	// executa
	int iderror = cpu->runID();
	
	// verifica se a instrução está implementada
	if (iderror) {
		cout << "Instrução não implementada: 0x" << expectedIR << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	// verifica leitura de registradores
	long A = cpu->getA();
	long B = cpu->getB();
	cout << "	A=0x" << A << "; B=0x" << B << endl;
	cout << "Esperados: A=0x" << expectedA << "; B=0x" << expectedB << endl;
	if ((A != expectedA) || (B != expectedB)){
		cout << "ID() FALHOU na leitura de registradores!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de leitura de registradores!" << endl << endl;

	// verifica ALUctrl
	ALUctrlFlag ALUctrl = cpu->getALUctrl();
	cout << "	ALUctrl=0x" << ALUctrl << "; Esperado ALUctrl=0x"
			<< expectedALUctrl << endl;
	if (ALUctrl != expectedALUctrl)
	{
		cout << "ID() FALHOU no set do controle da ULA!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de set do controle da ULA!" << endl << endl;

	//
	// Testa EXI (depende do sucesso no teste de ID)
	//
	cout << "Testando EXI..." << endl;
	
	// executa
	int exierror = cpu->runEXI();
	if (exierror) {
		cout << "Controle não implementado: 0x" << cpu->getALUctrl() << endl;
		cout << "EXI() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}
	
	// verifica ALUout
	long ALUout = cpu->getALUout();
	cout << "	ALUout=0x"
			<< setfill('0') << setw(8) << ALUout
			<< "; Esperado ALUout=0x"
			<< setfill('0') << setw(8) << expectedALUout << endl;
	if (ALUout != expectedALUout)
	{
		cout << "EXI() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}
	
	cout << "EXI() passou no teste!" << endl;
	
	cout << "SUCESSO!" << endl;
	
}
