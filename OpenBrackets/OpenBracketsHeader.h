#pragma once

#include <vector>
using namespace std;

//! ������������ ����� ����� � �������� ������
#define MaxSize 30

//! ���������� ����
#define NotExist -1

//! ���� ������
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
        this->parent = NotExist; // �������, ��� ����-�������� �� ����������
        this->firstChild = NotExist; // �������, ��� ����-������ ������ �� ����������
        this->secondChild = NotExist; // �������, ��� ����-������ ������ �� ����������
        this->value = "\0"; // �������, ��� � ���� ����������� ��������
    }

    //!> ����������� ��� ����� �������������
    Node(int parent, int firstChild, int secondChild, string value)
    {
        this->parent = parent;
        this->firstChild = firstChild;
        this->secondChild = secondChild;
        this->value = value;
    }

    //!> �������� ��������� ������ �� ���������
    bool operator == (const Node& other) const
    {
        bool isEqual = false; // �������, ��� ���� �� ����� ����� �����
       
        // ���� ��� ���� ����� ���������
        if (this->secondChild == other.secondChild && 
            this->firstChild == other.firstChild && 
            this->parent == other.parent && 
            this->value == other.value)
            isEqual = true; // �������, ��� ���� ����� ����� �����

        return isEqual;
    }
};

//! ���� ������ 
enum ErrorType
{
    //!> ��� ������
    NO_ERROR,

    //!> ������� ���� �� ����������
    INPUT_FILE_NOT_EXIST,

    //!> ������� ���� ����� ������������ ����������
    UNKNOWN_FILE_EXTENSION,

    //!> ���������� ������� ��������� �������� ����
    OUTPUT_FILE_CREATION_FAILED,

    //!> �� ������� ����� ������ ��������������� ������ �� ������������� ����������
    WRONG_DATA_FORMAT,

    //!> � ����� ������ ������� ��������� ������ ���� �����
    NOT_BINARY_TREE,

    //!> �������������� ����� ���������
    SAME_NODES_ID,

    //!> ������������� ������������� ���� ��������� � ��������������� ����
    SAME_PARENT_AND_NODE_ID,

    //!> � �������� ������� ���� ���������
    LACK_OF_OPERANDS,

    //!> ������������� ���� ������ ������� ��������� ��� ��������������� ���������
    NODE_ID_OUT_OF_RANGE,

    //!>  ������������� ������������� ���� ��� ���� � ������ ������� ��������� ��� ��������������� ���������
    PARENT_ID_OUT_OF_RANGE,

    //!> ������������ ������ � �������� ��������
    INVALID_NODE_SYMBOL,

    //!>  �������� � ���� � ����� �� ���������
    NOT_RIGHT_LINK,

    //!> ������������� ������������� ���� �������� ��������������� ����-������
    UNEXCEPTABLE_PARENT_ID,

    //!> ���������� ��������� ����
    NO_ROOT,

    //!> ����� ����� ������ ������� ��������� ��� ��������������� ���������
    TREE_SIZE_OUT_OF_RANGE,

    //!> ��������� ����� ����� ������ ������� ��������� �� ��������� � ����������� ������ �������� �����
    INVALID_NUMBER_OF_NODES
};

/*! �������� ������ � �������� ���������
    \param[in] currentNode - ������ ���� ������ � �������� ������� ���������� ������
    \param[in\out] tree - ������ ������� ���������
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! ����������� ����� ������ ���� �������� ���� � ������������ � ���������
    \param[in] currentNode - ������ ���� ������ � �������� ������� ������������� ������
    \param[in] operation - �������� �������� ����
    \param[in\out] tree - ������ ������� ���������
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! ������� ��������� �� ������
    \param[in] error - ��� ������
    \return true - ��� �������� ������, false - �����
*/
bool crashOutput(ErrorType error);

/*! ��������� ������ �� ������
    \param[in] size - ������ ������
    \param[in] root - ������ ����� ������
    \param[in] tree - ������ ������� ���������
    \return - ������������ ��� ������
*/
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root);

/*! �������� ��� ������ ����� �����
    \param[in] firstTree - ������ ������
    \param[in] rootOfFirstTree - ������ ��������� ���� ������� ������
    \param[in] secondTree - ������ ������
    \param[in] rootOfSecondTree - ������ ��������� ���� ������� ������
    \return true - ���� ������� ���������, false - ���� ������� ������
*/
bool isEqualTrees(vector<Node> firstTree, int rootOfFirstTree, vector<Node> secondTree, int rootOfSecondTree);

/*! ��������� ������� ������ �� ������������� �������
    \param[in\out] tree - ������ ������� ���������
*/
void initializeFullTree(vector<Node>& inputTree);

/*! ������ �������� ������ ������� ���������
    \param[in\out] tree - ������ ������� ���������
    \param[in\out] root - ������ ����� ������ ������� ���������
    \return true - ��� �������� ������, false - �����
*/
bool inputTree(vector<Node>& tree, int& root);

/*! ������� ������ ������� ���������
    \param[in] tree - ������ ������� ���������
    \param[in] current - ������ �������, � ������� ����������� ����� ������
    \return true - ��� �������� ������, false - �����
*/
bool outputTree(vector<Node>& tree, int& current);

/*! ������� ������� ������ ������� � �������
    \param[in] tree - ������ ������� ���������
    \param[in] current - ������������� ������� � ������� ����������� ����� 
*/
void dfsOutput(vector<Node>& tree, int current);

/*! ����������� �������� ������� � ������� ������
    \param[in] currentNode ������ ���������� �������
    \param[in\out] tree ������ ������
    \return ������ ������� ������������� �������
*/
int copyVertex(vector<Node>& tree, int currentNode);