

#include "graph.h"
#include <set>
#include <list>

using namespace std;

gint  compare_vertex(gconstpointer  a,  gconstpointer  b)
{
    vertex_t * aa = (vertex_t*)a;
    vertex_t * bb = (vertex_t*)b;
 
    return aa->vertex_id - bb->vertex_id;
}
gint  compare_edge(gconstpointer  a,  gconstpointer  b)
{
    const edge_t * aa = (const edge_t*)a;
    const edge_t * bb = (const edge_t*)b;
 
    if (aa->from == bb->from && aa->to == bb->to && aa->weight == bb->weight)
    {
        return 0;
    }
    return 1;
}

//图初始化
int graph_init(graph_t * g, bool is_directed)
{
    g->is_directed = is_directed;
    g->vertex_list = NULL;
    return 0;
}

//往图里加一个顶点
int graph_add_vertex(graph_t * g, vertex_id_t id)
{
    
    vertex_t * v = (vertex_t *)malloc(sizeof(vertex_t));
    if (v == NULL)
    {
        perror("malloc");
        return -1;
    }
    v->edge_list = NULL;
    v->vertex_id = id;
    GList *position1 = g_list_find_custom(g->vertex_list, v, compare_vertex);
    if (position1 != NULL) // vertex exist
    {
        free(v);
        v = NULL;
        return 0;
    }
    else // new vertex
    {
        g->vertex_list = g_list_append(g->vertex_list, v);
        return 0;
    }
}

// 边e描述的from -> to这个方向 在邻接表里增加一下,相当于当作有向图处理
static int graph_add_edge_one_direction(graph_t * g, const edge_t * e)
{
    // 维护好edge e的from 顶点
    {
        vertex_t v;
        v.vertex_id = e->from;
        
        GList * position1 = g_list_find_custom(g->vertex_list, &v, compare_vertex);
        if (position1 != NULL) // vertex exist
        {
            
            vertex_t * pv = (vertex_t *)position1->data;
            GList * position2 = g_list_find_custom(pv->edge_list, e, compare_edge);
            if (position2 != NULL) // edge exist
            {
                edge_t * pe = (edge_t*)position2->data;
                pe->weight = e->weight;
            }
            else // new edge
            {
                edge_t * pe = (edge_t*)malloc(sizeof(edge_t));
                if (pe == NULL) {perror("malloc"); return -1;}
                memcpy(pe, e, sizeof(edge_t));
                pv->edge_list = g_list_append(pv->edge_list, pe);
            }
        }
        else // new vertex
        {
            vertex_t* pv = (vertex_t*)malloc(sizeof(vertex_t)); 
            if (pv == NULL) {perror("malloc"); return -1;}
            pv->vertex_id = e->from;
            pv->edge_list = NULL;

            edge_t * pe = (edge_t*)malloc(sizeof(edge_t));
            if (pe == NULL) {perror("malloc"); free(pv); return -1;}
            memcpy(pe, e, sizeof(edge_t));

            pv->edge_list = g_list_append(pv->edge_list, pe);
            g->vertex_list= g_list_append(g->vertex_list, pv);
        }
    }
    // 维护好 to 顶点，确保存在
    {
        vertex_t v;
        v.vertex_id = e->to;
        
        GList * position1 = g_list_find_custom(g->vertex_list, &v, compare_vertex);
        if (position1 == NULL) // to vertex does NOT exist
        {
            //printf("to vertex does NOT exist %d\n", e->to);
            vertex_t* pv = (vertex_t*)malloc(sizeof(vertex_t)); 
            if (pv == NULL) {perror("malloc"); return -1;}
            pv->vertex_id = e->to;
            pv->edge_list = NULL;

            g->vertex_list = g_list_append(g->vertex_list, pv);
        }
        else
        {
            //printf("to vertex  exist already. %d\n", e->to);
        }
    }
    return 0;
}


//往图里加一条边
int graph_add_edge(graph_t * g, const edge_t * e)
{
   if (g->is_directed) //有向图，就只加一次
   {
        return graph_add_edge_one_direction(g, e);
   }
   else // 无向图，这条边其实可以认为是双向的，加两次
   {
        int iret = graph_add_edge_one_direction(g, e);
        if (iret) { return iret;}
        edge_t ee;
        ee.from = e->to;
        ee.to = e->from;
        ee.weight = e->weight;
        return graph_add_edge_one_direction(g, &ee);
   }
}
void free_edge(gpointer data)
{
    edge_t * e = (edge_t *)data;
    if (e == NULL) {return;}
    free(e);
    return;
    
}
void free_vertex(gpointer data)
{
    vertex_t * v = (vertex_t *)data;
    if (v == NULL) {return;}
    g_list_free_full(v->edge_list, free_edge);
    v->edge_list = NULL;
    free(v);
    return;

}
void free_common(gpointer data)
{
    free(data);
}
int graph_free(graph_t * g)
{
    g_list_free_full(g->vertex_list, free_vertex);
    g->vertex_list = NULL;
    return 0;
}

int graph_copy(graph_t * from, graph_t *to, std::set<vertex_id_t> * except)
{
    if ( from == NULL || to == NULL) {return 0;}
    graph_free(to);
    to->is_directed = from->is_directed;
    //遍历每一个顶点，
    for (GList* v1 = from->vertex_list; v1 != NULL; v1 = v1->next) 
    {
        vertex_t * pv = (vertex_t*)v1->data;
        if (except &&  except->find(pv->vertex_id) != except->end()) { continue;}
        graph_add_vertex(to, pv->vertex_id);
        for (GList * v2 = pv->edge_list; v2 != NULL; v2 = v2->next)//遍历该顶点发出的每一条边
        {
            edge_t * pe = (edge_t*)v2->data;
            if (except && 
                (except->find(pe->from) != except->end() || except->find(pe->to) != except->end())) {continue;}
            if (graph_add_edge(to, pe))
            {
                return -1;
            }
        }

    }
    return 0;
}
