#include "graph.h"

int graph_dfscan(graph_t *g, vertex_id_t * start, std::list<vertex_id_t> & topo_seq,
    std::list<vertex_id_t> & result1, std::list<edge_t> & result2)
{
    if (g == NULL)
    {
        return -1;
    }
    vertex_id_t start_id;
    if (start == NULL)
    {
        GList *first = g_list_first(g->vertex_list);
        if (first == NULL)
        {
            return 0;
        }
        start_id = ((vertex_t*)first->data)->vertex_id;
    }
    else
    {
        start_id = *start;
    }
    std::stack<vertex_id_t> vertex_ancestor;
    std::set<vertex_id_t> vertex_visited;
    vertex_ancestor.push(start_id);
    vertex_visited.insert(start_id);

    while (!vertex_ancestor.empty())
    {
        vertex_id_t parent = vertex_ancestor.top();
        
        while (1)
        {
            //找到parent这个顶点
            vertex_t v;
            v.vertex_id = parent;
            GList* position = g_list_find_custom(g->vertex_list, &v, compare_vertex);
            if (position == NULL)
            {
                fprintf(stderr, "failed to locate vertex %d in graph\n", parent);
                return -1;
            }
            //找parent出发的一条没有访问过的边，继续深入下去
            GList * current = ((vertex_t*)position->data)->edge_list;
            bool findNewChild = false;
            while (current != NULL)
            {
                edge_t * pe = (edge_t*)current->data;
                vertex_id_t child = pe->to;
                if (vertex_visited.find(child) == vertex_visited.end() ) // 没有访问过
                {
                    //一路深挖下去
                    vertex_ancestor.push(child);
                    vertex_visited.insert(child);
                    parent = child;
                    findNewChild = true;
                    break;
                }
                else
                {
                    current = current->next; //看下一个孩子
                }    
            }
            if (!findNewChild) // parent的所有孩子都访问过了，或者没有孩子继续往深处走，那这个顶点就可以访问了，已经穷尽了深度
            {
                vertex_ancestor.pop();
                result1.push_back(parent);
                if (g->is_directed  && start != NULL) {topo_seq.push_back(parent);}

                // 根据parent，反向找到指向它的边
                if (!vertex_ancestor.empty())
                {
                    vertex_id_t parentOfParent = vertex_ancestor.top();
                    vertex_t v;
                    v.vertex_id = parentOfParent;
                    GList* position1 = g_list_find_custom(g->vertex_list, &v, compare_vertex);
                    if (position1 == NULL)
                    {
                        fprintf(stderr, "failed to locate vertex %d in graph\n", parentOfParent);
                        return -1;
                    }
                    edge_t e;
                    e.from = parentOfParent;
                    e.to = parent;
                    vertex_t * pv = (vertex_t*)position1->data;
                    GList* position2 = g_list_find_custom(pv->edge_list, &e, compare_edge);
                    if (position2 == NULL)
                    {
                        fprintf(stderr, "failed to locate edge %d->%d\n", parentOfParent, parent);
                        return -1;
                    }
                    edge_t * pe = (edge_t *)position2->data;
                    result2.push_back(*pe);
                }
                
                break;
            }
        }
    }
    if (g->is_directed && start != NULL) {topo_seq.reverse();}

    return 0;

}