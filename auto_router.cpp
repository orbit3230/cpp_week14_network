#include "auto_router.h"
#include "nat.h"
#include <iostream>

void AutoRouter::calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links) {
  // 각 Host들로 향하는 경로 중에서, 최단 경로를 찾아
  // 해당 Host의 Address와 함께, 첫 번째 Link를 RoutingEntry로 구성하여 routingTable_에 추가할 것이다.  
  // 최단 경로를 찾기 위해서는 다익스트라 알고리즘을 사용할 것이다.
  int n = 15;
  bool *visited = new bool[n];   // nodeArray의 인덱스와 대응
  double *dist = new double[n];  // nodeArray의 인덱스와 대응 
  Node **prev = new Node*[n];
  
  // 3주차 과제 수정사항 node vector -> array
  Node **nodeArray = new Node*[n];
  for(int i = 0; i < n; i++) {
    nodeArray[i] = nullptr;
  }
  for(Node *node : nodes) {
    nodeArray[node->id()] = node;
  }

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
    if(visited[id]) continue;
    if(nodeArray[id] == nullptr) continue; // nodeArray에 없는 경우 pass (Fifth 시나리오의 clients id에 해당)
    visited[id] = true;

    for (Link *link : nodeArray[id]->links()) {
      int link_id = link->other(nodeArray[id])->id();
      double delay = link->delay();

      if (dist[id] + delay < dist[link_id]) {
        dist[link_id] = dist[id] + delay;
        prev[link_id] = nodeArray[id];
        pq.push({dist[link_id], link_id});
      }
    }
  }

  // Host(또는 Nat)들의 id가 무엇인지 확인할 것이다.
  bool isHostOrNat[n] = {false, };
  for(int i = 0; i < n; i++) {
    Host *host = dynamic_cast<Host *>(nodeArray[i]);
    if(host != nullptr)
      isHostOrNat[i] = true;
    Nat *nat = dynamic_cast<Nat *>(nodeArray[i]);
    if(nat != nullptr)
      isHostOrNat[i] = true;
  }

  for (int i = 0; i < n; i++) {
    // Host에 대한 경로의 첫 링크를 찾아서 추가
    if (isHostOrNat[i]) {
      std::vector<Node *> path;
      // prev를 이용하여 역추적
      for (Node *node = nodeArray[i]; node != nullptr; node = prev[node->id()]) {
        path.push_back(node);
      }
      std::reverse(path.begin(), path.end());

      // path[1]은 현재 router에서 Host로 향하는 첫 번째 Link이다. (path[0]은 router 자신)
      Host *host = dynamic_cast<Host *>(nodeArray[i]);  // Host로 타입 캐스팅 시도
      if(host == nullptr) {  // Host가 아니라면 Nat이다.
        Nat *nat = dynamic_cast<Nat *>(nodeArray[i]);  // Nat로 타입 캐스팅
        if(path.size() > 1) {
          routingTable_.push_back(RoutingEntry(nat->address(), path[1]->linkTo(path[0])));
        }
        // 링크가 하나면 직접 연결..
        else {
          routingTable_.push_back(RoutingEntry(nat->address(), nat->linkTo(path[0])));
        }
        continue;
      }
      // Host인 경우
      if(path.size() > 1) {
        routingTable_.push_back(RoutingEntry(host->address(), path[1]->linkTo(path[0])));
      }
      // 링크가 하나면 직접 연결..
      else {
        routingTable_.push_back(RoutingEntry(host->address(), host->linkTo(path[0])));
      }
    }
  }
}