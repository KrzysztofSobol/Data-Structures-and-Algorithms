#include <iostream>
#include <fstream>
#include <vector>
#include <queue> 

using namespace std;

int INF = 2147483647;
int cities, roads, p_roads;

struct Node {
    int length;
    int dest;
}typedef Node;

struct CompareLength {
    bool operator()(const Node& node1, const Node& node2) const {
        return node1.length > node2.length;
    }
};

vector<int> Dijkstra(vector<vector<Node>>& graph) {
    vector<int> d;
    bool* visited = new bool[cities];
    for (int i = 0; i < cities; i++) {
        visited[i] = false;
        d.push_back(INF);
    }

    priority_queue<Node, vector<Node>, CompareLength> priorityQueue;
    Node node{ 0,0 };
    priorityQueue.push(node);
    d[0] = 0;

    while (!priorityQueue.empty()) {
        int x = priorityQueue.top().dest;
        priorityQueue.pop();

        if (visited[x]) continue;
        visited[x] = true;

        int dest;
        for (int i = 0; i < graph[x].size(); i++) {
            dest = graph[x][i].dest;
            Node node{ d[x] + graph[x][i].length, dest };
            if (d[x] + graph[x][i].length < d[dest]) {
                priorityQueue.push(node);
                d[dest] = d[x] + graph[x][i].length;
            }
        }
    }

    return d;
}

int CheckDeeper(int x, int r, vector<int>& d, vector<bool>& v, vector<vector<Node>>& graph) {
    int dest, count = 0;
    for (int i = 0; i < graph[x].size(); i++) {

        int c_road = r + graph[x][i].length;
        dest = graph[x][i].dest;

        if (c_road < d[dest]) {
            if (v[dest] == false) {
                count++;
                if (count > 100)
                    break;
            }
            d[dest] = c_road;
            v[dest] = true;
            count += CheckDeeper(dest, c_road, d, v, graph);
        }
    }
    return count;
}

void PossibleRoad(int a, int b, int r, vector<int> d, vector<vector<Node>>& graph) {
    ofstream out("out.txt", ios::app);

    vector<bool> v(cities, false);
    int count = 0;
    int x, abr;

    if (d[a - 1] <= d[b - 1]) {
        abr = d[a - 1] + r;
        x = b - 1;
    }
    else {
        abr = d[b - 1] + r;
        x = a - 1;
    }

    if (abr < d[x]) {
        count++;
        d[x] = abr;
    } else {
        out << 0 << endl;
        return;
    }

    count += CheckDeeper(x, abr, d, v, graph);

    if (count > 100)
        out << "100+" << endl;
    else
        out << count << endl;
    out.close();
}

int main()
{
    // input file
    string input;
    cout << "Podaj nazwe pliku: ";
    cin >> input;
    input += ".txt";

    // input
    ifstream in(input);
    ofstream out("out.txt");
    out.close();

    if (!in.is_open()) {
        cout << "ERROR: Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    in >> cities >> roads >> p_roads;

    // graph array
    cout << "Wczytywanie danych";
    vector<vector<Node>> graph(cities);
    int x, y, l;
    for (int i = 0; i < roads; i++) {
        in >> x >> y >> l;
        graph[x - 1].push_back(Node{ l,y - 1 });
        graph[y - 1].push_back(Node{ l,x - 1 });
    }
    cout << " done" << endl;

    // Dijkstra
    vector<int> d(cities);
    d = Dijkstra(graph);

    cout << "Dijksrta done\n";

    // p_roads
    for (int i = 0; i < p_roads; i++) {
        in >> x >> y >> l;
        graph[x - 1].push_back(Node{ l,y - 1 });
        graph[y - 1].push_back(Node{ l,x - 1 });

        PossibleRoad(x, y, l, d, graph);

        graph[x - 1].pop_back();
        graph[y - 1].pop_back();
    }
    cout << "p_roads done\n";

    return 0;
}