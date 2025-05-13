#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cout;

namespace parse_tree {

enum NodeType {
  AliasClause,
  Binop,
  ColumnDefinition,
  ColumnName,
  DataType,
  DerivedTable,
  JoinedTable,
  Limit,
  Num,
  On,
  Order,
  QueryExpression,
  QueryExpressionBodyTerm,
  QuerySpecification,
  SubqueryExpression,
  TableDefinition,
  TableElementList,
  TableName,
  TableReferenceList,
  Union,
};

struct Node {

  Node(NodeType t) : tag(t) {}

  template <typename T, typename = std::enable_if_t<!std::is_same_v<T, Node *>>>
  Node(NodeType type, T t) : tag(type), content(t) {}

  template <typename... Args, typename = std::enable_if_t<std::conjunction_v<
                                  std::is_same<Args, Node *>...>>>
  Node(NodeType t, Args... args) : tag(t) {
    (children.push_back(std::unique_ptr<Node>(args)), ...);
  }

  void push_back(Node *node) {
    children.push_back(std::unique_ptr<Node>(node));
  }

  void print() {}

  NodeType tag;
  std::vector<std::unique_ptr<Node>> children;
  std::variant<int, std::string> content;
};

template <typename... Ts> Node *make_node(NodeType type, Ts &&...ts) {
  return new Node(type, std::forward<Ts>(ts)...);
}

} // namespace parse_tree
