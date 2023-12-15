#include <iostream>
#include <fstream>
#include "dsu.h"
#include "graph.h"

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*   value - значение для заполнения
*/
template <typename T>
T readValue(const char* prompt = "") {
    T value = 0;
    cout << prompt;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Incorrect input. Enter new value: ";
            cin.clear();
            // numeric_limits<streamsize> это предел количества знаков в streamsize (вернёт число)
            // нужно чтобы очистить максимальное количество оставшихся символов в буфере до новой строки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void loadGraph(Graph& g) {
    while (true) {
        try {
            system("cls");
            g = Graph::fromFile("input.txt");
            cout << "Loaded successfully\n";
            return;
        } catch (runtime_error e) {
            cout << "Loading error: " << e.what() << endl;
            cout << "Press anything to load again\n";
            system("pause");
        }
    }
}

int main()
{
    Graph graph;
    loadGraph(graph);
    while (true) {
        system("cls");
        cout << "Graph loaded\n";
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. Reload graph\n"
            "2. MST to console\n"
            "3. MST to file\n"
            "4. Depth First Search\n"
            "5. Breadth First Search\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                loadGraph(graph);
                break;
            }
            case 2: {
                auto mst = graph.mst();
                for (Edge e : mst.get_edges()) {
                    cout << e.a << ' ' << e.b << endl;
                }
                cout << mst.get_mass() << endl;
                break;
            }
            case 3: {
                ofstream ofs("output.txt");
                auto mst = graph.mst();
                for (Edge e : mst.get_edges())
                    ofs << e.a << ' ' << e.b << endl;
                ofs << mst.get_mass();
                break;
            }
            case 4: {
                auto w = graph.dfs(graph.first());
                for(std::string s : w) {
                    cout << s << ' ';
                }
                cout << endl;
                break;
            }
            case 5: {
                auto w = graph.bfs(graph.first());
                for(std::string s : w) {
                    cout << s << ' ';
                }
                cout << endl;
                break;
            }
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}