#pragma once
#include <iostream>
#include <vector>
#include <algorithm>  
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;


#pragma region Constantes

typedef pair<int, int> int_pair;
typedef pair<int, string> wt_pair;
typedef unordered_map <string, vector<wt_pair>> Hash_Graph;
typedef priority_queue <int_pair, vector<int_pair>, greater<int_pair>> min_heap_pair_queue;
typedef priority_queue <wt_pair, vector<wt_pair>, greater<wt_pair>> min_heap_wt_pair_queue;

const string NV_INDEX = "No se han indicado vertices validos";
const string NVK = "No se han indicado llaves validas";
const unsigned short int INFINITE = 9999;
const short int NV_VERTEX = -1;
const string NANKEY = "NAN";

#pragma endregion

#pragma region Vertices

class Vertex {
private:
	unsigned short int index;
	vector<vector<int>> shortest_paths;
	//key = Row, pair = (Weight, Pre Vertex)
	unordered_map<string, wt_pair> hash_shortest_paths;
	unordered_map<string, vector<vector<wt_pair>>>  possible_paths;
	string tag;

public:
	//Read nd_shortest_paths 
	//Return a vector where first[0] space is the shortest distance
	//The remaining spaces represent the vertexes indexes to achieve the shortest distance
	//Vertexes indexes go from start to end
	vector<int> shortest_path(int end_idx) {
		vector<int> path;
		int objective = end_idx, previous;
		previous = objective;
		while (true) {
			previous = shortest_paths[objective][1];
			if (previous == NV_VERTEX)
				break;
			path.insert(path.begin(), previous);
			objective = previous;
		}
		path.insert(path.begin(), shortest_paths[end_idx][0]);
		path.push_back(end_idx);
		return path;
	}

	vector<wt_pair> hash_shortest_path(string end_vertex) {
		vector<wt_pair> path;
		string objective = end_vertex, previous;
		previous = objective;
		while (true) {
			previous = hash_shortest_paths.at(objective).second;
			if (previous == NANKEY)
				break;
			path.insert(path.begin(), make_pair(hash_shortest_paths.at(previous).first, previous));
			objective = previous;
		}
		path.insert(path.begin(), make_pair(hash_shortest_paths.at(end_vertex).first, end_vertex));
		path.push_back(make_pair(hash_shortest_paths.at(end_vertex).first, end_vertex));
		return path;
	}


	Vertex() {}
	Vertex(string p_tag) {
		tag = p_tag;
	}

	string get_tag() {
		return tag;
	}
	vector<vector<int>> get_shortest_paths() {
		return shortest_paths;
	}
	unordered_map<string, wt_pair> get_hash_shortest_paths() {
		return hash_shortest_paths;
	}
	unordered_map<string, vector<vector<wt_pair>>> get_possible_paths() {
		return possible_paths;
	}
	int get_index() {
		return index;
	}
	void set_index(int n_index) {
		index = n_index;
	}
	void set_tag(string n_tag) {
		tag = n_tag;
	}
	void set_shortest_path(vector<vector<int>> p_nd_shortest_path) {
		shortest_paths = p_nd_shortest_path;
	}
	void set_hash_shortest_path(unordered_map<string, wt_pair> p_hash_shortest_paths) {
		hash_shortest_paths = p_hash_shortest_paths;
	}
	void set_possible_paths(unordered_map<string, vector<vector<wt_pair>>> p_possible_paths) {
		possible_paths = p_possible_paths;
	}
	void add_possible_path_key(string destination) {
		vector<vector<wt_pair>> tmp;
		possible_paths.insert(make_pair(destination, tmp));
	}
	void add_possible_path(string key, vector<wt_pair> path) {
		possible_paths.at(key).push_back(path);
	}
};

#pragma endregion

#pragma region Graph

class Graph {

private:
	size_t vertexes;
	vector<Vertex> vertexes_list;
	Hash_Graph hash_graph;
	vector<vector<int>>  graph;
	void init_graph() {
		graph.resize(vertexes);/*Rows - Origin*/
		for (size_t i = 0; i < vertexes; i++) {
			vertexes_list[i].set_index(i); /*Assigning the indices of the vertices*/
			graph[i].resize(vertexes);/*Colums - End*/
			for (size_t j = 0; j < vertexes; j++) {
				graph[i][j] = 0;
			}
		}

	}
	void init_map_graph() {
		size_t i = 0;
		for (auto x : vertexes_list) {
			hash_graph[x.get_tag()];
			vertexes_list[i].set_index(i);
			i++;
		}
	}
	vector<vector<int>> init_sd_matrix(int vertex_idx) {
		int org_idx = vertex_idx;//Graph's Matrix row index

		//n(vertexes) * m(info cols (2))
		vector<vector<int>> info_table;
		info_table.resize(vertexes); //Vertexes rows

		for (size_t idx = 0; idx < vertexes; idx++) {
			idx == org_idx ? info_table[idx].push_back(0) : info_table[idx].push_back(INFINITE); //Shortest distance from start
			info_table[idx].push_back(NV_VERTEX); //Previous vertex
		}

		return info_table;
	}
	unordered_map<string, wt_pair> init_sd_hash(string vertex_tag) {
		unordered_map<string, wt_pair> returned;
		for (size_t i = 0; i < vertexes_list.size(); i++)
			vertex_tag != vertexes_list[i].get_tag() ? returned[vertexes_list[i].get_tag()] = make_pair(INFINITE, "NAN")
			: returned[vertexes_list[i].get_tag()] = make_pair(0, "NAN");
		return returned;
	}
	unordered_map<string, vector<vector<string>>> init_possible_paths() {
		unordered_map<string, vector<vector<string>>> tmp;
		vector<vector<string>> tmp_vect;
		for (auto x : vertexes_list) {
			tmp.insert(make_pair(x.get_tag(), tmp_vect));
		}
		return tmp;
	}

public:

	void print_graph() {
		cout << "  ";
		for (auto x : vertexes_list)
			cout << x.get_tag() << " ";
		cout << endl;
		for (size_t i = 0; i < vertexes; i++)
		{
			for (size_t j = 0; j < vertexes; j++)
			{
				j == 0 ? cout << vertexes_list[i].get_tag() << " " : cout;
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}

	void print_hash_graph() {
		for (auto x : hash_graph) {
			cout << "Vertex: " << x.first;
			for (auto y : x.second)
				cout << " (End: " << y.first << " , Weight: " << y.second << ") ";
			cout << endl;
		}
	}

	// :?) Perdon
	void foo() {}

	//If bidir is true: Edge (weight A->B [3] A<-B [3]) 
	//Edge  (weight A->B [3] A<-B [?])) 
	void add_edge(string vertex_a, string vertex_b, int weight, bool bidir = false) {
		int v_a = vertex_index(vertex_a), v_b = vertex_index(vertex_b);
		if (v_a > -1 && v_b > -1) {
			bidir ? (graph[v_a][v_b] = weight, graph[v_b][v_a] = weight) : graph[v_a][v_b] = weight;
			return;
		}
		cout << NV_INDEX << endl;
	}

	//If bidir is true: Edge (weight map[A]->[B,3] map[B]->[A,3]) 
	//Edge  (weight map[A]->[B,3] map[A]->[?]) 
	void add_hash_edge(string vertex_a, string vertex_b, int weight, bool bidir = false) {
		try
		{
			bidir ? (hash_graph.at(vertex_a).push_back(make_pair(weight, vertex_b)), hash_graph.at(vertex_b).push_back(make_pair(weight, vertex_a)))
				: hash_graph.at(vertex_a).push_back(make_pair(weight, vertex_b));;
		}
		catch (const exception&)
		{
			cout << NVK << endl;
		}
	}

	//Dijkstra shortest path. From vertex org to every other one (Vertex Tag)(Matrix)
	void shortest_paths(string vertex, int vertex_idx = -1) {
		//Check if vertex_index returned something != -1
		int start_vertex = (vertex_idx != -1) ? vertex_idx : vertex_index(vertex);
		if (start_vertex != -1) {
			vector<vector<int>> info_table = init_sd_matrix(start_vertex);

			int current_vertex;
			vector<int> visited_vertexes;
			vector<int> current_neighbors;
			vector<int> current_neighbors_distances;

			//min-heap priority queue, where the elements are represented by a pair
			//of integers, being the first one the minimum distance from the start to
			//a vertex, represented by the second value
			min_heap_pair_queue m_q;

			//Loading priority queue
			m_q.push(make_pair(0, start_vertex));

			//Visiting all vertexes 
			while (!m_q.empty()) {

				current_vertex = m_q.top().second;

				//Current vertex unvisited neighbors 
				current_neighbors = get_current_uv_neighbors(current_vertex, visited_vertexes);


				//Distances from start vertex to neighbors 
				current_neighbors_distances = get_current_uv_neighbors_sd(current_vertex, current_neighbors, info_table);

				m_q.pop();

				update_sd(current_vertex, current_neighbors, current_neighbors_distances, info_table, m_q);

				visited_vertexes.push_back(current_vertex);

			}
			//Update vertex nd_shortest_paths
			vertexes_list[start_vertex].set_shortest_path(info_table);
			return;
		}
		cout << NV_INDEX << endl;
	}

	//The shortest path from the start vertex to end vertex
	vector<int> shortest_path(string start_vertex, string end_vertex) {
		int start_vertex_idx = vertex_index(start_vertex), end_vertex_idx;
		vector<int> error_return;
		if (start_vertex_idx != -1) {
			end_vertex_idx = vertex_index(end_vertex);
			if (end_vertex_idx != -1) {
				if (vertexes_list[start_vertex_idx].get_shortest_paths().size() > 0) {
					//Read Table
					return vertexes_list[start_vertex_idx].shortest_path(end_vertex_idx);
				}
				else {
					//Load Table
					shortest_paths("NAN", start_vertex_idx);

					//Read Table
					return vertexes_list[start_vertex_idx].shortest_path(end_vertex_idx);
				}
			}
			else {
				return error_return;
			}
		}
		else {
			return error_return;
		}
	}

	// 	Dijkstra shortest path. From vertex org to every other one (Vertex Tag)(Hash)
	void hash_shortest_paths(string vertex, int vertex_idx = -1) {
		//Check if vertex tag exists
		int org_idx = (vertex_idx != -1) ? vertex_idx : vertex_index(vertex);
		if (org_idx != -1)
		{
			string current_vertex = vertex;
			vector<wt_pair> current_neighbors;
			auto info_table = init_sd_hash(vertex);
			min_heap_wt_pair_queue m_q;

			//Loading priority queue
			m_q.push(make_pair(0, current_vertex));

			//Visiting all vertexes (Check priority queue size)
			while (!m_q.empty()) {
				current_vertex = m_q.top().second;
				current_neighbors = hash_graph.at(current_vertex);
				m_q.pop();
				update_hash_sd(current_vertex, current_neighbors, info_table, m_q);
			}

			vertexes_list[org_idx].set_hash_shortest_path(info_table);
			return;
		}

		cout << NVK << endl;
	}

	//The shortest path from the start vertex to end vertex (Hash)
	vector<wt_pair> hash_shortest_path(string start_vertex, string end_vertex) {
		vector<wt_pair> error_return;
		int start_vertex_idx = vertex_index(start_vertex), end_vertex_idx;
		if (start_vertex_idx != -1) {
			end_vertex_idx = vertex_index(end_vertex);
			if (end_vertex_idx != -1) {
				if (vertexes_list[start_vertex_idx].get_shortest_paths().size() > 0) {
					//Read Table
					return vertexes_list[start_vertex_idx].hash_shortest_path(end_vertex);
				}
				else {
					//Load Table
					hash_shortest_paths(start_vertex, start_vertex_idx);

					//Read Table
					return vertexes_list[start_vertex_idx].hash_shortest_path(end_vertex);
				}
			}
			else {
				return error_return;
			}
		}
		else {
			return error_return;
		}
	}

	//All possible paths from source to destination
	//https://www.geeksforgeeks.org/iterative-depth-first-traversal/
	//https://www.geeksforgeeks.org/find-paths-given-source-destination/
	void get_all_paths(string source, string destination) {
		//Vertexes list index;
		int source_idx = vertex_index(source);

		vertexes_list[source_idx].add_possible_path_key(destination);

		//All vertexes marked as not visited
		unordered_map<string, bool> visited;

		//Paths
		vector<wt_pair> path(vertexes, make_pair(0, ""));
		int path_index = 0;

		for (auto x : vertexes_list)
			visited.insert(make_pair(x.get_tag(), false));

		get_all_paths_utils(source, destination, visited, path, path_index, source_idx, 0);

	}

	//All possible paths from source to destination
	void get_all_paths_utils(string source, string destination, unordered_map<string, bool>& visited
		, vector<wt_pair> path, int& path_index, int source_idx, int source_w) {
		//Mark the current node and store it in path[]
		visited.at(source) = true;
		path[path_index] = make_pair(source_w, source);
		path_index++;

		//Print - Save path
		if (source == destination) {
			vertexes_list[source_idx].add_possible_path(destination, path);
		}
		else { //Current vertex is not destination

			// Recur for all the vertices adjacent to current vertex
			for (auto x : hash_graph.at(source))
				if (!visited.at(x.second))
					get_all_paths_utils(x.second, destination, visited, path, path_index, source_idx, x.first);
		}
		path_index--;
		visited.at(source) = false;

	}

	//Update infotable 
	void update_sd(int pre_vertex, vector<int> neighbors, vector<int> neighbors_distances, vector<vector<int>>& info_table, min_heap_pair_queue& m_q) {
		int idx = 0;
		for (auto x : neighbors) {
			//if there is a shorter path to a vertex, then update the info table and add the registry to the priority queue
			if (neighbors_distances[idx] < info_table[x][0]) {
				info_table[x][0] = neighbors_distances[idx];
				info_table[x][1] = pre_vertex;
				m_q.push(make_pair(info_table[x][0], x));
			}
			idx++;
		}
	}

	//Update hash infotable
	void update_hash_sd(string current_vertex, vector<wt_pair>  current_neighbors, unordered_map<string, wt_pair>& info_table, min_heap_wt_pair_queue& m_q) {
		int start_to_current_distance = info_table.at(current_vertex).first;
		for (auto x : current_neighbors) {
			if ((x.first + start_to_current_distance) < info_table.at(x.second).first) {
				info_table.at(x.second).first = x.first + start_to_current_distance;
				info_table.at(x.second).second = current_vertex;
				m_q.push(make_pair(info_table.at(x.second).first, x.second));
			}

		}
	}

	//Vertex row index given a  tag
	int vertex_index(string tag) {
		auto it = find_if(vertexes_list.begin(), vertexes_list.end(), [tag](Vertex obj) {return obj.get_tag() == tag; });
		if (it != vertexes_list.end())
			return (*it).get_index();
		return -1;
	}

	//Row index of the matrix's unvisited shortest registered distance (Dijkstra)
	int get_uv_known_sd_vertex(vector<vector<int>> info_table, vector<int> visited) {
		int minimum = INFINITE, min_index = NV_VERTEX, idx = 0;
		for (auto x : info_table) {
			minimum = (x[0] < minimum && find(visited.begin(), visited.end(), idx) == visited.end()) ? (min_index = idx, x[0]) : minimum;
			idx++;
		}
		return min_index;
	}

	//Current-vertex's neighbors
	vector<int> get_current_uv_neighbors(int current_idx, vector<int> visited) {
		vector<int> neighbours;
		for (size_t i = 0; i < vertexes; i++)
			graph[current_idx][i] > 0 && find(visited.begin(), visited.end(), i) == visited.end() ? neighbours.push_back(i) : foo();
		return neighbours;
	}


	//Shortest distances from start to neighbors  of the current vertex 
	vector<int> get_current_uv_neighbors_sd(int current_idx, vector<int> neighbors, vector<vector<int>> infotable) {
		//Start to current distance
		int start_to_current_sd = infotable[current_idx][0];
		vector<int> distances;
		//Start to current  + current to neighbor 
		for (unsigned int i = 0; i < neighbors.size(); i++)
			distances.push_back(graph[current_idx][neighbors[i]] + start_to_current_sd);
		return distances;
	}

	Graph(vector<Vertex> p_vertexes, bool init_hash_graph = false) {
		vertexes_list = p_vertexes;
		vertexes = vertexes_list.size();
		init_hash_graph ? init_map_graph() : init_graph();
	}

	Graph() {}

	Hash_Graph get_hash_graph() {
		return hash_graph;
	}
	vector<vector<int>> get_graph() {
		return graph;
	}
	vector<Vertex> get_vertexes_list() {
		return vertexes_list;
	}
	size_t get_vertexes() {
		return vertexes;
	}
	void set_graph(vector<vector<int>> p_graph) {
		graph = p_graph;
	}
	void set_vertexes_list(vector<Vertex> p_vertexes_list) {
		vertexes_list = p_vertexes_list;
	}
	void set_vertexes(int p_vertexes) {
		vertexes = p_vertexes;
	}
	void set_hash_graph(Hash_Graph p_hash_graph) {
		hash_graph = p_hash_graph;
	}

};

#pragma endregion
