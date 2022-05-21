/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

#include <algorithm>

int main()
{
  OrgChart DemoRun;
  DemoRun.add_root("10").add_sub("10", "2");
  DemoRun.add_sub("2", "77").add_sub("10", "34").add_sub("10", "56").add_sub("10", "100").add_sub("100", "7");
  DemoRun.add_sub("2", "88").add_sub("56", "1").add_sub("100", "8").add_sub("100", "9");
  //   Input :          10
  //              /   /    \   \
  //             2  34    56   100
  //            / \        |   / | \
  //           77  88      1   7  8  9

  cout << DemoRun;
  // Output : 10
  //          2 34 56 100
  //          77 88 1 7 8 9
  cout << "\n";
  try
  {
    auto it = find(DemoRun.begin(), DemoRun.end(), "77"); 
    cout << *it << "\n";
  }
  catch (...)
  {
  }
  cout << "\n";
  int i = 1; // change i to decided all of demorun smaller than i : 
  if (std::all_of(DemoRun.begin(), DemoRun.end(), [i](std::string a)
                  { return a.size() <= i; }))
  {
    cout << "all are smaller than " << i << "\n";
  }
  else
    cout << "not all are smaller than " << i << "!\n";

  for (auto it = DemoRun.begin_preorder(); it != DemoRun.end_preorder(); ++it)
  {
    cout << *it << " ";
  }

    cout << endl;
  return 0;
}

// int main() {
//   OrgChart organization;
//   organization.add_root("CEO")
//       .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
//       .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
//       .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
//       .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
//       .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

//   cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
//        CEO
//        |--------|--------|
//        CTO      CFO      COO
//        |                 |
//        VP_SW             VP_BI
//  */

//   for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
//   {
//     cout << (*it) << " " ;
//   } // prints: CEO CTO CFO COO VP_SW VP_BI
//   for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
//   {
//     cout << (*it) << " " ;
//   } // prints: VP_SW VP_BI CTO CFO COO CEO
// for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
//   cout << (*it) << " " ;
// }  // prints: CEO CTO VP_SW CFO COO VP_BI

// for (auto element : organization)
// { // this should work like level order
//   cout << element << " " ;
// } // prints: CEO CTO CFO COO VP_SW VP_BI

// // demonstrate the arrow operator:
// for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
// {
//   cout << it->size() << " " ;
// } // prints: 3 3 3 3 5 5
//}
