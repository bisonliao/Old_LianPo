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

int graph_kahn(graph_t * g, std::list<vertex_id_t> & topo_seq)
{
    if (g== NULL){return -1;}
    if (!g->is_directed) {return 1;}
    graph_t tmp1, tmp2; //这两个图用来倒腾，不断的拷贝，每次拷贝会删掉一个入度为0的顶点和它相连的边
    graph_init(&tmp1, g->is_directed);
    graph_init(&tmp2, g->is_directed);
    graph_t * from = &tmp1;
    graph_t * to = &tmp2;

    if (graph_copy(g, &tmp1))
    {
        fprintf(stderr, "graph_copy() failed!\n");
        return -1;
    }
    
    
    while (1)
    {
        std::set<vertex_id_t> toRemove;
        // 从from中找到 入度为0 的顶点，放到toRemove中
        std::map<vertex_id_t, int> indegree;
        for (GList* v1 = from->vertex_list; v1 != NULL; v1 = v1->next) 
        {
            vertex_t * pv = (vertex_t*)v1->data;
            indegree[pv->vertex_id] = 0;
        }
        
        for (GList* v1 = from->vertex_list; v1 != NULL; v1 = v1->next) 
        {
            vertex_t * pv = (vertex_t*)v1->data;
            for (GList * v2 = pv->edge_list; v2 != NULL; v2 = v2->next)//遍历该顶点发出的每一条边
            {
                edge_t * pe = (edge_t*)v2->data;
                indegree[pe->to] = indegree[pe->to] + 1;
            }
        }
       
        for (std::map<vertex_id_t, int>::const_iterator it = indegree.begin();
            it != indegree.end(); ++it)
        {
            if (it->second == 0)
            {
                toRemove.insert(it->first);
                topo_seq.push_back(it->first);
                printf("find a vertex with 0 in degree:%d\n", it->first);
            }
        }
        
        // 发现没有入度为0 的点了
        if (toRemove.size() < 1)
        {
            if (g_list_length(from->vertex_list) > 0) //但这时候图中还有节点
            {
                graph_free(&tmp1);
                graph_free(&tmp2);
                return 1;
            }
            else
            {
                graph_free(&tmp1);
                graph_free(&tmp2);
                return 0;
            }
            
        }
        
        
        if (graph_copy(from, to, &toRemove))
        {
            fprintf(stderr, "fatal error! graph_copy() failed!\n");
            return -1;
        }
        
        // swap from and to
        graph_t * tmp = to;
        to = from;
        from = tmp;
    }

   
    graph_free(&tmp1);
    graph_free(&tmp2);
    return 0;
}