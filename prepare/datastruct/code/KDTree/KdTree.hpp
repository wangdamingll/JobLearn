#include <iostream>
#include <vector>
using namespace std;

/**
 * Quick illustration of a two-dimensional tree.
 * No abstraction here.
 */
template <typename T>
class KdTree
{
  public:
    KdTree( ) : root( nullptr ) { }

    void insert( const vector<T> & x )
    {
        insert( x, root, 0 );
    }

    /**
     * Print items satisfying
     * low[ 0 ] <= x[ 0 ] <= high[ 0 ] and
     * low[ 1 ] <= x[ 1 ] <= high[ 1 ]
     */
    void printRange( const vector<T> & low,
                        const vector<T> & high ) const
    {
        printRange( low, high, root, 0 );
    }

  private:
    struct KdNode
    {
        vector<T> data;
        KdNode            *left;
        KdNode            *right;

        KdNode( const vector<T> & item )
          : data( item ), left( nullptr ), right( nullptr ) { }
    };

    KdNode *root;

    void insert( const vector<T> & x, KdNode * & t, int level )
    {
        if( t == nullptr )
            t = new KdNode( x );
        else if( x[ level ] < t->data[ level ] )
            insert( x, t->left, 1 - level );
        else
            insert( x, t->right, 1 - level );
    }

    void printRange( const vector<T> & low,
                     const vector<T> & high,
                     KdNode *t, int level ) const
    {
        if( t != nullptr )
        {
            if( low[ 0 ] <= t->data[ 0 ] && high[ 0 ] >= t->data[ 0 ] && 
                low[ 1 ] <= t->data[ 1 ] && high[ 1 ] >= t->data[ 1 ] )
                cout << "(" << t->data[ 0 ] << "," 
                            << t->data[ 1 ] << ")" << endl;

            if( low[ level ] <= t->data[ level ] )
                printRange( low, high, t->left, 1 - level );
            if( high[ level ] >= t->data[ level ] )
                printRange( low, high, t->right, 1 - level );
        }
    }
};

