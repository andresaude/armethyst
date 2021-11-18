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

#include "Cache.h"
#include "FACache.h"
#include "SACache.h"

#include <string>
#include <fstream>

using namespace std;

Cache::Cache(int size, int lineSize, int associativity) {
	this->size = size;
	this->lineSize = lineSize;
	this->associativity = associativity;
}

/**
 * Constructs a Cache of 'size' bytes organized in lines of 'lineSize' bytes, with
 * associativity 'associativity'.
 * 
 * Associativity is the number of ways in this cache implementation. If 'associativity'
 * is a positive power of 2, the constructed cache is a set associative cache. If
 * 'associativity' is less or equal to 0, the constructed cache is a fully associative
 * cache. If 'associativity' is positive, but not a power of 2, an exception is raised.
 * 
 * Constraints: 'size' must be a multiple of 'lineSize', and both must be a power of 2.
 */
Cache* Cache::createCache(int size, int lineSize, int associativity) {
	Cache *cache = NULL;
	if (associativity <= 0) {
		cache = new FACache(size, lineSize);
	} else {
		cache = new SACache(size, lineSize, associativity);
	}
	return cache;
}

/*
 * Attribute access methods.
 */
int Cache::getSize() {
	return size;
}
int Cache::getLineSize() {
	return lineSize;
}
int Cache::getAssociativity() {
	return associativity;
}
int Cache::getNumLines() {
	return numLines;
}
int Cache::getNumSets() {
	return numSets;
}

//~ /**
 //~ * Reads 'size' bytes starting at address 'address'.
 //~ * 
 //~ * Returns a pointer to a copy of the data, if cache hit, null otherwise.
 //~ */
//~ void * readData(uint32_t address, int size);

//~ /**
 //~ * Fetches one line from slower memory and writes to this cache.
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

