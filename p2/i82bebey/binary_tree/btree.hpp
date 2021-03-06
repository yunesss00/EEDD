#ifndef __ED_BTree_HPP__
#define __ED_BTree_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>


/** @brief a BTree's Node.*/
template <class T>
class BTNode
{
public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a BTNode.
     * @post n_children() == 0
     */
    BTNode (T const& it=T(), BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        //TODO
        data = it;
        leftptrNode = left;
        rightptrNode = right;
    }

    /**
     * @brief Create a BTNode using dynamic memory.
     * @param it the value save in the node.
     * @param left links to the left child.
     * @param right links to the right child.
     * @return a shared referente to the new node.
     */
    static typename BTNode<T>::Ref create(T const& it, BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        return std::make_shared<BTNode<T>> (it, left, right);
    }

    /*std::ostream& fold(std::ostream& out, BTNode<T>::Ref next) const{

    	if (next == nullptr)
    	{
    		out<<"[]";

    	}else{

    		out<<"[ ";
    		out<<next->data;
    		out<<' ';


    		fold(out, next->leftptrNode);
    		out<<' ';
    		fold(out, next->rightptrNode);
    		out<<" ]";

    	}

    	return out;
    }*/
    

    /** @brief Destroy a BTNode. **/
    ~BTNode()
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        //TODO
        return data;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        //TODO
        if (leftptrNode != nullptr) return true;
        return false;
    }

    /** @brief get the left child.*/
    BTNode<T>::Ref left() const
    {
        //TODO
        return leftptrNode;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        //TODO
        if (rightptrNode != nullptr) return true;
        return false;
    }

    /** @brief get the right child.*/
    BTNode<T>::Ref right() const
    {
        //TODO
        return rightptrNode;
    }
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        //TODO
        data = new_it;
    }

    /** @brief Set the left child.*/
    void set_left(BTNode<T>::Ref new_child)
    {
        //TODO
        leftptrNode = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        //TODO: hint see std::share_ptr doc.
        leftptrNode = nullptr;
    }

    /** @brief Set the right child.*/
    void set_right(BTNode<T>::Ref new_child)
    {
        //TODO
        rightptrNode = new_child;
    }

    /** @brief Remove linkt to the right child. */
    void remove_right()
    {
        //TODO: hint see std::share_ptr doc.
        rightptrNode = nullptr;
    }

protected:
    //TODO
    //Hint: use typename SNode<T>::Ref for the link to other nodes.
    typename BTNode<T>::Ref leftptrNode;
    typename BTNode<T>::Ref rightptrNode;
    T data;
};

/**
 * @brief ADT BTree.
 * Models a BTree of T.
 */
template<class T>
class BTree
{
  public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTree<T> > Ref;

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an empty BTree.
     * @post is_empty()
     */
    BTree ()
    {
        //TODO
        rootptr = nullptr;
        assert(is_empty());

    }

  /** @brief Create Leaf BTree.
   * @post not is_empty()
   */
  BTree (const T& item)
  {
      //TODO
      rootptr = BTNode<T>::create(item);

  }

  /**
   * @brief Create an empty BTree.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create()
  {
      return std::make_shared<BTree<T>> ();
  }

  /**
   * @brief Create a leaf BTree.
   * @param item is the root's item.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create(T const& item)
  {
      return std::make_shared<BTree<T>>(item);
  }

  /**
   * @brief Load a tree from a input stream.
   *
   * The input format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @return a reference to the tree created.
   * @warning runtime_error will throw if worng input format was found.
   */
  static typename BTree<T>::Ref create (std::istream& in) noexcept(false)
  {
      auto tree = BTree<T>::create();
      std::string token;
      //in >> token;
      if (!in)
          throw std::runtime_error("Wrong input format.");

      //TODO     
      char trash; 
      in>>token;
      if (token == "[]") return tree;

      if (!in) throw std::runtime_error("Wrong input format.");
      
      in>>token;
      std::istringstream translater(token);

      T item;
      translater>>item;
      tree->create_root(item);

      if (!in) throw std::runtime_error("Wrong input format.");  

      //in>>token;

        auto leftTree = BTree<T>::create(in);
        tree->set_left(leftTree);    

      //in>>token;
      
        auto rightTree = BTree<T>::create(in);
        tree->set_right(rightTree);
      
      
       in>>trash; 

      return tree;
  }

  /** @brief Destroy a BTree.**/
  ~BTree()
  {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      if (rootptr == nullptr) return true;
      return false;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& item() const
  {
      assert(!is_empty());
      //TODO
      return rootptr->item();
  }

  /**
   * @brief Get the left subtree.
   * @return a reference to the left subtFree.
   * @pre !is_empty()
   */
  typename BTree<T>::Ref left() const
  {
      assert(!is_empty());
      auto l_subtree = BTree<T>::create();

      //TODO
      l_subtree->rootptr = rootptr->left();
      //

      return l_subtree;
  }

  /**
   * @brief Get the right subtree.
   * @return a reference to the right subtree.
   * @pre !is_empty()   
   */
  typename BTree<T>::Ref right() const
  {
      assert(!is_empty());
      auto r_subtree = BTree<T>::create();

      //TODO
      r_subtree->rootptr = rootptr->right();
      //

      return r_subtree;
  }

  /**
   * @brief Fold a binary tree.
   *
   * The output format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param out is the output stream.
   * @param tree is the tree.
   * @return the output stream.
   * @pre tree!=nullptr
   */
  std::ostream& fold(std::ostream& out) const
  {
      //TODO
      

      if (is_empty() == true )
      {
          out<<"[]";
      }
      else
      {
          out<<"[ ";
          out<<rootptr->item();
          out<<" ";

          auto auxLeftTree =BTree<T>::left();
          auto auxRightTree =BTree<T>::right();

          auxLeftTree->fold(out);
          out<<" ";
          auxRightTree->fold(out);
          out<<" ]";
      }
      //rootptr->fold(out, rootptr);

      //
      return out;
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief set the root's item.
   * @pre not is_empty()
   */
  void set_item(const T& new_it)
  {
      assert(!is_empty());
      //TODO
      rootptr->set_item(new_it);
  }

  /**
   * @brief Create the root node.
   * item is the new root item.
   * @post !is_empty()
   */
  void create_root(T const& item)
  {
      //TODO
      //rootptr = nullptr;
      //rootptr->set_item(item);
      rootptr = BTNode<T>::create(item);
      assert(!is_empty());
  }

  /**
   * @brief Remove the link to the root node.
   * @post is_empty()
   */
  void remove_root()
  {
      //TODO
      rootptr = nullptr;
      assert(is_empty());
  }

  /**
   * @brief Attach a new subtree as left child of root.
   * @param new_left is the new left subtree.
   * @pre !is_empty()
   */
  void set_left(typename BTree<T>::Ref new_left)
  {
      assert(!is_empty());
      //TODO
      rootptr->set_left(new_left->rootptr);
  }

  /**
   * @brief Detach the left child of root.
   * @pre !is_empty()
   */
  void remove_left()
  {
      assert(!is_empty());
      //TODO
      rootptr->remove_left();
  }

  /**
   * @brief Attach a new subtree as right child of root.
   * @param t is the new right subtree.
   */
  void set_right(typename BTree<T>::Ref t)
  {
      assert(!is_empty());
      //TODO
      rootptr->set_right(t->rootptr);
  }

  /**
   * @brief Detach the right child of root.
   * @pre !is_empty()
   */
  void remove_right()
  {
      assert(!is_empty());
      //TODO
      rootptr->remove_right();
  }

  /** @}*/

protected:

  //TODO
  typename BTNode<T>::Ref rootptr;

};
#endif
