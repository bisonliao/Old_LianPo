#include <iostream>
#include <map>
#include <list>
#include <assert.h>
#include "graph.h"

// 测试无向图的最短路径
void test_undirected_graph() {
    graph_t g;
    graph_init(&g, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};
    edge_t e4 = {2, 4, 2};
    edge_t e5 = {3, 4, 4};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 2);
    assert(distance[4] == 3);

    assert(paths[1] == path_t({}));
    assert(paths[2] == path_t({1}));
    assert(paths[3] == path_t({1, 2}));
    assert(paths[4] == path_t({1, 2}));

    graph_free(&g);

    std::cout << "Test undirected graph: PASS" << std::endl;
}

// 测试有向图的最短路径
void test_directed_graph() {
    graph_t g;
    graph_init(&g, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};
    edge_t e4 = {2, 4, 2};
    edge_t e5 = {3, 4, 4};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 2);
    assert(distance[4] == 3);

    assert(paths[1] == path_t({}));
    assert(paths[2] == path_t({1}));
    assert(paths[3] == path_t({1, 2}));
    assert(paths[4] == path_t({1, 2}));

    graph_free(&g);

    std::cout << "Test directed graph: PASS" << std::endl;
}

// 测试包含孤立顶点的无向图
void test_isolated_vertex_undirected() {
    graph_t g;
    graph_init(&g, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 2);
    //assert(distance[4] == MAX_WEIGHT_VALUE); // 顶点 4 是孤立的

    assert(paths[1] == path_t({}));
    assert(paths[2] == path_t({1}));
    assert(paths[3] == path_t({1, 2}));

    graph_free(&g);

    std::cout << "Test isolated vertex in undirected graph: PASS" << std::endl;
}

// 测试包含孤立顶点的有向图
void test_isolated_vertex_directed() {
    graph_t g;
    graph_init(&g, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 2);
    //assert(distance[4] == MAX_WEIGHT_VALUE); // 顶点 4 是孤立的

    assert(paths[1] == path_t({}));
    assert(paths[2] == path_t({1}));
    assert(paths[3] == path_t({1, 2}));

    graph_free(&g);

    std::cout << "Test isolated vertex in directed graph: PASS" << std::endl;
}

// 测试包含重复边的无向图
void test_duplicate_edges_undirected() {
    graph_t g;
    graph_init(&g, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 4);

    graph_free(&g);

    std::cout << "Test duplicate edges in undirected graph: PASS" << std::endl;
}

// 测试包含重复边的有向图
void test_duplicate_edges_directed() {
    graph_t g;
    graph_init(&g, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<vertex_id_t, path_t> paths;
    std::map<vertex_id_t, edge_weight_t> distance;

    assert(graph_dijkstra(&g, 1, paths, distance) == 0);

    assert(distance[1] == 0);
    assert(distance[2] == 1);
    assert(distance[3] == 4);

    graph_free(&g);

    std::cout << "Test duplicate edges in directed graph: PASS" << std::endl;
}



int main() {
    test_undirected_graph();
    test_directed_graph();
    test_isolated_vertex_undirected();
    test_isolated_vertex_directed();
    test_duplicate_edges_undirected();
    test_duplicate_edges_directed();
    

    std::cout << "All tests passed!" << std::endl;
    return 0;
}