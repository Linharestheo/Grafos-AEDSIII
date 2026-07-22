#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <queue>
#include <climits>
#include <iomanip>

const int INF = INT_MAX; // <climits>

using namespace std;

class Grafo
{

private:
    vector<vector<int>> matriz;      // declaro matriz dos adjacentes
    vector<vector<int>> coordenadas; // declaro matriz para cordenadas
    vector<string> nomes;            // armazenar nomes dos vertices
    int nvertice = 0;                // numero de vértices
    bool direcionado = false;        // grafo direcionado ou não

    // busca em profundide
    vector<char> corBEP;
    vector<int> tempoDescBEP;
    vector<int> tempoTermBEP;
    vector<int> antBEP;
    int tempo;

    // busca em largura
    vector<char> corBEL;
    vector<int> distBEL;
    vector<int> antBEL;

public:
    void importar()
    {
        ifstream arq;
        arq.open("arq.txt", ios::in); // abro o arquivo

        if (!arq.is_open())
        {
            cout << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        string linha;
        getline(arq, linha); // leitura da primeira linha (direcionado ou nao)

        if (linha.find("direcionado=sim") != string::npos) // verifica se o grafo e direcionado ou nao
        {
            direcionado = true;
        }
        else
        {
            direcionado = false;
        }

        arq >> nvertice; // leitura do numero de vertices
        vazio(nvertice); // passo como parametro (para definir o tamanho das matrizes)

        int id, x, y;
        string nome;
        for (int i = 0; i < nvertice; i++)
        {
            arq >> id >> x >> y;
            arq.ignore();
            getline(arq, nome);
            nomes[id] = nome;
            editarCoordenadaDoVertice(id, x, y); // adiciona as cordenadas do vertice (lendo no arquivo)
        }

        int qtdaresta;
        arq >> qtdaresta; // leitura da quantidade de arestas

        int u, v, p;
        for (int i = 0; i < qtdaresta; i++)
        {
            arq >> u >> v >> p;
            inserAresta(u, v, p); // insere as arestas
        }

        arq.close();
    }

    void insereManual()
    {
        char op;
        int qtd;

        do
        {
            cout << "O grafo e direcionado? (s|n): ";
            cin >> op;

            switch (op)
            {
            case 's':
                direcionado = true;
                op = '!';
                break;
            case 'n':
                direcionado = false;
                op = '!';
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
            }
        } while (op != '!');

        cout << "Digite a quantidade de vertices: ";
        cin >> qtd;
        vazio(qtd); // define o tamanho das matrizes
    }

    void vazio(int qtd)
    {
        nvertice = qtd;
        matriz.resize(nvertice, vector<int>(nvertice, 0)); // matriz (nvertice x nvertice)
        coordenadas.resize(nvertice, vector<int>(2, 0));   // matriz cordenadas (nvertice x 2)
        nomes.resize(nvertice);
    }

    void exibirTodasAsAdjacencias() // imprime a matriz
    {
        cout << "Matriz adjacente:\n\n    ";

        // Mostrar os vértices de destino no topo da matriz
        for (int i = 0; i < nvertice; i++)
        {
            cout << setw(5) << i;
        }

        cout << "\n\n";

        // Imprimir a matriz de adjacência
        for (int u = 0; u < nvertice; u++)
        {
            cout << setw(3) << u << "|"; // Mostrar vértice de origem ao lado da matriz

            for (int v = 0; v < nvertice; v++)
            {
                cout << setw(5) << matriz[u][v];
            }

            cout << "\n\n";
        }
    }

    int consultarSeAdjacente(int u, int v) // verificar se existe aresta
    {
        if (u < 0 || u >= nvertice || v < 0 || v >= nvertice)
        {
            return -2;
        }
        if (matriz[u][v] == 0) // verifica se NAO existe aresta
        {
            return -1; // retorna falso
        }
        else
        {
            return 1; // retorna verdadeiro
        }
    }

    void inserAresta(int u, int v, int p)
    {
        // verifica se os vértices são válidos
        if (u < 0 || u >= nvertice || v < 0 || v >= nvertice)
        {
            cout << "Vertice invalido!" << endl;
            return;
        }

        if (matriz[u][v] != 0) // verifica se a aresta já existe
        {
            cout << "Erro: A aresta ja existe!" << endl;
            Sleep(2000);
            return;
        }

        // verifica se o peso é válido
        if (p <= 0)
        {
            cout << "O valor do peso é invalido!" << endl;
            return;
        }

        // adiciona a aresta
        matriz[u][v] = p;
        if (direcionado == false) // se não for direcionado
        {
            matriz[v][u] = p;
        }
    }

    void inserirArestaConjunto()
    {
        char op;

        do
        {
            int u, v, p;
            cout << "Digite a origem: ";
            cin >> u;
            cout << "Digite o destino: ";
            cin >> v;
            cout << "Digite o peso: ";
            cin >> p;

            inserAresta(u, v, p);

            cout << "Inserir outra aresta? (s|n): ";
            cin >> op;
            if (op != 's' && op != 'n')
            {
                cout << "Opcao invalida!, retornando ao menu..." << endl;
                break;
            }
            cout << endl;
            system("cls");

        } while (op != 'n');
    }

    void removerAresta(int u, int v)
    {
        if (u < 0 || u >= nvertice || v < 0 || v >= nvertice) // verifica se o parametro é valido
        {
            cout << "Vertice invalido!" << endl;
            return;
        }

        if (matriz[u][v] == 0) // verifica se a aresta existe
        {
            cout << "A aresta nao existe!" << endl;
            return;
        }

        matriz[u][v] = 0; // remove a aresta principal

        if (direcionado == false) // se não for direcionado, remove também a volta
        {
            matriz[v][u] = 0;
        }

        cout << "Aresta removida com sucesso!" << endl;
    }

    bool editarCoordenadaDoVertice(int u, int x, int y)
    {
        if (u >= 0 && u < nvertice) // verifica se o indice do vertice que o usuario digitou é valido
        {
            coordenadas[u][0] = x; // se for troca as cordenadas
            coordenadas[u][1] = y;
            return true;
        }
        else
        {
            cout << endl;
            cout << "ERRO: O vertice nao existe!" << endl;
            return false;
        }
    }

    bool editarNomeDoVertice(int u, string novoNome)
    {
        if (u >= 0 && u < nvertice) // verifica se o indice do vertice que o usuario digitou é valido
        {
            nomes[u] = novoNome;
            return true;
        }
        else
        {
            cout << endl;
            cout << "ERRO: O vertice nao existe!" << endl;
            return false;
        }
    }

    int primeiroAdjacenteDoVertice(int u)
    {
        if (u >= 0 && u < nvertice) // verifica se o parametro passado e valido
        {
            for (int v = 0; v < nvertice; v++)
            {
                if (matriz[u][v] != 0) // percorre a linha da matriz procurando o primeiro adjacente
                {
                    return v; // se encontrar, retorna o indice
                }
            }
            return -1; // caso nao encontre nenhum adjacente, retorna -1
        }
        else
        {
            return -2; // parametro invalido
        }
    }

    int proximoAdjacenteDoVertice(int u, int atual)
    {
        if ((u >= 0 && u < nvertice) && (atual >= 0 && atual < nvertice)) // verifica se indice passado no paramentro e valido
        {
            for (int v = atual + 1; v < nvertice; v++) // percorre a linha a partir da proxima coluna apos "atual"
            {
                if (matriz[u][v] != 0)
                {
                    return v; // se encontrar, retorna o indice encontrado
                }
            }
            return -1; // caso nao encontre nenhum adjacente, retorna -1
        }
        else
        {
            return -2;
        }
    }

    void listaCompletaDeAdjacentesDoVertice(int u)
    {
        if (u >= 0 && u < nvertice) // verifica se o indice e valido
        {
            int adj = primeiroAdjacenteDoVertice(u); // variavel "adj" recebe o indice do primeiro adjacente

            while (adj != -1) // enquanto tiver adjacentes
            {
                cout << adj << " ";                      // imprime na tela
                adj = proximoAdjacenteDoVertice(u, adj); // "adj" recebe o proximo adjacente
            }
        }
        else
        {
            cout << "valor invalido!";
            return;
        }
    }

    int contarArestas()
    {
        int contador = 0;

        for (int u = 0; u < nvertice; u++)
        {
            for (int v = 0; v < nvertice; v++)
            {
                if (matriz[u][v] != 0 && (direcionado || v > u)) // v>u para não contar a aresta 2 vezes
                {
                    contador++;
                }
            }
        }
        return contador;
    }

    void exportar()
    {
        ofstream arq;
        arq.open("saida.txt", ios::out);
        if (!arq.is_open())
        {
            cout << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        if (direcionado == true) // exporta se e direcionado ou nao
        {
            arq << "direcionado=sim" << endl;
        }
        else
        {
            arq << "direcionado=nao" << endl;
        }

        arq << nvertice << endl; // exporta a quantidade de vertices

        for (int i = 0; i < nvertice; i++) // exporta as cordenadas dos vertices
        {
            arq << i << " " << coordenadas[i][0] << " " << coordenadas[i][1] << " " << nomes[i] << endl;
        }

        int qtdarestas = contarArestas();
        arq << qtdarestas << endl; // exporta a quantidade de arestas

        for (int u = 0; u < nvertice; u++) // exporta as arestas
        {
            for (int v = 0; v < nvertice; v++)
            {
                if (matriz[u][v] != 0)
                {
                    if (direcionado || v > u) // v>u para não repetir a aresta
                    {
                        arq << u << " " << v << " " << matriz[u][v] << endl;
                    }
                }
            }
        }

        arq.close();
    }

    void mostrarGraficamente()
    {
        cout << "funcao nao adicionada!" << endl;
    }

    void imprimirTabelaBEP()
    {
        cout << "\n BUSCA EM PROFUNDIDADE\n";
        cout << " Vert   | Desc  | Term  | Ant   | Cor\n";
        cout << "--------------------------------------\n";

        for (int i = 0; i < nvertice; i++)
        {
            cout << " " << i << "\t| ";
            cout << tempoDescBEP[i] << "\t| ";
            cout << tempoTermBEP[i] << "\t| ";

            if (antBEP[i] == -1)
                cout << "-\t| ";
            else
                cout << antBEP[i] << "\t| ";

            cout << corBEP[i] << endl;
        }
    }

    // explora completamente um grafo, indo o mais fundo possível em cada caminho antes de voltar.
    void buscaEmProfundidade()
    {
        tempoDescBEP.assign(nvertice, 0);
        tempoTermBEP.assign(nvertice, 0);
        antBEP.assign(nvertice, -1);
        corBEP.assign(nvertice, 'B');
        tempo = 0;

        for (int u = 0; u < nvertice; u++)
        {
            if (corBEP[u] == 'B')
            {
                visitaEmProfundidade(u);
            }
        }
        imprimirTabelaBEP();
    }

    void visitaEmProfundidade(int u)
    {
        corBEP[u] = 'C'; // marca o vertice como processado
        tempo++;
        tempoDescBEP[u] = tempo;
        cout << "Descobrindo vertice " << u << " (tempo = " << tempoDescBEP[u] << ")" << endl;

        int v = primeiroAdjacenteDoVertice(u); 

        while (v != -1) // percorre todos adjacentes de u
        {
            cout << "Explorando aresta " << u << " -> " << v << endl;
            if (corBEP[v] == 'B') // vertice adjacente nao visitado
            {
                antBEP[v] = u;
                cout << "Antecessor de " << v << " = " << u << endl;
                visitaEmProfundidade(v); // continuar a partir de v
            }
            v = proximoAdjacenteDoVertice(u, v); // avanca para o proximo adjacente
        }
        // apos finalizar o processo
        corBEP[u] = 'P';
        tempo++;
        tempoTermBEP[u] = tempo;
        cout << "Finalizacao: vertice " << u << " (tempo = " << tempoTermBEP[u] << ")" << endl;
    }

    void imprimirTabelaBEL()
    {
        cout << "\n BUSCA EM LARGURA\n";
        cout << " Vert   | Cor   | Dist  | Ant\n";
        cout << "------------------------------\n";

        for (int i = 0; i < nvertice; i++)
        {
            cout << " " << i << "\t| ";
            cout << corBEL[i] << "\t| ";
            cout << distBEL[i] << "\t| ";

            if (antBEL[i] == -1)
                cout << "-" << endl;
            else
                cout << antBEL[i] << endl;
        }
    }

    // percorrer o grafo por níveis, visitando primeiro todos os vértices mais próximos da origem.
    void buscaEmLargura()
    {
        antBEL.assign(nvertice, -1);
        corBEL.assign(nvertice, 'B');
        distBEL.assign(nvertice, INF);

        for (int u = 0; u < nvertice; u++)
        {
            if (corBEL[u] == 'B')
            {
                visitaEmLargura(u);
            }
        }
        imprimirTabelaBEL();
    }

    void visitaEmLargura(int u)
    {
        corBEL[u] = 'C';
        distBEL[u] = 0;
        queue<int> f; // fila f
        f.push(u); // adiciono u na fila
        cout << "Vertice " << u << " foi descoberto (dist=0)" << endl;

        while (!f.empty())
        {
            int v = f.front();
            f.pop();
            int k = primeiroAdjacenteDoVertice(v);

            while (k != -1) // perocorre todos adjacentes de v
            {
                if (corBEL[k] == 'B') // se o vertice adjacente ainda nao foi descoberto
                {
                    cout << "Visitando vertice " << k << endl;
                    corBEL[k] = 'C';
                    antBEL[k] = v;
                    distBEL[k] = (distBEL[v] + 1); // Como k é adjacente de v, sua distância é a de v + 1
                    f.push(k);
                }
                k = proximoAdjacenteDoVertice(v, k);
            }
            // apos processar todos adjacentes
            corBEL[v] = 'P';
            cout << "Vertice " << v << " finalizado" << endl;
        }
    }

    // Encontrar a Arvore geradora minima de um grafo
    void Prim()
    {
        if (direcionado) // O algoritmo de Prim premite somente grafos NAO direcionados.
        {
            cout << "O algoritmo de Prim so funciona para grafos NAO direcionados!" << endl;
            return;
        }

        int origem = 0;

        vector<int> P(nvertice, INF); // guarda o menor peso
        vector<int> A(nvertice, -1);  // antecessores
        vector<bool> naAGM(nvertice, false); // indicar se o vertice foi incluido na AGM

        P[origem] = 0; // vertice inicial
        cout << "Prim iniciando no vertice " << origem << endl;

        for (int i = 0; i < nvertice - 1; i++)
        {
            int u = -1, menor = INF;

            for (int v = 0; v < nvertice; v++) // escolhe o vertice fora da AGM com menor peso
            {
                if (!naAGM[v] && P[v] < menor)
                {
                    menor = P[v];
                    u = v;
                }
            }

            if (u == -1)
            {
                cout << "Grafo nao conexo!" << endl;
                return;
            }

            naAGM[u] = true; // marca o vertice como true na AGM
            cout << "Vertice escolhido: " << u << endl;
            cout << "Vertice " << u << " adicionado a AGM" << endl;

            // Atualiza os custos dos vértices adjacentes a u
            for (int v = 0; v < nvertice; v++)
            {
                // Se existe aresta entre u e v, v ainda não está na AGM
                // e o peso da aresta é menor que o custo atual.
                if (matriz[u][v] != 0 && !naAGM[v] && matriz[u][v] < P[v])
                {
                    P[v] = matriz[u][v];
                    A[v] = u;
                    cout << " Atualiza aresta (" << u << " - " << v << ") peso = " << matriz[u][v] << endl;
                }
            }
        }

        int pesoTotal = 0;
        cout << "\nArvore geradora minima encontrada: " << endl;

        for (int v = 0; v < nvertice; v++)
        {
            if (A[v] != -1)
            {
                cout << A[v] << " " << v << "\t(peso=" << matriz[A[v]][v] << ")" << endl;
                pesoTotal += matriz[A[v]][v];
            }
        }
        cout << "(Peso total = " << pesoTotal << ")" << endl;
    }

    
    void Djkstra(string origem, string destino) // Calcula o caminho minimo entre a origem e o destino
    {
        int o=-1, d=-1;
        for (int i = 0; i < nvertice; i++) // Identifica os indices
        {
            if (nomes[i] == origem)
            {
                o=i;
            }
            if (nomes[i] == destino)
            {
                d=i;
            }
        }

        if (o == -1 || d==-1)
        {
            cout << "Erro: Vertice de origem ou destino nao encontrado.\n";
            return;
        }

        vector<int> V(nvertice); // vertices nao processados
        vector<int> P(nvertice, INF); // pesos
        vector<int> A(nvertice, -1); // antecessores

        // Inicializa V com os indices
        for (int i = 0; i < nvertice; i++)
        {
            V[i] = i;
        }

        // Define distancia da origem
        P[o] = 0;

        // Enquanto existir vertices nao processados
        while (!V.empty())
        {
            int menor = 0;

            // encontra o vertice com menor peso
            for (int i = 0; i < V.size(); i++)
            {
                if (P[V[i]] < P[V[menor]])
                {
                    menor = i;
                }
            }

            // u guarda o indice do vertice
            int u = V[menor];

            // remove u de V, pois foi processado
            V.erase(V.begin() + menor);

            // relaxa as arestas que saem de u
            for (int v = 0; v < nvertice; v++)
            {
                if (matriz[u][v] != 0 && P[u] != INF)
                {
                    // Se passar por u gera um caminho menor ate v
                    if (P[v] > (P[u] + matriz[u][v]))
                    {
                        // Atualiza a menor distancia ate v
                        P[v] = (P[u] + matriz[u][v]);
                        A[v] = u;
                    }
                }
            }
        }
        
        // Verificar se existe caminho
        if (A[d] == -1 && d != o)
        {
            cout << "Nao existe caminho entre os vertices!" << endl;
            return;
        }
        
        // reconstruir caminho a partir dos antecessores
        vector<int> caminho;
        int atual = d;

        while (atual != -1)
        {
            caminho.push_back(atual);
            atual = A[atual];
        }
        
        //imprimir resultado
        cout << "\nCaminho minimo de " << origem << " ate " << destino << ":\n";

        for (int i = caminho.size()-1; i>=0; i--)
        {
            cout << nomes[caminho[i]];
            if (i!=0)
            {
                cout << " -> ";
            }  
        }
        cout << "\n(Distancia total = " << P[d] << ")" <<endl;
    }
};