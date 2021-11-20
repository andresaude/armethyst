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
#pragma once

#include "Cache.h"

#include <cstdint>

using namespace std;

/**
 * Fully Associative Cache.
 */
class FACache : public Cache
{
protected:
	char * data;			// the cache data
	uint64_t * directory;	// the cache directory
	int writeIndex = 0;		// índice da linha a ser escrito o próximo fetch
	
public:

	/**
	 * Constructs a FACache of 'size' bytes organized in lines of 'lineSize' bytes.
	 * 
	 * The inherited 'associativity' attribute is set to 'size / lineSize' (integer division).
	 * 
	 * Constraints: 'size' must be a multiple of 'lineSize', and both must be a power of 2.
	 */
	 FACache(unsigned int size, unsigned int lineSize);
	~FACache();
    
    /**
     * Reads the 32 bit value 'value' in address 'address'.
     * 
     * Returns
     * 		true, if cache hit
     * 		false, if cache miss
     */
    bool read32(uint64_t address, uint32_t * value);

    /**
     * Reads the 64 bit value 'value' in address 'address'.
     * 
     * Returns
     * 		true, if cache hit
     * 		false, if cache miss
     */
    bool read64(uint64_t address, uint64_t * value);

    /**
     * Overwrites the 32 bit value 'value' in address 'address'.
     * 
     * Returns
     * 		true, if cache hit and writing is successful
     * 		false, if cache miss
     */
    bool write32(uint64_t address, uint32_t value);

    /**
     * Overwrites the 64 bit value 'value' in address 'address'.
     * 
     * Returns
     * 		true, if cache hit and writing is successful
     * 		false, if cache miss
     */
    bool write64(uint64_t address, uint64_t value);

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
     * 		null, if the line is not set as modified
     * 		a pointer to a copy of the line, if the line is set as modified
     */
    char * fetchLine(uint64_t address, char * data);

};

