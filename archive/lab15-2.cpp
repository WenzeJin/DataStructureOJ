#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int from;
	int to;
	int ee;
	int el;
	int weight;
};


class Sequence {
	vector<vector<Edge> > &fromMap;
	bool ready;
	vector<int> sequence;
	vector<int> visited;
	vector<int> outDegree;
	void makeSequenceHelp(int u)
	{
		visited[u] = 1;
		
		for (int i = 0; i < fromMap[u].size(); i++)
		{
			if (!visited[fromMap[u][i].from])
			{
				makeSequenceHelp(fromMap[u][i].from);
			}
		}
		sequence.push_back(u);
	}

public:
	Sequence(vector<vector<Edge> > &fromMap):fromMap(fromMap), ready(false){
		visited.resize(fromMap.size());
		outDegree.resize(fromMap.size());
		
	}

	void makeSequence() {
		for (int i = 0; i < fromMap.size(); i++)
		{
			for (int j = 0; j < fromMap[i].size(); j++)
			{
				outDegree[fromMap[i][j].from]++;
			}
		}

		for(int i = 0; i < fromMap.size(); i++)
		{
			if (outDegree[i] == 0 && !visited[i])
			{
				makeSequenceHelp(i);
			}
		}
		ready = true;
	}

	vector<int> getSequence() {
		if (!ready)
		{
			makeSequence();
		}
		return sequence;
	}
};

int main()
{
	int n, e;
	cin >> n >> e;
	vector<vector<Edge> > toMap(n);
	vector<vector<Edge> > fromMap(n);
	

	for (int i = 0; i < e; i++)
	{
		int from, to, weight;
		cin >> from >> to >> weight;
		Edge edge;
		edge.from = from;
		edge.to = to;
		edge.weight = weight;
		toMap[from].push_back(edge);
		fromMap[to].push_back(edge);
	}

	//sort
	Sequence sequence(fromMap);
	vector<int> seq = sequence.getSequence();



	//calculate ve
	vector<int> ve(n, 0);
	for (int i = 0; i < seq.size(); i++)
	{
		int to = seq[i];
		for (int j = 0; j < fromMap[to].size(); j++)
		{
			int from = fromMap[to][j].from;
			int weight = fromMap[to][j].weight;
			if (ve[from] + weight > ve[to])
			{
				ve[to] = ve[from] + weight;
			}
		}
	}
	int total = 0;
	for (int i = 0; i < ve.size(); i++)
	{
		if (ve[i] > total)
		{
			total = ve[i];
		}
	}


	//calculate vl
	vector<int> vl(n, total);
	for (int i = seq.size() - 1; i >= 0; i--)
	{
		int from = seq[i];
		for (int j = 0; j < toMap[from].size(); j++)
		{
			int to = toMap[from][j].to;
			int weight = toMap[from][j].weight;
			if (vl[to] - weight < vl[from])
			{
				vl[from] = vl[to] - weight;
			}
		}
	}


	//calculate ee and el in toMap
	for (int i = 0; i < toMap.size(); i++)
	{
		for (int j = 0; j < toMap[i].size(); j++)
		{
			int from = toMap[i][j].from;
			int to = toMap[i][j].to;
			int weight = toMap[i][j].weight;
			toMap[i][j].ee = ve[from];
			toMap[i][j].el = vl[to] - weight;
		}
	}

	//output keyroute
	for (int i = 0; i < toMap.size(); i++)
	{
		for (int j = 0; j < toMap[i].size(); j++)
		{
			if (toMap[i][j].ee == toMap[i][j].el)
			{
				cout << toMap[i][j].from << " " << toMap[i][j].to << endl;
			}
		}
	}

}
