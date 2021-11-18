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

#include "FACache.h"

using namespace std;

/**
 * Constructs a FACache of 'size' bytes organized in lines of 'lineSize' bytes.
 * 
 * The inherited 'associativity' attribute is set to 0, meaning it is a Fully Associtative Cache.
 * 
 * Constraints: 'size' must be a multiple of 'lineSize', and both must be a power of 2.
 */
FACache::FACache(int size, int lineSize) : Cache::Cache(size, lineSize, 0) {

	// TODO
	// 1. Validar os argumentos:
	//		size e lineSize são potências de 2?
	//		size é um múltiplo de lineSize?
	bool validArgs = false;
	if (!validArgs) {
		throw "Bad FACache initialization. Invalid arguments.";
	}
	
	numSets = 1;
	// TODO
	// 2. Calcular e inicializar atributo numLines
	// 3. Alocar size bytes organizados em numLines linhas para armazenar os dados da cache
	// 4. Alocar vetor de numLines uint32_t para armazenar o diretório da cache
}

FACache::~FACache() {
	// TODO
	// 1. Fazer 'delete' para toda a memória alocada
}

//~ /**
 //~ * Reads 'size' bytes starting at address 'address'.
 //~ * 
 //~ * Returns a pointer to a copy of the data, if cache hit, null otherwise.
 //~ */
//~ void * readData(uint32_t address, int size);

//~ /**
 //~ * Fetches one line to cache.
 //~ * 
 //~ * The bytes written are the bytes of the line that contains the byte in address
 //~ * 'address'. The total number of bytes copied is exactly 'Cache::lineSize'.
 //~ * The argument 'data' is a pointer to the bytes supposed to be copied.
 //~ */
//~ void fetchLine(uint32_t address, char * data);

//~ /**
 //~ * Overwrites the 32 bit value 'value' in address 'address'.
 //~ * 
 //~ * Returns
 //~ * 		true, if cache hit and writing is successful
 //~ * 		false, if cache miss
 //~ */
//~ bool writeValue32(uint32_t address, uint32_t value);

//~ /**
 //~ * Overwrites the 64 bit value 'value' in address 'address'.
 //~ * 
 //~ * Returns
 //~ * 		true, if cache hit and writing is successful
 //~ * 		false, if cache miss
 //~ */
//~ bool writeValue64(uint32_t address, uint64_t value);
