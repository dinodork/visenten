#include "parse_tree.hpp"

namespace parse_tree {

void print(Node *node) {
  Stringifier s;
  node->accept(s);
  cout << "Stringified:\n"
       << "'" << s.result_string() << "'";
}

void print(Node *node, std::ostream &stream) { stream << "pitt!" << node; }

} // namespace parse_tree
