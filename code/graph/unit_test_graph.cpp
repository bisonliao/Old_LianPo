#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

// 包含你的图的定义和函数
#include "graph.h"

void test_graph_init() {
    graph_t g;
    graph_init(&g, true);
    assert(g.is_directed == true);
    assert(g.vertex_list == NULL);
    printf("Test graph_init: PASS\n");
}

void test_graph_add_vertex() {
    graph_t g;
    graph_init(&g, false);
    assert(graph_add_vertex(&g, 1) == 0);
    assert(graph_add_vertex(&g, 2) == 0);
    assert(g_list_length(g.vertex_list) == 2);
    printf("Test graph_add_vertex: PASS\n");
}

void test_graph_add_edge() {
    graph_t g;
    graph_init(&g, false);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    assert(g_list_length(g.vertex_list) == 2);
    vertex_t *v = g_list_nth_data(g.vertex_list, 0);
    assert(v->vertex_id == 1);
    assert(g_list_length(v->edge_list) == 1);
    edge_t *edge = g_list_nth_data(v->edge_list, 0);
    assert(edge->from == 1 && edge->to == 2 && edge->weight == 10);
    printf("Test graph_add_edge: PASS\n");
}

void test_graph_add_edge_existing_vertex() {
    graph_t g;
    graph_init(&g, false);
    assert(graph_add_vertex(&g, 1) == 0);
    assert(graph_add_vertex(&g, 2) == 0);
    printf("vertex number:%d\n", g_list_length(g.vertex_list));
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    printf("vertex number:%d\n", g_list_length(g.vertex_list));
    assert(g_list_length(g.vertex_list) == 2);
    vertex_t *v = g_list_nth_data(g.vertex_list, 0);
    assert(v->vertex_id == 1);
    assert(g_list_length(v->edge_list) == 1);
    edge_t *edge = g_list_nth_data(v->edge_list, 0);
    assert(edge->from == 1 && edge->to == 2 && edge->weight == 10);
    printf("Test graph_add_edge_existing_vertex: PASS\n");
}

void test_graph_add_edge_existing_edge() {
    graph_t g;
    graph_init(&g, false);
    assert(graph_add_vertex(&g, 1) == 0);
    assert(graph_add_vertex(&g, 2) == 0);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    assert(graph_add_edge(&g, &e) == 0); // Add same edge again
    vertex_t *v = g_list_nth_data(g.vertex_list, 0);
    assert(g_list_length(v->edge_list) == 1);
    edge_t *edge = g_list_nth_data(v->edge_list, 0);
    assert(edge->from == 1 && edge->to == 2 && edge->weight == 10);
    printf("Test graph_add_edge_existing_edge: PASS\n");
}

void test_graph_add_edge_update_weight() {
    graph_t g;
    graph_init(&g, false);
    assert(graph_add_vertex(&g, 1) == 0);
    assert(graph_add_vertex(&g, 2) == 0);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    e.weight = 20; // Update weight
    assert(graph_add_edge(&g, &e) == 0);
    vertex_t *v = g_list_nth_data(g.vertex_list, 0);
    edge_t *edge = g_list_nth_data(v->edge_list, 0);
    assert(edge->weight == 20);
    printf("Test graph_add_edge_update_weight: PASS\n");
}

void test_graph_free() {
    graph_t g;
    graph_init(&g, false);
    assert(graph_add_vertex(&g, 1) == 0);
    assert(graph_add_vertex(&g, 2) == 0);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    assert(graph_free(&g) == 0);
    assert(g.vertex_list == NULL);
    printf("Test graph_free: PASS\n");
}

void test_graph_add_edge_directed() {
    graph_t g;
    graph_init(&g, true);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    vertex_t *v1 = g_list_nth_data(g.vertex_list, 0);
    vertex_t *v2 = g_list_nth_data(g.vertex_list, 1);
    assert(v1->vertex_id == 1 && v2->vertex_id == 2);
    assert(g_list_length(v1->edge_list) == 1);
    assert(g_list_length(v2->edge_list) == 0);
    printf("Test graph_add_edge_directed: PASS\n");
}

void test_graph_add_edge_undirected() {
    graph_t g;
    graph_init(&g, false);
    edge_t e = {1, 2, 10};
    assert(graph_add_edge(&g, &e) == 0);
    vertex_t *v1 = g_list_nth_data(g.vertex_list, 0);
    vertex_t *v2 = g_list_nth_data(g.vertex_list, 1);
    assert(v1->vertex_id == 1 && v2->vertex_id == 2);
    assert(g_list_length(v1->edge_list) == 1);
    assert(g_list_length(v2->edge_list) == 1);
    printf("Test graph_add_edge_undirected: PASS\n");
}

void test_graph_add_edge_self_loop() {
    graph_t g;
    graph_init(&g, false);
    edge_t e = {1, 1, 10};
    assert(graph_add_edge(&g, &e) == 0);
    assert(g_list_length(g.vertex_list) == 1);
    vertex_t *v = g_list_nth_data(g.vertex_list, 0);
    assert(v->vertex_id == 1);
    assert(g_list_length(v->edge_list) == 1);
    edge_t *edge = g_list_nth_data(v->edge_list, 0);
    assert(edge->from == 1 && edge->to == 1 && edge->weight == 10);
    printf("Test graph_add_edge_self_loop: PASS\n");
}

int main() {
    
    test_graph_init();
    test_graph_add_vertex();
    test_graph_add_edge();
    test_graph_add_edge_existing_vertex();
    
    test_graph_add_edge_existing_edge();
    test_graph_add_edge_update_weight();
    test_graph_free();
    test_graph_add_edge_directed();
    test_graph_add_edge_undirected();
    test_graph_add_edge_self_loop();
    printf("All tests passed!\n");
    return 0;
}