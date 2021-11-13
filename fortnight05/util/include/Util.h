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

#include <cstdint>

class Util
{
	public:

		/**
		 * Look at a 32-bit floating point value as a 64-bit unsigned
		 * integer without conversion (the binary code remains unchanged
		 * and the number is extended to 64 bits with 32 zeros left).
		 */
		static uint64_t floatAsUint64Low(float value);
		
		/**
		 * Look at the lower 32 bits of a 64-bit unsigned integer as a
		 * 32-bit floating point value without conversion (the binary
		 * code remains unchanged).
		 */
		static float uint64LowAsFloat(uint64_t value);
	
		/**
		 * Look at a 64-bit floating point value as a 64-bit unsigned
		 * integer without conversion (the binary code remains unchanged).
		 */
		static uint64_t doubleAsUint64(double value);
		
		/**
		 * Look at a 64-bit unsigned integer value as a 64-bit floating
		 * point without conversion (the binary code remains unchanged).
		 */
		static double uint64AsDouble(uint64_t value);
};