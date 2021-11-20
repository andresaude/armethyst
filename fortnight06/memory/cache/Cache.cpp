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

/**
 * Basic constructor. Initializes the attributes without testing any constraint.
 */
Cache::Cache(unsigned int size, unsigned int lineSize, unsigned int associativity) {
	this->size = size;
	this->lineSize = lineSize;
	this->associativity = associativity;
}

//~ /**
 //~ * Constructs a Cache of 'size' bytes organized in lines of 'lineSize' bytes, with
 //~ * associativity 'associativity'.
 //~ * 
 //~ * Associativity is the number of ways (lines of each fully associative set) in this
 //~ * cache implementation. The following values are valid:
 //~ * 		- 'associativity <= 1': the constructed cache is a fully associative cache (FACache);
 //~ * 		- 'associativity > 1': the constructed cache is a set associative cache (SACache).
 //~ * 
 //~ * The constraints of each cache implementation must also be satisfied. This constructor does
 //~ * not handle such constraints.
 //~ * 
 //~ * Constraints: 'size' must be a multiple of 'lineSize', and both must be a power of 2.
 //~ */
//~ Cache* Cache::createCache(unsigned int size, unsigned int lineSize, unsigned int associativity) {
	//~ Cache *cache = NULL;
	//~ if (associativity <= 1) {
		//~ cache = new FACache(size, lineSize);
	//~ } else {
		//~ cache = new SACache(size, lineSize, associativity);
	//~ }
	//~ return cache;
//~ }

/*
 * Attribute access methods.
 */
unsigned int Cache::getSize() {
	return size;
}
unsigned int Cache::getLineSize() {
	return lineSize;
}
unsigned int Cache::getAssociativity() {
	return associativity;
}
unsigned int Cache::getNumSets() {
	return numSets;
}
