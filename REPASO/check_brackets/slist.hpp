#ifndef __ED_SList_HPP__
#define __ED_SList_HPP__

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

/** @brief a single link node.*/
template <class T>
class SNode
{
public:

    /** @brief Define a shared reference to a SNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< SNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a node.
     * @post !has_next()
     */
    SNode (T const& it)
    {
        //TODO
        nodeData = T;
        nodeCurr_ = nullptr;
        assert(!has_next());
    }

    /** @brief Create an empty Stack.*/
    SNode (T const& it, SNode<T>::Ref& next)
    {
        //TODO
        nodeData = it;
        nodeCurr_ = next;
    }

    /**
     * @brief Create a SNode using dynamic memory.
     * @param it the value save in the node.
     * @param next link to the next node.
     * @return a shared referente to the new node.
     */
    static typename SNode<T>::Ref create(T const& it, SNode<T>::Ref next=nullptr)
    {
        return std::make_shared<SNode<T>> (it, next);
    }

    /** @brief Destroy a SNode.**/
    ~SNode()
    {
        //TODO: think if it is needed.
    }
    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        //TODO
        return nodeData;
    }

    /**
     * @brief Has it a next node?.
     * @return true if it has a next node.
    */
    bool has_next() const
    {
        //TODO
        if (nodeCurr_ != nullptr) return true;
        return false;
    }

    /** @brief Get the link to next element.*/
    SNode<T>::Ref next() const
    {
        //TODO
        return nodeCurr_;
    }

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        //TODO
        nodeData = new_it;
    }

    /** @brief Set the link to the next node.*/
    void set_next(SNode<T>::Ref next)
    {
        //TODO
        nodeCurr_ = next;
    }

protected:

    //TODO
    T nodeData;
    SNode<T>::Ref nodeCurr_;
};

/**
 * @brief ADT SList.
 * Models a Single linked list[T].
 */
template<class T>
class SList
{
  public:

    /** @brief Define a shared reference to a SNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< SList<T> > Ref;

  /** @name Life cicle.*/
  /** @{*/

  /** @brief Create an empty Stack.
   * @post is_empty()
   */
  SList ()
  {
      //TODO
      head_ = nullptr;
      curr_ = head_;
      assert(is_empty());
  }

  /** @brief Destroy a Stack.**/
  ~SList()
  {}

  /**
   * @brief Create a SList using dynamic memory.
   * @return a shared referente to the new slist.
   */
  static typename SList<T>::Ref create()
  {
      return std::make_shared<SList<T>> ();
  }

  /**
   * @brief Create a SList unfoldig from an input stream.
   *
   * The input format will be "[]" for the empty list
   * or "[" item1 item2 ... item_n "]" where item1 is the head.
   *
   * @param in is the input stream.
   * @warning if the input format is not correct a std::runtime_error with
   * what message "Wrong input format." will be reaised.
   * @return A shared referente to the new slist.
   */
  static typename SList<T>::Ref create(std::istream& in) noexcept(false)
  {      
      auto list = SList<T>::create();

        //TODO
        //Hint: use std::istringstream to convert a token into generic T type.
        std::string token;
        std::getline(in,token,'\n');

        std::string aux = token.substr(token.find(' ') + 1);

        if (aux[0] != "[" or aux[aux.size() - 1] != "]")
        {
            throw std::runtime_error("Wrong input format.")
        }

        if (aux == "[]")
        {
            return list;
        }
        
        aux = aux.substr(2,aux.size() - 4);

        int espacios = 0;

        for (auto aux2 : aux) if (aux2 == ' ') espacios++;
        espacios++;

        std::istringstream translater(aux);

        for (int i = 0; i < espacios; i++)
        {
            int cant;
            translater>>cant;
            list->insert(cant);
            if (i != 0) list->goto_next();
        }
        
        
        
        

      return list;
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      if (head_ == nullptr) return true;
      return false;
  }

  /**
   * @brief Get the head's item of the list.
   * @return the item at the head.
   */
  const T& front() const
  {
      assert(!is_empty());
      //TODO
      return head_->item();
  }

  /** @brief get the current item.
   * @pre not is_empty()
   */
  const T& current() const
  {
      assert(! is_empty());
      //TODO
      return curr_->item();
  }

  /**
   * @brief Is there a next item?
   * @return true if there is.
   * @pre !is_empty()
   */
  bool has_next() const
  {
      assert(!is_empty());
      //TODO
      if (curr_->next() != nullptr)  return true;
      return false;
  }

  /**
   * @brief Get the next item.
   * @return the next item data.
   * @pre has_next()
   */
  T const& next() const
  {
      assert(has_next());
      //TODO
      return curr_->next()->item();
  }


  /**
   * @brief Has it the item data?
   * @param[in] it is the item to find.
   * @return true if the item is into the list.
   */
  bool has(T const& it) const
  {
      //TODO
      auto aux_ = head_;
      while (aux_ != nullptr)
      {
          if (aux_->item() == it) return true;
          aux_ = aux_->next();
      }
      return false;
  }

  /**
   * @brief Fold to an output stream.
   *
   * The format will be "[]" for the empty list or  '[' item1 item2 item3 ... item_n ']'
   * where item1 is the head.
   *
   * @param out is the output stream.
   * @return the output stream.
   */

  void fold(std::ostream& out) const
  {
      //TODO
      auto aux_ = head_;
      if (is_empty())
      {
          out<<"[]";
      }
      else
      {
          out<<"[";
          while (aux_ != nullptr)
          {
              out<<" "<<aux_->item();
              aux_ = aux_->next();
          }
          out<<" ]";
          
      }
      
      
  }

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief Set a new value for current.
   * @param new_v is the new value.
   * @pre !is_empty()
   * @post item()==new_v
   */
  void set_current(T const& new_v)
  {
      assert(!is_empty());
      //TODO
      curr_->set_item(new_v);

      assert(current()==new_v);
  }


  /**
   * @brief insert an item as the new list's head.
   * @param new_it is the item to insert.
   * @post head()==new_it
   */
  void push_front(T const& new_it)
  {
        //TODO
        if (is_empty())
        {
            head_ = SNode<T>::create(new_it,head_);
            curr_ = head_;
        }
        else
        {
            auto newHead_ = SNode<T>::create(new_it,head_);
            head_ = newHead_;
            curr_ = head_;
        }
        

      assert(front()==new_it);
  }


  /**
   * @brief insert a new item before current.
   * @param new_it is the item to insert.
   * @post old.is_empty() implies item()==head()==new_it
   * @post !old.is_empty() implies item()==old.item() && has_next() && next()==new_it
   */
  void insert(T const& new_it)
  {
#ifndef NDEBUG
      auto old_is_empty = is_empty();
      T old_item;
      if (!old_is_empty)
          old_item = current ();
#endif

        //TODO
        if (is_empty())
        {
            push_front(new_it);
        }
        else
        {
            auto newNode = SNode<T>::create(new_it, curr_->next());
            curr_->set_next(newNode);
        }
        
      assert(!old_is_empty || (front()==new_it && current()==new_it));
      assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
  }

  /**
   * @brief Remove the head.
   * @prec !is_empty()
   * @post is_empty() || head() == "next of old.head()".
   */
  void pop_front()
  {
      assert(!is_empty());
      //TODO
      if (head_->has_next())
      {
          head_ = head_->next();
          curr_ = head_;
      }
      else
      {
          head_ = nullptr;
          curr_ = head_;
      }      
  }


  /**
   * @brief Remove current item.
   * @pre !is_empty()
   * @post old.has_next() implies current()==old.next()
   * @post !old.has_next() implies is_empty() || current()=="old previous item."
   */
  void remove()
  {
      assert(!is_empty());
#ifndef NDEBUG
      bool old_has_next = has_next();
      T old_next;
      if (has_next())
          old_next=next();
#endif

      //TODO:
      //Study three cases: remove from head, remove from last and
      //remove from middle.

      if (curr_ == head_)
      {
          pop_front();
      }
      else if (curr_->next() == nullptr)
      {
          auto aux_ = head_;
          while (aux_->next() != curr_)
          {
               aux_ = aux_->next();
          }
          aux_->set_next(nullptr);
          curr_ = aux_;
          
      }
      else
      {
        auto aux_ = head_;
        while (aux_->next() != curr_)
        {
            aux_ = aux_->next();
        }
        aux_ = set_next(curr_->next());
        curr_ = aux_;
          
          
      }
      

      assert(!old_has_next || current()==old_next);
  }

  /**
   * @brief Move the cursor to the next list's item.
   * @pre has_next()
   * @post old.next()==current()
   */
  void goto_next()
  {
      assert(has_next());      
#ifndef NDEBUG
      auto old_next = next();
#endif

      //TODO
        curr_ = curr_->next();
      assert(current()==old_next);
  }

  /**
   * @brief Move the cursor to the list's head.
   * @pre !is_empty()
   * @post current()==front()
   */
  void goto_first()
  {
      assert(!is_empty());
      //TODO
        curr_ = head_;
      assert(current()==front());
  }

  /**
   * @brief Move the cursor to the first occurrence of a value from the head of the list.
   * If the item is not found, the cursor will be at the end of the list.
   * @param it is the value to be found.
   * @return true if it is found.
   * @pre !is_empty()
   * @post !ret_val || item()==it
   * @post ret_value || !has_next()
   */
  bool find(T const& it)
  {
      assert(!is_empty());
      bool found = false;
      //TODO
        curr_->goto_first();

        while (curr_ != nullptr)
        {
            if (curr_->item() == it)
            {
                return true;
            }
            curr_ = curr_->next();
        }
        
    

      assert(!found || current()==it);
      assert(found || !has_next());
      return found;
  }

  /**
   * @brief Move the cursor to the next occurrence of a value from current.
   * If the item is not found, the cursor will be at the end of the list.
   * @param it is the value to be found.
   * @return true if it is found.
   * @pre has_next()
   * @post !ret_val || item()==it
   * @post ret_value || !has_next()
   */
  bool find_next(T const& it)
  {
      assert(has_next());
      bool found = false;
      //TODO
        curr_ = curr_->next();

        while (curr_ != nullptr)
        {
            if (curr_->item == it)
            {
                found = true;
                return found;
            }
            curr_ = curr_->next();
            
        }
        
      assert(!found || current()==it);
      assert(found || !has_next());
      return found;
  }

  /** @}*/


protected:

  //TODO
  typename SNode<T>::Ref head_;
  typename SNode<T>::Ref curr_;

};

#endif //ED_SList

