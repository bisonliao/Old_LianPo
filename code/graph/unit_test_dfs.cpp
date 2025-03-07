#include <iostream>
#include <map>
#include <list>
#include <assert.h>
#include "graph.h"

void print_vlist(const char * msg, const std::list<vertex_id_t> & l)
{
    printf("%s", msg);
    std::list<vertex_id_t>::const_iterator it;
    for (it = l.begin(); it != l.end(); ++it)
    {
        printf("%d ", *it);
    }
    printf("\n");
}
void print_elist(const char * msg, const std::list<edge_t> & l)
{
    printf("%s", msg);
    std::list<edge_t>::const_iterator it;
    for (it = l.begin(); it != l.end(); ++it)
    {
        printf("%d--%d-->%d, ", it->from, it->weight, it->to);
    }
    printf("\n");
}

// 测试单个顶点
void test_single_vertex() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 1);
    std::list<vertex_id_t> topo_seq;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_dfscan(&g, &start, topo_seq, result1, result2) == 0);
    assert(result1.size() == 1);
    assert(result1.front() == 1);
    assert(result2.empty());
    graph_free(&g);
    std::cout << "Test single vertex: PASS" << std::endl;
}


// 测试两个顶点，一条边
void test_two_vertices_one_edge() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    edge_t e = {1, 2, 1};
    graph_add_edge(&g, &e);
    std::list<vertex_id_t> topo_seq;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_dfscan(&g, &start, topo_seq, result1, result2) == 0);
    print_vlist("顶点列表", result1);
    print_elist("边列表", result2);
    print_vlist("topo排序", topo_seq);
    assert(result1.size() == 2);
    assert(result1.front() == 2);
    assert(result1.back() == 1);

    assert(result2.size() == 1);
    assert(result2.front().from == 1 && result2.front().to == 2);
    graph_free(&g);
    std::cout << "Test two vertices one edge: PASS" << std::endl;
}

// 测试三个顶点，两条边
void test_three_vertices_two_edges() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 3, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    std::list<vertex_id_t> topo_seq;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_dfscan(&g, &start, topo_seq, result1, result2) == 0);
    print_vlist("顶点列表", result1);
    print_elist("边列表", result2);
    print_vlist("topo排序", topo_seq);
    assert(result1.size() == 3);
    assert(result1.front() == 3);
    assert(result1.back() == 1);
    assert(result2.size() == 2);
    graph_free(&g);
    std::cout << "Test three vertices two edges: PASS" << std::endl;
}

// 测试有环的图
void test_cyclic_graph() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 3, 1};
    edge_t e3 = {3, 1, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    std::list<vertex_id_t> topo_seq;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_dfscan(&g, &start, topo_seq, result1, result2) == 0);
    print_vlist("顶点列表", result1);
    print_elist("边列表", result2);
    print_vlist("topo排序", topo_seq);
    assert(result1.size() == 3);
    assert(result1.front() == 3 || result1.front() == 2);
    assert(result1.back() == 1);
    assert(result2.size() == 2);
    graph_free(&g);
    std::cout << "Test cyclic graph: PASS" << std::endl;
}

// 测试多个路径
void test_multiple_paths() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);
    edge_t e1 = {1, 2, 1};
    edge_t e2 = {1, 3, 1};
    edge_t e3 = {2, 4, 1};
    edge_t e4 = {3, 4, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    std::list<vertex_id_t> topo_seq;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_dfscan(&g, &start, topo_seq, result1, result2) == 0);
    print_vlist("顶点列表", result1);
    print_elist("边列表", result2);
    print_vlist("topo排序", topo_seq);
    assert(result1.size() == 4);
    assert(result1.front() == 3 ||result1.front() == 4);

    assert(result2.size() == 3);
    graph_free(&g);
    std::cout << "Test multiple paths: PASS" << std::endl;
}

int main() {
    test_single_vertex();
    test_two_vertices_one_edge();
    test_three_vertices_two_edges();
    test_cyclic_graph();
    test_multiple_paths();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}