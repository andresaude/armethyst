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

using namespace std;


SACache::SACache(int size, int lineSize, int associativity) : Cache::Cache(size,lineSize,associativity) {

	// TODO
	// 1. Validar os argumentos:
	//		associativity, lineSize e size são potencia de 2?
	//		size = múltiplo de lineSize * associativity?
	bool validArgs = false;
	if (!validArgs) {
		throw "Bad FACache initialization. Invalid arguments.";
	}

	// TODO
	// 2. Calcular e inicializar atributo numSets
	// 3. Calcular e inicializar atributo numLines
	// 4. Alocar numSets FACache(size,lineSize) e colocar em um vetor
}

SACache::~SACache() {
	// TODO
	// 1. Fazer 'delete' para toda a memória alocada	
}


//~ //Implementar uma função ou método
//~ //SACache createSACache(int c, int a, int l);
//~ //onde SACache é o tipo de dado (struct ou classe) que representa uma cache associativa por conjuntos com capacidade total de c bytes, associatividade a e l bytes por linha. É obrigatório que c, a e l sejam inteiros potências de 2 e que c seja um múltiplo de a*l (testar a corretude da entrada e informar o erro, caso exista, é condição bônus).
//~ //Cada conjunto da SACache deve ser uma TACache e, portanto, createSACache deve chamar createTACache.
//~ //Implementar também as seguintes funções ou métodos de acesso a informações sobre o SACache:
//~ int getSACacheCapacity(SACache sac);
//~ int getSACacheLineSize(SACache sac);
//~ que retornam, respectivamente, a capacidade e o tamanho da linha da cache associativa por conjuntos sac.
//~ Implementar a seguinte função ou método de acesso a dados da cache:
	//~ bool getSACacheData(SACache sac, int address, int * value);
//~ que busca o valor do endereço address na cache associativa por conjuntos sac. O valor é retornado no parâmetro de saída value e o método ou função retorna true, se o endereço foi encontrado na cache (hit) ou false, senão (miss). A verificação dos bits de lookup do endereço address para extrair o número do conjunto deve ser feita com o uso de operadores lógicos.
//~ Implementar a seguinte função ou método de acesso a dados da cache:
	//~ void setSACacheLine(SACache tac, int address, int *line);
//~ que escreve toda a linha line, que contém o endereço address, na cache associativa por conjuntos sac, usando setTACacheLine da TACache.
//~ Implementar a seguinte função ou método de acesso a dados da cache:
	//~ bool setSACacheData(SACache sac, int address, int value);
//~ que grava o valor value, do endereço address, na cache associativa por conjuntos sac, utilizando setTACacheData da TACache, e com o mesmo padrão de retorno de setTACacheData.
//~ Implementar a função
//~ SACache duplicateSACache(SACache sac);

