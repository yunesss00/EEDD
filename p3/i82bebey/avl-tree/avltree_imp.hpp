#pragma once

#include "avltree.hpp"

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
    int bf = 0 , bf_l = 0, bf_r = 0;
    //TODO
    if(has_left()) bf_l = left_->height()+1;
    
    if(has_right()) bf_r = right_->height()+1;
    bf = bf_r - bf_l;
    //
    return bf;
}

template <class T>
bool AVLTNode<T>::has_parent() const
{
    //TODO
    if (parent_ == nullptr) return false;

    else return true;
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
    if(left_ == nullptr) return false;

    else return true;
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
    if(right_ == nullptr) return false;

    else return true;
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

    //
    return true;
}

template <class T>
void AVLTNode<T>::set_item(const T& new_it)
{
    //TODO
    item_ = new_it;
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
    if(right_ == nullptr && left_ == nullptr) height_ = 0;

    else{

        int max = 0;
        if(right_ != nullptr){
            if(right_->height() > max){
                max = right_->height();
            }
        }

        if(left_ != nullptr){
            if(left_->height() > max){
                max = left_->height();
            }
        }

        height_ = max + 1;

    }
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
    current_ = nullptr;
    parent_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
AVLTree<T>::AVLTree (T const& item)
{
    //TODO
    //
    root_->set_item(item);

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
    char aux;
      T item;
      
      if (token == "[]") { 
        return tree;
      }

        if (!in){ throw std::runtime_error("Wrong input format");}

        in>>token;
        std::istringstream translater(token);


        
        translater >> item;
        tree->create_root(item);

        if (!in){ throw std::runtime_error("Wrong input format"); }

        auto left_tree = AVLTree<T>::create(in);
        tree->set_left(left_tree);

        auto right_tree = AVLTree<T>::create(in);
        tree->set_right(right_tree);

        in>>aux;

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

    
    if(end-begin>0){
            tree->insert(data[begin+(end-begin)/2]);
            create_inserting_median(data, begin, begin + ((end-begin)/2), tree);
            create_inserting_median(data, begin + ((end-begin)/2)+1, end, tree);       
    }
    

    //TODO
    //Hint: use a recursive design by inserting the median of input
    // (begin, end] interval
    //and recursively, apply to each sub-interval [begin, median),
    //[median+1, end).
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
    if(root_ == nullptr) return true;
    else return false;
}

template <class T>
T const& AVLTree<T>::item() const
{
    assert(!is_empty());

    return root_->item();
}

template <class T>
std::ostream& AVLTree<T>::fold(std::ostream& out) const
{
    //TODO
    if(is_empty()){ out << "[]";}

      else{

          out<<"[ ";
          out<< item();
          out<<" ";
          auto l_tree = left();
          auto r_tree = right();

          l_tree->fold(out); 
          out<<" ";
          r_tree->fold(out);
          out<<" ]";
      }
    //
    
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    //TODO
    if(current_ != nullptr) return true;

    else return false;
}

template <class T>
T const& AVLTree<T>::current() const
{
    assert(current_exists());
    //TODO    
    return current_->item();
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO
    auto aux = root_;

    while(aux != current_){
        if(aux->item() > current_->item()) aux = aux->left();

        else if (aux->item() < current_->item()) aux = aux->right();

        level++;
    }
    
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    //TODO
    AVLTree<T>::Ref l_tree = AVLTree<T>::create();
    l_tree->root_ = root_->left();

    root_->compute_height();
    return l_tree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    //TODO
    AVLTree<T>::Ref r_tree = AVLTree<T>::create();
    r_tree->root_ = root_->right();
    root_->compute_height();

    return r_tree;
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
    if( is_empty() ) return h;
    else return root_->height();
    //
    
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO
    bf = right()->height() - left()->height();
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
  //TODO
  bool found = false;

    if(!is_empty()){
        if(k < item() ){
            found = left()->has(k);
        }

        else if( k > item() ){
            found = right()->has(k);
        }

        else{
            found = true;
        }
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
    bool is_bst = false;
    //TODO
    bool r = false;
    bool l = false;
    int t = 0;

    if( is_empty() ) return true;

    if( root_->has_left() ) l = true;
    if( root_->has_right() ) r = true;

    if( l==false && r==false ) return true;
    else{

        if(l==true){
            if(root_->item() > root_->left()->item()){
                left()->is_a_binary_search_tree();
                t++;
            }
            else{
                return false;
            }
        }

        if(r==true){
            if(root_->item() < root_->right()->item()){
                right()->is_a_binary_search_tree();
                t++;
            }
            else{
                return false;
            }
        }

        if(t==0) return false;
        else return true;
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
    if(is_empty()) return true;

    else{
        is_balanced = ( std::abs(balance_factor())<=1 && left()->is_a_balanced_tree() && right()->is_a_balanced_tree() );
    }

    return is_balanced;

    //

#endif
}

template <class T>
void AVLTree<T>::create_root(T const& item)
{
    assert(is_empty());
    //TODO
    root_ = AVLTNode<T>::create(item);
    root_ -> compute_height();
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    //assert(item()==item);

}

template <class T>
bool AVLTree<T>::search(T const& k)
{
    bool found = false;

   current_ = root_;
   parent_ = nullptr;

   while(current_ != nullptr && found == false){
       if(current_->item() == k){
           found = true;
           //current_->compute_height();
       }

       else{
           parent_ = current_;
           if(current_->item() > k){
               current_ = current_->left();
           }

           else{
               current_ = current_->right();
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
    if(!search(k)){
    if(is_empty()){
        current_ = AVLTNode<T>::create(k);
        root_ = current_;

    }

    else
    {
        //TODO
        current_ = AVLTNode<T>::create(k, parent_,nullptr,nullptr);
        if(parent_->item() > k){
            parent_->set_left(current_);
        }

        else{
            parent_->set_right(current_);
        }
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

    assert(current_exists());
    assert(current()==k);
}

template <class T>
void AVLTree<T>::remove ()
{
    //check preconditions.
    assert(current_exists());

    bool ReplaceWithSubTree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO
    // Check which of cases 0,1,2,3 we have.


    //
    if( (!current_->has_left() && (!current_->has_right())) ){
            subtree = nullptr;
        }

        else if(!current_->has_right()){
            subtree = current_->left();
        }

        else if(!current_->has_left()){
            subtree = current_->right();
        }

        else{
            ReplaceWithSubTree = false;
        }
   
    if (ReplaceWithSubTree)
    {
        //TODO
        //Manage cases 0,1,2
            if(parent_ == nullptr){
                root_ = subtree;
                current_ = nullptr;
            }

            else if(parent_->right() == current_){
                parent_->set_right(subtree);
                current_ = nullptr;
            }

            else{
                parent_ -> set_left(subtree);
                current_ = nullptr;
            }


        //
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
        assert(!current_exists());
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
            auto tmp = current_;
            find_inorder_sucessor();
            tmp->set_item(current_->item());
            remove();
        //
    }

    root_->compute_height();
}

template <class T>
AVLTree<T>::AVLTree (typename AVLTNode<T>::Ref root_node)
{
    //TODO
    root_ = root_node;

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
    root_->set_left(subtree->root_);
    root_->compute_height();

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
    root_->set_right(subtree->root_);
    root_->compute_height();


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

    if(!current_->has_right()){
        current_ = current_;
    }

    else{
        parent_ = current_;
        current_ = current_->right();

        while(current_->has_left()){
            parent_ = current_;
            current_ = current_->left();
         }

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
    auto lc = node->left();

    if(!node->has_parent()){
        root_ = lc;
    }

    else if(node->parent()->right() == node){
        node->parent()->set_right(lc);
    }

    else{
        node->parent()->set_left(lc);
        
    }

    lc->set_parent(node->parent());

    if(lc->has_right()){
        node->set_left(lc->right());
        lc->right()->set_parent(node);
    }

    else{
        node->remove_left();
        
    }

    lc->set_right(node);
    node->set_parent(lc);
    node->compute_height();
    lc->compute_height();
    //
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    //TODO
    //Remenber when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    auto rc = node->right();

    if(!node->has_parent()){
        root_ = rc;
    }

    else if(node->parent()->right() == node){
        node->parent()->set_right(rc);
    }

    else{
        node->parent()->set_left(rc);
        
    }

    rc->set_parent(node->parent());

    if(rc->has_left()){
        node->set_right(rc->left());
        rc->left()->set_parent(node);
    }

    else{
        node->remove_right();
        
    }

    rc->set_left(node);
    node->set_parent(rc);
    node->compute_height();
    rc->compute_height();
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
    int bfp;
    int bfc;

    typename AVLTNode<T>::Ref child;

    while(parent_ != nullptr){

        parent_->compute_height();
        bfp = parent_->balance_factor();

        if(bfp < -1){
            child = parent_->left();
            bfc = child->balance_factor();

            if(bfc <= 0){
                rotate_left(parent_);
            }

            else{
                rotate_right(child);
                rotate_left(parent_);
            }
        }

        else if(bfp > 1){
            child = parent_->right();
            bfc = child->balance_factor();

            if(bfc >= 0){
                rotate_right(parent_);
            }

            else{
                rotate_left(child);
                rotate_right(parent_);
            }
        }
        else{
            parent_ = parent_->parent();
        }

        
    }

    //
    

#endif //__ONLY_BSTREE__
}