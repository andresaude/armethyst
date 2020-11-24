/* ----------------------------------------------------------------------------

    (EN) BasicCPU - a basic CPU with the following characteristics:
		- AArch64 ISA (limited), from ARMv8
		- MIPS datapath
		
	armethyst - A simple ARM Simulator written in C++ for Computer Architecture
    teaching purposes. Free software licensed under the MIT License (see license
    below).

    (EN) BasicCPU - uma CPU básica com as seguintes características:
		- AArch64 ISA (limitado), do ARMv8
		- caminho de dados do MIPS
    
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

#include "CPU.h"

// Códigos de controle
enum ALUctrlFlag {ALU_UNDEF, ALU_NONE, ADD, SUB};
enum MEMctrlFlag {MEM_UNDEF, MEM_NONE, READ32, WRITE32, READ64, WRITE64};
enum WBctrlFlag {WB_UNDEF, WB_NONE, RegWrite};
		
class BasicCPU: public CPU
{
	protected:
	
	
		/**
		 * Registradores da CPU.
		 *
		 * Declarações de PC, IR, registradores do banco de registradores e
		 * demais registradores auxiliares.
		 */
		 
		// Registrador PC
		uint64_t PC;
		
		// Registrador SP
		// 		Registrador SP (stack pointer), de 64 bits
		uint64_t SP;
		
		// Banco de registradores inteiros
		//		Declara os registradores Rn descritos no documento
		// 		armV8ppB181-B182_registradores.pdf. Veja que o documento
		// 		explica que o ARMv8 tem o conjunto de registradores
		//		R0-R30 (portanto 31 registradores) de 64 bits, que podem ser
		//		usados como registradores de 64	bits, com nomes X0-X30 ou
		//		podem ser usados como registradores	de 32 bits, com nomes
		//		W0-W30.
		uint64_t R[31];
		uint64_t *Rd;
		
		/**
		 * Lê registrador inteiro de 32 bits.
		 */
		int32_t getW(int n);

		/**
		 * Escreve registrador inteiro de 32 bits.
		 */
		void setW(int n, int32_t value);

		/**
		 * Lê registrador inteiro de 64 bits.
		 */
		int64_t getX(int n);

		/**
		 * Escreve registrador inteiro de 64 bits.
		 */
		void setX(int n, int64_t value);

		// Registradores auxiliares
		
		// IR (instruction register), 32 bits, saída do estágio de busca
		// da instrução (IF)
		uint32_t IR; 
		
		// A, 64 bits, saída 1 do estágio de decodificação da instrução (ID)
		// (Rn lido do banco de registradores)
		int64_t A;
		
		// B, 64 bits, saída 2 do estágio de decodificação da instrução (ID)
		// (Rm lido do banco de registradores ou valor imediato lido
		// diretamente da instrução
		int64_t B;
		
		// ALUctrl, enum, saída 3 do estágio de decodificação da instrução (ID),
		// armazena o código de controle da ULA.
		ALUctrlFlag ALUctrl = ALUctrlFlag::ALU_UNDEF;

		// fpOP, bool, saída 4 do estágio de decodificação da instrução (ID),
		// informa se a operação é inteira ou ponto flutuante.
		bool fpOP = false;

		// MEMctrl, enum, saída 5 do estágio de decodificação da instrução
		// (ID), informa se haverá acesso de leitura (READ), escrita (WRITE)
		// ou nenhum (NONE) acesso à memória de dados no estágio de acesso
		// à memória de dados (MEM).
		MEMctrlFlag MEMctrl = MEMctrlFlag::MEM_UNDEF;

		// MEMctrl, enum, saída 6 do estágio de decodificação da instrução
		// (ID), informa se haverá escrita (WRITE) ou não (NONE) de valor
		// (proveniente de EXI, EXF ou MEM) em algum registrador de destino. 
		WBctrlFlag WBctrl = WBctrlFlag::WB_UNDEF;

		// MemtoReg, bool, saída 7 do estágio de decodificação da instrução
		// (ID), informa se haverá leitura (true) ou não (false) de dados
		// na memória.
		bool MemtoReg = false;

		// ALUout, 64 bits, saída do estágio de execução de operação
		// inteira (EXI)
		int64_t ALUout;

		// MDR, 64 bits, saída do estágio de acesso à memória de dados (MEM).
		int64_t MDR;

		/**
		 * Caminho de dados (Datapath)
		 *
		 * Métodos que implementam cada estágio desta CPU. Todos os métodos
		 * possuem assinatura do tipo 'void NOME()', pois utilizam, tanto como
		 * entrada, quanto como saída, os registradores da CPU.
		 */

		/**
		 * Busca da instrução.
		 * 
		 * Lê a memória de instruções no endereço PC e coloca no registrador IR.
		 */
		void IF();

		/**
		 * Decodificação da instrução.
		 * 
		 * Decodifica o registrador IR, lê registradores do banco de registradores
		 * e escreve em registradores auxiliares o que será usado por estágios
		 * posteriores.
		 *
		 * Escreve A, B e ALUctrl para o estágio EXI
		 * ATIVIDADE FUTURA: escreve registradores para os estágios EXF, MEM e WB.
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int ID();
		
		/**
		 * Execução lógico aritmética inteira.
		 * 
		 * Executa a operação lógico aritmética inteira com base nos valores
		 * dos registradores auxiliares A, B e ALUctrl, e coloca o resultado
		 * no registrador auxiliar ALUout.
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se o controle presente em ALUctrl não estiver implementado.
		 */
		int EXI();
		
		/**
		 * Execução lógico aritmética em ponto flutuante.
		 * 
		 * Executa a operação lógico aritmética em ponto flutuant com base
		 * nos valores dos registradores auxiliares AF, BF e ALUctrl, e coloca o
		 * resultado no registrador auxiliar ALUoutF.
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se o controle presente em ALUctrl não estiver implementado.
		 */
		int EXF();
		
		/**
		 * Acesso a dados na memória.
		 * 
		 * Retorna 0: se executou corretamente e
		 *		   1: se o controle presente nos registradores auxiliares não
		 * 				estiver implementado.
		 */
		int MEM();

		/**
		 * Write-back. Escreve resultado da operação no registrador destino.
		 * 
		 * Retorna 0: se executou corretamente e
		 *		   1: se o controle presente nos registradores auxiliares não
		 * 				estiver implementado.
		 */
		int WB();
		
	public:
		BasicCPU(Memory *memory);
		
		/**
		 * Métodos herdados de CPU
		 */
		int run(uint64_t startAddress);
		
	private:
		/**
		 * Decodifica instruções do grupo
		 * 		100x Data Processing -- Immediate
		 *
		 * C4.1.2 Data Processing -- Immediate (p. 232)
		 * This section describes the encoding of the Data Processing -- Immediate group.
		 * The encodings in this section are decoded from A64 instruction set encoding.
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int decodeDataProcImm();

		/**
		 * ATIVIDADE FUTURA: Decodifica instruções do grupo
		 * 		101x Branches, Exception Generating and System instructions
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int decodeBranches();

		/**
		 * ATIVIDADE FUTURA: Decodifica instruções do grupo
		 * 		x1x0 Loads and Stores on page C4-246
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int decodeLoadStore();

		/**
		 * Decodifica instruções do grupo
		 * 		x101 Data Processing -- Register on page C4-278
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int decodeDataProcReg();

		/**
		 * ATIVIDADE FUTURA: Decodifica instruções do grupo
		 * 		x111 Data Processing -- Scalar Floating-Point and Advanced SIMD
		 * 				on page C4-288
		 *
		 * Retorna 0: se executou corretamente e
		 *		   1: se a instrução não estiver implementada.
		 */
		int decodeDataProcFloat();
	
};
