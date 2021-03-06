#include <gtest/gtest.h>
#include "priority_queue_stl.h"
#include "grid_node.h"


template<typename T>
class ScalarPriority {
public:
  static bool less_priority(T t0, T t1) {
    return t0 > t1;
  }

  static T get_priority(T t0) {
    return t0;
  }

  static void set_priority(T &t, T v) {
    t = v;
  }
};

template<typename Q>
static const string stringify_q(const Q &q) {
  stringstream ss;
  for (auto n : q.queue_ ) {
    ss << n <<",";
  }
  return ss.str();
}

const char *stringify(const PriorityQueueSTL<int, int,
                                             ScalarPriority<int>> &q) {
  return stringify_q<PriorityQueueSTL<int, int,
                                      ScalarPriority<int>>>(q).c_str();
}

const char *stringify(const PriorityQueueSTL<GridNode<int>*, int, GridNode<int>> &q) {
  return stringify_q<PriorityQueueSTL<GridNode<int>*, int, GridNode<int>>>(q).c_str();
}

const char *stringify(const PriorityQueueSTL<GridNode<double>*, double, GridNode<double>> &q) {
  return stringify_q<PriorityQueueSTL<GridNode<double>*, double, GridNode<double>>>(q).c_str();
}

TEST(PriorityQueueSTL, insert_remove_increase_int) {
  PriorityQueueSTL<int, int, ScalarPriority<int>> q;
  q.insert(10);
  ASSERT_STREQ("10,", stringify(q));
  q.insert(50);
  ASSERT_STREQ("10,50,", stringify(q));
  q.insert(30);
  ASSERT_STREQ("10,50,30,", stringify(q));
  q.insert(20);
  ASSERT_STREQ("10,20,30,50,", stringify(q));
  q.insert(15);
  ASSERT_STREQ("10,15,30,50,20,", stringify(q));
  q.insert(40);
  ASSERT_STREQ("10,15,30,50,20,40,", stringify(q));
  q.insert(5);
  ASSERT_STREQ("5,15,10,50,20,40,30,", stringify(q));
  /*
   *          5
   *       /     \
   *      15     10
   *     /  \   /  \
   *    50  20 40  30
   */


  ASSERT_EQ(5, q.remove_front());
  ASSERT_STREQ("10,15,30,50,20,40,", stringify(q));
  /*
   *          10
   *       /     \
   *      15     30
   *     /  \   /
   *    50  20 40
   */

  q.insert(5);
  ASSERT_STREQ("5,15,10,50,20,40,30,", stringify(q));
  /*
     *          5
     *       /     \
     *      15     10
     *     /  \   /  \
     *    50  20 40  30
     */

  q.increase_priority(40, 2);
  ASSERT_STREQ("2,15,5,50,20,10,30,", stringify(q));
  /*
   *          2
   *       /     \
   *      15      5
   *     /  \   /  \
   *    50  20 10  30
   */

  q.insert(5);
  ASSERT_STREQ("2,5,5,15,20,10,30,50,", stringify(q));
  /*
   *          2
   *       /     \
   *      5      5
   *     /  \   /  \
   *    15  20 10  30
   *   /
   *  50
   */

  ASSERT_EQ(2, q.remove_front());
  ASSERT_STREQ("5,5,10,15,20,50,30,", stringify(q));
  /*
   *          5
   *       /     \
   *      5      10
   *     /  \   /  \
   *    15  20 50  30
   */

}


TEST(PriorityQueueSTL, increase_priority_node_int) {
  using C = pair<int,int>;
  using CostType = int;

  PriorityQueueSTL<GridNode<CostType>*, CostType, GridNode<CostType>> q;

  GridNode<CostType> n00(C(0,0), 10);
  q.insert(&n00);
  ASSERT_STREQ("10,", stringify(q));

  GridNode<CostType> n10(C(1,0), 50);
  q.insert(&n10);
  ASSERT_STREQ("10,50,", stringify(q));

  GridNode<CostType> n20(C(2,0), 30);
  q.insert(&n20);
  ASSERT_STREQ("10,50,30,", stringify(q));

  GridNode<CostType> n30(C(3,0), 20);
  q.insert(&n30);
  ASSERT_STREQ("10,20,30,50,", stringify(q));

  GridNode<CostType> n40(C(4,0), 15);
  q.insert(&n40);
  ASSERT_STREQ("10,15,30,50,20,", stringify(q));

  GridNode<CostType> n50(C(5,0), 40);
  q.insert(&n50);
  ASSERT_STREQ("10,15,30,50,20,40,", stringify(q));

  GridNode<CostType> n60(C(6,0), 5);
  q.insert(&n60);
  ASSERT_STREQ("5,15,10,50,20,40,30,", stringify(q));
  /*
   *          5
   *       /     \
   *      15     10
   *     /  \   /  \
   *    50  20 40  30
   */


  ASSERT_EQ(&n60, q.remove_front());
  ASSERT_EQ(5, n60.f_);
  ASSERT_STREQ("10,15,30,50,20,40,", stringify(q));
  /*
   *          10
   *       /     \
   *      15     30
   *     /  \   /
   *    50  20 40
   */

  q.insert(&n60);
  ASSERT_STREQ("5,15,10,50,20,40,30,", stringify(q));
  /*
     *          5
     *       /     \
     *      15     10
     *     /  \   /  \
     *    50  20 40  30
     */

  q.increase_priority(&n50, 2);
  /*
   *          2
   *       /     \
   *      15      5
   *     /  \   /  \
   *    50  20 10  30
   */
  ASSERT_STREQ("2,15,5,50,20,10,30,", stringify(q));
}

TEST(PriorityQueueSTL, increase_priority_node_double) {
  using C = pair<int,int>;
  using CostType = double;

  PriorityQueueSTL<GridNode<CostType>*, CostType, GridNode<CostType>> q;

  /*
  [D] node inserted: coord:(0,0)<-(-1,-1) g:0 f:12.7279
  */
  GridNode<CostType> n00(C(0,0), 12.7279);
  q.insert(&n00);
  ASSERT_STREQ("12.7279,", stringify(q));

  /*
   [D] front node removed: coord:(0,0)<-(-1,-1) g:0 f:12.7279
  */
  ASSERT_EQ(&n00, q.remove_front());
  ASSERT_STREQ("", stringify(q));

  /*
  [D] node inserted: coord:(1,0)<-(0,0) g:1 f:13.0416
  [D] node inserted: coord:(0,1)<-(0,0) g:1 f:13.0416
  [D] node inserted: coord:(1,1)<-(0,0) g:1.4143 f:12.728
  */
  GridNode<CostType> n10(C(1,0), 13.0416);
  q.insert(&n10);
  ASSERT_STREQ("13.0416,", stringify(q));

  GridNode<CostType> n01(C(0,1), 13.0416);
  q.insert(&n01);
  ASSERT_STREQ("13.0416,13.0416,", stringify(q));

  GridNode<CostType> n11(C(1,1), 12.728);
  q.insert(&n11);
  ASSERT_STREQ("12.728,13.0416,13.0416,", stringify(q));

  /*
  [D] front node removed: coord:(1,1)<-(0,0) g:1.4143 f:12.728
  */
  ASSERT_EQ(&n11, q.remove_front());
  ASSERT_STREQ("13.0416,13.0416,", stringify(q));

  /*
  [D] node inserted: coord:(2,0)<-(1,1) g:2.8286 f:14.2304
  [D] node inserted: coord:(2,1)<-(1,1) g:2.4143 f:13.0444
  [D] node inserted: coord:(0,2)<-(1,1) g:2.8286 f:14.2304
  [D] node inserted: coord:(1,2)<-(1,1) g:3.4143 f:14.0444
  */
  GridNode<CostType> n20(C(2,0), 14.2304);
  q.insert(&n20);
  ASSERT_STREQ("13.0416,13.0416,14.2304,", stringify(q));

  GridNode<CostType> n21(C(2,1), 13.0444);
  q.insert(&n21);
  ASSERT_STREQ("13.0416,13.0416,14.2304,13.0444,", stringify(q));

  GridNode<CostType> n02(C(0,2), 14.2304);
  q.insert(&n02);
  ASSERT_STREQ("13.0416,13.0416,14.2304,13.0444,14.2304,", stringify(q));

  GridNode<CostType> n12(C(1,2), 14.0444);
  q.insert(&n12);
  ASSERT_STREQ("13.0416,13.0416,14.0444,13.0444,14.2304,14.2304,",
      stringify(q));
  /*
   *                   13.0416
   *              /              \
   *          13.0416          14.0444
   *         /       \           /
   *      13.0444   14.2304  14.2304
   */

  /*
  [D] front node removed: coord:(0,1)<-(0,0) g:1 f:13.0416
  */
  ASSERT_EQ(&n01, q.remove_front());
  ASSERT_STREQ("13.0416,13.0444,14.0444,14.2304,14.2304,", stringify(q));
  /*
   *                13.0416
   *              /         \
   *          13.0444     14.0444
   *         /       \
   *      14.2304   14.2304
   */

  /*
  [D] node priority increased: coord:(0,2)<-(0,1) g:2 f:13.4018
  */
  q.increase_priority(&n02, 13.4018);
  /*
   *                13.0416
   *              /         \
   *          13.0444      14.0444
   *         /       \
   *      14.2304   13.4018
   */
   ASSERT_STREQ("13.0416,13.0444,14.0444,14.2304,13.4018,", stringify(q));

  /*
  [D] front node removed: coord:(1,0)<-(0,0) g:1 f:13.0416
  */
   ASSERT_EQ(&n10, q.remove_front());
   ASSERT_STREQ("13.0444,13.4018,14.0444,14.2304,", stringify(q));
   /*
    *                13.0444
    *              /         \
    *          13.4018     14.0444
    *         /
    *      14.2304
    */

  /*
  [D] node priority increased: coord:(2,0)<-(1,0) g:2 f:13.4018
  */
   q.increase_priority(&n20, 13.4018);
   /*
    *                13.0444
    *              /         \
    *        0,2,13.4018     14.0444
    *         /
    *    2,0,13.4018
    */
   ASSERT_STREQ("13.0444,13.4018,14.0444,13.4018,", stringify(q));

  /*
  [D] front node removed: coord:(2,1)<-(1,1) g:2.4143 f:13.0444
  */
   ASSERT_EQ(&n21, q.remove_front());
   ASSERT_STREQ("13.4018,13.4018,14.0444,", stringify(q));
   /*
    *              0,2,13.4018
    *              /         \
    *        2,0,13.4018     14.0444
    *
    *
    */


  /*
  [D] node inserted: coord:(3,0)<-(2,1) g:8.0715 f:18.8882
  [D] node inserted: coord:(3,2)<-(2,1) g:9.4858 f:18.7053
  */
   GridNode<CostType> n30(C(3,0), 18.8882);
   q.insert(&n30);
   ASSERT_STREQ("13.4018,13.4018,14.0444,18.8882,", stringify(q));

   GridNode<CostType> n32(C(3,2), 18.7053);
   q.insert(&n32);
   ASSERT_STREQ("13.4018,13.4018,14.0444,18.8882,18.7053,", stringify(q));
   /*
    *              0,2,13.4018
    *              /         \
    *        2,0,13.4018     14.0444
    *            /  \
    *      18.8882  18.7053
    */

   ASSERT_EQ(&n02, q.remove_front());
   ASSERT_STREQ("13.4018,18.7053,14.0444,18.8882,", stringify(q));
   /*
    *            2,0,13.4018
    *              /         \
    *          18.7053     14.0444
    *            /
    *      18.8882
    */

}

