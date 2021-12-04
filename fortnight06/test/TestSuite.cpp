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

#include "TestSuite.h"

#define TOTAL_NUM_CASES 6

TestSuite::TestSuite() {
	cases = new TestCase*[TOTAL_NUM_CASES];
	
	cases[0] = new TestCase01(); // basic arithmetic: add, sub
	cases[1] = new TestCase02(); // basic float: fadd, fsub
	cases[2] = new TestCase03(); // basic arithmetic: add, sub
	cases[3] = new TestCase04(); // basic float: fadd, fsub
	cases[4] = new TestCase05(); // basic arithmetic: add, sub
	cases[5] = new TestCase06(); // basic float: fadd, fsub
}

TestSuite::~TestSuite() {
	delete [] cases;
}

int TestSuite::runSuite(TestSuite::Suite suite) {
	TestCase **suiteCases = new TestCase*[TOTAL_NUM_CASES];
	int numCases = 0;
	
	switch (suite) {
		case TestSuite::Suite::BASIC_ARITH:
			numCases = 1;
			suiteCases[0] = cases[0];
			break;
		case TestSuite::Suite::BASIC_FLOAT:
			numCases = 1;
			suiteCases[0] = cases[1];
			break;
		case TestSuite::Suite::ALL_LOAD_STORE:
			numCases = 1;
			suiteCases[0] = cases[2];
			break;
		case TestSuite::Suite::ALL_FLOAT:
			numCases = 1;
			suiteCases[0] = cases[3];
			break;
		case TestSuite::Suite::BASIC_LOAD_STORE:
			numCases = 1;
			suiteCases[0] = cases[4];
			break;
		case TestSuite::Suite::MEM_HIERARCHY:
			numCases = 1;
			suiteCases[0] = cases[5];
			break;
		default:
			throw "Undefined test suite.";
	}
	
	for (int c = 0; c < numCases; c++) {
		suiteCases[c]->run();
	}

	return 0;
}
