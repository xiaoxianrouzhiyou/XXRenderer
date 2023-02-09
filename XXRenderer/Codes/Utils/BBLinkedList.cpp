#include "BBLinkedList.h"

BBLinkedList::BBLinkedList()
{
    m_pNext = nullptr;
}

int BBLinkedList::getCount()
{
    if (m_pNext == nullptr)
    {
        return 1;
    }
    else
    {
        return 1 + m_pNext->getCount();
    }
}

void BBLinkedList::pushBack(BBLinkedList *pNode)
{
    if (m_pNext == nullptr)
    {
        m_pNext = pNode;
    }
    else
    {
        m_pNext->pushBack(pNode);
    }
}

void BBLinkedList::insertAfter(BBLinkedList *pNode)
{
    m_pNext = pNode->m_pNext;
    pNode->m_pNext = this;
}

void BBLinkedList::remove(BBLinkedList *pNode)
{
    if (m_pNext == pNode)
    {
        m_pNext = m_pNext->m_pNext;
        pNode->m_pNext = nullptr;
    }
    else
    {
        m_pNext->remove(pNode);
    }
}

bool BBLinkedList::isEnd()
{
    if (m_pNext == nullptr)
        return true;
    else
        return false;
}

void BBLinkedList::clear()
{
    // to do
}
