# 🕸️ Grafo em C++

Implementação de um **TAD Grafo** com **matriz de adjacência ponderada** e menu interativo no console. Suporta grafos **direcionados** e **não direcionados**, importação/exportação por arquivo e os algoritmos clássicos **DFS, BFS, Prim e Dijkstra**.

![C++](https://img.shields.io/badge/C%2B%2B-11%2B-00599C?logo=c%2B%2B&logoColor=white)
![Plataforma](https://img.shields.io/badge/plataforma-Windows-0078D6?logo=windows&logoColor=white)

## ✨ Funcionalidades

- Criar grafo vazio ou **importar de arquivo `.txt`**
- Inserir, remover e consultar arestas (individual ou em lote)
- Editar **nome** e **coordenadas** dos vértices
- Navegar pelos adjacentes (primeiro, próximo e lista completa)
- Exibir a matriz de adjacência e contar arestas
- **Exportar** o grafo para `saida.txt`
- Algoritmos com passo a passo no console:
  - **Busca em Profundidade (DFS)**: tempos de descoberta/término e antecessores
  - **Busca em Largura (BFS)**: distâncias em arestas e antecessores
  - **Prim**: árvore geradora mínima (grafos não direcionados)
  - **Dijkstra**: caminho mínimo entre dois vértices, pelo nome

## 📁 Estrutura

```
├── main.cpp    # menus e interação com o usuário
├── grafo.cpp   # classe Grafo (estrutura de dados + algoritmos)
├── arq.txt     # grafo de exemplo (20 cidades de MG)
└── README.md
```

## 🚀 Como executar

Requer compilador C++ e **Windows** (usa `<windows.h>`, `system("cls")` e `Sleep()`).

```bash
g++ main.cpp -o grafo.exe
grafo.exe
```

> O `grafo.cpp` é incluído pelo `main.cpp`, então só o `main.cpp` é compilado. O `arq.txt` deve ficar na mesma pasta do executável.

## 📄 Formato do arquivo

```
direcionado=nao          # ou direcionado=sim
20                       # quantidade de vértices
0 1 1 Belo Horizonte     # id  x  y  nome
1 50 20 Uberlandia
...
20                       # quantidade de arestas
0 1 50                   # origem  destino  peso
0 19 43
...
```

- Vértices indexados de `0` a `N-1`.
- Pesos devem ser **positivos** (`0` na matriz = sem aresta).
- Em grafos não direcionados, cada aresta aparece **uma vez** no arquivo.

## ⏱️ Complexidade

Com matriz de adjacência (`V` = nº de vértices): espaço `O(V²)`; consulta/inserção/remoção de aresta `O(1)`; DFS, BFS, Prim e Dijkstra `O(V²)`.

## ⚠️ Limitações e melhorias futuras

- Funciona apenas no Windows
- Pesos inteiros e positivos
- Prim e Dijkstra sem fila de prioridade (poderiam ser `O(E log V)`)
- A função `mostrarGraficamente()` ainda não foi implementada

## 👤 Autor

Desenvolvido por **[Seu Nome]**, [Disciplina] — [Instituição].
