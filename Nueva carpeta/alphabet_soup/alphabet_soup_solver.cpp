#include <cassert>
#include "alphabet_soup_solver.hpp"
#include "trie.hpp"

std::istream&
operator>>(std::istream & in, AlphabetSoup& soup)
{
    int rows, cols;
    in >> rows >> cols;
    if (in)
    {
        soup.resize(rows, cols);
        in.ignore(); //remove newline.
        std::string row;
        for(int i=0;i<rows && in; ++i)
        {
            in >> row;
            if (in)
                soup.set_row(i, row);
        }
    }
    return in;
}

std::ostream&
operator<<(std::ostream& out, AlphabetSoup const& soup)
{
    out << soup.rows() << ' ' << soup.cols() << std::endl;
    for (int i=0;i<soup.rows();++i)
        out << soup.row(i) << std::endl;
    return out;
}

/**
 * @brief scan a cell looking for the next letter of a word.
 * @param row and
 * @param col are the current cell coordinates.
 * @param dy and
 * @param dx are direction vector to follow the next letter.
 * @param soup is the alphabet soup where looking for.
 * @param node is the current node of the trie.
 * @param scan_result save the current chain. Is a pair of <word, cells_coordinates [row,col]>
 *
 */
void
scan_cell(int row, int col, int dy, int dx, AlphabetSoup const& soup, TrieNode::ref node,
          std::pair<std::string, std::stack <std::pair<int, int> >> & scan_result)
{
    //ALGORITHM
    //1. If this node is a leaf node (Leaf nodes has value != "").
    //1.1 Save the word in the first item of the scan_result pair and finish recursion.
    //2. Else, we can have tree cases.
    //2.1.1 This is the first letter of word (dx==dy==0)
    //2.1.2 Scan all the 3x3 neighbourhood for the next letter.
    //2.2.1 This is a next right letter, so we need scan the next in the direction (dy, dx).
    //2.3 if a word was found (first item of the scan_result pair != ""), we push the current
    //    cell's coordinates [row,col] into the second item of scan_result.

    if (node->value() != "")
    {
        //Base case: We are in a leaf so we have just found a word.
        scan_result.first = node->value();
        //update scan_result first value to the key value found.
    }
    else
    {
        if (row>=0 && row<soup.rows() && col>=0 && col<soup.cols())
        {
            auto const cell_v = soup.cell(row, col);

            if (node->has(cell_v))
            {
                //Recursion case: looking for the next letter.

                node = node->child(cell_v);
                bool found = false;                
                if (dx == 0 && dy == 0)
                {
                    //TODO
                    //It is the first letter, so we scan all the neighbourhood (but not the current cell!).
                    for(int b = -1; b <= 1; b++)

                    {
                        for(int c = -1; c <= 1; c++)
                        {
                            if(c == 0 && b == 0)
                                c++;
                            if(scan_result.first == "")
                                scan_cell(row+b, col+b, b, c, soup, node, scan_result);
                        }
                    }
                    //Was a word found?
                    found = (scan_result.first != "");
                }
                else
                {
                    //TODO
                    //Not is the first letter, so we follow the scan direction (dy,dx) if we can.
                    if(scan_result.first == "")
                        scan_cell(row+dx, col+dy, dy, dx, soup, node, scan_result);


                    //Was a word found?
                    found = (scan_result.first != "");
                }
                if (found)
                    //TODO
                    scan_result.second.push(std::make_pair(row, col));
                    //If a word was found for this chain, we save the current cell coordinates into
                    //the scan_result stack of cells. Note that the cells are numbered from (1,1) to (rows,cols).
                    ;
            }
            //else Base case: not found. This chain not is a valid word. Do nothing.
        }
        //else Base case: not found. We are out of the soup grid. Do nothing.
    }
}

std::vector< std::pair<std::string, std::stack<std::pair<int, int> >>>
alphabet_soup_solver(AlphabetSoup& soup, std::vector<std::string> const& words)
{
    std::vector< std::pair<std::string, std::stack<std::pair<int, int> >>> result;
    Trie trie;

    //Generate a trie with the words as keys.
    for (size_t i = 0; i<words.size(); ++i)
        trie.insert(words[i]);

    for (int row = 0; row < soup.rows(); ++row)
    {
        for (int col = 0; col < soup.cols(); ++col)
        {
            auto scan_result = std::make_pair(std::string(""), std::stack<std::pair<int,int>>());
            //Scan from this cell. This is the first letter so dx==dy==0.
            scan_cell(row, col, 0, 0, soup, trie.root(), scan_result);
            if (scan_result.first!="")
              //A word was found, so to save it into the results.
              result.push_back(scan_result);
        }
    }
    return result;
}

