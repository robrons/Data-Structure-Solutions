#ifndef ___SEQUENCE_INTERFACE_HEADER____
#define ___SEQUENCE_INTERFACE_HEADER____


/* token
*  -- A token is a 20 character c string,
*/
struct _token{
  char text[21];
};

typedef struct _token token;


/*Sequence Interface
* -- A sequence is actually an enumerator for a sequence.
* -- An enumerator advances through indeces and returns the element
*    at each index, in order.  So we dispense with indexes and
*    manually tell the sequence enumerator when to go to the next element.
*    The element is returned in the form of a token string.
*/
struct _seq_interface{
    token (*getCurrent)(struct _seq_interface*);
    void (*gotoNext)(struct _seq_interface*);
    void (*destroy) (struct _seq_interface*);
};
typedef struct _seq_interface seq;

#endif
