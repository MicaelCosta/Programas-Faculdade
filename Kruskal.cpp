// Implementação do algoritmo de kruskal

// Para detectar ciclos iremos utilizar o algoritmo Union-Find que 
// detecta ciclos em grafos não direcionados

#include <iostream>
#include <vector>
#include <algorithm> // para ordenar o vetor de arestas utilizando a função Sort
#include <string.h> // utilização do MEMSET para inicilizar o vetor 

using namespace std;

class Aresta{
		int vertice1, vertice2, peso;
		
public:
		Aresta(int v1, int v2, int peso){
			vertice1 = v1;
			vertice2 = v2;
			this->peso = peso;
		}
		
		// funções para acessar de fora da classe, devido ser privado
		int obterVertice1(){
			return vertice1;
		}
		int obterVertice2(){
			return vertice2;
		}
		int obterPeso(){
			return peso;
		}
		
		// sobrescrita do operador "<", devido precisar ordenar as arestas (objetos) pelo menor peso
		bool operator < (const Aresta& aresta2) const {
			return (peso < aresta2.peso); // comparação para ordenar os pesos em ordem crescente
		}
		
};
class Grafo{
		int V; // número de vértices
		vector<Aresta> arestas; // vetor de arestas
	   
public:
	   	Grafo (int V){ // construtor do grafo
			   this->V = V;
		}
		
		// função para adicionar aresta
		void adicionarAresta(int v1, int v2, int peso){
			Aresta aresta(v1, v2, peso);
			arestas.push_back(aresta);  // inserir a aresta do vetor de arestas
		}
		
		// função que busca o subconjunto de um elemento "i", equivalente a função FindSet
		int buscar(int subset[], int i){
			if (subset[i] == -1)
				return i;
			return buscar(subset, subset[i]);
		}
		
		// função para unir dois subconjuntos em um único subconjunto, equivalente a função UNION
		void unir(int subset[], int v1, int v2){
			int v1_set = buscar(subset, v1);
			int v2_set = buscar(subset, v2);
			subset[v1_set] = v2_set;
		}
		
		// função Algoritmo Kruskal
		void kruskal(){
			vector<Aresta> arvore; // todas arestas que fazem parte da arvore geradora minima, adiciona no vetor arvore
			int size_arestas = arestas.size();
			
			// ordenar as arestas pelo menor peso
			sort(arestas.begin(), arestas.end());
			
			// aloca memória para criar "V" subconjuntos, equivalente a função Malloc
			int * subset = new int[V];
			
			// inicializa todos os subconjuntos como conjuntos 	de um único elemento, equivalente a função MakeSet
			memset(subset, -1, sizeof(int) * V);
			
			// Percorrer as arestas
			for(int i = 0; i < size_arestas; i++){
				int v1 = buscar(subset, arestas[i].obterVertice1());
				int v2 = buscar(subset, arestas[i].obterVertice2());
				if(v1 != v2){ 
				// se verdadeiro é porque não forma ciclos, adiciona a arestas no vetor "arvore"
					arvore.push_back(arestas[i]);
					unir(subset, v1, v2);
				}
			}
			
			int size_arvore = arvore.size();
			
			// mostrar as arestas selecionadas com seus repectivos pesos
			for(int i=0; i < size_arvore; i++){
				// em vez de representar os vertices por numeros, alteramos para letras a partir de 'M'
				char v1 = 'M' + arvore[i].obterVertice1();
				char v2 = 'M' + arvore[i].obterVertice2();
				cout << "(" << v1 << "," << v2 << ") = " << arvore[i].obterPeso() << endl;
			}
		}
};
int main(int argc, char** argv)
{
	int V, E;
	cin >> V;
	cin >> E;
	Grafo g(V); // grafo com tamanho "V" vertices
	int aux1[E], aux2[E], auxpeso[E]; // vetores auxiliares para armazenar as arestas com seu respectivo peso
	for(int i = 0; i < E; i++){
		cin >> aux1[i] >> aux2[i] >> auxpeso[i];
	}
	
	// mandar as arestas armazenadas para a função adicionarAresta
	for(int i = 0; i < E; i++){
		g.adicionarAresta(aux1[i], aux2[i], auxpeso[i]);
	}
	
	g.kruskal(); // roda o algoritmo de kruskal
	return 0;
}