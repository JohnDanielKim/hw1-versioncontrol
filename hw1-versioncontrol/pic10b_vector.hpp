//
//  pic10b_vector.hpp
//  hw1-versioncontrol
//
//  Created by Daniel Kim on 6/12/20.
//  Copyright © 2020 John Kim. All rights reserved.
//

#ifndef pic10b_vector_hpp
#define pic10b_vector_hpp

#include <stdio.h>
#include <iostream>

namespace Pic10b {
	
	template <typename T>
	class vector {
	private:
		double* the_data;
		size_t the_size;
		size_t the_capacity;
		
		static const int INIT_CAP = 10;
		
		
	public:
		// The big 4
		vector();
		vector( const vector& );
		vector& operator=( const vector& );
		~vector();
		
		// Other members [public]
		bool empty () const;
		size_t size() const;
		size_t capacity() const;
		double front() const;
		double back() const;
		double at( size_t index ) const;
		double& operator[]( size_t index );
		double operator[]( size_t index ) const;
		void dump_data_to( std::ostream& out ) const;
		void dump_data() const;
		void push_back( double new_value );
		void pop_back();
		
		// added members
		vector& operator += (const vector& rhs);
		bool operator == (const vector& rhs);
		bool operator != (const vector& rhs);
		bool operator < (const vector& rhs);
		bool operator <= (const vector& rhs);
		bool operator > (const vector& rhs);
		bool operator >= (const vector& rhs);
	private:
		//Other members [private]
		void reserve( size_t new_capacity );
		
	}; // end Pic10b::vector
	
	
	/** ************************* THE BIG 4 ************************* **/
	template <typename T>
	vector<T>::vector () : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {
		
		std::cout << "xxxxxxxxxx: Default constructor called :xxxxxxxxxx" << std::endl;
		
		the_data = new double[the_capacity];
	}
	
	template <typename T>
	vector<T>::vector (const vector<T>& source) : the_data(nullptr),
	the_size(source.the_size), the_capacity(source.the_capacity) {
		
		std::cout << "xxxxxxxxxx: Copy constructor called :xxxxxxxxxx" << std::endl;
		
		the_data = new double[the_capacity];
		
		// Deep copy of internal array
		for ( int i = 0 ; i < the_size ; ++i ){
			the_data[i] = source.the_data[i];
		}
	}
	
	template <typename T>
	vector<T>& vector<T>::operator= (const vector& rhs) {
		
		std::cout << "xxxxxxxxxx: Assignment constructor called :xxxxxxxxxx" << std::endl;
		
		if ( this != &rhs ) {     // Self-assignment?
			// Release old memory and request more
			delete[] the_data;
			the_data = new double[rhs.the_capacity];
			
			// Shallow copy non-pointers
			the_size = rhs.the_size;
			the_capacity = rhs.the_capacity;
			
			// Deep copy internal array
			for ( int i = 0 ; i < the_size ; ++i )
				the_data[i] = rhs.the_data[i];
		}
		return *this;
	}
	
	template <typename T>
	vector<T>::~vector () {
		
		std::cout << "xxxxxxxxxx: Destructor called :xxxxxxxxxx" << std::endl;
		
		delete[] the_data;
	}
	
	/** *********************** OTHER MEMBERS *********************** **/
	template <typename T>
	bool vector<T>::empty () const {
		return the_size == 0;
	}
	
	template <typename T>
	size_t vector<T>::size () const {
		return the_size;
	}
	
	template <typename T>
	size_t vector<T>::capacity () const {
		return the_capacity;
	}
	
	template <typename T>
	double vector<T>::front () const {
		return *the_data;
	}
	
	template <typename T>
	double vector<T>::back () const {
		return *(the_data + the_size - 1);
	}
	
	template <typename T>
	double vector<T>::at( size_t index ) const {
		if ( index < the_size ) {
			return the_data[index];
		}
		return the_data[0];
	}
	
	template <typename T>
	double& vector<T>::operator [] (size_t index) {
		return the_data[index];
	}
	
	template <typename T>
	double vector<T>::operator [] (size_t index) const {
		return the_data[index];
	}
	
	template <typename T>
	void vector<T>::dump_data_to (std::ostream& out) const {
		out << "Vector (dump): ";
		for ( size_t i = 0 ; i < the_capacity ; ++i )
			out << the_data[i] << ' ';
		out << '\n';
	}
	
	template <typename T>
	void vector<T>::dump_data () const {
		dump_data_to( std::cout );
	}
	
	template <typename T>
	void vector<T>::push_back (double new_value) {
		if (the_size == the_capacity) {
			reserve(the_capacity + 1);
		}
		the_data[the_size++] = new_value;

	}
	
	template <typename T>
	void vector<T>::pop_back () {
		if (the_size > 0) {
			--the_size;
		}
	}
	
	template <typename T>
	void vector<T>::reserve (size_t new_capacity) {
		if (new_capacity > the_capacity) {
			if (new_capacity <= 2 * the_capacity) {
				new_capacity = 2 * the_capacity;
			}
			double* old_location = the_data;
			
			the_data = new double[new_capacity];
			the_capacity = new_capacity;
			
			for ( size_t i = 0 ; i < the_size ; ++i ) {
				the_data[i] = old_location[i];
			}
			delete old_location;
		}
	}
	
	// added arithmetic member function, += operator
	template <typename T>
	vector<T>& vector<T>::operator += (const vector<T>& rhs) {
		for (int i = 0; i < the_size; ++i) {
			the_data[i] += rhs[i];
		}
		return *this;
	}

	
	/* other necessary member functions: comparison */
	template <typename T>
	bool vector<T>::operator == (const vector<T>& rhs) {
		return ((*this) * (*this)) == (rhs * rhs);
	}
	
	template <typename T>
	bool vector<T>::operator != (const vector<T>& rhs) {
		return ((*this) * (*this)) != (rhs * rhs);
	}
	
	template <typename T>
	bool vector<T>::operator < (const vector<T>& rhs) {
		return ((*this) * (*this)) < (rhs * rhs);
	}
	
	template <typename T>
	bool vector<T>::operator <= (const vector<T>& rhs) {
		return ((*this) * (*this)) <= (rhs * rhs);
	}
	
	template <typename T>
	bool vector<T>::operator > (const vector<T>& rhs) {
		return ((*this) * (*this)) > (rhs * rhs);
	}
	
	template <typename T>
	bool vector<T>::operator >= (const vector<T>& rhs) {
		return ((*this) * (*this)) >= (rhs * rhs);
	}
	
	// added arithmetic functions
	template <typename T>
	Pic10b::vector<T> operator + (const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
		Pic10b::vector<T> sum = lhs;
		for (int i = 0; i < lhs.size(); ++i) {
			sum[i] += rhs[i];
		}
		return sum;
	}
	
	template <typename T>
	T operator * (const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
		T product = 0;
		for (int i = 0; i < lhs.size(); ++i) {
			product += lhs[i] * rhs[i];
		}
		return product;
	}
	
	template <typename T>
	Pic10b::vector<T> operator * (T lhs, const Pic10b::vector<T>& rhs) {
		Pic10b::vector<T> product = rhs;
		for (int i = 0; i < rhs.size(); ++i) {
			product[i] *= lhs;
		}
		return product;
	}
	
	template <typename T>
	Pic10b::vector<T> operator * (const Pic10b::vector<T>& lhs, T rhs) {
		Pic10b::vector<T> product = lhs;
		for (int i = 0; i < lhs.size(); ++i) {
			product[i] *= rhs;
		}
		return product;
	}
	
	
	// all added functions for working with strings
//	template <typename T>
//	void vector<std::string>::push_back (double new_value) {
//		if (the_size == the_capacity) {
//			reserve(the_capacity + 1);
//		}
//		the_data[the_size++] = new_value;
//
//	}
//
//	template <typename T>
//	Pic10b::vector<std::string> operator * (std::string lhs, const Pic10b::vector<std::string>& rhs) {
//		Pic10b::vector<std::string> product = rhs;
//		for (int i = 0; i < rhs.size(); ++i) {
//			product[i].append(lhs);
//		}
//		return product;
//	}
//
//	template <typename T>
//	Pic10b::vector<std::string> operator * (const Pic10b::vector<std::string>& lhs, std::string rhs) {
//		Pic10b::vector<std::string> product = lhs;
//		for (int i = 0; i < lhs.size(); ++i) {
//			product[i].append(rhs);
//		}
//		return product;
//	}
//
//	template <typename T>
//	Pic10b::vector<std::string> operator * (const Pic10b::vector<std::string>& lhs, const Pic10b::vector<std::string>& rhs) {
//		Pic10b::vector<std::string> str = lhs;
//		for (int i = 0; i < lhs.size(); ++i) {
//			str[i] += rhs[i];
//		}
//		return str;
//	}
	
} // end Pic10b namespace



/** ************************ OTHER FUNCTIONS ************************ **/
template <typename T>
std::ostream& operator<< (std::ostream& out, const Pic10b::vector<T>& v) {
	for ( size_t i = 0 ; i < v.size() ; ++i )
		out << v[i] << ' ';
	return out;
}

// added ostream function for strings
template <typename T>
std::ostream& operator<< (std::ostream& out, const Pic10b::vector<std::string>& v) {
	for ( size_t i = 0 ; i < v.size() ; ++i )
		out << v[i] << ' ';
	return out;
}

template <typename T>
void print_vector (const Pic10b::vector<T>& v) {
	if ( v.empty() )
		std::cout << "Vector is empty\n";
	else
		std::cout << "Vector (contents): " << v << '\n' ;
}

#endif /* vector_hpp */
