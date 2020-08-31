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

#include "SimpleMemoryTest.h"
#include "BasicCPUTest.h"

#include <iostream>
#include <iomanip>

using namespace std;

#define STARTSP 0x1000 // endereço inicial da pilha: 4096

#define CALLTEST() test(instruction,cpu,memory,startAddress,startSP,xpctdIR,xpctdA,xpctdB,xpctdALUctrl,xpctdMEMctrl,xpctdWBctrl,xpctdALUout,xpctdMDR,xpctdRd)

#define RESETTEST()	startAddress=-1;xpctdIR=-1;xpctdA=-1;xpctdB=-1;xpctdALUctrl=ALUctrlFlag::ALU_UNDEF;xpctdALUout=-1;xpctdMEMctrl=MEMctrlFlag::MEM_UNDEF;xpctdMDR=-1;xpctdWBctrl=WBctrlFlag::WB_UNDEF;xpctdRd=-1;cpu->resetFlags();memory->resetLastDataMemAccess();

void test(BasicCPUTest* cpu, SimpleMemoryTest* memory);
void test(string instruction,
			BasicCPUTest* cpu,
			SimpleMemoryTest* memory,
			long startAddress,
			long startSP,
			int xpctdIR,
			int xpctdA,
			int xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl,
			long xpctdALUout,
			long xpctdMDR,
			long xpctdRd);

int main()
{	
	// (EN) create memory
	// (PT) cria memória
	SimpleMemoryTest* memory = new SimpleMemoryTest(MEMORY_SIZE);
	
	// (EN) create CPU
	// (PT) cria CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
		
	// (EN) load executable binary
	// (PT) carrega binário executável
	memory->loadBinary(FILENAME);
	memory->relocateManual();
	
	// (EN) create human readable representation of the binary file
	// (PT) cria representação legível do arquivo binário
	memory->writeBinaryAsText(FILENAME);

	// (EN) create human readable representation of the binary file
	// (PT) cria representação legível do arquivo binário
	memory->writeBinaryAsTextELF(FILENAME);
	
	// Teste:
	//		Como não temos o caminho de dados completo, faremos apenas testes.
	test(cpu, memory);
	
	return 0;
}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para as instruções 'sub sp, sp, #16' e 'add w1, w1, w0'.
 */
void test(BasicCPUTest* cpu, SimpleMemoryTest* memory)
{
	string instruction;

	long startAddress;
	long startSP = STARTSP;

	int xpctdIR;

	long xpctdA;
	long xpctdB;
	ALUctrlFlag xpctdALUctrl;
	MEMctrlFlag xpctdMEMctrl;
	WBctrlFlag xpctdWBctrl;

	long xpctdALUout;

	long xpctdMDR;

	long xpctdRd;

	RESETTEST();
	
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
	cpu->setW(0,xpctdB); // temos que fazer w1 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = xpctdALUout;

	CALLTEST();
	RESETTEST();


	//
	// Test ldrsw x1, [sp, 12] (linha 38)
	//
	instruction = "ldrsw x1, [sp, 12]";
	startAddress = 0x54; 	// endereço de 'ldrsw x1, [sp, 12]'
	xpctdIR = 0xB9800FE1;
	xpctdA = STARTSP; 		// SP deve ser lido para A
	xpctdB = 12;			// valor imediato do offset
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ64;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 2;
	memory->writeData64(xpctdALUout, STARTSP << 2);

	CALLTEST();
	RESETTEST();
	
	
	//
	// Test ldr w0, [sp, 12] (linha 51)
	//
	instruction = "ldr w0, [sp, 12]";
	startAddress = 0x84; 	// endereço da linha
	xpctdIR = 0xB9400FE0;
	xpctdA = STARTSP; 		// SP deve ser lido para A
	xpctdB = 12;			// valor imediato do offset
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 2;
	memory->writeData32(xpctdALUout, STARTSP << 2);

	CALLTEST();
	RESETTEST();



	//
	// Test ldr w0, [x0] (linha 42)
	//
	instruction = "ldr w0, [x0]";
	startAddress = 0x64; 	// endereço da linha
	xpctdIR = 0xB9400000;	
	xpctdA = 0x800; 		// valor arbitrário para x0
	xpctdB = 0;
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 3;
	memory->writeData32(xpctdALUout, STARTSP << 3);

	CALLTEST();
	RESETTEST();




	//
	// Test str w1, [x0] (linha 46)
	//
	instruction = "str w1, [x0]";
	startAddress = 0x74; 	// endereço da instrução
	xpctdIR = 0xB9000001;
	xpctdA = 0x800; 		// valor arbitrário para x0
	xpctdB = 0;
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	cpu->setW(1,0x77);		// valor arbitrário para w1
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::WRITE32;
	xpctdWBctrl = WBctrlFlag::WB_NONE;
	
	xpctdALUout = xpctdA + xpctdB;

	CALLTEST();
	RESETTEST();


	//
	// Test str w0, [sp, 12] (linha 49)
	//
	instruction = "str w0, [sp, 12]";
	startAddress = 0x80; 	// endereço da instrução
	xpctdIR = 0xB9000FE0;
	xpctdA = STARTSP; 		// valor arbitrário para x0
	xpctdB = 12;
	cpu->setW(0,0x12345);		// valor arbitrário para w1
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::WRITE32;
	xpctdWBctrl = WBctrlFlag::WB_NONE;

	xpctdALUout = xpctdA + xpctdB;

	CALLTEST();
	RESETTEST();


	
	//
	// Test ldr w1, [x0, x1, lsl 2] (linha 39)
	//
	instruction = "ldr w1, [x0, x1, lsl 2]";
	startAddress = 0x58; 	// endereço da linha
	xpctdIR = 0xB8617801;	
	xpctdA = 0x800; 		// valor arbitrário para x0
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	xpctdB = 0x7; 			// valor arbitrário para x1
	cpu->setX(1,xpctdB);	// temos que fazer x1 valer xpctdA
	xpctdB = xpctdB << 2; 	// aplicando lsl 2
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP >> 2;
	memory->writeData32(xpctdALUout, STARTSP >> 2);

	CALLTEST();
	RESETTEST();

	

}

/**
 * Testa o estágio IF.
 */
void testIF(BasicCPUTest* cpu, int xpctdIR)
{
	//
	// Testa IF
	//
	cout << "Testando IF..." << endl;
	
	// executa
	cpu->runIF();
	cout << "	IR=0x" << cpu->getIR()
			<< ";  Esperado IR=0x" << xpctdIR << endl;
	
	// verifica
	if (cpu->getIR() != xpctdIR) {
		cout << "IF() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "IF() passou no teste!" << endl << endl;
}

/**
 * Testa o estágio ID.
 */
void testID(BasicCPUTest* cpu,
			int xpctdIR,
			int xpctdA,
			int xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl)
{
	//
	// Testa ID (depende do sucesso no teste de IF)
	//
	cout << "Testando ID..." << endl;
	
	// executa
	int iderror = cpu->runID();
	
	// verifica se a instrução está implementada
	if (iderror) {
		cout << "Instrução não implementada: 0x" << xpctdIR << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	// verifica leitura de registradores
	long A = cpu->getA();
	long B = cpu->getB();
	cout << "	A=0x" << A << "; B=0x" << B << endl;
	cout << "Esperados: A=0x" << xpctdA << "; B=0x" << xpctdB << endl;
	if ((A != xpctdA) || (B != xpctdB)){
		cout << "ID() FALHOU na leitura de registradores!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de leitura de registradores!" << endl << endl;

	// verifica ALUctrl
	ALUctrlFlag ALUctrl = cpu->getALUctrl();
	cout << "	ALUctrl=0x" << ALUctrl << "; Esperado ALUctrl=0x"
			<< xpctdALUctrl << endl;
	if (ALUctrl != xpctdALUctrl)
	{
		cout << "ID() FALHOU no set do controle da ULA!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de set do controle da ULA!" << endl << endl;

	// verifica MEMctrl
	MEMctrlFlag MEMctrl = cpu->getMEMctrl();
	cout << "	MEMctrl=0x" << MEMctrl << "; Esperado MEMctrl=0x"
			<< xpctdMEMctrl << endl;
	if (MEMctrl != xpctdMEMctrl)
	{
		cout << "ID() FALHOU no set do controle de MEM!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de set do controle de MEM!" << endl << endl;

	// verifica WBctrl
	WBctrlFlag WBctrl = cpu->getWBctrl();
	cout << "	WBctrl=0x" << WBctrl << "; Esperado WBctrl=0x"
			<< xpctdWBctrl << endl;
	if (WBctrl != xpctdWBctrl)
	{
		cout << "ID() FALHOU no set do controle de WB!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}

	cout << "ID() passou no teste de set do controle de WB!" << endl << endl;

	cout << "ID() passou nos testes de set dos controles da ULA, MEM e WB!" << endl << endl;
}

/**
 * Testa o estágio EXI.
 */
void testEXI(BasicCPUTest* cpu, long xpctdALUout)
{
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
			<< setfill('0') << setw(8) << xpctdALUout << endl;
	if (ALUout != xpctdALUout)
	{
		cout << "EXI() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}
	
	cout << "EXI() passou no teste!" << endl;
}

/**
 * Testa o estágio MEM - NAO IMPLEMENTADO.
 */
void testMEM(BasicCPUTest* cpu,
				SimpleMemoryTest* memory,
				MEMctrlFlag xpctdMEMctrl,
				long xpctdALUout)
{
	//
	// Test MEM (depends on the success of previous stages)
	//
	cout << "Testing MEM..." << endl;
	
	// executa
	int memerror = cpu->runMEM();
	if (memerror) {
		cout << "Controle não implementado: 0x" << cpu->getMEMctrl() << endl;
		cout << "MEM() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}
		
	//
	// Test access type
	//
	
	// map MEMctrlFlag to SimpleMemoryTest::MemAccessType
	SimpleMemoryTest::MemAccessType xpctdLastDataMemAccess;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::MEM_NONE:
			xpctdLastDataMemAccess = SimpleMemoryTest::MemAccessType::MAT_NONE;
			break;
		case MEMctrlFlag::READ32:
			xpctdLastDataMemAccess = SimpleMemoryTest::MemAccessType::MAT_READ32;
			break;
		case MEMctrlFlag::READ64:
			xpctdLastDataMemAccess = SimpleMemoryTest::MemAccessType::MAT_READ64;
			break;
		case MEMctrlFlag::WRITE32:
			xpctdLastDataMemAccess = SimpleMemoryTest::MemAccessType::MAT_WRITE32;
			break;
		case MEMctrlFlag::WRITE64:
			xpctdLastDataMemAccess = SimpleMemoryTest::MemAccessType::MAT_WRITE64;
			break;
	}

	SimpleMemoryTest::MemAccessType lastDataMemAccess =
			memory->getLastDataMemAccess();
	cout << "	Testing MEM access type..." << endl;
	cout << "		Expected access type: "
			<< xpctdLastDataMemAccess << endl;
	cout << "		Executed access type: "
			<< lastDataMemAccess << endl;
	if (xpctdLastDataMemAccess != lastDataMemAccess) {
		// incorrect memory access type
		cout << "MEM() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	} else {
		cout << "	MEM() executed the correct access type!" << endl;
	}

	//
	// Test content
	//
	
	// no memory access -> success
	if (xpctdMEMctrl == MEMctrlFlag::MEM_NONE) {
		cout << "	No content to be tested!" << endl;
		cout << "MEM() test: SUCCESS!" << endl;
		return;
	}
	
	// get read or written content (access depends on 32 or 64 bit mode)
	long memData, xpctdMemData;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::READ32:
			cout << "	READ Mode: testing read content..." << endl;
			memData = (long)memory->readData32(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::READ64:
			cout << "	READ Mode: testing read content..." << endl;
			memData = memory->readData64(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::WRITE32:
			cout << "	WRITE Mode: testing written content..." << endl;
			memData = (long)memory->readData32(xpctdALUout);
			xpctdMemData = cpu->getRd();
			break;
		case MEMctrlFlag::WRITE64:
			cout << "	WRITE Mode: testing written content..." << endl;
			memData = memory->readData64(xpctdALUout);
			xpctdMemData = cpu->getRd();
			break;
	}
	
	// memory content verbose
	cout << "		Expected memory content: 0x"	<< xpctdMemData << endl;
	cout << "		Effective memory content: 0x"	<< memData << endl;
	cout << "		Address tested: 0x" << xpctdALUout << endl;

	// finish content test
	if (memData == xpctdMemData) {
		cout << "	Memory content OK..." << endl;
		cout << "MEM() test: SUCCESS!" << endl;
		return;
	}
	
	// otherwise
	cout << "	Memory content FAILED..." << endl;
	cout << "MEM() FAILED!" << endl;
	exit(1);
}

/**
 * Testa o estágio WB.
 */
void testWB(BasicCPUTest* cpu,
		WBctrlFlag xpctdWBctrl,
		long xpctdRd)
{
	//
	// Testa WB (depende do sucesso nos testes de estágios anteriores)
	//
	cout << "Testando WB..." << endl;
	
	// executa
	int wberror = cpu->runWB();
	if (wberror) {
		cout << "Controle não implementado: 0x" << cpu->getWBctrl() << endl;
		cout << "WB() FALHOU!" << endl;
		cout << "Saindo..." << endl;
		exit(1);
	}
	
	bool ok = true;
	unsigned long Rd = cpu->getRd();
	if(xpctdWBctrl == WBctrlFlag::RegWrite)
	{
		cout << "	Rd=0x"
			<< setfill('0') << setw(8) << Rd
			<< "; Esperado xpctdRd=0x"
			<< setfill('0') << setw(8) << xpctdRd << endl;
			
		if (Rd != xpctdRd)
		{
			cout << "WB() FALHOU!" << endl;
			cout << "Saindo..." << endl;
			exit(1);
		}
	}
	
	cout << "WB() passou no teste!" << endl;
}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para a instrução 'sub sp, sp, #16'.
 */
void test(string instruction,
			BasicCPUTest* cpu,
			SimpleMemoryTest* memory,
			long startAddress,
			long startSP,
			int xpctdIR,
			int xpctdA,
			int xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl,
			long xpctdALUout,
			long xpctdMDR,
			long xpctdRd)
{
	
	cout << "#\n#\n#\n# Testing '" << instruction << "'...\n#\n#\n#\n" << endl;

	
	// saídas em hexadecimal
	cout << hex;	
	
	cout << "Iniciando processador..." << endl;
	cout << "	PC: 0x" << startAddress << endl;
	cout << "	SP: 0x" << startSP << endl;
	cpu->run(startAddress);
	cpu->setSP(startSP);
	cout << "processor iniciado." << endl << endl;
	
	testIF(cpu, xpctdIR);

	testID(cpu, xpctdIR, xpctdA, xpctdB, xpctdALUctrl,
			xpctdMEMctrl, xpctdWBctrl);
	
	testEXI(cpu, xpctdALUout);

	testMEM(cpu, memory, xpctdMEMctrl, xpctdALUout);
	
	testWB(cpu, xpctdWBctrl, xpctdRd);
	
	cout << "SUCESSO!" << endl;
	
	cout << "Fim '" << instruction << "'." << endl << endl << endl;
	
}

