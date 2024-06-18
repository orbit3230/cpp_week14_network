#include "auto_router.h"
#include <iostream>

void AutoRouter::calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links) {
  // 각 Host들로 향하는 경로 중에서, 최단 경로를 찾아
  // 해당 Host의 Address와 함께, 첫 번째 Link를 RoutingEntry로 구성하여 routingTable_에 추가할 것이다.  
  // 최단 경로를 찾기 위해서는 다익스트라 알고리즘을 사용할 것이다.
  int n = nodes.size();
  bool *visited = new bool[n];   // nodes의 인덱스와 대응
  double *dist = new double[n];  // nodes의 인덱스와 대응 
  Node **prev = new Node*[n];

  for (int i = 0; i < n; i++) {
    visited[i] = false;
    dist[i] = std::numeric_limits<double>::max();
    prev[i] = nullptr;
  }

  // delay를 먼저 비교하여 작은 것을 우선으로, 만약 같다면 node id를 기준으로 작은 것을 우선으로.
  std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
  int startId = this->id();
  dist[startId] = 0;
  pq.push({0, startId});

  while (!pq.empty()) {
    int id = pq.top().second;
    pq.pop();
    // 이미 방문한 노드라면 pass
    if (visited[id]) continue;
    visited[id] = true;

    for (Link *link : nodes[id]->links()) {
      int link_id = link->other(nodes[id])->id();
      double delay = link->delay();

      if (dist[id] + delay < dist[link_id]) {
        dist[link_id] = dist[id] + delay;
        prev[link_id] = nodes[id];
        pq.push({dist[link_id], link_id});
      }
    }
  }

  // Host들의 id가 무엇인지 확인할 것이다.
  bool isHost[n];
  for(int i = 0; i < n; i++) {
    Host *host = dynamic_cast<Host *>(nodes[i]);
    if(host != nullptr)
      isHost[i] = true;
    else
      isHost[i] = false;
  }

  for (int i = 0; i < n; i++) {
    // Host에 대한 경로의 첫 링크를 찾아서 추가
    if (isHost[i]) {
      std::vector<Node *> path;
      // prev를 이용하여 역추적
      for (Node *node = nodes[i]; node != nullptr; node = prev[node->id()]) {
        path.push_back(node);
      }
      std::reverse(path.begin(), path.end());

      // path[1]은 현재 router에서 Host로 향하는 첫 번째 Link이다. (path[0]은 router 자신)
      Host *host = dynamic_cast<Host *>(nodes[i]);  // Host로 타입 캐스팅
      routingTable_.push_back(RoutingEntry(host->address(), path[1]->linkTo(path[0])));
    }
  }
}