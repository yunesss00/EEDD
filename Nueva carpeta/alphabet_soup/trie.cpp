#include "trie.hpp"


bool
TrieNode::has(char k) const
{
    //TODO
    if(children_.find(k) != children_.end())
    {
        return true;
    }
    return false;
}

TrieNode::ref const&
TrieNode::child(char k) const
{
    assert(has(k));
    //TODO
    return children_.find(k)->second;
}

TrieNode::ref
TrieNode::child(char k)
{
    assert(has(k));
    //TODO
  return children_.find(k)->second;
}

std::string const&
TrieNode::value() const
{
    //TODO
    return value_;
}

const std::map<char, TrieNode::ref> &TrieNode::children() const
{
    return children_;
}

void
TrieNode::set_value(std::string const& new_v)
{
    //TODO
    value_ = new_v;
}

void
TrieNode::insert(char k, ref node)
{
    //TODO
    children_.emplace(k, node);
}

Trie::Trie()
{
    //DO nothing.
}

bool
Trie::find(std::string const& k) const
{
    auto node = find_node(k);
    //The Trie can have a prefix==k but does not store the key k.
    const bool found = (node != nullptr) && (node->value().size()==k.size());
    assert(!found || node->value()==k);
    return found;
}

std::vector<std::string>
Trie::keys(std::string const& pref) const
{
    std::vector<std::string> keys;
    NodeRef node = find_node(pref);
    if (node != nullptr)
        preorder_traversal(node, keys);
    return keys;
}


void
Trie::insert(std::string const& k)
{
    //TODO
    {
        TrieNode z;
        root_ = std::make_shared <TrieNode> (z);
    }

    NodeRef nod = root_;

    for(unsigned a = 0 ; a < k.length() ; a++)
    {
        if(nod->has(k[a]))
        {
            nod = nod->child(k[a]);
        }
        else
        {
            TrieNode z;
            NodeRef newNodo = std::make_shared <TrieNode> (z);
            nod->insert(k[a], newNodo);
            nod = newNodo;
        }
    }

    nod->set_value(k);
    
    assert(find(k));
}

Trie::NodeRef
Trie::find_node(std::string const& pref) const
{
    //TODO
    NodeRef nod = root_;
    for(unsigned i = 0; i < pref.length(); i++)
    {
        if(nod->has(pref[i]))
           nod = nod->child(pref[i]);
        else
            return nullptr;
    }

    return nod;
}

void
Trie::preorder_traversal(NodeRef const& node, std::vector<std::string> & keys) const
{
    //TODO

    if(node->value() != "")
        keys.push_back(node->value());

    for(std::map<char, std::shared_ptr<TrieNode>>::const_iterator i = node->children().begin(); i != node->children().end(); i++)
    {
        preorder_traversal(i->second, keys);
    }

}
