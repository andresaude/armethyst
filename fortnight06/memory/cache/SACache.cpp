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

#include "SACache.h"

#include <cstddef>

using namespace std;


/**
 * Constructs a SACache of 'size' bytes organized in sets of associativity 'associativity'
 * and line size of 'lineSize' bytes.
 * 
 * Constraints: 'size' must be equal to 'numSets*associativity*lineSize', and all the attributes
 * must be a power of 2.
 */
SACache::SACache(unsigned int size, unsigned int lineSize, unsigned int associativity) : Cache::Cache(size,lineSize,associativity) {

	bool validArgs = false;
	// TODO
	// 1. Note que este construtor chama o construtor da superclasse! Veja o que já é feito
	//		no construtor da superclasse.
	// 2. Calcule e inicialize o atributo numSets.
	// 3. Validar os atributos que acabam e ser inicializados:
	//		os valores são coerentes, ou seja, 'numSets*associativity*lineSize == size'?
	//		size, numSets, lineSize e associativity são potências de 2?
	if (!validArgs) {
		throw "Bad FACache initialization. Invalid arguments.";
	}
	
	// TODO
	// 4. Alocar o atributo 'sets' com 'numSets' ponteiros para FACache (FACache *)
	// 5. Percorrer 'sets' e, para cada índice, alocar uma FACache de dimensões coerentes com
	//		esta SACache.
}

SACache::~SACache() {
	// TODO
	// 1. Fazer 'delete' para toda a memória alocada.
	//		ATENÇÃO: percorra 'sets' e faça delete de cada FACache para depois fazer delete
	//		de 'sets'
}

/**
 * Reads the 32 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit
 * 		false, if cache miss
 */
bool SACache::read32(uint64_t address, uint32_t * value) {
	// TODO
	// 1. Encontre tag, lookup e offset do address. Sugestão: faça um ou mais procedimentos,
	//		pois isso será utilizado nos próximos métodos. Você pode ainda criar atributos
	//		privados na classe (SACache.h) e incializa-los no construtor, para armazenar as
	//		máscaras usadas na extração desses campos.
	// 2. Delegue a tarefa para read32 da FACache que se encontra em sets[lookup].
	
	return false;
}

/**
 * Reads the 64 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit
 * 		false, if cache miss
 */
bool SACache::read64(uint64_t address, uint64_t * value) {
	// TODO
	// 1. Repita o código de read32 alterando apenas a delegação da tarefa para read64.
	return false;
}

/**
 * Overwrites the 32 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit and writing is successful
 * 		false, if cache miss
 */
bool SACache::write32(uint64_t address, uint32_t value) {
	// TODO
	// 1. Repita o código de read32 alterando apenas a delegação da tarefa para write32.
	return false;
}

/**
 * Overwrites the 64 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit and writing is successful
 * 		false, if cache miss
 */
bool SACache::write64(uint64_t address, uint64_t value) {
	// TODO
	// 1. Repita o código de read32 alterando apenas a delegação da tarefa para write64.
	return false;
}

/**
 * Fetches one line from slower memory and writes to this cache.
 * 
 * The bytes written are the bytes of the line that contains the byte in address
 * 'address'. The total number of bytes copied is exactly 'Cache::lineSize'.
 * 
 * The argument 'data' is a pointer to the whole data of the slower memory from
 * where the data is to be fetched.
 * 
 * Returns:
 * 		NULL, if the line is not set as modified
 * 		a pointer to a copy of the line, if the line is set as modified
 */
char * SACache::fetchLine(uint64_t address, char * data) {
	// TODO
	// 1. Repita o código de read32 alterando apenas a delegação da tarefa para fetchLine.
	return NULL;
}
