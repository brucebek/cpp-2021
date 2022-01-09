#include "LinkedList.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list>

using ::testing::IsEmpty;
using ::testing::ElementsAre;
using ::testing::Eq;

TEST(LinkedList, Constructors) {
    // default
    LinkedList<int> lst;
    EXPECT_THAT(lst, IsEmpty());

    // count
    LinkedList<int> lst2(5);
    EXPECT_THAT(lst2, ElementsAre(0, 0, 0, 0, 0));

    // count with value
    LinkedList<int> lst3(LinkedList<int>::size_type(5), 5);
    EXPECT_THAT(lst3, ElementsAre(5, 5, 5, 5, 5));

    // initializer_list
    LinkedList<int> lst4{1, 2, 3, 4, 5};
    EXPECT_THAT(lst4, ElementsAre(1, 2, 3, 4, 5));

    // iterator
    LinkedList<int> lst5(lst4.begin(), lst4.end());
    EXPECT_THAT(lst5, ElementsAre(1, 2, 3, 4, 5));

    // copy
    LinkedList<int> lst6(lst4);
    EXPECT_THAT(lst6, ElementsAre(1, 2, 3, 4, 5));

    //move
    LinkedList<int> lst7(std::move(lst4));
    EXPECT_THAT(lst7, ElementsAre(1, 2, 3, 4, 5));
    EXPECT_THAT(lst4, IsEmpty());

    std::cout << "0: " << &lst << std::endl;
    std::cout << "2: " << &lst2 << std::endl;
    std::cout << "3: " << &lst3 << std::endl;
    std::cout << "4: " << &lst4 << std::endl;
    std::cout << "5: " << &lst5 << std::endl;
    std::cout << "6: " << &lst6 << std::endl;
    std::cout << "7: " << &lst7 << std::endl;


}

TEST(LinkedList, FuncsAssign) {
    const LinkedList<int> clst{1, 2, 3, 4, 5};
    LinkedList<int> lst{6, 7, 8, 9, 10};

    // copy
    lst = clst;
    EXPECT_THAT(lst, ElementsAre(1, 2, 3, 4, 5));

    // move
    lst = LinkedList<int>{6, 7, 8, 9, 10};
    EXPECT_THAT(lst, ElementsAre(6, 7, 8, 9, 10));

    // init_lst
    lst = {1, 2, 3, 4, 5};
    EXPECT_THAT(lst, ElementsAre(1, 2, 3, 4, 5));

    // assign count with value
    lst.assign(LinkedList<int>::size_type(5), 1);
    EXPECT_THAT(lst, ElementsAre(1, 1, 1, 1, 1));


    lst.assign(LinkedList<int>::size_type(3), 2);
    EXPECT_THAT(lst, ElementsAre(2, 2, 2));


    lst.assign(LinkedList<int>::size_type(7), 3);
    EXPECT_THAT(lst, ElementsAre(3, 3, 3, 3, 3, 3, 3));

    // assign init
    lst.assign({10, 20, 30});
    EXPECT_THAT(lst, ElementsAre(10, 20, 30));

    lst.assign({40, 50, 60});
    EXPECT_THAT(lst, ElementsAre(40, 50, 60));

    lst.assign({70, 80, 90, 100, 110});
    EXPECT_THAT(lst, ElementsAre(70, 80, 90, 100, 110));


    //assign iterators
    std::list authentic_lst = {1, 2, 3, 4};
    lst.assign(authentic_lst.rbegin(), authentic_lst.rend());
    EXPECT_THAT(lst, ElementsAre(4, 3, 2, 1));

    std::vector vec = {2, 7, 1, 8};
    lst.assign(vec.begin(), vec.end());
    EXPECT_THAT(lst, ElementsAre(2, 7, 1, 8));

    std::initializer_list<int> init = {6, 9, 6, 9, 6, 9};
    lst.assign(init.begin(), init.end());
    EXPECT_THAT(lst, ElementsAre(6, 9, 6, 9, 6, 9));

}

TEST(LinkedList, FuncsFrontBack) {
    const LinkedList<int> clst{1, 2, 3, 4, 5};
    LinkedList<int> lst{1, 2, 3, 4, 5};

    EXPECT_THAT(clst.front(), Eq(1));
    EXPECT_THAT(lst.front(), Eq(1));

    EXPECT_THAT(clst.back(), Eq(5));
    EXPECT_THAT(lst.back(), Eq(5));
}


TEST(LinkedList, FuncsIterators) {
    LinkedList<int> lst{1, 2, 3, 4, 5};
    int i = 1;
    for (const int &x: lst) {
        EXPECT_THAT(x, Eq(i));
        ++i;
    }
}


TEST(LinkedList, FuncsSize) {
    LinkedList<int> lst{1, 2, 3, 4, 5};
    EXPECT_THAT(lst.size(), Eq(5));
    EXPECT_THAT(lst.empty(), false);

}


TEST(LinkedList, FuncsInsertErase) {
    LinkedList<int> lst{1, 2, 3, 4, 5};
    auto it = lst.cend();
    --it;

    lst.insert(it, 1);
    EXPECT_THAT(lst, ElementsAre(1, 2, 3, 4, 1, 5));

    std::list authentic_lst = {0, 1, 2};
    lst.insert(--it, authentic_lst.begin(), authentic_lst.end());
    EXPECT_THAT(lst, ElementsAre(1, 2, 3, 4, 0, 1, 2, 1, 5));

    lst.insert(--it, {1, 2, 3});
    EXPECT_THAT(lst, ElementsAre(1, 2, 3, 4, 0, 1, 1, 2, 3, 2, 1, 5));

    lst.push_back(20);
    lst.push_front(10);
    EXPECT_THAT(lst, ElementsAre(10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 2, 1, 5, 20));

    lst.erase(it);
    EXPECT_THAT(lst, ElementsAre(10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20));

    lst.erase(++lst.cbegin(), --lst.cend());
    EXPECT_THAT(lst, ElementsAre(10, 20));

    lst.pop_back();
    lst.pop_front();
    EXPECT_THAT(lst, IsEmpty());

}


TEST(LinkedList, FuncsSortRemoveUnique) {
    std::list<int> authentic_lst{10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};
    LinkedList<int> lst{10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};

    // sort
    lst.sort();
    authentic_lst.sort();
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    auto p = [](const int &x, const int &y) { return x > y; };
    lst.sort(p);
    authentic_lst.sort(p);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    // unique
    lst.unique();
    authentic_lst.unique();
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    for(int& x : lst){ std::cout << x << std::endl;}

    std::cout << std::endl;

    lst.unique(p);
    authentic_lst.unique(p);
    for(int& x : lst){ std::cout << x << std::endl;}

    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    authentic_lst = {10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};
    lst = {10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};

    lst.remove(3);
    authentic_lst.remove(3);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    auto p2 = [](const int &x) { return x % 2; };

    lst.remove_if(p2);
    authentic_lst.remove_if(p2);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

}


TEST(LinkedList, FuncsResizeClearSwap) {
    std::list<int> authentic_lst{10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};
    LinkedList<int> lst{10, 1, 2, 3, 4, 0, 1, 1, 2, 3, 1, 5, 20};

    std::list<int> authentic_lst2{1, 1};
    LinkedList<int> lst2{1, 1};

    // resize
    lst.resize(30, 6);
    authentic_lst.resize(30, 6);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    lst.resize(15);
    authentic_lst.resize(15);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));

    // swap
    authentic_lst.swap(authentic_lst2);
    lst.swap(lst2);
    EXPECT_THAT(lst, ::testing::ElementsAreArray(authentic_lst));
    EXPECT_THAT(lst2, ::testing::ElementsAreArray(authentic_lst2));

    // clear
    authentic_lst2.clear();
    lst2.clear();
    EXPECT_THAT(lst2, IsEmpty());
    EXPECT_THAT(authentic_lst2, IsEmpty());

}

