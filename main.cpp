#include <iostream>
#include "grafo.cpp"
#include <limits>
using namespace std;

int main()
{

    Grafo grafo;
    int op;
    bool prox = false;

    while (!prox)
    {
        system("cls");
        cout << "-------------------- MENU --------------------" << endl;
        cout << "Como deseja iniciar o grafo?" << endl;
        cout << "1 - Importar arquivo de texto" << endl;
        cout << "2 - Criar grafo vazio (inserir manualmente)" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;

        if (op == 1)
        {
            grafo.importar();
            prox = true;
            break; // sai do menu
        }
        else if (op == 2)
        {
            grafo.insereManual();
            prox = true;
            break; // sai do menu
        }
        else
        {
            cout << "Opcao invalida!\n";
            cout << "\nAperte enter para escolher novamente!\n";
            cin.ignore(); // Limpar o buffer
            cin.get();    // Espera o usuario apertar enter
        }
    }

    cin.ignore();

    do
    {
        system("cls");

        cout << "==================== MENU ====================" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Exibir todas adjacencias (Matriz) " << endl;
        cout << "2 - Consultar adjacente" << endl;
        cout << "3 - Inserir aresta" << endl;
        cout << "4 - Inserir arestas em conjunto" << endl;
        cout << "5 - Remover aresta" << endl;
        cout << "6 - Editar cordenada do vertice" << endl;
        cout << "7 - Primeiro adjacente do vertice" << endl;
        cout << "8 - Proximo adjacente do vertice" << endl;
        cout << "9 - Lista completa de adjacentes do vertice" << endl;
        cout << "10 - Contar arestas" << endl;
        cout << "11 - Exportar" << endl;
        cout << "12 - Editar nome do vertice" << endl;
        cout << "13 - Busca em profundidade" << endl;
        cout << "14 - Busca em largura" << endl;
        cout << "15 - Prim" << endl;
        cout << "16 - Dijkstra" << endl; 
        cout << "==============================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 0: // Sair
        {
            cout << "Saindo..." << endl;
            return 0;
            break;
        }
        case 1: // Imprimir matriz (arestas)
        {
            grafo.exibirTodasAsAdjacencias();
            break;
        }
        case 2: // Consultar se existe aresta
        {
            int u, v;
            cout << "Digite a origem: ";
            cin >> u;
            cout << "Digite o destino: ";
            cin >> v;
            cout << endl;

            if (grafo.consultarSeAdjacente(u, v) == 1)
                cout << "Existe aresta!" << endl;
            else if (grafo.consultarSeAdjacente(u, v) == -1)
                cout << "Nao existe aresta!" << endl;
            else
                cout << "Vertice invalido!" << endl;
            break;
        }
        case 3: // Inserir aresta
        {
            int u, v, p;
            cout << "Digite a origem: ";
            cin >> u;
            cout << "Digite o destino: ";
            cin >> v;
            cout << "Digite o peso: ";
            cin >> p;
            grafo.inserAresta(u, v, p);
            break;
        }
        case 4: // Inserir aresta em conjunto
        {
            grafo.inserirArestaConjunto();
            break;
        }
        case 5: // Remover aresta
        {
            int u, v;
            cout << "digite a origem: ";
            cin >> u;
            cout << "Digite o destino: ";
            cin >> v;
            grafo.removerAresta(u, v);
            break;
        }
        case 6: // Editar cordenada do vertice
        {
            int u, x, y;
            cout << "Digite o indice do vertice que deseja editar a coordenada: ";
            cin >> u;
            cout << "Digite a nova posicao x: ";
            cin >> x;
            cout << "Digite a nova posicao y: ";
            cin >> y;
            if (grafo.editarCoordenadaDoVertice(u, x, y))
            {
                cout << endl;
                cout << "Coordenada do vertice editada com sucesso!" << endl;
            }
            break;
        }
        case 7: // Primeiro adjacente do vertice
        {
            int u;
            cout << "Digite o indice do vertice: ";
            cin >> u;

            if (grafo.primeiroAdjacenteDoVertice(u) == -2)
            {
                cout << "O valor do vertice e invalido!";
                break;
            }
            else if (grafo.primeiroAdjacenteDoVertice(u) == -1)
            {
                cout << "O vertice nao possui adjacente!\n"
                     << endl;
                break;
            }
            else
            {
                cout << "Primeiro adjacente do vertice: " << grafo.primeiroAdjacenteDoVertice(u) << endl;
                break;
            }
        }
        case 8: // Proximo adjacente do vertice
        {
            int u, atual;
            cout << "Digite o vertice: ";
            cin >> u;
            cout << "A partir de qual?: ";
            cin >> atual;

            int prox = grafo.proximoAdjacenteDoVertice(u, atual);

            if (prox == -1)
                cout << "Nao ha proximo adjacente." << endl;
            else if (prox == -2)
                cout << "Parametro Invalido!" << endl;
            else
            {
                cout << "Proximo adjacente: " << prox << endl;
            }
            break;
        }

        case 9: // Lista completa de adjacente
        {
            int u;
            cout << "Digite o indice do vertice: ";
            cin >> u;
            grafo.listaCompletaDeAdjacentesDoVertice(u);
            break;
        }
        case 10: // Quantidade de arestas
        {
            cout << "Quantidade de arestas: " << grafo.contarArestas() << endl;
            break;
        }
        case 11: // Exportar
        {
            grafo.exportar();
            break;
        }
        case 12: // Editar nome do vertice
        {
            int u;
            string novoNome;
            cout << "Digite o indice do vertice que deseja editar o nome: ";
            cin >> u;
            cin.ignore();
            cout << "Digite o novo nome: ";
            getline(cin, novoNome);
            if (grafo.editarNomeDoVertice(u, novoNome))
            {
                cout << endl;
                cout << "Nome do vertice editado com sucesso!" << endl;
            }
            break;
        }
        case 13: // Busca em profundidade
        {
            grafo.buscaEmProfundidade();
            break;
        }
        case 14: // Busca em largura
        {
            grafo.buscaEmLargura();
            break;
        }
        case 15: // Prim
        {
            grafo.Prim();
            break;
        }
        case 16: // Djkstra
        {
            string origem, destino;
            cin.ignore();
            cout << "Digite o nome da origem: ";
            getline(cin, origem);
            cout << "Digite o nome do destino: ";
            getline(cin, destino);
            grafo.Djkstra(origem, destino);
            break;
        }
        default:
        {
            cout << "Opcao invalida!" << endl;
            break;
        }
        }
        cout << endl;
        cout << "Aperte ENTER para continuar..." << endl;
        cin.ignore(); // Limpa o buffer
        cin.get();    // Espera o usuario apertar enter
    } while (op != 0);

    return 0;
}