#ifndef RANK_TREAP_H
#define RANK_TREAP_H

#include <climits>
#include "UniformRandom.h"
#include <iostream>

using namespace std;

// RankTreap class
//
// ******************PUBLIC OPERATIONS*********************
// void Insert( x )       --> Insert x
// void Remove( x )       --> Remove x (unimplemented)
// bool Contains( x )     --> Return true if x is present
// T FindMin( )  --> Return smallest item
// T FindMax( )  --> Return largest item
// bool IsEmpty( )        --> Return true if empty; else false
// void MakeEmpty( )      --> Remove all items
// void PrintTree( )      --> Print tree in sorted order
// T Kth(k)               --> Kth element
// uint64_t Rank(x)       --> Kth of x element
// ******************WARNING********************************
// can not Insert duplicate T

template <typename T>
class RankTreap
{
  public:
    RankTreap( )
    {
        nullNode = new TreapNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }

    RankTreap( const RankTreap & rhs )
    {
        nullNode = new TreapNode;
        nullNode->left = nullNode->right = nullNode;
        root = clone( rhs.root );
    }

    ~RankTreap( )
    {
        MakeEmpty( );
        delete nullNode;
    }
    

    RankTreap( RankTreap && rhs ) noexcept : root{ rhs.root }, nullNode{ rhs.nullNode }
    {
        rhs.root = nullptr;
        rhs.nullNode = nullptr;
    }

    
    /**
     * Deep copy.
     */
    RankTreap & operator=( const RankTreap & rhs )
    {
        if(this==&rhs){
            return *this;
        }
        RankTreap copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    RankTreap & operator=( RankTreap && rhs )noexcept
    {
        std::swap( root, rhs.root );
        std::swap( nullNode, rhs.nullNode );
        
        return *this;
    }
    /**
     * kth element.
     */
    const T& Kth(uint64_t k){
        if(IsEmpty()){
            return nullNode->element;
        }
        return Kth(root,k);
    }

    /**
     * kth of x element.
     */
    uint64_t Rank(const T& x){
        if(IsEmpty()){
            return nullNode->element;
        }
        return Rank(root,x);
    }

    const T & FindMin( ) const
    {
        if( IsEmpty( ) ){
            return nullNode->element;
        }

        TreapNode *ptr = root;
        while( ptr->left != nullNode )
            ptr = ptr->left;

        return ptr->element;
    }

    const T & FindMax( ) const
    {
        if( IsEmpty( ) ){
            return nullNode->element;
        }

        TreapNode *ptr = root;
        while( ptr->right != nullNode )
            ptr = ptr->right;

        return ptr->element;
    }

    bool Contains( const T & x ) const
    {
        TreapNode *current = root;
        nullNode->element = x;

        for( ; ; )
        {
            if( x < current->element )
                current = current->left;
            else if( current->element < x )
                current = current->right;
            else
                return current != nullNode;
        }
    }

    bool IsEmpty( ) const
    {
        return root == nullNode;
    }

    void PrintTree( ) const
    {
        if( IsEmpty( ) )
            cout << "Empty tree" << endl;
        else
            PrintTree( root );
    }

    void MakeEmpty( )
    {
        MakeEmpty( root );
    }

    void Insert( const T & x )
    {
        Insert( x, root );
    }

    void Insert( T && x )
    {
        Insert( std::move( x ), root );
    }

    void Remove( const T & x )
    {
        Remove( x, root );
    }

  private:
    struct TreapNode
    {
        T element {};
        TreapNode *left {nullptr};
        TreapNode *right{nullptr};
        int        priority{INT_MAX};
        uint64_t s{0};//以它为根的总结点数

        TreapNode() = default;
        
        TreapNode( const T & e, TreapNode *lt, TreapNode *rt, int pr ,uint64_t s)
          : element{ e }, left{ lt }, right{ rt }, priority{ pr },s{s}
          { }
        
        TreapNode( T && e, TreapNode *lt, TreapNode *rt, int pr ,uint64_t s)
        : element{ std::move( e ) }, left{ lt }, right{ rt }, priority{ pr },s{s}{ }


    };

    TreapNode *root;
    TreapNode *nullNode;
    UniformRandom randomNums;

private:
    /**
     * Internal method to caculate s.
     * t is the root to caculate.
     */
    void Caculate(TreapNode *& t){
        t->s = 1;
        if(t->left!=nullNode){
            t->s+=t->left->s;
        }
        if(t->right!=nullNode){
            t->s+=t->right->s;
        }
    }

    /**
     * Internal method to kth element.
     * k is the kth.
     * t is the node that roots the tree.
     * return kth element
     */
     const T& Kth(TreapNode *& t,int k){
        if(t==nullNode || k>t->s||k<=0){
            return nullNode->element;
        }

        if(k==t->left->s+1){
            return t->element;
        }
        if(k<=t->left->s){
            return Kth(t->left,k);
        }else{
            return Kth(t->right,k-t->left->s-1);
        }
     }

    /**
    * Internal method to x element is kth.
    * x is the element.
    * t is the node that roots the tree.
    * return x element kth
    */
    int Rank(TreapNode *& t,const T& x){
        if(t==nullNode){
            return 0;
        }
        int res =0;
        if(x<=t->element){
            res+=Rank(t->left,x);
            res += (x == t->element);
        }else{
            res += t->left->s+1;
            res += Rank(t->right,x);
        }
        return res;
    }

    // Recursive routines
    /**
     * Internal method to Insert into a subtree.
     * x is the item to Insert.
     * t is the node that roots the tree.
     * Set the new root of the subtree.
     * (randomNums is a UniformRandom object that is a data member of RankTreap.)
     */
    void Insert( const T & x, TreapNode* & t )
    {
        if( t == nullNode )
            t = new TreapNode{ x, nullNode, nullNode, randomNums.nextInt( ),1};
        else if( x < t->element )
        {
            Insert( x, t->left );
            if( t->left->priority < t->priority )
                rotateWithLeftChild( t );
            Caculate(t);
        }
        else if( t->element < x )
        {
            Insert( x, t->right );
            if( t->right->priority < t->priority )
                rotateWithRightChild( t );
            Caculate(t);
        }
        // else duplicate; do nothing
    }
    
    /**
     * Internal method to Insert into a subtree.
     * x is the item to Insert.
     * t is the node that roots the tree.
     * Set the new root of the subtree.
     * (randomNums is a UniformRandom object that is a data member of RankTreap.)
     */
    void Insert( T && x, TreapNode* & t )
    {
        if( t == nullNode )
            t = new TreapNode{ std::move( x ), nullNode, nullNode, randomNums.nextInt( ), 1};
        else if( x < t->element )
        {
            Insert( std::move( x ), t->left );
            if( t->left->priority < t->priority )
                rotateWithLeftChild( t );
            Caculate(t);
        }
        else if( t->element < x )
        {
            Insert( std::move( x ), t->right );
            if( t->right->priority < t->priority )
                rotateWithRightChild( t );
            Caculate(t);
        }
        // else duplicate; do nothing
    }

    /**
     * Internal method to Remove from a subtree.
     * x is the item to Remove.
     * t is the node that roots the tree.
     * Set the new root of the subtree.
     */
    void Remove( const T & x, TreapNode * & t )
    {
        if( t != nullNode )
        {
            if( x < t->element )
                Remove( x, t->left );
            else if( t->element < x )
                Remove( x, t->right );
            else
            {
                // Match found
                if( t->left->priority < t->right->priority )
                    rotateWithLeftChild( t );
                else
                    rotateWithRightChild( t );

                if( t != nullNode )      // Continue on down
                    Remove( x, t );
                else
                {
                    delete t->left;
                    t->left = nullNode;  // At a leaf
                }
            }
            Caculate(t);
        }
    }

    void MakeEmpty( TreapNode * & t )
    {
        if( t != nullNode )
        {
            MakeEmpty( t->left );
            MakeEmpty( t->right );
            delete t;
        }
        t = nullNode;
    }

    void PrintTree( TreapNode *t ) const
    {
        if( t != nullNode )
        {
            cout << t->element<<":"<<t->s<< endl;
            PrintTree( t->left );
            PrintTree( t->right );
        }
    }

    // Rotations
    void rotateWithLeftChild( TreapNode * & k2 )
    {
        TreapNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        Caculate(k2);
        Caculate(k1);

        k2 = k1;
    }

    void rotateWithRightChild( TreapNode * & k1 )
    {
        TreapNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        Caculate(k1);
        Caculate(k2);

        k1 = k2;
    }

    TreapNode * clone( TreapNode * t ) const
    {
        if( t == t->left )  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new TreapNode{ t->element, clone( t->left ), clone( t->right ), t->priority,t->s };
    }
};

#endif//RANK_TREAP_H
