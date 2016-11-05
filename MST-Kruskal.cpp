// Implementação do algoritmo de kruskal

// autor: Micael Costa
// RA: 1299109521
// Turma: CCS4

#include <iostream>
#include <vector> // para trabalhar com o vetor
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
			arestas.push_back(aresta);  // inserir a aresta ao vetor de arestas
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
			vector<Aresta> arvore; // todas arestas que fazem parte da arvore geradora minima, será adicionada ao vetor arvore
			int size_arestas = arestas.size();
			
			// ordena as arestas pelo menor peso
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
				// se verdadeiro é porque não forma ciclos, adiciona a aresta no vetor "arvore"
					arvore.push_back(arestas[i]);
					unir(subset, v1, v2);
				}
			}
			
			int size_arvore = arvore.size();
			
			// mostra as arestas selecionadas com seus respectivos pesos
			for(int i=0; i < size_arvore; i++){
				// em vez de apresentar os vertices por numeros, alteramos para letras a partir de 'M'
				char v1 = 'M' + arvore[i].obterVertice1();
				char v2 = 'M' + arvore[i].obterVertice2();
				cout << "(" << v1 << "," << v2 << ") = " << arvore[i].obterPeso() << endl;
			}
		}
};
int main(int argc, char** argv){
	int V, E, cont = 0;
	cin >> V;
	cin >> E;
	Grafo g(V); // grafo com tamanho "V" vertices
	int aux1[E], aux2[E], auxpeso[E]; // vetores auxiliares para armazenar as arestas com seu respectivo peso
	for(int i = 0; i < E; i++){
		cin >> aux1[i] >> aux2[i] >> auxpeso[i];
	}
	
	// manda as arestas armazenadas para a função adicionarAresta
	for(int i = 0; i < E; i++){
		g.adicionarAresta(aux1[i], aux2[i], auxpeso[i]);
		cont = cont + auxpeso[i];
	}
	
	g.kruskal(); // roda o algoritmo de kruskal
	cout << "\n A arvore geradora minima tem custo " << cont << endl;
	return 0;
}