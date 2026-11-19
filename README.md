# 🕸️ Grafo em C++

![C++](https://img.shields.io/badge/C%2B%2B-11%2B-00599C?logo=c%2B%2B&logoColor=white)
![Plataforma](https://img.shields.io/badge/plataforma-Windows-0078D6?logo=windows&logoColor=white)
![Interface](https://img.shields.io/badge/interface-terminal-4D4D4D)
![Status](https://img.shields.io/badge/status-conclu%C3%ADdo-brightgreen)

Implementação de uma estrutura de dados de **grafos** em **C++**, usando **matriz de adjacência**, com interface interativa via terminal. O projeto foi desenvolvido para a disciplina de **Algoritmos e Estruturas de Dados III (AEDSIII)** e reúne operações básicas sobre grafos, algoritmos de busca, árvore geradora mínima e caminho mínimo.

---

## ⚙️ Funcionalidades

- ✅ Criação do grafo **a partir de um arquivo** (`arq.txt`) ou **vazio**, com inserção manual
- ✅ Suporte a grafos **direcionados** e **não direcionados**
- ✅ Grafos **ponderados** (peso inteiro positivo nas arestas)
- ✅ Vértices com **nome** e **coordenadas** (x, y)
- ✅ **Exportação** do grafo para arquivo (`saida.txt`), no mesmo formato da importação
- ✅ Menu interativo com 16 operações

### Menu de opções

| Opção | Descrição |
|:-----:|-----------|
| 0  | Sair |
| 1  | Exibir todas as adjacências (matriz) |
| 2  | Consultar se existe aresta entre dois vértices |
| 3  | Inserir aresta |
| 4  | Inserir arestas em conjunto |
| 5  | Remover aresta |
| 6  | Editar coordenada do vértice |
| 7  | Primeiro adjacente do vértice |
| 8  | Próximo adjacente do vértice |
| 9  | Lista completa de adjacentes do vértice |
| 10 | Contar arestas |
| 11 | Exportar grafo |
| 12 | Editar nome do vértice |
| 13 | Busca em profundidade (DFS) |
| 14 | Busca em largura (BFS) |
| 15 | Algoritmo de Prim (árvore geradora mínima) |
| 16 | Algoritmo de Dijkstra (caminho mínimo) |

---

## 🧠 Algoritmos implementados

| Algoritmo | Objetivo | Observações | Complexidade* |
|-----------|----------|-------------|:-------------:|
| **Busca em Profundidade (DFS)** | Explorar o grafo indo o mais fundo possível antes de voltar | Percorre todos os vértices (também em grafos desconexos) e mostra tempos de descoberta/término | O(V²) |
| **Busca em Largura (BFS)** | Percorrer o grafo por níveis, a partir de cada vértice ainda não visitado | Mostra cor, distância e antecessor de cada vértice | O(V²) |
| **Prim** | Encontrar a árvore geradora mínima (AGM) | Somente grafos **não direcionados**; inicia no vértice `0` e avisa se o grafo não for conexo | O(V²) |
| **Dijkstra** | Encontrar o caminho mínimo entre dois vértices | Origem e destino são informados pelo **nome** do vértice; reconstrói o caminho pelos antecessores | O(V²) |

\* Considerando a representação por matriz de adjacência, onde `V` é o número de vértices.

---

## 📁 Estrutura do projeto

```
📦 projeto-grafos
 ┣ 📜 main.cpp      # Menus e interação com o usuário
 ┣ 📜 grafo.cpp     # Classe Grafo (estrutura de dados e algoritmos)
 ┣ 📜 arq.txt       # Arquivo de entrada com o grafo (opcional)
 ┗ 📜 README.md     # Documentação
```

---

## 📌 Pré-requisitos

- Compilador C++ com suporte a **C++11** ou superior (por exemplo, **MinGW-w64 / g++**)
- **Windows**, pois o código usa a biblioteca `<windows.h>` (função `Sleep`) e o comando `system("cls")`

---

## 🚀 Como compilar e executar

1. Clone o repositório:

```bash
git clone https://github.com/<seu-usuario>/<nome-do-repositorio>.git
cd <nome-do-repositorio>
```

2. Compile:

```bash
g++ main.cpp -o main
```

> O `main.cpp` já inclui o `grafo.cpp` por meio de `#include "grafo.cpp"`.

3. Execute:

```bash
main.exe
```

> Ao escolher a opção **1 – Importar arquivo de texto**, o arquivo `arq.txt` precisa estar na **mesma pasta de onde o programa é executado**.

---

## 📄 Formato do arquivo de entrada

O arquivo `arq.txt` segue a estrutura abaixo:

```
direcionado=<sim|nao>
<quantidade de vértices>
<id> <x> <y> <nome>          (uma linha por vértice)
...
<quantidade de arestas>
<origem> <destino> <peso>    (uma linha por aresta)
...
```

### Exemplo (`arq.txt`)

```
direcionado=nao
5
0 100 100 A
1 300 100 B
2 100 300 C
3 300 300 D
4 500 200 E
6
0 1 4
0 2 1
2 1 2
1 3 5
2 3 8
3 4 3
```

| Campo | Significado |
|-------|-------------|
| `id` | Índice do vértice (de `0` a `V-1`) |
| `x`, `y` | Coordenadas do vértice |
| `nome` | Nome do vértice (pode conter espaços) |
| `peso` | Peso da aresta (inteiro **maior que 0**) |

O comando de **exportação** (opção 11) gera o arquivo `saida.txt` neste mesmo formato.

---

## 💻 Exemplo de uso

### Menu inicial

```
-------------------- MENU --------------------
Como deseja iniciar o grafo?
1 - Importar arquivo de texto
2 - Criar grafo vazio (inserir manualmente)
----------------------------------------------
Escolha uma opcao:
```

### Dijkstra (opção 16) com o grafo de exemplo

```
Digite o nome da origem: A
Digite o nome do destino: E

Caminho minimo de A ate E:
A -> C -> B -> D -> E
(Distancia total = 11)
```

### Prim (opção 15) com o grafo de exemplo

```
Arvore geradora minima encontrada:
2 1	(peso=2)
0 2	(peso=1)
1 3	(peso=5)
3 4	(peso=3)
(Peso total = 11)
```

---

## 🔍 Detalhes de implementação

- **Representação:** matriz de adjacência (`vector<vector<int>>`). O valor `0` indica ausência de aresta; qualquer valor positivo é o peso da aresta.
- **Grafos não direcionados:** ao inserir ou remover uma aresta `(u, v)`, a posição simétrica `(v, u)` também é atualizada.
- **Contagem e exportação de arestas:** em grafos não direcionados, cada aresta é contada/exportada uma única vez (considerando apenas `v > u`).
- **Cores nas buscas:** `B` (branco, não visitado), `C` (cinza, em processamento) e `P` (preto, finalizado).
- **Infinito:** representado por `INT_MAX` (`<climits>`).
- **Iteração sobre adjacentes:** feita pelas funções `primeiroAdjacenteDoVertice` e `proximoAdjacenteDoVertice`, reaproveitadas em DFS, BFS e na listagem de adjacentes.
- **Validações:** índices de vértices inválidos, arestas duplicadas, pesos menores ou iguais a zero e falhas na abertura de arquivos são tratados com mensagens de erro.

---

## ⚠️ Limitações conhecidas

- Funciona apenas em **Windows** (uso de `<windows.h>` e `system("cls")`).
- Os pesos das arestas devem ser **inteiros positivos** (o valor `0` é reservado para "sem aresta").
- O algoritmo de **Prim** não aceita grafos direcionados.
- No **Dijkstra**, origem e destino devem ser informados pelo **nome** do vértice; se houver nomes repetidos, será considerado o último vértice encontrado com aquele nome.
- As coordenadas dos vértices são armazenadas e exportadas, mas a exibição gráfica do grafo ainda **não foi implementada**.

---

## 👨‍💻 Autor

Desenvolvido por **Theo Linhares Mariano**
Bacharelado em Sistemas de Informação — IFMG, Campus São João Evangelista
Disciplina: Algoritmos e Estruturas de Dados III (AEDSIII)
