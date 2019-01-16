#ifndef __AST_H__
#define __AST_H__

typedef enum NodeType{
  statementNode,
  expressionNode,
}NodeType;

typedef struct Node{
  NodeType type;
}Node;

typedef struct Statement{
  NodeType statementNode;
  void **stmt;
}Statement;

#endif /* __AST_H__ */
