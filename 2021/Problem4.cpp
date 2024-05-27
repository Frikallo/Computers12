#include <bits/stdc++.h>

using namespace std;

const int Mxn = 200005;
vector<int> graph[Mxn];
int s[Mxn], walk[Mxn];
bool seen[Mxn];

// calculate the shortest walk time from each station to n
void bfs(int n)
{
  int d = 0;
  queue<int> q;
  q.push(n);
  seen[n] = true;

  while (!q.empty())
  {
    for (int _ = q.size(); _ > 0; _--)
    {
      int u = q.front();
      q.pop();
      walk[u] = d;
      for (int v : graph[u])
      {
        if (!seen[v])
        {
          seen[v] = true;
          q.push(v);
        }
      }
    }
    d++;
  }
}

int main()
{
  int n, w, d;
  cin >> n >> w >> d;
  for (int i = 0; i < w; i++)
  {
    int a, b;
    cin >> a >> b;
    graph[b].push_back(a);
  }

  bfs(n);

  multiset<int> time;
  for (int i = 0; i < n; i++)
  {
    cin >> s[i];
    if (walk[s[i]] != -1)
    {
      time.insert(i + walk[s[i]]);
    }
  }

  for (int i = 0; i < d; i++)
  {
    int x, y;
    cin >> x >> y;
    x--, y--;

    assert(x != 0 && y != 0);
    if (walk[s[x]] != -1)
    {
      auto it = time.find(x + walk[s[x]]);
      time.erase(it);
      time.insert(y + walk[s[x]]);
    }
    if (walk[s[y]] != -1)
    {
      auto it = time.find(y + walk[s[y]]);
      time.erase(it);
      time.insert(x + walk[s[y]]);
    }

    swap(s[x], s[y]);
    cout << *time.begin() << '\n';
  }

  return 0;
}