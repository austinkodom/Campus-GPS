#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;
/* A struct node that will be each vertex name
 * or a point on campus.
 */
struct Node {
    string name;

    Node(const string& n) : name(n) {}
};

#endif // NODE_H
