//
//  vector.hpp
//  hw1-versioncontrol
//
//  Created by Daniel Kim on 6/7/20.
//  Copyright © 2020 John Kim. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <iostream>

namespace Pic10b {
	
	template <class T> class vector {
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
		void empty () const;
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
		
	private:
		//Other members [private]
		void reserve( size_t new_capacity );
		
	}; // end Pic10b::vector
	
	
	/** ************************* THE BIG 4 ************************* **/
	vector::vector() : the_data(nullptr), the_size(0), the_capacity(INIT_CAP){
		
		std::cout << "xxx: Default constructor :xxx" << std::endl;
		
		the_data = new double[the_capacity];
	}
	
	vector::vector( const vector& source ) : the_data(nullptr),
	the_size(source.the_size), the_capacity(source.the_capacity){
		
		std::cout << "xxx: Copy constructor :xxx" << std::endl;
		
		the_data = new double[the_capacity];
		
		// Deep copy of internal array
		for ( int i = 0 ; i < the_size ; ++i ){
			the_data[i] = source.the_data[i];
		}
	}
	
	vector& vector::operator=( const vector& rhs ){
		
		std::cout << "xxx: Copy assignment constructor :xxx" << std::endl;
		
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
	
	vector::~vector(){
		
		std::cout << "xxx: Destructor :xxx" << std::endl;
		
		delete[] the_data;
	}
	
	/** *********************** OTHER MEMBERS *********************** **/
//	bool vector::empty() const {
//		return the_size == 0;
//	}
	template <class T>
	void vector<T>::empty () const {
		return the_size == 0;
	}
	
//	size_t vector::size() const {
//		return the_size;
//	}
	template <class T>
	size_t vector<T>::size () const {
		return the_size;
	}
	
//	size_t vector::capacity() const {
//		return the_capacity;
//	}
	template <class T>
	size_t vector<T>::capacity () const {
		return the_capacity;
	}
	
	double vector::front() const {
		return *the_data;
	}
	
	double vector::back() const {
		return *(the_data + the_size - 1);
	}
	
	double vector::at( size_t index ) const {
		if ( index < the_size )
			return the_data[index];
		return the_data[0];
	}
	
	double& vector::operator[]( size_t index ){
		return the_data[index];
	}
	double vector::operator[]( size_t index ) const {
		return the_data[index];
	}
	
	void vector::dump_data_to( std::ostream& out ) const {
		out << "Vector (dump): ";
		for ( size_t i = 0 ; i < the_capacity ; ++i )
			out << the_data[i] << ' ';
		out << '\n';
	}
	void vector::dump_data() const {
		dump_data_to( std::cout );
	}
	
	
	void vector::push_back( double new_value ){
		if ( the_size == the_capacity )
			reserve( the_capacity + 1 );     // `the_data` is reassigned
		
		the_data[the_size++] = new_value;
	}
	
	// This implementation does not shrink the vector (ever)
	void vector::pop_back(){
		if ( the_size > 0 )
			--the_size;
	}
	
	
	void vector::reserve( size_t new_capacity ){
		if ( new_capacity > the_capacity ) {
			if ( new_capacity <= 2 * the_capacity )
				new_capacity = 2 * the_capacity;
			
			double* old_location = the_data;
			
			the_data = new double[new_capacity];
			the_capacity = new_capacity;
			
			for ( size_t i = 0 ; i < the_size ; ++i )
				the_data[i] = old_location[i];
			
			delete old_location;
		}
	}
	
} // end Pic10b namespace



/** ************************ OTHER FUNCTIONS ************************ **/
std::ostream& operator<<( std::ostream& out, const Pic10b::vector& v ){
	for ( size_t i = 0 ; i < v.size() ; ++i )
		out << v[i] << ' ';
	return out;
}


void print_vector( const Pic10b::vector& v ){
	if ( v.empty() )
		std::cout << "Vector is empty\n";
	else
		std::cout << "Vector (contents): " << v << '\n' ;
}

#endif /* vector_hpp */
