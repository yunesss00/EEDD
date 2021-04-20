#pragma once

#include "avltree.hpp"
#include <bits/stdc++.h>


#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert ("Assert violation!", __FILE__, __LINE__),0));
#endif
}

/****
 * AVLTNode class implementation.
 ****/


template <class T>
AVLTNode<T>::AVLTNode (T const& it, AVLTNode<T>::Ref parent,
                       AVLTNode<T>::Ref left, AVLTNode<T>::Ref right):
    item_(it), parent_(parent), left_(left), right_(right), height_(0)
{
    //TODO
    compute_height();
    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const& it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared< AVLTNode<T> > (it, parent, left, right);
}

template <class T>
const T& AVLTNode<T>::item() const
{
    //TODO
    return item_;
}

template <class T>
int AVLTNode<T>::height() const
{
    //TODO
    return height_;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //TODO
    bf = left_.heigth() - right_.height();
    //
    return bf;
}

template <class T>
bool AVLTNode<T>::has_parent() const
{
    //TODO
    if (parent_ != nullptr) return true;
    return false;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    //TODO
    return parent_;
}

template <class T>
bool AVLTNode<T>::has_left() const
{
    //TODO
    if (left_ != nullptr) return true;
    return false;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    //TODO
    return left_;
}

template <class T>
bool AVLTNode<T>::has_right() const
{
    //TODO
    if (right_ != nullptr) return true;
    return false;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    //TODO
    return right_;
}

template <class T>
bool AVLTNode<T>::check_height_invariant () const
{
    bool ret_val = false;
    //TODO
    

    int left = -1, right = -1, max;

    if (has_left()) left = left_->height();

    if (has_right()) right = right_->height();

    if (right > left)
    {
        max = right + 1;
    }
    else
    {
        max = left + 1;
    }

    if (height_ == max)
    {
        ret_val = true;
    }

    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T& new_it)
{
    //TODO
    item_ = new_it;
    compute_height();

    //
    assert(item()==new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref const& new_parent)
{
    //TODO
    parent_ = new_parent;
    compute_height();

    //
    assert(parent()==new_parent);
}

template <class T>
void AVLTNode<T>::remove_parent()
{
    //TODO
    parent_ = nullptr;
    compute_height();
    //
    assert(!has_parent());
}

template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref const& new_child)
{
    //TODO
    left_ = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(left()==new_child);
}

template <class T>
void AVLTNode<T>::remove_left()
{
    //TODO
    left_ = nullptr;
    compute_height();    
    //
    assert(check_height_invariant());
    assert(!has_left());
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref const& new_child)
{
    //TODO
    right_ = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(right()==new_child);
}

template <class T>
void AVLTNode<T>::remove_right()
{
    //TODO
    right_ = nullptr;
    compute_height();
    //
    assert(check_height_invariant());
    assert(!has_right());
}

template <class T>
void AVLTNode<T>::compute_height()
{
    //TODO
    T max = INT_MIN;
    if (!has_left() && !has_right())
    {
        max = -1;
    }
    
    if (has_left())
    {
        
        max = left_->height();

    }
    if (has_right() && right_.get()->height() > max)
    {

        max = right_->height();

    }
      
    height_ =  1 + max;
    //
    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree ()
{
    //TODO
    root_ = nullptr;
    curr_ = nullptr;
    prev_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
AVLTree<T>::AVLTree (T const& item)
{
    //TODO
    root_ = AVLTNode<T>::create(item);
    assert(!is_empty());
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create ()
{
    return std::make_shared< AVLTree<T> >();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create (T const& item)
{
    return std::make_shared<AVLTree<T>> (item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream& in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    in >> token;
    if (!in)
        throw std::runtime_error("Wrong input format");

    //TODO
    if (token != "[]")
    {
        throw std::runtime_error("Wrong input format");
    }
    else if (token == "[")
    {
        T item;

        in >> item;
        tree = AVLTree<T>::create(item);
        auto left_tree = AVLTree<T>::create(in);
        auto right_tree = AVLTree<T>::create(in);
        tree->set_left(left_tree);
        tree->set_right(right_tree);
        in >> token;
    }
    

    

    //

    if (! tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (! tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");
    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create a BSTree by inserting the median of an ordered sequence.
 * @param data is an ordered sequence of keys.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of data to use.
 * @pre data values are in order.
 * @pre 0 <= begin <= end <=data.size()
 */
template<class T>
void create_inserting_median(std::vector<T> const& data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref& tree)
{
    assert(begin<=end);
    assert(end<=data.size());

    //TODO
    //Hint: use a recursive design by inserting the median of input
    // (begin, end] interval
    //and recursively, apply to each sub-interval [begin, median),
    //[median+1, end).

    if ((end - begin) > 0)
    {
        tree->insert(data[begin + ((end - begin) / 2)]);
        create_inserting_median(data, begin, begin + ((end - begin) / 2), tree);
        create_inserting_median(data, begin + ((end - begin) / 2) + 1, end, tree);
    }

}

template<class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::vector<T> & data)
{
    assert(data.size()>0);
    auto tree = AVLTree<T>::create();
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);
    return tree;
}
#endif //#ifdef __ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty () const
{
    //TODO
    if (root_ != nullptr) return true;
    return false;
}

template <class T>
T const& AVLTree<T>::item() const
{
    return root_->item();
}

template <class T>
std::ostream& AVLTree<T>::fold(std::ostream& out) const
{
    //TODO
    if (is_empty())
    {
        out << "[]";
    }
    else
    {
        out << "[ ";
        out << item() << " ";
        left()->fold(out);
        out << " ";
        right() ->fold(out);
        out << " ]";
    }
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    //TODO
    auto auxptr = root_;

    while (true)
    {
        if (curr_ == nullptr) return false;

        if (curr_->item() > auxptr->item())
        {
            if (auxptr->has_right())
            {
                auxptr = auxptr->right();
            }
            else return false;
            
        }
        else if (curr_->item() < auxptr->item())
        {
            if (auxptr->has_left())
            {
                auxptr = auxptr->left();
            }
            else return false;
        }
        else return false;
        
        
    }
    
    return false;
}

template <class T>
T const& AVLTree<T>::current() const
{
    assert(current_exists());
    //TODO    
    return curr_->item();
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO
    auto auxptr = root_;
    
    while (auxptr != curr_)
    {
        if (auxptr->item() > curr_->item())
        {
            auxptr = auxptr->left();
        }
        else  if (auxptr->item() < curr_->item())
        {
            auxptr = auxptr->item();
        }
        
        level++;
    }
    
    //
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    //TODO
    auto left_tree = AVLTree<T>::create();
    
    if (root_->has_left())
    {
        left_tree->create_root(root_->left()->item());
        left_tree->root_->set_left(root_->left()->left());
        left_tree->root_->set_right(root_->left()->right());
        left_tree->root_->set_parent(nullptr);
    }
    
    return left_tree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    //TODO
    auto right_tree = AVLTree<T>::create();
    
    if(root_->has_right())
    {
        right_tree->create_root(root_->right()->item());
        right_tree->root_->set_left(root_->right()->left());
        right_tree->root_->set_right(root_->right()->right());
        right_tree->root_->set_parent(nullptr);
    }
    return right_tree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    //TODO
    if (!is_empty())
        s = 1 + left()->size() + right()->size();
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = -1;
    //TODO
    if(!is_empty())
        h = root_->height();
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO
    if(!is_empty())
        bf = root_->balance_factor();
    //
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T& k) const
{
#ifndef NDEBUG
  bool old_current_exists = current_exists();
  T old_current;
  if (old_current_exists)
      old_current = current();
#endif

  bool found = true;

  //TODO
  auto auxptr = root_;

  while (true)
  {
      if (k < auxptr->item())
      {
          if (auxptr->has_left())
          {
              auxptr = auxptr->left();
          }
          else 
          {
              found = false;
              break;
          }
      }
      else if (k > auxptr->item())
      {
          if (auxptr->has_right())
          {
              auxptr = auxptr->right();
          }
          else
          {
              found = false;
              break;
          }
          
      }
      else break;
      
    
  }
  

  //
#ifndef NDEBUG
  assert (!old_current_exists || old_current == current());
#endif
  return found;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //TODO
    
    if (!is_empty())
    {
        if (root_->has_left())
        {
            is_bst = is_bst && (item() > left()->item());
        }

        if (root_->has_right())
        {
            is_bst = is_bst && (item() < right()->item());
        }

        is_bst = is_bst && left()->is_a_binary_search_tree() && right()->is_a_binary_search_tree();
        
    }
    
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    //TODO
    
    if (!is_empty())
    {
        is_balanced = ( std::abs(balance_factor()) <= 1 && left()->is_a_balanced_tree() && right()->is_a_balanced_tree() );
    }
    
    //
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const& item)
{
    assert(is_empty());
    //TODO
    root_ = AVLTNode<T>::create(item, nullptr, nullptr, nullptr);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item()==item);

}

template <class T>
bool AVLTree<T>::search(T const& k)
{
    bool found = false;
    //TODO
    curr_ = root_;
    prev_ = nullptr;

    while (curr_ != nullptr && !found)
    {
        if (curr_->item() == k) found = true;
        else
        {
            prev_ = curr_;
            if (curr_->item() > k)
            {
                curr_ = curr_->left();
            }
            else
            {
                curr_ = curr_->right();
            }
            
        }
    }

    
    //
    assert(!found || current()==k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const& k)
{
    if (!search(k))
    {
        //TODO
       
        if (is_empty())
        {
            curr_ = AVLTNode<T>::create(k, nullptr, nullptr, nullptr);
            root_ = curr_;
        }
        else
        {
            curr_ = AVLTNode<T>::create(k, prev_, nullptr, nullptr);

            if(prev_->item() > k) prev_->set_left(curr_);
            else prev_->set_right(curr_);
        }

        //
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
#endif
    }

    //check postconditions.
    assert(current_exists());
    assert(current()==k);
}

template <class T>
void AVLTree<T>::remove ()
{
    //check preconditions.
    assert(current_exists());

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO
    // Check which of cases 0,1,2,3 we have.

    if (!curr_->has_left() && !curr_->has_right()) subtree = nullptr;
   
    else if (!curr_->has_right()) subtree = curr_->left();
   
    else if (!curr_->has_left()) subtree = curr_->right();
    
    else replace_with_subtree = false;

    //

    if (replace_with_subtree)
    {
        //TODO
        //Manage cases 0,1,2

        if (prev_ == nullptr) root_ = subtree;
       
        else if (prev_->right() == curr_) prev_->set_right(subtree);

        else prev_->set_left(subtree);

        curr_ = nullptr;

        //
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
        assert(! current_exists());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
        assert(! current_exists());
#endif
    }
    else
    {
        //TODO
        //Manage case 3.

        auto aux = curr_;
        find_inorder_sucessor();
        aux->set_item(curr_->item());
        remove();
        //
    }
}

template <class T>
AVLTree<T>::AVLTree (typename AVLTNode<T>::Ref root_node)
{
    //TODO
}

template <class T>
typename AVLTree<T>::Ref  AVLTree<T>::create (typename AVLTNode<T>::Ref root)
{
     AVLTree<T>::Ref ret_v (new AVLTree<T>(root));
     return ret_v;
}

template <class T>
typename AVLTNode<T>::Ref const&  AVLTree<T>::root() const
{
    //TODO
    return root_;
}

template <class T>
void AVLTree<T>::set_left(typename AVLTree<T>::Ref& subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.

    if(!subtree->is_empty())
    {
        auto new_node = AVLTNode<T>::create(subtree->root_->item(),root_,subtree->root_->left(),subtree->root_->right());
        new_node->compute_height();
        root_->set_left(new_node);
    }
    else root_->set_left(nullptr);

    //
    assert(subtree->is_empty() || left()->item()==subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(typename AVLTree<T>::Ref& subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.

    if(!subtree->is_empty())
    {
        auto new_node = AVLTNode<T>::create(subtree->root_->item(),root_,subtree->root_->left(),subtree->root_->right());
        new_node->compute_height();
        root_->set_right(new_node);
    }
    else root_->set_right(nullptr);

    //
    assert(subtree->is_empty()|| right()->item()==subtree->item());
    assert(!subtree->is_empty()|| right()->is_empty());
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
#ifndef NDEBUG
    T old_curr = current();
#endif
    //TODO
    
    prev_ = curr_;
    curr_ = curr_->right();

    while (curr_->has_left())
    {
        prev_ = curr_;
        curr_ = curr_->left();
    }
    

    //
    assert(current_exists());
#ifndef NDEBUG
    assert(current()>old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    //TODO
    //Remenber when set a node A as child of a node B, also is needed set
    // node B as parent of node A.

    auto left_node = node->left();

    if(not node->has_parent())
    {
        root_ = left_node;
    }
    else if(node->parent()->right() == node)
    {
        node->parent()->set_right(left_node);
    }
    else
    {
        node->parent()->set_left(left_node);
    }

    left_node->set_parent(node->parent());

    if( left_node->has_right())
    {
        node->set_left(left_node->right());
        left_node->right()->set_parent(node);
    }
    else
    {
        node->remove_left();
    }

    left_node->set_right(node);
    node->set_parent(left_node);

    node->compute_height();
    left_node->compute_height();

    //
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    //TODO
    //Remenber when set a node A as child of a node B, also is needed set
    // node B as parent of node A.

    auto right_node = node->right();

    if(not node->has_parent() )
    {
        root_ = right_node;
    }
    else if(node->parent()->right() == node)
    {
        node->parent()->set_right(right_node);
    }
    else
    {
        node->parent()->set_left(right_node);
    }

    right_node->set_parent(node->parent());

    if(right_node->has_left())
    {
        node->set_right(right_node->left());
        right_node->left()->set_parent(node);
    }
    else
    {
        node->remove_right();
    }

    right_node->set_left(node);
    node->set_parent(right_node);

    node->compute_height();
    right_node->compute_height();

    //
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    //TODO
    //From current position, go up until root's node is achieved.
    //In each step, check if the current subtree is balanced and balance it
    // if not.


    //

   // if (current_exists())
    //{
        //TODO
        // Remember that due to the rotations, the state of attributes curr and prev
        // may be inconsistent, so we need to force that "previous of current" is the
        // parent of "current" when current_exists().

        while (prev_)
        {
            prev_->compute_height();
            int bf = prev_->balance_factor();

            if (bf < -1)
            {
                auto child = prev_->left();
                int bf_child = child->balance_factor();

                if (bf_child <= 0)
                {
                    rotate_left(prev_);
                }
                else
                {
                    rotate_right(child);
                    rotate_left(prev_);
                }   
            }
            else if (bf > 1)
            {
                auto child = prev_->right();
                int bf_child = child->balance_factor();

                if (bf_child >= 0)
                {
                    rotate_right(prev_);
                }
                else
                {
                    rotate_left(child);
                    rotate_right(prev_);
                }
            }
            else
            {
                prev_ = prev_->parent();
            }
        }

        //
    //}

#endif //__ONLY_BSTREE__
}
