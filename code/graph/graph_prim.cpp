#include "graph.h"

int graph_prim(graph_t * g, graph_t * t)
{
    if (g == NULL || t == NULL) { return -1;}
    graph_init(t, g->is_directed);

    GList * first = g_list_first(g->vertex_list);
    if (first == NULL)
    {
        return 0;
    }
    
    std::set<vertex_id_t> visited_vertex;
    vertex_id_t vid = ((vertex_t*)first->data)->vertex_id;
    graph_add_vertex(t, vid);
    visited_vertex.insert(vid);

    while(1)
    {
        bool findNewVertex = false;
        edge_t edgeWithMinWeight;
        edgeWithMinWeight.weight = MAX_WEIGHT_VALUE;
        
        GList * currentV = t->vertex_list;
        while (currentV != NULL) // t中的每一个顶点
        {
            vertex_t * pv = (vertex_t *)currentV->data;

            //到原图中去找到该节点，检查它的发出的每一条边
            GList *position = g_list_find_custom(g->vertex_list, pv, compare_vertex);
            if (position == NULL)
            {
                fprintf(stderr, "failed to locate vertex %d in g\n", pv->vertex_id);
                return -1;
            }
            GList * currentE = ((vertex_t *)(position->data))->edge_list;
            while (currentE != NULL) // 顶点里的每一条边
            {
                edge_t * pe = (edge_t*)currentE->data;
                if (visited_vertex.find(pe->to) == visited_vertex.end()) //终止顶点 没有出现在t这个图里
                {
                    if (pe->weight < edgeWithMinWeight.weight) // 且权重是最小的
                    {
                        edgeWithMinWeight = *pe;
                        findNewVertex = true;
            
                    }
                }
                currentE = currentE->next;
            }

            currentV = currentV->next;
        }
        if (findNewVertex)
        {
            graph_add_edge(t, &edgeWithMinWeight);
            visited_vertex.insert(edgeWithMinWeight.to);
            printf("add new edge %d-%d->%d\n", edgeWithMinWeight.from, edgeWithMinWeight.weight, edgeWithMinWeight.to);
        }
        else
        {
            break;
        }

    }
    return 0;
}