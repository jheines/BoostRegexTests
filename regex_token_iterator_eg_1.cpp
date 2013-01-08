/*
 *
 * Copyright (c) 2003
 * John Maddock
 *
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_token_iterator_example_1.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex_token_iterator example: split a string into tokens
  */


#include <boost/regex.hpp>

#include <iostream>
using namespace std;


#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && (__BORLANDC__==0x550))
//
// problem with std::getline under MSVC6sp3
istream& getline(istream& is, std::string& s)
{
   s.erase();
   char c = static_cast<char>(is.get());
   while(c != '\n')
   {
      s.append(1, c);
      c = static_cast<char>(is.get());
   }
   return is;
}
#endif


// int main(int argc, const char*[])
// updated by JMH on December 5, 2012 at 12:21 PM to allow command line input
// note that if the command line input contains white space, it must be enclosed
//    in double quotes
int main(int argc, char** argv)
{
   string s;
   do{
      if ( argc == 1 )
      {
         cout << "Enter text to split (or \"quit\" to exit): ";
         getline(cin, s);
         if(s == "quit") break;
      }
      else {
        // s = "This is a string of tokens";
        s = argv[1] ;
        // cout << argc << " " << s << endl ;
      }

      boost::regex re("\\s+");

      // the -1 parameter below causes the token iterator to consider as tokens
      //    those parts of the input that do *not* match the regex
      // such an iterator, if dereferenced, returns a match_results corresponding to
      //    the sequence of characters between the last match and the end of sequence
      // see http://boost-sandbox.sourceforge.net/libs/xpressive/doc/html/boost_xpressive/user_s_guide/string_splitting_and_tokenization.html
      // and http://en.cppreference.com/w/cpp/regex/regex_token_iterator
      boost::sregex_token_iterator i(s.begin(), s.end(), re, -1);

      // the default-constructed sregex_token_iterator is the end-of-sequence iterator
      // see http://en.cppreference.com/w/cpp/regex/regex_token_iterator
      boost::sregex_token_iterator j;

      unsigned count = 0;
      while(i != j)
      // while(i != s.end())  yields compiler error: no match for operator!=
      {
         cout << *i++ << endl;
         count++;
      }
      cout << "There were " << count << " tokens found." << endl;

   }while(argc == 1);
   return 0;
}
