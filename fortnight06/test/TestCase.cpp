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
#include <iomanip>

/**
 * Carrega arquivo na memória e reloca endereços de variáveis.
 */
void TestCase::memoryLoadReloc (MemoryTest* memory, string fname)
{
	// load executable binary
	MemoryLoader loader{memory, fname};

	// Relocate
	memory->relocateManual();
	
	// create human readable representation of the binary file
	loader.writeBinaryAsText(fname);

	// create human readable representation of the binary file
	loader.writeBinaryAsTextELF(fname);
}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para a instrução 'sub sp, sp, #16'.
 */
void TestCase::test(
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
			uint64_t xpctdRd)
{
	cout << "#\n#\n#\n# Testing '" << instruction << "'...\n#\n#\n#\n" << endl;

	cout << "\n\nTEST_LEVEL: Starting processor...\n\n" << endl;
	
	// saídas em hexadecimal
	cout << hex;
	
	cout << "Starting processor..." << endl;
	cout << "	PC: 0x" << startAddress << endl;
	cout << "	SP: 0x" << startSP << endl;
	cpu->run(startAddress);
	cpu->setSP(startSP);
	cout << "processor started!." << endl << endl;

	if (TEST_LEVEL > TEST_LEVEL_START)
	{
		cout << "\n\nTEST_LEVEL: IF\n\n" << endl;
		testIF(cpu, xpctdIR);
		
		if (TEST_LEVEL > TEST_LEVEL_IF)
		{
			cout << "\n\nTEST_LEVEL: ID\n\n" << endl;
			testID(cpu, xpctdIR, xpctdA, xpctdB, xpctdALUctrl,
					xpctdMEMctrl, xpctdWBctrl);

			if (TEST_LEVEL > TEST_LEVEL_ID)
			{
				cout << "\n\nTEST_LEVEL: EX\n\n" << endl;
				testEX(cpu, fpOp, xpctdALUout);

				if (TEST_LEVEL > TEST_LEVEL_EX)
				{
					cout << "\n\nTEST_LEVEL: MEM\n\n" << endl;
					testMEM(cpu, memory, xpctdMEMctrl,
							xpctdALUout, xpctdRd);
					if (TEST_LEVEL > TEST_LEVEL_MEM)
					{
						cout << "\n\nTEST_LEVEL: WB\n\n" << endl;
						testWB(cpu, xpctdWBctrl, xpctdRd);
					}
				}
			}
		}
	}
	cout << "SUCCESS!" << endl;
	
	cout << "End '" << instruction << "'." << endl << endl << endl;
	
}

/**
 * Testa o estágio IF.
 */
void TestCase::testIF(BasicCPUTest* cpu, uint32_t xpctdIR)
{
	//
	// Testa IF
	//
	cout << "Testing IF..." << endl;
	
	// executa
	cpu->runIF();
	cout << "	IR=0x" << cpu->getIR()
			<< ";  Expected IR=0x" << xpctdIR << endl;
	
	// verifica
	if (cpu->getIR() != xpctdIR) {
		cout << "IF() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	cout << "IF() SUCCESS!" << endl << endl;
}

/**
 * Testa o estágio ID.
 */
void TestCase::testID(BasicCPUTest* cpu,
			uint32_t xpctdIR,
			uint64_t xpctdA,
			uint64_t xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl)
{
	//
	// Testa ID (depende do sucesso no teste de IF)
	//
	cout << "Testing ID..." << endl;
	
	// executa
	int iderror = cpu->runID();
	
	// verifica se a instrução está implementada
	if (iderror) {
		cout << "Instruction not implemented: 0x" << xpctdIR << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	// verifica leitura de registradores
	cout << "ID() testing registers reading..." << endl << endl;
	uint64_t A = cpu->getA();
	uint64_t B = cpu->getB();
	cout << "	A=0x" << setw(16) << A << "; B=0x" << setw(16) << B << endl;
	cout << "Expected: A=0x" << setw(16) << xpctdA << "; B=0x" << setw(16) << xpctdB << endl;
	if ((A != xpctdA) || (B != xpctdB)){
		cout << "ID() FAILED on registers reading!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	cout << "ID() succeeded on registers reading!" << endl << endl;

	if (TEST_LEVEL > TEST_LEVEL_ID)
	{

		cout << "ID() testing ALU control set..." << endl << endl;
		
		// verifica ALUctrl
		ALUctrlFlag ALUctrl = cpu->getALUctrl();
		cout << "	ALUctrl=0x" << ALUctrl << "; Expected ALUctrl=0x"
				<< xpctdALUctrl << endl;
		if (ALUctrl != xpctdALUctrl)
		{
			cout << "ID() FAILED on ALU control set!" << endl;
			cout << "Exit..." << endl;
			exit(1);
		}

		cout << "ID() succeeded on ALU control set!" << endl << endl;

		if (TEST_LEVEL > TEST_LEVEL_EX)
		{
			cout << "ID() testing MEM control set..." << endl << endl;
		
			// verifica MEMctrl
			MEMctrlFlag MEMctrl = cpu->getMEMctrl();
			cout << "	MEMctrl=0x" << MEMctrl << "; Expected MEMctrl=0x"
					<< xpctdMEMctrl << endl;
			if (MEMctrl != xpctdMEMctrl)
			{
				cout << "ID() FAILED on MEM control set!" << endl;
				cout << "Exit..." << endl;
				exit(1);
			}

			cout << "ID() succeeded on MEM control set!" << endl << endl;

			if (TEST_LEVEL > TEST_LEVEL_MEM)
			{
				cout << "ID() testing WB control set..." << endl << endl;

				// verifica WBctrl
				WBctrlFlag WBctrl = cpu->getWBctrl();
				cout << "	WBctrl=0x" << WBctrl << "; Expected WBctrl=0x"
						<< xpctdWBctrl << endl;
				if (WBctrl != xpctdWBctrl)
				{
					cout << "ID() FAILED on WB control set!" << endl;
					cout << "Exit..." << endl;
					exit(1);
				}

				cout << "ID() succeeded on WB control set!" << endl << endl;
			}
		}
	}

	cout << "ID() SUCCESS!" << endl << endl;
}

/**
 * Testa o estágio EX.
 */
void TestCase::testEX(BasicCPUTest* cpu, bool fpOp, uint64_t xpctdALUout)
{
	//
	// Testa EXI (depende do sucesso no teste de ID)
	//
	cout << "Testing EX..." << endl;
	
	// executa
	int exerror;
	if (fpOp) {
		cout << "\tfloat: testing EXF..." << endl;
		exerror = cpu->runEXF();
	} else {
		cout << "\tinteger: testing EXI..." << endl;
		exerror = cpu->runEXI();
	}
	if (exerror) {
		cout << "Control not implemented: 0x" << cpu->getALUctrl() << endl;
		cout << "EX() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	// verifica ALUout
	uint64_t ALUout = cpu->getALUout();
	cout << "	ALUout=0x"
			<< setfill('0') << setw(16) << ALUout
			<< "; Expected ALUout=0x"
			<< setfill('0') << setw(16) << xpctdALUout << endl;
	if (ALUout != xpctdALUout)
	{
		cout << "EX() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	cout << "EX() SUCCESS!" << endl;
}

/**
 * Testa o estágio MEM - NAO IMPLEMENTADO.
 */
void TestCase::testMEM(BasicCPUTest* cpu,
				MemoryTest* memory,
				MEMctrlFlag xpctdMEMctrl,
				uint64_t xpctdALUout,
				uint64_t xpctdRd)
{
	//
	// Test MEM (depends on the success of previous stages)
	//
	cout << "Testing MEM..." << endl;
	
	// executa
	int memerror = cpu->runMEM();
	if (memerror) {
		cout << "Control not implemented: 0x" << cpu->getMEMctrl() << endl;
		cout << "MEM() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
		
	//
	// Test access type
	//
	
	// map MEMctrlFlag to MemoryTest::MemAccessType
	MemoryTest::MemAccessType xpctdLastDataMemAccess;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::MEM_NONE:
			xpctdLastDataMemAccess = MemoryTest::MemAccessType::MAT_NONE;
			break;
		case MEMctrlFlag::READ32:
			xpctdLastDataMemAccess = MemoryTest::MemAccessType::MAT_READ32;
			break;
		case MEMctrlFlag::READ64:
			xpctdLastDataMemAccess = MemoryTest::MemAccessType::MAT_READ64;
			break;
		case MEMctrlFlag::WRITE32:
			xpctdLastDataMemAccess = MemoryTest::MemAccessType::MAT_WRITE32;
			break;
		case MEMctrlFlag::WRITE64:
			xpctdLastDataMemAccess = MemoryTest::MemAccessType::MAT_WRITE64;
			break;
	}

	MemoryTest::MemAccessType lastDataMemAccess =
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
	uint64_t memData, xpctdMemData;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::READ32:
			cout << "	READ Mode: testing read content..." << endl;
			memData = (uint64_t)memory->readData32(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::READ64:
			cout << "	READ Mode: testing read content..." << endl;
			memData = memory->readData64(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::WRITE32:
			cout << "	WRITE Mode: testing written content..." << endl;
			memData = (uint64_t)memory->readData32(xpctdALUout);
			xpctdMemData = xpctdRd;//cpu->getRd();
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
void TestCase::testWB(BasicCPUTest* cpu,
		WBctrlFlag xpctdWBctrl,
		uint64_t xpctdRd)
{
	//
	// Testa WB (depende do sucesso nos testes de estágios anteriores)
	//
	cout << "Testing WB..." << endl;
	
	// executa
	int wberror = cpu->runWB();
	if (wberror) {
		cout << "Control not implemented: 0x" << cpu->getWBctrl() << endl;
		cout << "WB() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	bool ok = true;
	uint64_t Rd = cpu->getRd();
	if(xpctdWBctrl == WBctrlFlag::RegWrite)
	{
		cout << "	Rd=0x"
			<< setfill('0') << setw(8) << Rd
			<< "; Expected xpctdRd=0x"
			<< setfill('0') << setw(8) << xpctdRd << endl;
			
		if (Rd != xpctdRd)
		{
			cout << "WB() FAILED!" << endl;
			cout << "Exit..." << endl;
			exit(1);
		}
	}
	
	cout << "WB() SUCCESS!" << endl;
}

