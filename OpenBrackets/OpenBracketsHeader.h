#pragma once

#include <vector>
using namespace std;

//! ������������ ����� ����� � �������� ������
#define MaxSize 30

//! ���������� ����
#define NotExist -1

struct Node
{   
    //!> ������������� ����-��������    
    int parent;

    //!> ������������� ����-������� ������
    int firstChild;

    //!> ������������� ����-������� ������
    int secondChild; 

    //!> �������� ����
    string value; 

    //!> ����������� ���� ������ �� ���������
    Node()
    {
        secondChild = NotExist;
        firstChild = NotExist;
        parent = NotExist;
    }
};

/*! �������� ������ � �������� ���������
    \param[in] currentNode ������ ���� ������ � �������� ������� ���������� ������
    \param[in\out] tree ������ ������� ���������
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! ����������� ����� ������ ���� �������� ���� � ������������ � ���������
    \param[in] currentNode ������ ���� ������ � �������� ������� ������������� ������
    \param[in] operation �������� �������� ����
    \param[in\out] tree ������ ������� ���������
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! ��������� � ������ ����� ������ ������ � ������� ������������ �������� ����
    \param[in] currentNode ������ ��������� ���� ��� ������ ������
    \param[in\out] tree ������ ������� ���������
*/
void dfs_output(vector<Node>& tree, int currentNode);

/*! ������� ���������� ���� � ������ ������� ���������
    \param[in\out] tree ������ ������� ���������
*/
void deleteOldNodes(vector<Node>& tree);

/*! ������ �������� ������ ������� ���������
    \param[in\out] tree ������ ������� ���������
    \param[in\out] root ������ ����� ������ ������� ���������
*/
void inputTree(vector<Node>& tree, int& root);

/*! ������� ������ ������� ���������
    \param[in] tree ������ ������� ���������
*/
void outputTree(vector<Node>& tree);

