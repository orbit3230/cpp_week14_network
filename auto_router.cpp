#include "auto_router.h"
#include <iostream>

void AutoRouter::calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links) {
  // 모든 노드에 대한 최단 경로를 저장하는 테이블
  std::map<int, std::vector<RoutingEntry>> routingTables;
  
  // 모든 노드에 대한 최단 경로를 계산
  for (Node *node : nodes) {
    // 최단 경로를 계산하기 위한 변수들(인덱스는 각 노드들의 id를 사용)
    std::map<Address, double> distance;
    std::map<Address, Node *> previous;
    std::set<Address> visited;
    
    // 초기화
    for (Node *node : nodes) {
      // 우선은 모든 거리를 무한대로 설정
      distance[node->id()] = std::numeric_limits<double>::infinity();
      previous[node->id()] = nullptr;
    }
    // 자기 자신에 대한 거리는 0 (adjacency matrix에서 diagonal entry를 의미)
    distance[node->id()] = 0;
  
    // 다익스트라 알고리즘
    // (bfs와 유사한 면이 있어보인다 ... 하지만 weight를 다루기에 일반 큐가 아닌 우선순위 큐를 사용)
    std::priority_queue<std::pair<double, Node *>> pq;
    pq.push({0, node});
    while (!pq.empty()) {
      Node *current = pq.top().second;
      pq.pop();
    
      // 이미 방문한 노드는 pass
      // find() 함수는 찾지 못하였을 경우 마지막을 가리키는 iterator(end())를 반환한다.  
      if (visited.find(current->id()) != visited.end()) {
        continue;
      }
      visited.insert(current->id());
    
      for (Link *link : current->links()) {
        Node *neighbor = link->other(current);
        double newDistance = distance[current->id()] + link->delay();
        // 새로 탐색한 거리가 기존의 거리보다 짧은 경우에만 업데이트 !
        if (newDistance < distance[neighbor->id()]) {
        distance[neighbor->id()] = newDistance;
        previous[neighbor->id()] = current;
        pq.push({-newDistance, neighbor});
        }
      }
    }
  
    // 최단 경로를 라우팅 테이블에 저장
    for (Node *destination : nodes) {
      std::vector<RoutingEntry> routingTable;
      Node *current = destination;
      while (current != nullptr) {
        Link *link = current->linkTo(previous[current->id()]);
        if (link != nullptr) {
        routingTable.push_back({destination->id(), link});
        }
        current = previous[current->id()];
      }
      std::reverse(routingTable.begin(), routingTable.end());
      routingTables[destination->id()] = routingTable;
    }
  }
  
  // 라우팅 테이블을 복사
  routingTable_.clear();
  for (const auto &entry : routingTables) {
    routingTable_ = entry.second;
  }

}