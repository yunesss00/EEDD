#ifndef __ED_Stack_HPP__
#define __ED_Stack_HPP__

#include <cassert>
#include <iostream>
#include "slist.hpp"

/**
 * @brief ADT Stack.
 * Models a Stack using a single linked list*
 */
template<class T>
class Stack
{
  public:
    /** @brief Define a shared reference to a Stack.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< Stack<T> > Ref;

  /** @name Life cicle.*/
  /** @{*/

  /** @brief Create an empty Stack.
   * @post is_empty()
   */
  Stack ()
  {
      //TODO
      assert(is_empty());
  }

  /**
   * @brief Create a Stack using dynamic memory.
   * @return a shared referente to the new stack.
   */
  static typename Stack<T>::Ref create()
  {
      return std::make_shared<Stack<T>>();
  }

  /**
   * @brief Create a Stack from an input stream.
   * The input format is the same of a single list.
   * @return a shared referente to the new stack.
   * @warning throw std::runtime_error if wrong input format.
   */
  static typename Stack<T>::Ref create(std::istream & in) noexcept(false)
  {
      auto stack = Stack<T>::create();

      //TODO
      //Hint: delegate in the SList type.

      return stack;
  }

  /** @brief Destroy a Stack.**/
  ~Stack()
  {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      return false;
  }

  /** @brief get the top item.
   * @pre not is_empty()
   */
  const T& top() const
  {
      assert(! is_empty());
      //TODO
      return T();
  }

  /**
   * @brief Fold the stack to an output stream.
   * The output format is like the slist.
   * @param out is the output stream.
   */
  void fold(std::ostream& out) const
  {
      //TODO
      //Hint: delegate in the SList type.
  }

  /**

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post top() == new_it
   */
  void push(const T& new_it)
  {
      //TODO

      assert(top()==new_it);
  }

  /** Remove the top item.
   * @pre not is_empty()
   */
  void pop()
  {
      assert(! is_empty());
      //TODO

  }

  /** @} */

protected:

  //TODO:
  //Hint:  delegate in SList<T> to implement the TAD Stack.

};

#endif //__ED_Stack_HPP__
