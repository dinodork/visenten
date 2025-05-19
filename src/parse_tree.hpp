#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <variant>
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
  ExprList,
  FromClause,
  InsertStatement,
  JoinedTable,
  Limit,
  Num,
  On,
  Order,
  QueryExpression,
  QueryExpressionBodyTerm,
  QuerySpecification,
  RowValueExpr,
  SelectList,
  Star,
  String,
  SubqueryExpression,
  TableDefinition,
  TableElementList,
  TableName,
  TableReferenceList,
  Union,
};

struct Node {

  using ChildList = std::vector<std::unique_ptr<Node>>;

  Node(NodeType t) : tag(t) {}

  template <typename T, typename = std::enable_if_t<!std::is_same_v<T, Node *>>>
  Node(NodeType type, T t) : tag(type), content(t) {}

  template <typename... Args, typename = std::enable_if_t<std::conjunction_v<
                                  std::is_same<Args, Node *>...>>>
  Node(NodeType t, Args... args) : tag(t), content(ChildList{}) {
    (push_back_if_not_null(args), ...);
  }

  void push_back(Node &node) {
    children().push_back(std::unique_ptr<Node>(&node));
  }

  void push_back_if_not_null(Node *node) {
    if (node == nullptr)
      return;
    push_back(*node);
  }

  bool is_leaf() const { return !std::holds_alternative<ChildList>(content); }

  ChildList &children() { return *std::get_if<ChildList>(&content); }

  NodeType tag;

  std::variant<ChildList, int, std::string> content;
};

template <typename... Ts> Node *make_node(NodeType type, Ts &&...ts) {
  return new Node(type, std::forward<Ts>(ts)...);
}

void print(Node *);

void print(Node *, std::ostream &);

} // namespace parse_tree
