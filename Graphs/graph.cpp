#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <optional>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

using Graph = unordered_map<string, vector<pair<string,int>>>;

static inline string trim(const string &s) {
    size_t a = 0, b = s.size();

    while (a < b && isspace((unsigned char)s[a])) ++a;
    while (b > a && isspace((unsigned char)s[b - 1])) --b;

    return s.substr(a, b - a);
}

vector<string> split_csv_line(const string &line) {
    vector<string> out;
    string cur;
    bool in_quotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            out.push_back(trim(cur)); cur.clear();
        } else {
            cur.push_back(c);
        }
    }

    out.push_back(trim(cur));

    return out;
}

void addVertices(Graph &G, const vector<string> &vertices) {
    for (const auto &v : vertices) {
        if (G.find(v) == G.end()) G[v] = {};
    }
}

void addEdges(Graph &G, const vector<tuple<string, string, int>> &edges) {
    for (const auto &t : edges) {
        const string &u = get<0>(t);
        const string &v = get<1>(t);
        int w = get<2>(t);

        G[u].push_back({v, w});
    }
}

// Create flight network from CSV file. CSV header expected. Fields: origin,to,duration,distance
Graph create_flight_network(const string &filename, int option) {
    Graph graph;

    ifstream ifs(filename);
    if (!ifs) return graph;

    string line;
    if (!getline(ifs, line)) return graph; // skip header

    while (getline(ifs, line)) {
        if (line.empty()) continue;

        auto cols = split_csv_line(line);
        if (cols.size() < 4) continue;

        string from = cols[0];
        string to = cols[1];
        int duration = 0, distance = 0;

        try { duration = stoi(cols[2]); } catch(...) { duration = 0; }
        try { distance = stoi(cols[3]); } catch(...) { distance = 0; }

        addVertices(graph, {from, to});

        if (option == 1) addEdges(graph, {{from, to, duration}});
        else if (option == 2) addEdges(graph, {{from, to, distance}});
    }

    return graph;
}

vector<string> get_flight_connections(const Graph &graph, const string &city, char option) {
    vector<string> connections;

    auto it = graph.find(city);
    if (it == graph.end()) return connections;

    if (option == 'o') {
        for (auto &e : it->second) connections.push_back(e.first);
    } else if (option == 'i') {
        for (auto &p : graph) {
            for (auto &e : p.second) if (e.first == city) connections.push_back(p.first);
        }
    }

    return connections;
}

int get_number_of_flight_connections(const Graph &graph, const string &city, char option) {
    auto con = get_flight_connections(graph, city, option);
    return static_cast<int>(con.size());
}

optional<int> get_flight_details(const Graph &graph, const string &origin, const string &destination) {
    auto it = graph.find(origin);
    if (it == graph.end()) return nullopt;

    for (auto &e : it->second) if (e.first == destination) return e.second;

    return -1;
}

void add_flight(Graph &graph, const string &origin, const string &destination, int weight) {
    if (graph.find(origin) == graph.end()) {
        cerr << origin << " not accessed by graph\n";
        return;
    }

    if (graph.find(destination) == graph.end()) {
        cerr << destination << " not accessed by graph\n";
        return;
    }

    for (size_t i = 0; i < graph[origin].size(); ++i) {
        if (graph[origin][i].first == destination) {
            graph[origin][i].second = weight;
            return;
        }
    }

    addEdges(graph, {{origin, destination, weight}});
}

void add_airport(Graph &graph, const string &city, const string &destination, int weight) {
    if (graph.find(city) != graph.end()) {
        cerr << city << " already exists\n";
        return;
    }

    addVertices(graph, {city});
    addEdges(graph, {{city, destination, weight}});
}

vector<string> get_secondary_flights(const Graph &graph, const string &city) {
    if (graph.find(city) == graph.end()) return {};

    vector<string> secondary;
    auto direct = get_flight_connections(graph, city, 'o');
    unordered_set<string> seen;

    for (auto &c : direct) {
        auto it = graph.find(c);
        if (it == graph.end()) continue;

        for (auto &e : it->second) {
            if (seen.insert(e.first).second) secondary.push_back(e.first);
        }
    }

    return secondary;
}

int counting_common_airports(const Graph &graph, const string &cityA, const string &cityB) {
    auto A = get_flight_connections(graph, cityA, 'o');
    auto B = get_flight_connections(graph, cityB, 'o');

    unordered_set<string> setB(B.begin(), B.end());
    int common = 0;

    for (auto &c : A) if (setB.find(c) != setB.end()) ++common;

    return common;
}

void remove_flight(Graph &graph, const string &origin, const string &destination) {
    if (graph.find(origin) == graph.end()) { 
        cerr << origin << " not accessed by graph\n"; 
        return; 
    }

    if (graph.find(destination) == graph.end()) { 
        cerr << destination << " not accessed by graph\n"; 
        return; 
    }

    auto &vec1 = graph[origin];
    vec1.erase(remove_if(vec1.begin(), vec1.end(), 
        [&](const pair<string,int> &p){ 
            return p.first == destination; 
        }), 
    vec1.end());

    auto &vec2 = graph[destination];
    vec2.erase(remove_if(vec2.begin(), vec2.end(), 
        [&](const pair<string,int> &p){ 
            return p.first == origin; 
        }), vec2.end());
}

void remove_airport(Graph &graph, const string &city) {
    if (graph.find(city) == graph.end()) { cerr << city << " not accessed by graph\n"; return; }
    graph.erase(city);

    for (auto &p : graph) {
        auto &vec = p.second;
        vec.erase(remove_if(vec.begin(), vec.end(), 
            [&](const pair<string,int> &e){ 
                return e.first == city; 
            }), 
        vec.end());
    }
}

// DFS to collect all routes (allow revisiting destination only at end)
void DFS_all_routes(const Graph &graph, const string &origin, const string &destination, vector<string> &route, vector<vector<string>> &all_routes) {
    if (route.size() > 1 && origin == destination) {
        all_routes.push_back(route);
        return;
    }

    auto it = graph.find(origin);
    if (it == graph.end()) return;

    for (auto &nei : it->second) {
        const string &neighbor = nei.first;
        bool canVisit = (find(route.begin(), route.end(), neighbor) == route.end()) || (neighbor == destination && route.size() > 1);

        if (canVisit) {
            route.push_back(neighbor);
            DFS_all_routes(graph, neighbor, destination, route, all_routes);
            route.pop_back();
        }
    }
}

vector<vector<string>> find_all_routes(const Graph &graph, const string &origin, const string &destination) {
    vector<vector<string>> all_routes;

    if (graph.find(origin) == graph.end() || graph.find(destination) == graph.end()) return {};
    if (origin == destination) return {};

    vector<string> route{origin};
    DFS_all_routes(graph, origin, destination, route, all_routes);

    return all_routes;
}

// DFS to count layovers (route length - 2)
void DFS_layovers(const Graph &graph, const string &origin, const string &destination, vector<string> &route, vector<int> &layovers) {
    if (route.size() > 1 && origin == destination) {
        layovers.push_back(static_cast<int>(route.size()) - 2);
        return;
    }

    auto it = graph.find(origin);
    if (it == graph.end()) return;

    for (auto &nei : it->second) {
        const string &neighbor = nei.first;
        bool canVisit = (find(route.begin(), route.end(), neighbor) == route.end()) || (neighbor == destination && route.size() > 1);

        if (canVisit) {
            route.push_back(neighbor);
            DFS_layovers(graph, neighbor, destination, route, layovers);
            route.pop_back();
        }
    }
}

vector<int> find_number_of_layovers(const Graph &graph, const string &origin, const string &destination) {
    if (graph.find(origin) == graph.end() || graph.find(destination) == graph.end()) return {};
    if (origin == destination) return {};

    vector<int> layovers;
    vector<string> route{origin};

    DFS_layovers(graph, origin, destination, route, layovers);
    sort(layovers.begin(), layovers.end());

    return layovers;
}

// BFS shortest route (in terms of edges)
vector<string> BFS_shortest_route(const Graph &graph, const string &origin, const string &destination) {
    if (graph.find(origin) == graph.end() || graph.find(destination) == graph.end()) return {};
    if (origin == destination) return {};

    queue<vector<string>> q;
    q.push({origin});

    while (!q.empty()) {
        auto route = q.front(); q.pop();
        string city = route.back();

        if (city == destination) return route;
        auto it = graph.find(city);
        if (it == graph.end()) continue;

        for (auto &nei : it->second) {
            auto new_route = route;
            new_route.push_back(nei.first);
            q.push(new_route);
        }
    }

    return {};
}

// Dijkstra shortest route (weights present)
vector<string> Dijkstra_shortest_route(const Graph &graph, const string &origin, const string &destination) {
    if (graph.find(origin) == graph.end() || graph.find(destination) == graph.end()) return {};
    if (origin == destination) return {};

    unordered_map<string, double> dist;
    unordered_map<string, string> pred;

    for (auto &p : graph) dist[p.first] = numeric_limits<double>::infinity();
    dist[origin] = 0.0;

    // simple priority queue using set of pairs
    using P = pair<double,string>;
    set<P> pq;
    pq.insert({0.0, origin});

    while (!pq.empty()) {
        auto it = pq.begin();
        double d = it->first; string u = it->second;
        pq.erase(it);

        if (u == destination) break;

        for (auto &e : graph.at(u)) {
            string v = e.first; double w = e.second;
            if (dist[u] + w < dist[v]) {
                // update
                if (pq.find({dist[v], v}) != pq.end()) pq.erase({dist[v], v});

                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.insert({dist[v], v});
            }
        }
    }
    vector<string> route;
    string cur = destination;

    if (pred.find(cur) == pred.end() && cur != origin) {
        // if no predecessor and not origin, maybe origin==destination handled earlier; return empty
        if (cur != origin) return {};
    }

    while (!cur.empty()) {
        route.insert(route.begin(), cur);
        if (cur == origin) break;

        auto pit = pred.find(cur);
        if (pit == pred.end()) break;
        cur = pit->second;
    }

    return route;
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <csv-file>\n";
        return 0;
    }

    string file = argv[1];
    auto g = create_flight_network(file, 1);
    cout << "Graph loaded. Airports: " << g.size() << "\n";

    // Example: print outgoing from first airport
    if (!g.empty()) {
        auto it = g.begin();
        cout << "Outgoing from " << it->first << ":\n";
        for (auto &e : it->second) cout << "  " << e.first << " (" << e.second << ")\n";
    }
    
    return 0;
}
