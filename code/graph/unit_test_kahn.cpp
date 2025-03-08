#include "graph.h"
#include <gtest/gtest.h>
#include <list>

// 辅助函数：创建测试用图
void create_test_graph(graph_t* g, bool is_directed) {
    graph_init(g, is_directed);
    graph_add_vertex(g, 0);
    graph_add_vertex(g, 1);
    graph_add_vertex(g, 2);
    graph_add_vertex(g, 3);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {2, 3, 1};
    graph_add_edge(g, &e1);
    graph_add_edge(g, &e2);
    graph_add_edge(g, &e3);
}
void print_topo(std::list<vertex_id_t>& topo)
{
    for (std::list<vertex_id_t>::const_iterator it = topo.begin();
            it != topo.end(); it++)
    {
        printf("%d ", *it);
    }
    printf("\n");
}

// 测试用例 1：简单的有向图
TEST(KahnTest, SimpleDirectedGraph) {
    graph_t g;
    
    std::list<vertex_id_t> topo_seq;
    
    create_test_graph(&g, true);
    
    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    print_topo(topo_seq);
    ASSERT_EQ(topo_seq.size(), 4);
    graph_free(&g);
}

// 测试用例 2：存在环的有向图
TEST(KahnTest, DirectedGraphWithCycle) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    create_test_graph(&g, true);
    edge_t e4 = {3, 0, 1};
    graph_add_edge(&g, &e4);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 1);
    graph_free(&g);
}

// 测试用例 3：无向图
TEST(KahnTest, UndirectedGraph) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    create_test_graph(&g, false);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 1); // 无向图无拓扑排序
    graph_free(&g);
}

// 测试用例 4：孤立顶点
TEST(KahnTest, IsolatedVertex) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    edge_t e1 = {0, 1, 1};
    graph_add_edge(&g, &e1);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    print_topo(topo_seq);
    ASSERT_EQ(topo_seq.size(), 3); // 包含孤立顶点
    graph_free(&g);
}

// 测试用例 5：空图
TEST(KahnTest, EmptyGraph) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    ASSERT_EQ(topo_seq.size(), 0);
    graph_free(&g);
}

// 测试用例 6：单个顶点
TEST(KahnTest, SingleVertex) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    ASSERT_EQ(topo_seq.size(), 1);
    graph_free(&g);
}

// 测试用例 7：多个孤立顶点
TEST(KahnTest, MultipleIsolatedVertices) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    ASSERT_EQ(topo_seq.size(), 3);
    graph_free(&g);
}

// 测试用例 8：复杂的有向图
TEST(KahnTest, ComplexDirectedGraph) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {0, 2, 1};
    edge_t e3 = {1, 3, 1};
    edge_t e4 = {2, 3, 1};
    edge_t e5 = {3, 4, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);

    ASSERT_EQ(graph_kahn(&g, topo_seq), 0);
    ASSERT_EQ(topo_seq.size(), 5);
    graph_free(&g);
}

// 测试用例 9：复杂的有向图（含环）
TEST(KahnTest, ComplexDirectedGraphWithCycle) {
    graph_t g;
    std::list<vertex_id_t> topo_seq;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);
    graph_add_vertex(&g, 3);
    graph_add_vertex(&g, 4);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {0, 2, 1};
    edge_t e3 = {1, 3, 1};
    edge_t e4 = {2, 3, 1};
    edge_t e5 = {3, 4, 1};
    edge_t e6 = {4, 0, 1}; // 形成环
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);
    graph_add_edge(&g, &e6);

    ASSERT_EQ(graph_kahn(&g, topo_seq), 1);
    graph_free(&g);
}

// 测试用例 10：图拷贝测试
TEST(KahnTest, GraphCopy) {
    graph_t g1, g2;
    graph_init(&g1, true);
    graph_init(&g2, true);
    std::list<vertex_id_t> topo_seq;
    create_test_graph(&g1, true);
    printf("%s %d\n", __FILE__, __LINE__);
    graph_copy(&g1, &g2);
    printf("%s %d\n", __FILE__, __LINE__);
    ASSERT_EQ(graph_kahn(&g2, topo_seq), 0);
    print_topo(topo_seq);
    ASSERT_EQ(topo_seq.size(), 4);
    graph_free(&g1);
    graph_free(&g2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}