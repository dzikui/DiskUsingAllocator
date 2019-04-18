/*
 ________________________________________________________________________________________________________________________________
|  ____________________________________________________________________________________________________________________________  |
| |                                                                                                                            | |
| |  Program: Allocator(v2) zapisujacy do pliku txt. Autor: Mateusz Idzikowski mat.idzikowski@gmail.com     data:12.02.2019    | |
| |____________________________________________________________________________________________________________________________| |
|  ____________________________________________________________________________________________________________________________  |
| |                                                                                                                            | |
| |                                                       INFO:                                                                | |
| |     Klasa szablonowa powsta³a na bazie allocatora œledz¹cego, dostepnego na YouTube na kanale "Code Blacksmith" oraz       | |
| |          na podstawie informacji zawartych w Sylabusach na stronie internetowej http://smurf.mimuw.edu.pl/                 | |
| |         Dzieki konstruktorowi i zawartym w ciele aliasom, alokator potrafi strumieniowac bezpoœrednio do pliku.            | |
| |____________________________________________________________________________________________________________________________| |
|  ____________________________________________________________________________________________________________________________  |
| |                                                                                                                            | |
| |                                                      ZMIANY:                                                               | |
| |     Allocator v1, to w 100% przepisany Tracking Allocator.                                                                 | |
| |     Allocator v2, to przerobiony Tracking allocator, aby potrafi³ w konstruktorze kierowaæ strumien do pliku.              | |
| |____________________________________________________________________________________________________________________________| |
|________________________________________________________________________________________________________________________________|
*/
#pragma once
#ifndef MY_OWN_ALLOCATOR_H
#define MY_OWN_ALLOCATOR_H
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

namespace std
{
	template <typename T>
	class My_Own_Allocator
	{
	public:
////////////////////////////////// KONSTRUKTOR DESTRUKTOR
		My_Own_Allocator()
		:fileName("file.txt") {file.open(fileName, std::ios::app);};
		~My_Own_Allocator()
		{file.close();}

////////////////////////////////// ZMIENNE PUBLICZNE
		std::fstream file;
		std::string fileName;
		using value_type = T;
		using pointer = T * ;
		using const_pointer = typename std::pointer_traits<pointer>::template rebind<const T*>;
		using void_pointer = typename std::pointer_traits<pointer>::template rebind<void *>;
		using const_void_pointer = typename std::pointer_traits<pointer>::template rebind<const void *>;
		using difference_type = typename std::pointer_traits<pointer>::difference_type;
		using size_type = size_t;

////////////////////////////////// ALIASY
		template<typename U>
		struct rebind_allocator	{using other_type = typename My_Own_Allocator<U>;};

		template<typename U>
		struct rebind_allocator_traits	
		{using other_type_traits = typename allocator_traits<My_Own_Allocator<U>>;};

		template<typename U>
		My_Own_Allocator(const My_Own_Allocator<U> & obj)
		:fileName(obj.fileName) {}

		template<class U, class... _Args>
		void construct(U * ptr, _Args && ...args)
		{new(static_cast<void *>(ptr)) U(std::forward<_Args>(args) ...);
		file << "Zamiast w pamieci, zapisze to tutaj: " << static_cast<void *>(ptr)<<endl;}

		template<class U>
		void destroy(U * ptr)
		{ptr->~U();}

		pointer allocate(size_type number_of_objects)
		{++mAllocations;
		return static_cast<T *>(malloc(sizeof(T) * number_of_objects));
		}

		void deallocate(pointer ptr, size_type number_of_objects)
		{delete(ptr);}
	private:
////////////////////////////////// ZMIENNE PRYWATNE
		static int mAllocations;
	};

	template<typename T>
	int My_Own_Allocator<T>::mAllocations = 0;
}

#endif
