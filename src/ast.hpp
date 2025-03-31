#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  virtual void print() = 0;
  virtual ~Node() {};
};



class Expression : public Node {};

class Binop : public Expression {
public:
  Binop(Expression *lhs, Expression *rhs) : m_lhs(lhs), m_rhs(rhs) {}

  void print() {
    m_lhs->print();
    cout << " = ";
    m_rhs->print();
  }

  Expression * m_lhs, * m_rhs;
};

class Num : public Expression
{
public:
  Num(int n) : m_n(n) {}

  void print() {
    cout << m_n;
  }

  int m_n;
};

class QueryExpression;
class QueryTerm;


class TableReference : public Node {};
class TableFactor : public TableReference {};

class QueryTerm : public Node {};

class Order : public Node {
public:
  void print() { cout << " ORDER BY ..."; }
};

class Limit : public Node {
public:
  void print() { cout << " LIMIT ..."; }
};

class QueryExpressionBody : public Node {};

class QueryExpressionBodyTerm : public QueryExpressionBody {
  QueryTerm* m_term;
public:
  QueryExpressionBodyTerm(QueryTerm* term) : m_term(term) {}

  void print() {
    m_term->print();
  }
};

class Union : public QueryExpressionBody {
  Node* m_lhs;
  Node* m_rhs;
public:
  Union(Node* lhs, Node* rhs) : m_lhs(lhs), m_rhs(rhs) {}

  void print() {
    m_lhs->print();
    cout << " UNION ";
    m_rhs->print();
  }
};

class QueryExpression : public Node {
  QueryExpressionBody* m_body;
  Order* m_order;

public:
  bool trailingInto;

  QueryExpression(QueryExpressionBody* body, Order* order, Limit*) :
    m_body(body),
    m_order(order),
    trailingInto(false)
  {}

  void print() {
    m_body->print();
    if (m_order)
      cout << " ORDER";
    if (trailingInto)
      cout << " INTO";
  }
};

class SubqueryExpression : public Expression {
public:
  QueryExpression *m_qe;
  SubqueryExpression(QueryExpression *qe) : m_qe(qe) {}

  void print() { m_qe->print(); }
};


class TableName : public TableFactor {
  string m_name;
public:
  TableName(const string &name) : m_name(name) {}
  void print() { cout << m_name; }
};

class DerivedTable : public TableFactor {
  QueryExpression &m_qe;
  string *m_alias;
public:
  DerivedTable(QueryExpression &qe, string *alias) : m_qe(qe), m_alias(alias) {}
  void print() {
    cout << "( ";
    m_qe.print();
    cout << " )";
    if ( m_alias != NULL )
    {
      cout << " ";
      cout << *m_alias << " ";
    }
  }
};

class JoinCondition : public Node {
};

class On : public JoinCondition {
  Expression* m_expr;
public:
  On(Expression* expr) : m_expr(expr) {}

  void print () {
    cout << " ON ";
    m_expr->print();
  }
};

class JoinedTable : public TableFactor {
  TableReference* m_lhs;
  TableReference* m_rhs;
  JoinCondition* m_cond;
public:
  JoinedTable(TableReference* tr, TableReference* tf) :
    m_lhs(tr), m_rhs(tf), m_cond(NULL) {}

  JoinedTable(TableReference* tr, TableReference* tf, JoinCondition* cond) :
    m_lhs(tr), m_rhs(tf), m_cond(cond) {}

  void print() {
    cout << '(';
    m_lhs->print();
    cout << ')';
    cout << " JOIN ";
    cout << '(';
    m_rhs->print();
    cout << ')';
    if (m_cond)
      m_cond->print();
  }
};

class TableReferenceList : public TableFactor {
  vector<TableReference*> m_trs;
public:
  TableReferenceList(TableReference* tr) { add(tr); }
  void add(TableReference* tr) { m_trs.push_back(tr); }
  void print() {
    vector<TableReference*>::iterator it;
    it = m_trs.begin();
    (*it)->print();
    for ( it++; it < m_trs.end() ; it++ )
    {
      cout << ", ";
      (*it)->print();
    }
  }
};

class QuerySpecification : public QueryTerm {
  Expression *m_expr;
  TableReferenceList* m_trs;
public:
  QuerySpecification(Expression *expr, TableReferenceList* trs) :
    m_expr(expr), m_trs(trs) {}
  void print() {
    cout << "SELECT ";
    m_expr->print();
    if (m_trs != NULL) { cout << " FROM "; m_trs->print(); }
  }
};
  

#endif // AST_H
