#include <iostream>
#include <map>
#include <list>
#include <assert.h>
#include "graph.h"

// 测试单个顶点
void test_single_vertex() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 1);
    std::map<vertex_id_t, path_t> returned_path;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_shortest_path_by_bfs(&g, &start, returned_path, result1, result2) == 0);
    assert(returned_path.size() == 1);
    assert(returned_path[1] == path_t({1}));
    graph_free(&g);
    std::cout << "Test single vertex: PASS" << std::endl;
}
void print_path(const path_t & p)
{
    for (auto i = p.begin(); i != p.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

// 测试两个顶点，一条边
void test_two_vertices_one_edge() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    edge_t e = {1, 2, 1};
    graph_add_edge(&g, &e);
    std::map<vertex_id_t, path_t> returned_path;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_shortest_path_by_bfs(&g, &start, returned_path, result1, result2) == 0);
    assert(returned_path.size() == 2);
    assert(returned_path[1] == path_t({1}));
    assert(returned_path[2] == path_t({1, 2}));
    graph_free(&g);
    std::cout << "Test two vertices one edge: PASS" << std::endl;
}

// 测试三个顶点，两条边
void test_three_vertices_two_edges() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 3, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    std::map<vertex_id_t, path_t> returned_path;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_shortest_path_by_bfs(&g, &start, returned_path, result1, result2) == 0);
    assert(returned_path.size() == 3);
    assert(returned_path[1] == path_t({1}));
    assert(returned_path[2] == path_t({1, 2}));
    assert(returned_path[3] == path_t({1, 2, 3}));
    graph_free(&g);
    std::cout << "Test three vertices two edges: PASS" << std::endl;
}

// 测试有环的图
void test_cyclic_graph() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    edge_t e1 = {1, 2, 1};
    edge_t e2 = {2, 3, 1};
    edge_t e3 = {3, 1, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    std::map<vertex_id_t, path_t> returned_path;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_shortest_path_by_bfs(&g, &start, returned_path, result1, result2) == 0);
    assert(returned_path.size() == 3);
    print_path(returned_path[1]);
    print_path(returned_path[2]);
    print_path(returned_path[3]);

    assert(returned_path[1] == path_t({1}));
    assert(returned_path[2] == path_t({1, 2}) || returned_path[2] == path_t({1, 3}));
    assert(returned_path[3] == path_t({1,  3}));
    graph_free(&g);
    std::cout << "Test cyclic graph: PASS" << std::endl;
}

// 测试多个路径
void test_multiple_paths() {
    graph_t g;
    graph_init(&g, false);
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
    std::map<vertex_id_t, path_t> returned_path;
    std::list<vertex_id_t> result1;
    std::list<edge_t> result2;
    vertex_id_t start = 1;
    assert(graph_shortest_path_by_bfs(&g, &start, returned_path, result1, result2) == 0);
    assert(returned_path.size() == 4);
    print_path(returned_path[1]);
    print_path(returned_path[2]);
    print_path(returned_path[3]);
    print_path(returned_path[4]);
 
    assert(returned_path[1] == path_t({1}));
    assert(returned_path[2] == path_t({1, 2})||returned_path[2] == path_t({1, 3}));
    assert(returned_path[3] == path_t({1, 3})||returned_path[2] == path_t({1, 3}));
    
    assert(returned_path[4] == path_t({1, 2, 4}) || returned_path[4] == path_t({1, 3, 4}));
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