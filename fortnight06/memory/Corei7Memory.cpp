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

#include "Corei7Memory.h"

Corei7Memory::Corei7Memory(int size)
{
	logger = new MemoryLogger("cacheLog.txt");
	initHierarchy();
	mainMemory = new BasicMemory(size);
}

Corei7Memory::~Corei7Memory()
{
	// TODO
	// 1. Fazer 'delete' para toda a memória alocada. Uma boa implementação só terá
	//		alocado memória no construtor ou nos métodos por ele chamados.
	delete[] mainMemory;
}

/**
 * Inicializa a hierarquia de memória. O ideal seria que este procedimento utilizasse um arquivo de configuração,
 * que descreveria a organização de toda a hierarquia de memória. Mas, para facilitar, vamos fazer isso hard-coded,
 * ou seja, no código mesmo!
 */
void Corei7Memory::initHierarchy() {
	// TODO
	// A instanciação da memória principal já está implementada no construtor.
	// 1. Instanciar as caches, conforme hierarquia definida no enunciado do trabalho:
	// 		l1i: cache de 2KB, 4 vias, linhas de 64B (escrita não se aplica)
	// 		l1d: cache de 2KB, 8 vias, linhas de 64B, estratégia write-through
	// 		l2: cache de 8KB, 8 vias, linhas de 64B, estratégia writeback
}

/**
 * Retorna o ponteiro para o início da memória.
 */
char *Corei7Memory::getData() {
	return mainMemory->getData();
}

/**
 * Lê uma instrução de 32 bits considerando um endereçamento em bytes.
 *
 * BasicMemory.cpp implementa a arquitetura de Von Neumman, com apenas uma
 * memória, que armazena instruções e dados.
 */
uint32_t Corei7Memory::readInstruction32(uint64_t address)
{
	int hitLevel = 1;
	uint32_t value;
	
	// TODO
	// 1. Implementar a simulação do comportamento da cache real, ou seja:
	//		Verificar l1i
	//			se hit, hitLevel = 1, retorna dado lido
	//			senão, verificar l2
	//				se hit
	//					hitLevel = 2, fetch da linha para l1i, retorna dado lido
	//				senão
	//					ler dado da memória principal
	//					hitLevel = 3, fetch da linha para l1i e para l2, retorna dado lido

	// TODO a linha a seguir deve entrar na lógica acima
	value = mainMemory->readInstruction32(address);
	
	// não mexa nas linhas a seguir, são necessárias para a correção do trabalho
	logger->memlog(MemoryLogger::READI,address,hitLevel);
	return value;
}

/**
 * Lê um dado de 32 bits considerando um endereçamento em bytes.
 */
uint32_t Corei7Memory::readData32(uint64_t address)
{
	int hitLevel = 1;
	uint32_t value;
	
	// TODO
	// 1. Replicar o código de readInstruction32, alterando apenas l1i para l1d e
	//	os métodos delegados.

	// TODO a linha a seguir deve entrar na lógica da hierarquia
	value = mainMemory->readData32(address);
	
	// não mexa nas linhas a seguir, são necessárias para a correção do trabalho
	logger->memlog(MemoryLogger::READ32,address,hitLevel);
	return value;
}

/**
 * Lê um dado de 64 bits considerando um endereçamento em bytes.
 */
uint64_t Corei7Memory::readData64(uint64_t address)
{
	int hitLevel = 1;
	uint64_t value;
	
	// TODO
	// 1. Replicar o código de readInstruction32, alterando apenas l1i para l1d e
	//	os métodos delegados.

	// TODO a linha a seguir deve entrar na lógica da hierarquia
	value = mainMemory->readData64(address);
	
	// não mexa nas linhas a seguir, são necessárias para a correção do trabalho
	logger->memlog(MemoryLogger::READ64,address,hitLevel);
	return value;
}

/**
 * Escreve uma instrução de 32 bits considerando um
 * endereçamento em bytes.
 */
void Corei7Memory::writeInstruction32(uint64_t address, uint32_t value)
{
	mainMemory->writeInstruction32(address,value);
}

/**
 * Escreve um dado (value) de 32 bits considerando um endereçamento em bytes.
 */
void Corei7Memory::writeData32(uint64_t address, uint32_t value)
{
	int hitLevel = 1;
	
	// TODO
	// 1. Replicar o código de readInstruction32, alterando apenas l1i para l1d e
	//	os métodos delegados.
	// 2. Acrescente à lógica implementada, as questões de manutenção da coerência
	//	de cache, utilizando as estratégias write-through ou writeback, conforme
	//	enunciado.

	// TODO a linha a seguir deve entrar na lógica da hierarquia
	mainMemory->writeData32(address,value);
	
	// não mexa nas linhas a seguir, são necessárias para a correção do trabalho
	logger->memlog(MemoryLogger::WRITE32,address,hitLevel);
}

/**
 * Escreve um dado (value) de 64 bits considerando um endereçamento em bytes.
 */
void Corei7Memory::writeData64(uint64_t address, uint64_t value)
{
	int hitLevel = 1;
	
	// TODO
	// 1. Replicar o código de writeData32, alterando apenas o que for necessário para
	//	a escrita 64 bits.

	// TODO a linha a seguir deve entrar na lógica da hierarquia
	mainMemory->writeData64(address,value);
	
	// não mexa nas linhas a seguir, são necessárias para a correção do trabalho
	logger->memlog(MemoryLogger::WRITE64,address,hitLevel);
}
