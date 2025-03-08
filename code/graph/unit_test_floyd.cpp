
#include <iostream>
#include "graph.h"
#include <assert.h>
// 辅助函数：打印路径和距离
void print_results(const std::map<floyd_key_t, path_t>& paths, const std::map<floyd_key_t, edge_weight_t>& distance) {
    for (const auto& pair : distance) {
        std::cout << "From " << pair.first.start << " to " << pair.first.end << ": ";
        std::cout << "Distance = " << pair.second << ", Path = ";
        for (const auto& v : paths.at(pair.first)) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

// 测试用例 1：无向图，简单三角形
void test_case_1() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {2, 0, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    print_results(paths, distance);

    assert((distance.size()) == 6);
    assert(( (distance[{0, 1}] == 1)) );
    assert(( (distance[{0, 2}] == 1)) );
    assert(( (distance[{1, 2}] == 1)) );

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}
#if 1
// 测试用例 2：有向图，简单三角形
void test_case_2() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {2, 0, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);

    assert((distance.size()) == 6);
    assert((distance[{0, 1}] == 1));
    assert((distance[{1, 2}] == 1));
    assert((distance[{2, 0}] == 1));

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 3：无向图，线性结构
void test_case_3() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    

    assert((distance.size()) == 6);
    assert((distance[{0, 1}] == 1));
    assert((distance[{0, 2}] == 2));
    assert((distance[{1, 2}] == 1));

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 4：有向图，线性结构
void test_case_4() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    

    assert((distance.size()) == 3);
    assert((distance[{0, 1}] == 1));
    assert((distance[{0, 2}] == 2));
    assert((distance[{1, 2}] == 1));

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 5：无向图，存在孤立顶点
void test_case_5() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    graph_add_edge(&g, &e1);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    

    assert((distance.size()) == 2);
    assert((distance[{0, 1}] == 1));
    assert((distance.find({0, 2})) == distance.end()); // 0 和 2 不可达

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 6：有向图，存在孤立顶点
void test_case_6() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    graph_add_edge(&g, &e1);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);

    assert((distance.size()) == 1);
    assert((distance[{0, 1}] == 1));
    assert((distance.find({1, 2})) == distance.end()); // 1 和 2 不可达

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 7：无向图，存在多条路径
void test_case_7() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {0, 2, 3};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);

    assert((distance.size()) == 6);
    assert((distance[{0, 2}] == 2)); // 0 -> 2 的最短路径是 0 -> 1 -> 2

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 8：有向图，存在多条路径
void test_case_8() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {0, 2, 3};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    

    assert((distance.size()) == 3);
    assert((distance[{0, 2}] == 2)); // 0 -> 2 的最短路径是 0 -> 1 -> 2

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 9：无向图，完全图
void test_case_9() {
    graph_t g;
    graph_init(&g, false);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {0, 2, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);

    assert((distance.size()) == 6);
    assert((distance[{0, 1}] == 1));
    assert((distance[{0, 2}] == 1));
    assert((distance[{1, 2}] == 1));

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}

// 测试用例 10：有向图，完全图
void test_case_10() {
    graph_t g;
    graph_init(&g, true);
    graph_add_vertex(&g, 0);
    graph_add_vertex(&g, 1);
    graph_add_vertex(&g, 2);

    edge_t e1 = {0, 1, 1};
    edge_t e2 = {1, 2, 1};
    edge_t e3 = {2, 0, 1};
    edge_t e4 = {0, 2, 1};
    edge_t e5 = {2, 1, 1};
    edge_t e6 = {1, 0, 1};
    graph_add_edge(&g, &e1);
    graph_add_edge(&g, &e2);
    graph_add_edge(&g, &e3);
    graph_add_edge(&g, &e4);
    graph_add_edge(&g, &e5);
    graph_add_edge(&g, &e6);

    std::map<floyd_key_t, path_t> paths;
    std::map<floyd_key_t, edge_weight_t> distance;
    graph_floyd(&g, paths, distance);
    print_results(paths, distance);

    assert((distance.size()) == 6);
    assert((distance[{0, 1}] == 1));
    assert((distance[{0, 2}] == 1));
    assert((distance[{1, 2}] == 1));

    graph_free(&g);
    printf("%s passed\n", __FUNCTION__);
}
#endif
int main() {
    test_case_1();

    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    test_case_7();
    test_case_8();
    test_case_9();
    test_case_10();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
