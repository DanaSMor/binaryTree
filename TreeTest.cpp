/**
 * Examples of automatic tests for the exercise on binary trees.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
using std::cout, std::endl;
#include "badkan.hpp"
#include "Tree.hpp"

int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree;  
  ariel::Tree testtree;
  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);
  testtree.insert(9).insert(15).insert(5).insert(72).insert(13).insert(8).insert(2);
  

  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK    (emptytree.remove(5))
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)
  
  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_OK    (threetree.print())
  
  .CHECK_EQUAL (testtree.size(), 7)
  .CHECK_THROWS(testtree.insert(5))
  .CHECK_EQUAL (testtree.size(), 7)
  .CHECK_EQUAL (testtree.contains(5), true)
  .CHECK_OK    (testtree.remove(13))
  .CHECK_THROWS(testtree.remove(13))
  .CHECK_OK    (testtree.remove(5))
  .CHECK_OK    (testtree.remove(2))
  .CHECK_EQUAL (testtree.size() ,4)
.print();
  
  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}