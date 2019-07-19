#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <iostream>

//!    Constant Variable initialized to 8
/*! Creates a new Vector element if the vector is full
*/
const int STARTSIZE = 8;


namespace  custom {

//! Custom templated vector approximating STL vector.
template<typename T>
class vector
{
public:
  //! Default constructor.
    vector() :size_v{ 0 }, elem{ nullptr }, space{ 0 }
	{}// end of vector

  //! Default constructor with parameter value defining 'space'
    explicit vector(int s) : size_v{ 0 }, space{ s }
	{
		elem = new T[s];
	}// end of vector(int)

  //! Copy constructor.
  /*! Constructor with parameter value defining a RHS/source vector
      to be copied
      \param rhs a source vector with internal data to be copied
      */
	vector(const vector& rhs) : space{ rhs.space }, size_v{ rhs.size_v }
	{
		elem = new T[rhs.space];
		for (int i = 0; i < size_v; i++)
		{
			*(elem + i) = *(rhs.elem + i);
		}
	}//end of vector(const vector&)

  //! Overloaded copy-assignment operator.
  /*! \param rhs a const-qualified reference to a source vector to be copied.
      \return Reference to the vector to be assigned.
  */
	vector& operator=(const vector& rhs) // copy assignment
	{
		if (this != &rhs)
		{
			if (size_v <= rhs.size_v) //if vector is less that rhs
			{
				delete[] elem;
				elem = new T[rhs.space];
				size_v = rhs.size_v;
				space = rhs.space;
			}
			else
			{
				size_v = rhs.size_v;
			}
			for (int i = 0; i < size_v; i++)
				*(elem + i) = *(rhs.elem + i);
		}
		return  *this;
	}

//! Move assignment constructor.
/*! Constructor whose temporary parameter vector _will_ be destroyed
    \param rhs a r-value to source vector (temporary object).
 */
	vector(vector&& rhs) noexcept // move constructor
		:size_v{ rhs.size_v }, space{ rhs.space }
	{
		elem = rhs.elem;
		rhs.elem = nullptr;
		rhs.size_v = 0;
		rhs.space = 0;
	}

//! Overloaded move-assignment operator.
/*! \param rhs a r-value to source vector (temporary object).
    \return Reference to vector object to be assigned.
    */
	vector& operator=(vector&& rhs) noexcept // move assignment
	{
		if (this != &rhs)
		{
			delete[] elem;
			elem = rhs.elem;
			size_v = rhs.size_v;
			space = rhs.space;

			rhs.elem = nullptr;
			rhs.size_v = 0;
			rhs.space = 0;
		}
		return *this;
	}

//! Destructor.
/*! Destroys instantiated vector object and de-allocates dynamically assigned
   internal array */
	~vector() // destructor
	{
		delete[] elem;
		elem = nullptr;
	}

//! Overloaded [] operator.
/*! \param index integer value of index within internal array.
    \returns reference value/address of element at index value passed */
	const T& operator[] (int index) // access: return reference
	{
		if (index >= size_v)
		{
			throw std::out_of_range("This is out of range of the vector. Invalid access.");
		}
		return elem[index];
	}

//! Member function returning current 'count'.
/*! \returns current count (i.e. size_v) of elements within internal array */
	int size() const // the current size
	{
		return size_v;
	}

  //! Member function returning current max capacity ('space').
  /*! \returns current max capacity (i.e. space) of internal array */
	int capacity() const // current available space
	{
		return space;
	}

  //! Member function to resize internal array and add additional space.
  /*! Re-allocates a new internal array (i.e. 'elem') with size given and copies
     current elements over to new array. note: re-allocation of new array also
     initializes empty elements with default type-constructor.
     \param newsize integer value to define new 'space' of internal array
     */
	void resize(int newsize) // grow
	{

		T* temp = new T[newsize];
		int i = 0;
		for (i; i < newsize; i++)
		{
			if (i < size_v)
				temp[i] = elem[i];
		}
		// this is not like the real STL vector
		//where we can accept another default argument to initialize
		//data if our old vector is smaller that the resize, this means
		// the default constructor will be used.

		size_v = newsize;
		space = newsize;
		delete[] elem;
		elem = temp;
		temp = nullptr;
	}

  //! Member function for item insertion.
  /*! add new element passed by parameter to end of vector (that is, after
     most recent addition)
     \param val object of templated type to be inserted. */
	void push_back(T val) // add element
	{
		if (size_v < space)
		{
			elem[size_v] = val;
			size_v++;
		}
		else
		{
            if(space == 0)// check for empty vector
            {
				reserve(STARTSIZE);
				elem[size_v] = val;
				size_v++;
            }
            else
            {
				reserve(space*2);
				elem[size_v] = val;
				size_v++;
            }
		}
	}

  //! Member function to resize internal array and add additional space.
  /*! Re-allocates a new internal array (i.e. 'elem') with size given and copies
     current elements over to new array. note: re-allocation of new array
     occurs _without_ initializing empty elements with type-constructor
     \param newalloc integer value to define new 'space' of internal array
     */
	void reserve(int newalloc) // get more space
	{
		if (newalloc > space)
		{
			T* temp = new T[newalloc];
			for (int i = 0; i < size_v; i++)
			{
				temp[i] = elem[i];
			}
			delete[] elem;
			elem = temp;
			temp = nullptr;
			space = newalloc;
		}
	}

  /* DEFINING ITERATOR SPECIFIC TO VECTOR */
  //! Iterator Type pointer
	using iterator = T * ;
  //!Const-qualified Iterator Type
	using const_iterator = const T*;

  //! Iterator member function to return address of first element.
  /*! \returns a pointer associated with first element in internal array.
     Random access iterator. */
	iterator begin() // points to first element
	{
		return elem;
	}

  //! Iterator member function to return address of first element.
  /*! \returns const-qualified pointer associated with first element of
     internal array. Read only iterator. */
	const_iterator begin() const
	{
		return elem;
	}

  //! Iterator member function to return address of last element.
  /*! \returns a pointer associated with one-past the last element of internal
   array. */
	iterator end() // points to one beyond the last element
	{
		return (elem + size_v);
	}

  //! Iterator member function to return address of last element.
  /*! \returns const-qualified pointer associated with one-past the last elements
   of internal array. Read only iterator. */
	const_iterator end() const
	{
		return elem + size_v;
	}
	iterator insert(iterator p, const T& v)// insert a new element v before p
	{
		T* temp = nullptr;
		if (size_v >= space)
		{
			temp = new T[size_v * 2];
			space = size_v * 2;
		}
		else
		{
			temp = new T[space];
		}
		int i = 0;
		iterator j;
		for (j = begin(); j != p; j++)
		{
			temp[i] = *j;
			i++;
		}
		iterator returnIt = temp + i;
		temp[i] = v;
		i++;

		for (j; j != end(); j++)
		{
			while (i < space)
			{
				temp[i] = *j;
				i++;
			}
		}

		size_v++;
		delete[] elem;
		elem = temp;
		temp = nullptr;

		return returnIt;
	}
	iterator erase(iterator p) // remove element pointed to by p
	{
		T* temp = new T[space];
		int i = 0;
		iterator j;
		for (j= begin(); j < p; j++)
		{
			temp[i] = *j;
		}

		iterator returnIt = temp + i;
		i++;

		for (i; i < size_v; ++i)
		{
			temp[i] = *j;
			j++;
		}

		size_v--;

		delete[] elem;
		elem = temp;
		temp = nullptr;

		return returnIt;
	}
private:
	int size_v; /*!< CURRENT COUNT OF ELEMENTS IN INTERNAL ARRAY */
	T* elem; /*!< POINTER TO INTERNAL DYNAMIC ARRAY OF TEMPLATED TYPE */
	int space;  /*!< MAXIMUM SIZE OF INTERNAL ARRAY */
};
}
#endif // VECTOR_H
