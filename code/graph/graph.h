#ifndef _GRAPH_H_INCLUDED_
#define _GRAPH_H_INCLUDED_

#include "glib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <list>
#include <map>
#include <set>
#include <bits/stl_pair.h>
#include <stack>

typedef int32_t edge_weight_t;
const edge_weight_t MAX_WEIGHT_VALUE = INT32_MAX;
typedef int32_t vertex_id_t;
typedef struct
{
    vertex_id_t from;
    vertex_id_t to;
    edge_weight_t weight;
} edge_t; //定义一条边

typedef struct
{
    vertex_id_t vertex_id;
    GList * edge_list; //原谅我设计成这个鸟样子，我一开始想用纯c的，后来受不了了才改用stl
    
} vertex_t; //定义一个顶点
 
typedef struct 
{
    bool is_directed;
    GList * vertex_list;//原谅我设计成这个鸟样子，我一开始想用纯c的，后来受不了了才改用stl
} graph_t; //定义一个图

typedef std::list<vertex_id_t> path_t; //定义一条路径，由经过的顶点构成的列表

int graph_init(graph_t * g, bool is_directed);
int graph_add_edge(graph_t * g, const edge_t * e);
int graph_add_vertex(graph_t * g, vertex_id_t id);
int graph_free(graph_t * g);

//图拷贝，从from拷贝到to。可以指明哪个顶点和与它有连接的边不要拷贝到to里。
int graph_copy(graph_t * from, graph_t *to, std::set<vertex_id_t> * except = NULL);

//广度优先搜索，得到从start顶点开始的最短路径，保存在returned_path里，依次搜索到的顶点和边保存在result1 result2里
int graph_shortest_path_by_bfs(graph_t * g, vertex_id_t*start, std::map<vertex_id_t, path_t> & returned_path,
    std::list<vertex_id_t> & result1, std::list<edge_t> & result2 );

//深度优先搜搜，如果是有向图，topo_seq将保存拓扑排序的结果，依次搜索到的顶点和边保存在result1 result2里
int graph_dfscan(graph_t *g, vertex_id_t * start, std::list<vertex_id_t> & topo_seq,
        std::list<vertex_id_t> & result1, std::list<edge_t> & result2);

//最小生成树
int graph_prim(graph_t * g, graph_t * tree);
int graph_kruskal(graph_t *g, graph_t*tree);

//最短路径。路径保存在paths里，距离值保存在distance里，他们都是以目标顶点为key的，表示start到目标顶点的最短路径和最短距离
int graph_dijkstra(graph_t * g, const vertex_id_t &start, std::map<vertex_id_t, path_t> & paths, 
    std::map<vertex_id_t, edge_weight_t> & distance);

// floyd算法计算两个顶点之间最小路径的时候，用下面的结构体作为key
typedef struct{
    vertex_id_t start; //起始顶点
    vertex_id_t end; // 结束顶点 
}floyd_key_t;

bool operator<(const floyd_key_t& a, const floyd_key_t& b) ;

//floyd算法求两个顶点之间的最小路径和最短距离，分别保存在paths和distance中，
// 他们都是以floyd_key_t为key的map。如果两个顶点不可达，就不会在这两个map中存在相关项
int graph_floyd(graph_t * g, std::map<floyd_key_t, path_t> & paths, 
    std::map<floyd_key_t, edge_weight_t> & distance);

// kahn算法求解有向图的拓扑排序， 1表示没有解，0表示成功，-1表示出错
int graph_kahn(graph_t * g, std::list<vertex_id_t> & topo_seq);

//一些辅助函数，开发者不用关心
gint  compare_vertex(gconstpointer  a,  gconstpointer  b);
gint  compare_edge(gconstpointer  a,  gconstpointer  b);
void free_edge(gpointer data);
void free_vertex(gpointer data);
void free_common(gpointer data);


#endif 