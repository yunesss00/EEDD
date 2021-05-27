#ifndef __GRAPH_UTILS_HPP__
#define __GRAPH_UTILS_HPP__

#include <iostream>
#include <memory>
#include <string>

#include "graph.hpp"

/**
 * @brief unfold a weighted graph from an input stream.
 * Input format:
 * <capacity>
 * <Nodes>
 * <node item_0>
 * ...
 * <node item_N-1>
 * <Edges>
 * <u_0> <v_0> <weight_0>
 * ...
 * <u_E-1> <v_E-1> <weight_E-1>
 */
template <class T>
bool
unfold_wgraph(std::istream& in, WGraph<T>& g)
{
    size_t capacity;
    in >> capacity;
    if (!in)
        return false;

    g = WGraph<T>(capacity);

    size_t n_nodes;
    in >> n_nodes;
    if (!in)
        return false;

    for(size_t n=0; n<n_nodes; ++n)
    {
        T item;
        in >> item;
        if (!in)
            return false;
        g.add_node(item);
    }
    size_t n_edges;
    in >> n_edges;
    for (size_t e=0;e<n_edges; ++e)
    {
        size_t u, v;
        float w;
        in >> u >> v >> w;
        if (!in || u>=n_nodes || v>=n_nodes)
            return false;
        g.set_weight(g.node(u), g.node(v), w);
    }
    return true;
}

/**
 * @brief Fold a weighted graph to an output stream.
 * Input format:
 * <capacity>
 * <Nodes>
 * <node item_0>
 * ...
 * <node item_N-1>
 * <Edges>
 * <u_0> <v_0> <weight_0>
 * ...
 * <u_E-1> <v_E-1> <weight_E-1>
 */
template <class T>
bool
fold_wgraph(std::ostream& out, WGraph<T> & g)
{
    out << g.capacity() << std::endl;
    out << g.size() << std::endl;
    for (size_t n=0;n<g.size();++n)
        out << g.node(n)->item() << std::endl;
    std::vector< typename WGraph<T>::EdgeRef > edges;
    g.goto_first_node();
    while(g.has_current_node())
    {
        g.goto_first_edge();
        while(g.has_current_edge())
        {
            edges.push_back(g.current_edge());
            g.goto_next_edge();
        }
        g.goto_next_node();
    }
    out << edges.size() << std::endl;
    for(size_t e=0;e<edges.size();++e)
        out << edges[e]->first()->label() << ' '
            << edges[e]->second()->label() << ' '
            << edges[e]->item() << std::endl;
    if (out)
        return true;
    else
        return false;
}

/**
 * @brief Create a Graph from txt representation.
 * If the graph is non directed, only one input u-v edge is needed but
 * it will be duplicated as u->v and v->u.
 *
 * Input Format:
 *
 * [DIRECTED|NON_DIRECTED]
 * <NUM-VERTICES>
 * <ITEM_1>
 * <ITEM_2>
 * ...
 * <ITEM_N>
 * <NUM-EDGES>
 * <ITEM_U> <ITEM_V> <WEIGTH>
 * ...
 *
 * @arg[in,out] in is the input stream.
 * @return a reference to the graph or nullptr if input error.
 * @warning std::runtime_error("Wrong graph") is throw if bad input format.
 */
template<class T>
std::shared_ptr<WGraph<T>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);    
    std::shared_ptr<WGraph<T>> ref;

    //TODO
    //Renember if the graph is non directed, each edge u--v generate two
    //directed edges u-->v and v-->u.
    //If the input format is wrong, the throw std::runtime_error("Wrong graph").
    std::string type;
    in >> type;
    std::string nodes;
    in >> nodes;
    int n_nodes=stoi(nodes);
    WGraph<T> graph(n_nodes);

    if(type=="DIRECTED"){  //DIRECTED
        for (int i = 0; i < n_nodes; i++)
        {
            T node;
            in >> node;
            graph.add_node(node);
        }
        std::string edges;
        in >> edges;
        int n_edges=stoi(edges);
        for (int i = 0; i < n_edges; i++)
        {
            T edge1,edge2;
            float val;
            in >> edge1;
            in >> edge2;
            in >> val;
           

            auto aux1=graph.find(edge1);
            auto aux2=graph.find(edge2);
            
            graph.set_weight(aux1,aux2,val);
            
        }
    }
    else{ //NON DIRECTED
        
        for (int i = 0; i < n_nodes; i++)
        {
            T node;
            in >> node;
            graph.add_node(node);
        }
        std::string edges;
        in >> edges;
        int n_edges=stoi(edges);
        for (int i = 0; i < n_edges; i++)
        {
            T edge1,edge2;
            float val;
            in >> edge1;
            in >> edge2;
            in >> val;
           

            auto aux1=graph.find(edge1);
            auto aux2=graph.find(edge2);
            
            graph.set_weight(aux1,aux2,val);
            graph.set_weight(aux2,aux1,val);
            
        }

    }

    ref=std::make_shared<WGraph<T>>(graph);
    return ref;
}

#endif //__GRAPH_UTILS_HPP__
