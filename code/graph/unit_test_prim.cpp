#include <iostream>
#include <map>
#include <list>
#include <set>
#include <assert.h>
#include "graph.h"

// 测试无向图的最小生成树
void test_undirected_graph() {
    graph_t g, t;

    graph_init(&g, false);
    graph_init(&t, false);
    printf("%d\n", __LINE__);

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
    printf("%d\n", __LINE__);

    assert(graph_prim(&g, &t) == 0);

    printf("%d\n", __LINE__);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;
    long total_weight = 0;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }
    printf("%d, %ld\n", __LINE__, total_weight);

    assert(vertex_list.size() == 4);
    assert(edge_list.size() == 6);
    assert(total_weight == 8);
    printf("%d\n", __LINE__);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test undirected graph: PASS" << std::endl;
}

// 测试有向图的最小生成树
void test_directed_graph() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, true);
    graph_init(&t, true);

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

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 4);
    assert(edge_list.size() == 3);
    assert(total_weight == 4);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test directed graph: PASS" << std::endl;
}

// 测试包含孤立顶点的无向图
void test_isolated_vertex_undirected() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, false);
    graph_init(&t, false);

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

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 4);
    assert(total_weight = 4);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test isolated vertex in undirected graph: PASS" << std::endl;
}

// 测试包含孤立顶点的有向图
void test_isolated_vertex_directed() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, true);
    graph_init(&t, true);

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

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 2);
    assert(total_weight = 2);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test isolated vertex in directed graph: PASS" << std::endl;
}

// 测试包含重复边的无向图
void test_duplicate_edges_undirected() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, false);
    graph_init(&t, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }
    printf("%d %ld\n", __LINE__, total_weight);
    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 4);
    assert(total_weight == 8);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test duplicate edges in undirected graph: PASS" << std::endl;
}
// 测试包含重复边的有向图
void test_duplicate_edges_directed() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, true);
    graph_init(&t, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 2, 2}; // 重复边，权重不同
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 2);
    assert(total_weight == 4);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test duplicate edges in directed graph: PASS" << std::endl;
}

// 测试包含多个顶点和边的无向图
void test_large_undirected_graph() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, false);
    graph_init(&t, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);
    graph_add_vertex(&g, 5);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};
    edge_t e4 = {2, 4, 2};
    edge_t e5 = {3, 4, 4};
    edge_t e6 = {3, 5, 5};
    edge_t e7 = {4, 5, 1};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);
    graph_add_edge(&g, &e6);
    graph_add_edge(&g, &e7);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 5);
    assert(edge_list.size() == 8);
    assert(total_weight == 10);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test large undirected graph: PASS" << std::endl;
}

// 测试包含多个顶点和边的有向图
void test_large_directed_graph() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, true);
    graph_init(&t, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);
    graph_add_vertex(&g, 5);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 3};
    edge_t e3 = {2, 3, 1};
    edge_t e4 = {2, 4, 2};
    edge_t e5 = {3, 4, 4};
    edge_t e6 = {3, 5, 5};
    edge_t e7 = {4, 5, 1};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);
    graph_add_edge(&g, &e6);
    graph_add_edge(&g, &e7);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 5);
    assert(edge_list.size() == 4);
    assert(total_weight == 5);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test large directed graph: PASS" << std::endl;
}

// 测试包含自环的无向图
void test_self_loop_undirected() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, false);
    graph_init(&t, false);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 2, 2}; // 自环
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 4);
    assert(total_weight == 8);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test self-loop in undirected graph: PASS" << std::endl;
}

// 测试包含自环的有向图
void test_self_loop_directed() {
    graph_t g, t;
    long total_weight = 0;
    graph_init(&g, true);
    graph_init(&t, true);

    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);

    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 2, 2}; // 自环
    edge_t e3 = {2, 3, 3};

    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    assert(graph_prim(&g, &t) == 0);

    std::list<vertex_id_t> vertex_list;
    std::list<edge_t> edge_list;

    for (GList* v = t.vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex_list.push_back(vertex->vertex_id);
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_list.push_back(*((edge_t*)e->data));
            total_weight += ((edge_t*)e->data)->weight;
        }
    }

    assert(vertex_list.size() == 3);
    assert(edge_list.size() == 2);
    assert(total_weight == 4);

    graph_free(&g);
    graph_free(&t);

    std::cout << "Test self-loop in directed graph: PASS" << std::endl;
}

int main()
{
    test_undirected_graph();
    test_directed_graph();
    test_isolated_vertex_undirected();
    test_isolated_vertex_directed();
    test_duplicate_edges_undirected();
    test_duplicate_edges_directed();
    test_large_undirected_graph();
    test_large_directed_graph();
    test_self_loop_undirected();
    test_self_loop_directed();
    std::cout << "All tests passed!" << std::endl;
    return 0;

}