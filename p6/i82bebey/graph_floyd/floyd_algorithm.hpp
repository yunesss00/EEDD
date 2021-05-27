#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"



/**
 * @brief Compute the weight matrix.
 * @arg[in] g is a weighted graph.
 * @arg[out] W is the Weight matrix.
 */
template<class T>
void compute_weight_matrix(WGraph<T>& g, std::valarray<std::valarray<float>>& W)
{
    W.resize(g.size(), std::valarray<float>(std::numeric_limits<float>::infinity(), g.size()));    
    //TODO
        
    
     for (size_t i = 0;  i < g.size(); i++)
     {
         for (size_t j = 0; j < g.size(); j++)
         {
             if (g.are_adjacent(g.node(i),g.node(j)))
             {
                 W[i][j]=g.edge(g.node(i),g.node(j))->item();
             }
             
         }
         
     }
     

}

/**
 * @brief Search for the minium path between vertices using the Floyd's algorithm.
 * @arg[in] g is a weighted graph.
 * @arg[out] D is the Distances matrix.
 * @arg[out] I is the Intermediate matrix.
 * @pre the weigths meet the triangular inequality: d(u,v) <= d(u,k) + d(k,v) for all u!=v!=k.
 * @post if none path between u,v exists then D[u][v]==inf and I[u][v]==-1
 * @post if an edge (u,v:w) exists then D[u][v]==w and I[u][v]==-1
 * @post if a path between u,v exits then D[u][v]<inf and D[u][v]==k, k is vertex in the minimum path linking u with v.
 */
template<class T>
void floyd_algorithm(WGraph<T>& g, std::valarray<std::valarray<float>>& D,
                     std::valarray<std::valarray<int>>& I)
{
    compute_weight_matrix<T>(g, D);
    //Set self-distances to zero.
    for (size_t i=0;i<g.size();++i)
        D[i][i]=0.0;
    I.resize(g.size(), std::valarray<int>(-1, g.size()));
   
    
    //TODO: codify the Floyd's algorithm.
    for (int i = 0; i < g.size(); i++)
        {
            for (int t = 0; t < g.size(); t++)
            {
                I[i][t] = t;
            }
        }

        for (int k = 0; k < g.size(); k++)
        {
            for (int v = 0; v < g.size(); v++)
            {
                for (int u = 0; u < g.size(); u++)
                {
                    if (D[u][k] + D[k][v] < D[u][v])
                    {
                        D[u][v] = D[u][k] + D[k][v];
                        I[u][v] = I[u][k];
                    }
                }
            }
        }
   


}

/**
 * @brief Given the Floyd's Intermidiate matrix, compute the path.
 * @arg[in] u is the label of the start vertex.
 * @arg[in] v is the label of the end vertex.
 * @arg[in] I is the Floyd's Intermidiate matrix.
 * @arg[out] path is a vector with the sequence of vertex's labels for the minimum path linking u with v.
 * @pre Let D be the Floyd's D matrix corresponding with I, D[u][v]<inf.
 * @post u is the first item of path.
 * @post v is the last item of path.
 */
inline void
floyd_compute_path(size_t u, size_t v, std::valarray<std::valarray<int>>& I, std::vector<size_t>& path)
{
    //Prec: distance (u,v) < inf
    path.resize(I.size());

    //TODO:
    //Think first: is it necessary to build a binary tree?
    // or
    // is it sufficient with a recursive descent by doing an in-depth search?
    if(u==v){
        path.resize(2);
        path[0]=u;
        path[1]=v;
    }
    else{

    
    auto start=u;
    auto end=v;
    path[0]=u;
    int tam=1;

        while (start != end)
        {
            start = I[start][end];
            path[tam]=start;
            tam++;
        }

        path[tam]=end;
        path.resize(tam);
    }
    
    

}


#endif //__FLOYD_ALGORITHM_HPP__
