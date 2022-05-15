#pragma once

#include <vector>
using namespace std;

//! Максимальное число узлов в заданном дереве
#define MaxSize 30

//! Отсутствие узла
#define NotExist -1

struct Node
{   
    //!> Идентификатор узла-родителя    
    int parent;

    //!> Идентификатор узла-первого ребёнка
    int firstChild;

    //!> Идентификатор узла-второго ребёнка
    int secondChild; 

    //!> Значение узла
    string value; 

    //!> Конструктор узла дерева по умолчанию
    Node()
    {
        secondChild = NotExist;
        firstChild = NotExist;
        parent = NotExist;
    }
};

//! Типы ошибок 
enum ErrorType
{
    //!> Нет ошибки
    NO_ERROR,

    //!> Входной файл не существует
    INPUT_FILE_NOT_EXIST,

    //!> Входной файл имеет неправильное расширение
    UNKNOWN_FILE_EXTENSION,

    //!> Невозможно создать указанный выходной файл
    OUTPUT_FILE_CREATION_FAILED,

    //!> Во входном файле формат предоставляемых данных не соответствует требуемому
    WRONG_DATA_FORMAT,

    //!> У узлов дерева разбора выражений больше двух детей
    NOT_BINARY_TREE,

    //!> Идентификаторы узлов совпадают
    SAME_NODES_ID,

    //!> Идентификатор родительского узла совпадает с идентификатором узла
    SAME_PARENT_AND_NODE_ID,

    //!> У операции слишком мало операндов
    LACK_OF_OPERANDS,

    //!> Идентификатор узла дерева разбора выражений вне поддерживаемого диапазона
    NODE_ID_OUT_OF_RANGE,

    //!>  Идентификатор родительского узла для узла в дереве разбора выражений вне поддерживаемого диапазона
    PARENT_ID_OUT_OF_RANGE,

    //!> Недопустимый символ в значении операнда
    INVALID_NODE_SYMBOL,

    //!>  Указана неподдерживаемая операция
    UNSUPPORTED_OPERATION,

    //!> Идентификатор родительского узла является идентификатором узла-ребёнка
    UNEXCEPTABLE_PARENT_ID,

    //!> Отсутствие корневого узла
    NO_ROOT,

    //!> Число узлов дерева разбора выражений вне поддерживаемого диапазона
    TREE_SIZE_OUT_OF_RANGE,

    //!> Указанное число узлов дерева разбора выражений не совпадает с фактическим числом заданных узлов
    INVALID_NUMBER_OF_NODES
};


/*! Раскрыть скобки в заданном выражении
    \param[in] currentNode индекс узла дерева с которого следует раскрывать скобки
    \param[in\out] tree дерево разбора выражений
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! Перестроить часть дерева ниже текущего узла в соответствии с операцией
    \param[in] currentNode индекс узла дерева с которого следует перестраивать дерево
    \param[in] operation операция текущего узла
    \param[in\out] tree дерево разбора выражений
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! Устранить в дереве циклы обойдя дерево в глубину относительно текущего узла
    \param[in] currentNode индекс статового узла для обхода дерева
    \param[in\out] tree дерево разбора выражений
*/
void dfs_output(vector<Node>& tree, int currentNode);

/*! Удалить устаревшие узлы в дереве разбора выражений
    \param[in\out] tree дерево разбора выражений
*/
void deleteOldNodes(vector<Node>& tree);

/*! Вывести сообщение об ошибке
    \param[in] error обнаруженный тип ошибки
    return true при успешном выводе, false иначе
*/
bool crashOutput(ErrorType error);

/*! Проверить дерево на ошибки
    \param[in] size размер дерева
    \param[in] root индекс корня дерева
    \param[in] tree дерево разбора выражений
    return обнаруженнфый тип ошибки
*/
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root);

/*! Ввести заданное дерево разбора выражений
    \param[in\out] tree дерево разбора выражений
    \param[in\out] root индекс корня дерева разбора выражений
*/
void inputTree(vector<Node>& tree, int& root);

/*! Вывести дерево разбора выражений
    \param[in] tree дерево разбора выражений
*/
void outputTree(vector<Node>& tree);

