#include "graph.h"

int graph_kruskal(graph_t *g, graph_t*tree)
{
    if (g == NULL || tree == NULL) {return -1;}

    std::map<vertex_id_t, int> vertex2subgraph; //顶点到子图的映射
    int i = 0;
    for (GList* v = g->vertex_list; v != NULL; v = v->next, i++) 
    {
        vertex_t* vertex = (vertex_t*)v->data;
        vertex2subgraph.insert(std::pair<vertex_id_t, int>(vertex->vertex_id, i+1));
    }

    //对每一条边进行遍历，找到最小权重的且两个顶点属于不同的子图的边，加入到最小生成树
    while (1)
    {
        edge_t edgeWithMinWeight;
        bool addNewEdgeFlag = false;
        edgeWithMinWeight.weight = MAX_WEIGHT_VALUE;
        for (GList* v = g->vertex_list; v != NULL; v = v->next) {
            vertex_t* vertex = (vertex_t*)v->data;
            for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
                edge_t* pe = (edge_t*)e->data;
                int sub1 = vertex2subgraph[pe->from];
                int sub2 = vertex2subgraph[pe->to];
                //printf("check edge(%d,%d,%d), belong to (%d,%d)\n", pe->from,pe->to,pe->weight,sub1, sub2);
                if (pe->weight <= edgeWithMinWeight.weight && sub1 != sub2)
                {
                    edgeWithMinWeight = *pe;
                    graph_add_edge(tree, pe);
                    //printf("add edge %d-%d->%d\n", pe->from, pe->weight,pe->to);
                    addNewEdgeFlag = true;
                    //合并这两个子图 std::map 的迭代器在修改元素的 value 时是安全的，只要不插入或删除元素，迭代器就会保持有效
                    std::map<vertex_id_t, int>::iterator it;
                    for (it = vertex2subgraph.begin(); it!= vertex2subgraph.end(); ++it)
                    {
                        if (it->second == sub2)
                        {
                            it->second = sub1;
                        }
                    }
                }
            }
        }
        if (!addNewEdgeFlag) //加无可加，就无需再加
        {
            break;
        }
    }
    return 0;
}
