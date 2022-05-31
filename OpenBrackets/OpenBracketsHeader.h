/*!
* \file 
* \brief Заголовочный файл программы
* 
* Файл содержит в себе структуры и заголовки для функций программы, раскрываюшей скобки в математическом выражении,
* заданном деревом разбора выражений в виде списка смежности.
*/

#pragma once

#include <vector>
using namespace std;

//! Максимальное число узлов в заданном дереве
#define MaxSize 30

//! Отсутствие узла
#define NotExist -1

//! Разрешить работу устаревшим функциям
#define _CRT_SECURE_NO_WARNINGS

//! \brief Узел дерева
struct Node
{   
    //! Идентификатор узла-родителя    
    int parent;

    //! Идентификатор узла-первого ребёнка
    int firstChild;

    //! Идентификатор узла-второго ребёнка
    int secondChild; 

    //! Значение узла
    string value; 

    //!> Конструктор узла дерева по умолчанию
    Node()
    {
        this->parent = NotExist; // Считать, что узел-родитель не существует
        this->firstChild = NotExist; // Считать, что узел-первый ребёнок не существует
        this->secondChild = NotExist; // Считать, что узел-второй ребёнок не существует
        this->value = "\0"; // Считать, что у узла отсутствует значение
    }

    //!> Конструктор при явной инициализации
    Node(int parent, int firstChild, int secondChild, string value)
    {
        this->parent = parent;
        this->firstChild = firstChild;
        this->secondChild = secondChild;
        this->value = value;
    }

    //!> Оператор сравнения вершин на равенство
    bool operator == (const Node& other) const
    {
        bool isEqual = false; // Считать, что узлы не равны между собой
       
        // Если все поля узлов совпадают
        if (this->secondChild == other.secondChild && 
            this->firstChild == other.firstChild && 
            this->parent == other.parent && 
            this->value == other.value)
            isEqual = true; // Считать, что узлы равны между собой

        return isEqual;
    }
};

//! \brief Типы ошибок 
enum ErrorType
{
    NO_ERROR, ///< Нет ошибки

    INPUT_FILE_NOT_EXIST, ///< Входной файл не существует
 
    UNKNOWN_FILE_EXTENSION, ///< Входной файл имеет неправильное расширение

    OUTPUT_FILE_CREATION_FAILED, ///< Невозможно создать указанный выходной файл

    WRONG_DATA_FORMAT, ///< Во входном файле формат предоставляемых данных не соответствует требуемому

    NOT_BINARY_TREE, ///< У узлов дерева разбора выражений больше двух детей

    SAME_NODES_ID, ///< Идентификаторы узлов совпадают

    SAME_PARENT_AND_NODE_ID, ///< Идентификатор родительского узла совпадает с идентификатором узла

    LACK_OF_OPERANDS, ///< У операции слишком мало операндов

    NODE_ID_OUT_OF_RANGE, ///< Идентификатор узла дерева разбора выражений вне поддерживаемого диапазона

    PARENT_ID_OUT_OF_RANGE, ///< Идентификатор родительского узла для узла в дереве разбора выражений вне поддерживаемого диапазона

    INVALID_NODE_SYMBOL, ///< Недопустимый символ в значении операнда

    NOT_RIGHT_LINK, ///< Родители и дети у узлов не совпадают

    UNEXCEPTABLE_PARENT_ID, ///< Идентификатор родительского узла является идентификатором узла-ребёнка

    NO_ROOT, ///< Отсутствие корневого узла

    TREE_SIZE_OUT_OF_RANGE, ///< Число узлов дерева разбора выражений вне поддерживаемого диапазона

    INVALID_NUMBER_OF_NODES ///< Указанное число узлов дерева разбора выражений не совпадает с фактическим числом заданных узлов
};

/*! \brief Раскрыть скобки в заданном выражении
*   \param[in] currentNode - индекс узла дерева с которого следует раскрывать скобки
*   \param[out] tree - дерево разбора выражений
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! \brief Перестроить часть дерева ниже текущего узла в соответствии с операцией
*   \param[in] currentNode - индекс узла дерева с которого следует перестраивать дерево
*   \param[in] operation - операция текущего узла
*   \param[out] tree - дерево разбора выражений
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! \brief Вывести сообщение об ошибке
*   \param[in] error - тип ошибки
*   \return true при успешном выводе, false - иначе
*/
bool crashOutput(ErrorType error);

/*! \brief Проверить дерево на ошибки
*   \param[in] size - размер дерева
*   \param[in] root - индекс корня дерева
*   \param[in] tree - дерево разбора выражений
*   \return обнаруженный тип ошибки
*/
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root);

/*! \brief Сравнить два дерева между собой
*   \param[in] firstTree - первое дерево
*   \param[in] rootOfFirstTree - индекс корневого узла первого дерева
*   \param[in] secondTree - второе дерево
*   \param[in] rootOfSecondTree - индекс корневого узла второго дерева
*   \return true - если деревья совпадают, false - если деревья разные
*/
bool isEqualTrees(vector<Node> firstTree, int rootOfFirstTree, vector<Node> secondTree, int rootOfSecondTree);

/*! \brief Заполнить входное дерево до максимального размера
*   \param[out] inputTree - дерево разбора выражений
*/
void initializeFullTree(vector<Node>& inputTree);

/*! \brief Ввести заданное дерево разбора выражений
*   \param[in] argc - аргумент командной строки
*   \param[in] argv[] - аргументы командной строки
*   \param[in] fin - входной поток
*   \param[out] tree - дерево разбора выражений
*   \param[out] root - индекс корня дерева разбора выражений
*   \return true - при успешном ввводе, false - иначе
*   \throw UNKNOWN_FILE_EXTENSION - неверно указано расширение входного файла
*   \throw INPUT_FILE_NOT_EXIST - не существует или не найден входной файл
*   \throw WRONG_DATA_FORMAT - неверный формат данных во входном файле
*   \throw TREE_SIZE_OUT_OF_RANGE - размер дерева во входном файле вне поддерживаемого диапазона
*/
bool inputTree(int argc, char* argv[], ifstream& fin, vector<Node>& tree, int& root);

/*! \brief Вывести дерево разбора выражений
*   \param[in] argc - аргумент командной строки
*   \param[in] argv[] - аргументы командной строки
*   \param[in] tree - дерево разбора выражений
*   \param[in] current - индекс вершины, с которой производить вывод дерева
*   \param[out] fout - выходной поток
*   \return true - при успешном выводе, false - иначе
*   \throw UNKNOWN_FILE_EXTENSION - неверно указано расширение выходного файла
*   \throw OUTPUT_FILE_CREATION_FAILED - невозможно создать выходной файл
*/
bool outputTree(int argc, char* argv[], ofstream& fout, vector<Node>& tree, int& current);

/*! \brief Вывести вершины дерева обходом в глубину
*   \param[in] tree - дерево разбора выражений
*   \param[in] current - идентификатор вершины с которой производить вывод 
*   \param[out] fout - выходной поток
*/
void dfsOutput(ofstream& fout, vector<Node>& tree, int current);

/*! \brief Скопировать заданную вершину в векторе вершин
*   \param[in] currentNode индекс копируемой вершины
*   \param[out] tree вектор вершин
*   \return индекс позиции скопированной вершины
*/
int copyVertex(vector<Node>& tree, int currentNode);