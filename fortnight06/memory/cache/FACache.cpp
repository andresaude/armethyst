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

#include <cstddef>

using namespace std;

/**
 * Constructs a FACache of 'size' bytes organized in lines of 'lineSize' bytes.
 * 
 * The inherited 'associativity' attribute is set to 'size / lineSize' (integer division).
 * 
 * Constraints: 'size' must be a multiple of 'lineSize', and both must be a power of 2.
 */
FACache::FACache(unsigned int size, unsigned int lineSize) : Cache::Cache(size, lineSize, size/lineSize) {

	bool validArgs = false;
	// TODO
	// 1. Note que este construtor chama o construtor da superclasse! Veja o que já é feito
	//		no construtor da superclasse.
	// 2. Validar os atributos que acabam e ser inicializados na superclasse:
	//		size é um múltiplo de lineSize? ou seja, associativity*lineSize == size?
	//		size, lineSize e associativity são potências de 2?
	if (!validArgs) {
		throw "Bad FACache initialization. Invalid arguments.";
	}
	
	numSets = 1; // fully associative cache does not have sets
	
	// TODO
	// 3. Alocar o atributo 'data' com 'size' bytes
	// 4. Alocar o atributo 'directory' com 'associativity' elementos uint64_t
}

FACache::~FACache() {
	// TODO
	// 1. Fazer 'delete' para toda a memória alocada. Uma boa implementação só terá
	//		alocado memória no construtor.
}

/**
 * Reads the 32 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit
 * 		false, if cache miss
 */
bool FACache::read32(uint64_t address, uint32_t * value) {
	// TODO
	// 1. Encontre a tag e o offset do address. O offset é a parte menos significativa
	//		de 'address', correspondente ao número de bits necessários para identificar
	//		cada byte na linha. Sugestão: faça um ou mais procedimentos, pois isso será
	//		utilizado nos próximos métodos.
	//			Exemplo: se lineSize = 64 (2^6), são 6 bits de offset e 26 bits de tag.
	//			O próprio atributo lineSize e sua inversão bit a bit (~lineSize) podem
	//			ser usados para separar tag e offset do address. Mas ATENÇÃO: address
	//			é uint64_t e lineSize é unsigned int, faça as devidas conversões!
	// 2. Percorra o diretório do cache verificando se a tag é encontrada e, se
	//		encontrada, em qual índice foi encontrada. Sugestão: faça um procedimento,
	//		pois isso será utilizado nos próximos métodos.
	// 3. Se a tag não foi encontrada (cache miss), retorne false
	// 4. Se a tag foi encontrada (cache hit), leia o valor na linha do cache, escreva-o
	//		no argumento de saída 'value' e retorne true.
	//			DESAFIO: toda a cache está implementada como um único vetor de bytes,
	//			declarado na forma do atributo 'data'. A variável 'data' é o endereço
	//			do primeiro byte da cache, ou seja, é também o endereço do início da
	//			primeira linha do cache. O endereço do ínicio da segunda linha do cache
	//			é 'data + lineSize', o do início da terceira linha do cache é 'data + 2*lineSize',
	//			e assim por diante. Logo, o endereço do início da linha precisa ser
	//			calculado com o uso do índice encontrado no passo 2 acima. Após obtido o
	//			endereço do início da linha, é preciso convertê-lo para um ponteiro do
	//			tipo de dado sendo lido. Não é uma tarefa trivial.
	return false;
}

/**
 * Reads the 64 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit
 * 		false, if cache miss
 */
bool FACache::read64(uint64_t address, uint64_t * value) {
	// TODO
	// A única diferença da implementação de read64 para a de read32 é o Passo 4.
	// 1, 2 e 3. Copie a implementação dos Passos 1, 2 e 3 de read32 para este método, pois é o
	//		mesmo código.
	// 4. Repita o Passo 4 de read32, alterando apenas o tipo do dado lido. Em read32
	//		é preciso converter um vetor e o índice a ser lido de char * para uint32_t *,
	//		enquanto em read64 é preciso converter de char * para uint64_t *.
	return false;
}

/**
 * Overwrites the 32 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit and writing is successful
 * 		false, if cache miss
 */
bool FACache::write32(uint64_t address, uint32_t value) {
	// TODO
	// A diferença do write32 para o read32 também é apenas o Passo 4, que agora se trata de escrita.
	// 1, 2 e 3. Copie a implementação dos Passos 1, 2 e 3 de read32 para este método, pois é o
	//		mesmo código.
	// 4. Se a tag foi encontrada (cache hit), escreva o valor do argumento de entrada 'value'
	//		 na linha do cache, altere o status da linha para 'modificado' e retorne true.
	//			DESAFIO 1: o primeiro desafio é o mesmo de read32, a conversão do tipo do vetor de
	//			dados para a escrita no local correto.
	//			DESAFIO 2: o segundo desafio é o citado status 'modificado'. Ao se alterar um
	//			valor na cache, ele deve ser marcado como modificado, para que o gestor da hierarquia
	//			de memória saiba que precisa atualizar essa linha nos níveis mais baixos da hierarquia.
	//			Você pode criar um vetor de bool, do tamanho do diretório do cache, mas é possível
	//			fazer isso no próprio diretório, usando o bit menos significativo da tag, visto que
	//			esse bit é sempre igual a 0. Você pode deixa-lo valendo 0, se a linha não possui
	//			modificações, e 1, se a linha possui modificações. O único cuidado agora é no Passo 2,
	//			quando a tag é buscada no diretório, mas se você implementou o Passo 2 como um
	//			procedimento, será fácil adaptar.
	return false;
}

/**
 * Overwrites the 64 bit value 'value' in address 'address'.
 * 
 * Returns
 * 		true, if cache hit and writing is successful
 * 		false, if cache miss
 */
bool FACache::write64(uint64_t address, uint64_t value) {
	// TODO
	// A única diferença da implementação de write64 para a de write32 é o Passo 4.
	// 1, 2 e 3. Copie a implementação dos Passos 1, 2 e 3 de write32 para este método, pois é o
	//		mesmo código.
	// 4. Repita o Passo 4 de write32, alterando apenas o tipo do dado lido, uint64_t no lugar de
	//		uint32_t.
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
char * FACache::fetchLine(uint64_t address, char * data) {
	char *removedLine = NULL;
	int localWriteIndex = writeIndex;
	
	// TODO
	// 1 e 2. Copie a implementação dos Passos 1 e 2 de read32 para este método, pois é o
	//		mesmo código.
	// 3. Se a tag foi encontrada no diretório, altere a variável localWriteIndex para o índice
	//		onde a tag foi encontrada.
	// 4. Verifique se a linha número 'localWriteIndex' está marcada como modificada. Se não
	//		estiver modificada, nada precisa ser feito. Se estiver modificada, faça:
	//		1.1 aloque um vetor de 'lineSize' bytes para a variável 'removedLine';
	//		1.2 copie toda a linha número 'localWriteIndex' (utilize memcpy) para 'removedLine'.
	// 5. Copie 'lineSize' bytes de data para a linha número 'localWriteIndex' (utilize memcpy).
	//		ATENÇÃO: a tag extraída de 'address' é também o índice do início da área de 'data'
	//		que deve ser copiada, ou seja, você não irá copiar 'lineSize' bytes a partir do
	//		endereço 'data', mas sim de &(data[tag]);
	
	// atualiza o índice para o próximo fetch (estratégia FIFO para escolha da linha)
	writeIndex = (writeIndex + 1) % associativity;
	return removedLine;
}
