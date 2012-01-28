**pointainer** - auto-cleaning container of pointers  
**pointerator** - iterator to T* that behaves like iterator to T

Example usage:

    pointainer< std::vector<int*> > v;
    // put stuff into v...

    v.erase( v.begin() );
    // frees the memory allocated for the int 42, and then removes the
    // first element of v.

    typedef pointerator<std::vector<int*>::iterator> Iter;
    // Note: if your compiler does not support partial template
    // specialization, you should write:
    // typedef pointerator<std::vector<int*>::iterator, int> Iter;

    Iter i = std::find(Iter(v.begin()), Iter(v.end()), 17);
    // finds element pointing to a 17

    std::cout << *i.get_iterator() << " points to " << *i;
    // *i is 17

	// when v's destructor is called, it frees the memory allocated for
	// all v's elements
