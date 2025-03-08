#include "graph.h"


int graph_dijkstra(graph_t * g, const vertex_id_t &start, std::map<vertex_id_t, path_t> & paths, 
    std::map<vertex_id_t, edge_weight_t> & distance)
{
    if (g == NULL) { return -1;}

    //找到起始顶点，初始化距离表，
    vertex_t v;
    v.vertex_id = start;
    GList *position = g_list_find_custom(g->vertex_list, &v, compare_vertex);
    if (position == NULL)
    {
        fprintf(stderr, "failed to locate vertex %d\n", start);
        return -1;
    }
    distance[start] = 0;
    path_t onePath;
    paths.insert(std::pair<vertex_id_t, path_t>(start, onePath));
    for (GList *current = ((vertex_t *)position->data)->edge_list;
         current != NULL;
         current = current->next)
    {
        edge_t * pe = (edge_t*)current->data;
        distance.insert( std::pair<vertex_id_t, edge_weight_t>(pe->to, pe->weight) );

        path_t onePath;
        onePath.push_back(pe->from);
        paths.insert( std::pair<vertex_id_t, path_t>(pe->to, onePath));
        printf("init path and distance for %d\n", pe->to);
    }

    std::set<vertex_id_t> usedBridge;
    while (1)
    {
        //找到距离表中当下最小的目标顶点，拿出来当作中间桥梁，看看是否让距离会缩短
        std::map<vertex_id_t, edge_weight_t>::const_iterator it;
        std::map<vertex_id_t, edge_weight_t>::const_iterator shortest = distance.end();
        for (it = distance.begin(); it != distance.end(); ++it)
        {
            if (usedBridge.find(it->first) != usedBridge.end()) //这个顶点作为bridge用过了
            {
                continue;
            }
            if (shortest == distance.end() || it->second < shortest->second)
            {
                shortest = it;
            }
        }
        if (shortest == distance.end()) //没有合适的顶点作为桥梁了
        {
            break;
        }
        usedBridge.insert(shortest->first); //标记为这个顶点做过桥梁了

        //把桥梁顶点的所有邻居边拿出来看一下，经由桥梁顶点，是否会缩短他们的距离
        edge_weight_t start2bridgeDistance = shortest->second; // 开始顶点到桥梁顶点的距离
        vertex_id_t bridgeVertex = shortest->first;
        vertex_t v;
        v.vertex_id = bridgeVertex;
        GList *position = g_list_find_custom(g->vertex_list, &v, compare_vertex);
        if (position == NULL)
        {
            fprintf(stderr, "failed to locate vertex %d\n", v.vertex_id);
            return -1;
        }
        for (GList *current = ((vertex_t *)position->data)->edge_list;
            current != NULL;
            current = current->next)
        {
            edge_t * pe = (edge_t*)current->data;
            edge_weight_t old_distance = MAX_WEIGHT_VALUE;
            std::map<vertex_id_t, edge_weight_t>::iterator it = distance.find(pe->to);
            if (it != distance.end())
            {
                old_distance = it->second;
            }
            if (start2bridgeDistance + pe->weight < old_distance) 
            {
                distance[pe->to] = start2bridgeDistance + pe->weight; //修改到pe->to的距离

                // 修改到pe->to的路径， 变成： start到桥梁顶点的路径，加上桥梁顶点到pe->to。
                std::map<vertex_id_t, path_t>::iterator path_it = paths.find(bridgeVertex);
                if (path_it == paths.end())
                {
                    fprintf(stderr, "fatal error, can NOT find path information for %d\n", bridgeVertex);
                    return -1;
                }
                path_t onePath = path_it->second; // 这里会发生拷贝，后面再操作onePath不会影响原有的
                onePath.push_back(bridgeVertex);
                paths[pe->to] = onePath;
            }
        } 
    }
    return 0;
}

// 重载 < 运算符
bool operator<(const floyd_key_t& a, const floyd_key_t& b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

int graph_floyd(graph_t * g, std::map<floyd_key_t, path_t> & paths, 
    std::map<floyd_key_t, edge_weight_t> & distance)
{
    if (g == NULL) {return -1;}
    //初始化距离和路径
    for (GList* v = g->vertex_list; v != NULL; v = v->next) {
        vertex_t* vertex = (vertex_t*)v->data;
        for (GList* e = vertex->edge_list; e != NULL; e = e->next) {
            edge_t* edge = (edge_t*)e->data;
            
            floyd_key_t key;
            key.start = edge->from;
            key.end = edge->to;

            path_t onePath;
            onePath.push_back(edge->from);

            paths.insert(std::pair<floyd_key_t, path_t>(key, onePath));
            distance.insert(std::pair<floyd_key_t, edge_weight_t>(key, edge->weight));
        }
    }
    //遍历每一个顶点，以它为桥梁，看可否缩短其他任意两顶点间的路径
    for (GList* v1 = g->vertex_list; v1 != NULL; v1 = v1->next) 
    {
        vertex_t* bridge = (vertex_t*)v1->data;

        for (GList* v2 = g->vertex_list; v2 != NULL; v2 = v2->next) 
        {
            vertex_t* start = (vertex_t*)v2->data;
            if (start->vertex_id == bridge->vertex_id) {continue;}
            floyd_key_t key1;
            key1.start = start->vertex_id;
            key1.end = bridge->vertex_id;
            edge_weight_t start2bridge, bridge2end, start2end;
            if (distance.find(key1) == distance.end()) {continue;} // start -> bridge不可达
            else 
            {
                start2bridge = distance.find(key1)->second;
            }
            
            for (GList* v3 = g->vertex_list; v3 != NULL; v3 = v3->next) 
            {
                vertex_t* end = (vertex_t*)v3->data;
                if (end->vertex_id == bridge->vertex_id) {continue;}
                if (end->vertex_id == start->vertex_id) {continue;}
                floyd_key_t key2, key3;
                key2.start = bridge->vertex_id;
                key2.end = end->vertex_id;
                if (distance.find(key2) == distance.end()) {continue;} // bridge -> end不可达
                else 
                {
                    bridge2end = distance.find(key2)->second;
                }

                key3.start = start->vertex_id;
                key3.end = end->vertex_id;
                if (distance.find(key3) == distance.end())
                {
                    start2end = MAX_WEIGHT_VALUE;
                }
                else
                {
                    start2end = distance.find(key3)->second;
                }

                if (start2bridge + bridge2end < start2end) //经由bridge会更短，更新距离和路径
                {
                    distance[key3] = start2bridge + bridge2end;

                    path_t path1 = paths[key1];
                    path_t path2 = paths[key2];
                    path1.insert(path1.end(), path2.begin(), path2.end());

                    paths[key3] = path1;
                    
                }

            }
        }
        
    }
    return 0;

}