#pragma once

#include <vector>
using namespace std;

//! ћаксимальное число узлов в заданном дереве
#define MaxSize 30

//! ќтсутствие узла
#define NotExist -1

struct Node
{   
    //!> »дентификатор узла-родител€    
    int parent;

    //!> »дентификатор узла-первого ребЄнка
    int firstChild;

    //!> »дентификатор узла-второго ребЄнка
    int secondChild; 

    //!> «начение узла
    string value; 

    //!>  онструктор узла дерева по умолчанию
    Node()
    {
        secondChild = NotExist;
        firstChild = NotExist;
        parent = NotExist;
    }
};

/*! –аскрыть скобки в заданном выражении
    \param[in] currentNode индекс узла дерева с которого следует раскрывать скобки
    \param[in\out] tree дерево разбора выражений
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! ѕерестроить часть дерева ниже текущего узла в соответствии с операцией
    \param[in] currentNode индекс узла дерева с которого следует перестраивать дерево
    \param[in] operation операци€ текущего узла
    \param[in\out] tree дерево разбора выражений
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! ”странить в дереве циклы обойд€ дерево в глубину относительно текущего узла
    \param[in] currentNode индекс статового узла дл€ обхода дерева
    \param[in\out] tree дерево разбора выражений
*/
void dfs_output(vector<Node>& tree, int currentNode);

/*! ”далить устаревшие узлы в дереве разбора выражений
    \param[in\out] tree дерево разбора выражений
*/
void deleteOldNodes(vector<Node>& tree);

/*! ¬вести заданное дерево разбора выражений
    \param[in\out] tree дерево разбора выражений
    \param[in\out] root индекс корн€ дерева разбора выражений
*/
void inputTree(vector<Node>& tree, int& root);

/*! ¬ывести дерево разбора выражений
    \param[in] tree дерево разбора выражений
*/
void outputTree(vector<Node>& tree);

