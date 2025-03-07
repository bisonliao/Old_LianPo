#include <iostream>
#include <map>
#include <list>
#include <assert.h>
#include "graph.h"

// 测试无向图的最小生成树
void test_undirected_graph() {
    graph_t g, tree;
    graph_init(&g, false);
    graph_init(&tree, false);

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

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    // 无向图的权重和会 double，因为每条边在两个顶点的 edge list 中都存储了
    assert(total_weight == 2 * (1 + 1 + 2)); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

    std::cout << "Test undirected graph: PASS" << std::endl;
}

// 测试有向图的最小生成树
void test_directed_graph() {
    graph_t g, tree;
    graph_init(&g, true);
    graph_init(&tree, true);

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

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    // 有向图的权重和不会 double
    assert(total_weight == 1 + 1 + 2); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

    std::cout << "Test directed graph: PASS" << std::endl;
}

// 测试包含孤立顶点的无向图
void test_isolated_vertex_undirected() {
    graph_t g, tree;
    graph_init(&g, false);
    graph_init(&tree, false);

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

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    assert(total_weight == 2 * (1 + 1)); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

    std::cout << "Test isolated vertex in undirected graph: PASS" << std::endl;
}

// 测试包含孤立顶点的有向图
void test_isolated_vertex_directed() {
    graph_t g, tree;
    graph_init(&g, true);
    graph_init(&tree, true);

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

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    assert(total_weight == 1 + 1); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

    std::cout << "Test isolated vertex in directed graph: PASS" << std::endl;
}

// 测试包含重复边的无向图
void test_duplicate_edges_undirected() {
    graph_t g, tree;
    graph_init(&g, false);
    graph_init(&tree, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    assert(total_weight == 2 * (1 + 3)); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

    std::cout << "Test duplicate edges in undirected graph: PASS" << std::endl;
}

// 测试包含重复边的有向图
void test_duplicate_edges_directed() {
    graph_t g, tree;
    graph_init(&g, true);
    graph_init(&tree, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_kruskal(&g, &tree) == 0);

    int total_weight = 0;
    for (GList* v = tree.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            total_weight += edge->weight;
        }
    }

    assert(total_weight == 1 + 3); // 最小生成树的权重和

    graph_free(&g);
    graph_free(&tree);

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