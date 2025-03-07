#include "graph.h"
#include <queue>
#include <bits/stl_pair.h>


int graph_shortest_path_by_bfs(graph_t * g, vertex_id_t*start, std::map<vertex_id_t, path_t> & returned_path,
    std::list<vertex_id_t> & result1, std::list<edge_t> & result2 )
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
    
    //把起始顶点入队列，起始顶点可能不在图里，后面会检查发现
    std::queue<std::pair< vertex_id_t, path_t> > q;
    path_t path;
    path.push_back(start_id);
    std::pair< vertex_id_t, path_t>  onePair(start_id, path);
    q.push(onePair);

    while (!q.empty())
    {
        // 弹出一个顶点，查找它在图里的信息
        std::pair< vertex_id_t, path_t> onePair = q.front();
        q.pop();
        vertex_t v;
        v.vertex_id = onePair.first;
        GList * position = g_list_find_custom(g->vertex_list, &v, compare_vertex);
        if (position == NULL)
        {
            fprintf(stderr, "can NOT find vertex with id=%d\n", *start);
            return -1;
        }
        vertex_t * pv = (vertex_t*)position->data;
        
        //访问到了一个顶点，保存到结果里
        returned_path.insert(onePair);
        result1.push_back(onePair.first);
        

        GList * current = pv->edge_list;//进一步探索更深的节点
        while (current != NULL)
        {
            edge_t *pe = (edge_t*)current->data;

            if (returned_path.find(pe->to) != returned_path.end()) //已经访问过了这个节点
            {
                current = current->next;
                continue;
            }
            result2.push_back(*pe);

            path_t onePath = onePair.second;
            onePath.push_back(pe->to);
            std::pair< vertex_id_t, path_t>  onePair(pe->to, onePath);
            q.push(onePair); 


            current = current->next;
        }

    }

    return 0;
}