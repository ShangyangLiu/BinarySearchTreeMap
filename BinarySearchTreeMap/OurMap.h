#ifndef OURMAP_H
#define OURMAP_H

#include <ostream>
#include "error.h"
#include "strlib.h"
#include "vector.h"
//#include "testing/MemoryDiagnostics.h"
//#include "testing/SimpleTest.h"

using namespace std;

template <typename KeyType, typename ValueType>
class OurMap
{
public:
    OurMap();
    ~OurMap();

    OurMap(const OurMap& map2);
    OurMap& operator=(const OurMap& map2);

    bool containsKey(const KeyType& key) const;
    void remove(const KeyType& key);
    void put(const KeyType& key,const ValueType& value);

    KeyType firstKey() const;
    KeyType lastKey() const;

    Vector<KeyType> Keys() const;
    Vector<ValueType> values() const;

    void clear();
    int size() const;
    bool isEmpty() const;

    ValueType& operator [](const KeyType& key);

private:
    struct TreeNode
    {
        KeyType key;
        ValueType value;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    int numItems;

    void freeTree(TreeNode* curNode);
    Vector<KeyType> KeysHelper(TreeNode* curNode) const;
    Vector<ValueType> ValuesHelper(TreeNode* curNode) const;
    bool containsKeyHelper(TreeNode* curNode, const KeyType& key) const;
    ValueType& getHelper(TreeNode* curNode, const KeyType& key) const;
    void putHelper(TreeNode*& curNode, const KeyType& key,const ValueType& value);
    void removeHelper(TreeNode*& curNode, const KeyType& key);
    void performDeletion(TreeNode*& curNode);
    TreeNode removeLargestFrom(TreeNode*& curNode);
    TreeNode* copy(TreeNode* curNode);

};

template <typename KeyType, typename ValueType>
OurMap<KeyType,ValueType>::OurMap()
{
    root = nullptr;
    numItems = 0;
}

template <typename KeyType, typename ValueType>
OurMap<KeyType,ValueType>::~OurMap()
{
    freeTree(root);

}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::freeTree(TreeNode* curNode)
{
    if(curNode == nullptr)
        return;
    else
    {
        freeTree(curNode->left);
        freeTree(curNode->right);
        delete curNode;
    }

}

template <typename KeyType, typename ValueType>
OurMap<KeyType,ValueType>::OurMap(const OurMap& map2)
{
    root = copy(map2.root);
    numItems = map2.numItems;
}

template <typename KeyType, typename ValueType>
typename OurMap<KeyType,ValueType>::TreeNode* OurMap<KeyType,ValueType>::copy(TreeNode* curNode)
{
    if(curNode == nullptr)
        return nullptr;
    else
        return new TreeNode{curNode->key,curNode->value,copy(curNode->left),copy(curNode->right)};
}


template <typename KeyType, typename ValueType>
class OurMap<KeyType,ValueType>:: OurMap& OurMap<KeyType,ValueType>::operator=(const OurMap& map2)
{
    clear();
    root = copy(map2.root);
    numItems = map2.numItems;
}


template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::clear()
{
    freeTree(root);
    root = nullptr;
    numItems = 0;
}

template <typename KeyType, typename ValueType>
int OurMap<KeyType,ValueType>::size() const
{
    return numItems;
}

template <typename KeyType, typename ValueType>
bool OurMap<KeyType,ValueType>::isEmpty() const
{
    return numItems == 0;
}

template <typename KeyType, typename ValueType>
Vector<KeyType> OurMap<KeyType,ValueType>::Keys() const
{
    return KeysHelper(root);
}

template <typename KeyType, typename ValueType>
Vector<KeyType> OurMap<KeyType,ValueType>::KeysHelper(TreeNode* curNode) const
{
    if(curNode == nullptr)
        return {};
    else
    {
        return KeysHelper(curNode->left) + curNode->key + KeysHelper(curNode->right);
    }
}

template <typename KeyType, typename ValueType>
Vector<ValueType> OurMap<KeyType,ValueType>::values() const
{
    return ValuesHelper(root);
}

template <typename KeyType, typename ValueType>
Vector<ValueType> OurMap<KeyType,ValueType>::ValuesHelper(TreeNode* curNode) const
{
    if(curNode == nullptr)
        return {};
    else
    {
        return ValuesHelper(curNode->left) + curNode->value + ValuesHelper(curNode->right);
    }
}

template <typename KeyType, typename ValueType>
bool OurMap<KeyType,ValueType>::containsKey(const KeyType& key) const
{
    return containsKeyHelper(root,key);
}

template <typename KeyType, typename ValueType>
bool OurMap<KeyType,ValueType>::containsKeyHelper(TreeNode* curNode, const KeyType& key) const
{
    if(curNode == nullptr)
        return false;
    else if(curNode->key == key)
        return true;
    else if(key > curNode->key)
        return containsKeyHelper(curNode->right,key);
    else
        return containsKeyHelper(curNode->left,key);
}

template <typename KeyType, typename ValueType>
KeyType OurMap<KeyType,ValueType>::firstKey() const
{
    if(numItems == 0)
        error("map为空");
    else
    {
        TreeNode* temp = root;
        while(temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp->key;
    }
}

template <typename KeyType, typename ValueType>
KeyType OurMap<KeyType,ValueType>::lastKey() const
{
    if(numItems == 0)
        error("map为空");
    else
    {
        TreeNode* temp = root;
        while(temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp->key;
    }
}

template <typename KeyType, typename ValueType>
ValueType& OurMap<KeyType,ValueType>::operator [](const KeyType& key)
{
    if(!containsKey(key))
    {
        put(key, ValueType());
    }
    return getHelper(root, key);
}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::put(const KeyType& key,const ValueType& value)
{
    putHelper(root,key,value);
}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::putHelper(TreeNode*& curNode, const KeyType& key,const ValueType& value)
{
    if(curNode == nullptr)
    {
        TreeNode* temp = new TreeNode{key,value,nullptr,nullptr};
        curNode = temp;
        numItems++;
    }
    else
    {
        if(key > curNode->key)
            putHelper(curNode->right,key,value);
        else if(key < curNode->key)
            putHelper(curNode->left,key,value);
        else
            curNode->value = value;
    }
}

template <typename KeyType, typename ValueType>
ValueType& OurMap<KeyType,ValueType>::getHelper(TreeNode* curNode, const KeyType& key) const
{
    if(key > curNode->key)
        return getHelper(curNode->right,key);
    else if(key < curNode->key)
        return getHelper(curNode->left,key);
    else
        return curNode->value;
}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::remove(const KeyType& key)
{
    removeHelper(root,key);
}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::removeHelper(TreeNode*& curNode, const KeyType& key)
{
    if(curNode == nullptr)
        return;
    else if(key > curNode->key)
        removeHelper(curNode->right,key);
    else if(key < curNode->key)
        removeHelper(curNode->left,key);
    else
        performDeletion(curNode);
}

template <typename KeyType, typename ValueType>
void OurMap<KeyType,ValueType>::performDeletion(TreeNode*& curNode)
{
    if(curNode->left == nullptr && curNode->right == nullptr)
    {
        delete curNode;
        curNode = nullptr;
    }
    else if(curNode->right == nullptr)
    {
        TreeNode* temp = curNode;
        curNode = curNode->left;
        delete temp;
    }
    else if(curNode->left == nullptr)
    {
        TreeNode* temp = curNode;
        curNode = curNode->right;
        delete temp;
    }
    else
    {
        TreeNode temp = removeLargestFrom(curNode->left);
        curNode->key = temp.key;
        curNode->value = temp.value;
    }
}

template <typename KeyType, typename ValueType>
typename OurMap<KeyType,ValueType>::TreeNode OurMap<KeyType,ValueType>::removeLargestFrom(TreeNode*& curNode)
{
    if(curNode->right == nullptr)
    {
       TreeNode temp = *curNode;
       performDeletion(curNode);
       return temp;
    }
    return removeLargestFrom(curNode->right);
}



#endif // OURMAP_H
