/** 
 *  File:  /~heines/91.204/91.204-2012-13f/204-lecs/code/BoostRegexTests/RegExTests.cpp
 *  Jesse M. Heines, UMass Lowell Computer Science, heines@cs.uml.edu
 *  Copyright (c) 2012 by Jesse M. Heines.  All rights reserved.  May be freely 
 *    copied or excerpted for educational purposes with credit to the author.
 *  updated by JMH on November 19, 2012 at 8:12 PM
 *  updated by JMH on November 23, 2012 at 9:58 PM
 */

#include <iostream>  // for cout and friends
#include <sstream>   // for string streams
#include <string>    // for the STL string class

#include <boost/regex.hpp>              // for regex_match
#include <boost/algorithm/string.hpp>   // for iequals (case-insensitive match)
  // the Boost string library contains many string manipulation functions not found in 
  //    the STL library that you may be familiar with from Java or JavaScript, such as
  //    case-insensitive comparisons and trimming
  // see http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
  // see http://www.boost.org/doc/libs/1_52_0/doc/html/string_algo/usage.html
  // see http://www.boost.org/doc/libs/1_52_0/doc/html/string_algo/reference.html


using namespace std ;     // to eliminate the need for std::
using namespace boost ;   // to eliminate the need for boost::


// this function is modeled after code found in credit_card_example.cpp
void test1_BasicAndCaseInsensitiveMatches() {
  // set up the strings to be tested
  string str[ 10 ] ;
  str[0] = "quit" ;
  str[1] = "exit" ;
  str[2] = "Quit" ;
  str[3] = "quite" ;
  str[4] = "unrequited" ;
  str[5] = "unreQUITed" ;
  int nStrings = 6 ;

  // define a regular expression to test for "quit"
  const boost::regex reQuit( "quit" ) ;
  cout << "Results of case-sensitive searches:" << endl ;
  // test each string against the regular expression
  for ( int k = 0 ; k < nStrings ; k++ ) {
    cout << "attempting to match \"" << str[k] << "\" to \"" << reQuit << "\" returned " 
        << boost::regex_match( str[k], reQuit ) << endl ;
  }
  
  // define a regular expression to test for "quit" anywhere in a string
  const boost::regex reQuitA( ".*quit.*" ) ;
  cout << "\nResults of anywhere searches:" << endl ;
  // test each string against the regular expression
  for ( int k = 0 ; k < nStrings ; k++ ) {
    cout << "attempting to match \"" << str[k] << "\" to \"" << reQuit << "\" returned " 
        << boost::regex_match( str[k], reQuitA ) << endl ;
  }
  
  // define a case-insensitive regular expression to test for "quit" anywhere in a string
  const boost::regex reQuitI( ".*quit.*", boost::regex::icase ) ;
  cout << "\nResults of case-insensitive anywhere searches:" << endl ;
  // test each string against the regular expression
  for ( int k = 0 ; k < nStrings ; k++ ) {
    cout << "attempting to match \"" << str[k] << "\" to \"" << reQuitI << "\" returned " 
        << boost::regex_match( str[k], reQuitI ) << endl ;
  }
}


// this function is modeled after code found in regex_match_example.cpp
// note that this code demonstrates just one way to address the issue of parsing
//    a command line using regular expressions, other approaches are not only
//    possible, but perhaps even better
void test2_BasicCommandParsing_v1() {

  string strCmd[10] ;
  strCmd[0] = " add element root first one" ;
  strCmd[1] = "  add element root second" ;
  strCmd[2] = "  add  attribute  first   attr1 attr1value" ;
  strCmd[3] = "  add  attribute  second  attr2" ;
  strCmd[4] = "print" ;
  strCmd[5] = "quit" ;
  strCmd[6] = "another command" ;
  int nCmds = 7 ;

  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  regex reBasicCmd( "^\\s*(add|print|quit).*", boost::regex::icase ) ;
  regex reAddCmd( "^\\s*add\\s*(element|attribute)\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ;
  regex reAddElementCmd( "^\\s*add\\s*element\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ;
  regex reAddAttributeCmd( "^\\s*add\\s*attribute\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ;
  regex reQuitCmd( "^\\s*quit", boost::regex::icase ) ;

  // loop through all hard-coded command strings for testing purposes
  for ( int n = 0 ; n < nCmds ; n++ ) {

    // user entry point
    cout << "\nYour command: " ;
    // cin >> strCmd ;
    cout << strCmd[n] << endl ;

    // string version of a matched group 
    // for building a bridge between the cmatch type and an STL sting so that we can
    //    process matches with STL string functions
    string strWhat ;

    // test for a match of a basic command
    if ( regex_match( strCmd[n].c_str(), what, reBasicCmd ) ) {
      cout << "  what.size() = " << what.size() << endl ;
      for ( int k = 0 ; k < what.size() ; k++ ) {
        strWhat = what[k] ;
        cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << endl ;
      }
      
      // handle an ADD command
      if ( iequals( strWhat, "add" ) ) {
        cout << "  Command is ADD" << endl ;
        
        // test for a match on the second word in the command
        if ( regex_match( strCmd[n].c_str(), what, reAddCmd ) ) {
          for ( int k = 0 ; k < what.size() ; k++ ) {
            strWhat = what[k] ;
            cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << endl ;
          }
          strWhat = what[1] ;
          
          // handle an ADD ELEMENT command
          if ( iequals( strWhat, "element" ) ) {
            cout << "  Command is ADD ELEMENT" << endl ;
            cout << "  Continue with adding an element here." << endl ;
          } 
          // handle an ADD ATTRIBUTE command
          else if ( iequals( strWhat, "attribute" ) ) {
            cout << "  Command is ADD ATTRIBUTE" << endl ;
            cout << "  Continue with adding an attribute here." << endl ;
          } 
          // parsing error: ADD is followed by an invalid keyword
          else {
            cout << "    Invalid ADD command: 2nd word must be 'element' or 'attribute'." << endl ;
          }
        } 
        // parsing error: ADD command syntax does not match the regular expression
        else {
          cout << "    Invalid ADD command syntax." << endl ;
        }
      } 
      
      // handle a PRINT command
      else if ( iequals( strWhat, "print" ) ) {
        cout << "  Command is PRINT" << endl ;
        cout << "  Call your print function here." << endl ;
      } 
      
      // handle a QUIT command
      else if ( iequals( strWhat, "quit" ) ) {
        cout << "  Command is QUIT" << endl ;
        cout << "  Goodbye." << endl ;
        return ;
      } 
      
      // parsing error: the first keyword is not ADD, PRINT, or QUIT
      else {
        cout << "  Invalid command: 1st word must be 'add', 'print', or 'quit'." << endl ;
      }
    }  
  }
}




// this function is modeled after code found in regex_match_example.cpp
// note that this code demonstrates just one way to address the issue of parsing
//    a command line using regular expressions, other approaches are not only
//    possible, but perhaps even better
void test2_BasicCommandParsing_v2() {

  string strCmd[10] ;
  strCmd[0] = " add element root first one" ;
  strCmd[1] = "  add element root second" ;
  strCmd[2] = "  add  attribute  first   attr1 attr1value" ;
  strCmd[3] = "  add  attribute  second  attr2" ;
  strCmd[4] = "print" ;
  strCmd[5] = "a" ;
  strCmd[6] = "ad" ;
  strCmd[7] = "add" ;
  strCmd[8] = "quit" ;
  strCmd[9] = "another command" ;
  int nCmds = 10 ;

  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  regex reAddCmd( "^\\s*a(d|dd)?.*", boost::regex::icase ) ;
  regex rePrintCmd( "^\\s*p(r|ri|rin|rint)?.*", boost::regex::icase ) ;
  regex reQuitCmd( "^\\s*q(u|ui|uit)?.*", boost::regex::icase ) ;

  // loop through all hard-coded command strings for testing purposes
  for ( int n = 0 ; n < nCmds ; n++ ) {

    // user entry point
    cout << "\nYour command: " ;
    // cin >> strCmd ;
    cout << strCmd[n] << endl ;

    // string version of a matched group 
    // for building a bridge between the cmatch type and an STL sting so that we can
    //    process matches with STL string functions
    string strWhat ;

    // test for a match of an ADD command
    if ( regex_match( strCmd[n].c_str(), what, reAddCmd ) ) {
      cout << "  Command is ADD" << endl ;
      cout << "  Call a function to do your add command processing here." << endl ;
    }
      
    // test for a match of a PRINT command
    else if ( regex_match( strCmd[n].c_str(), what, rePrintCmd ) ) {
      cout << "  Command is PRINT" << endl ;
      cout << "  Call your print function here." << endl ;
    } 

    // handle a QUIT command
    else if ( regex_match( strCmd[n].c_str(), what, reQuitCmd ) ) {
      cout << "  Command is QUIT" << endl ;
      cout << "  Goodbye." << endl ;
      return ;
    } 

    // parsing error: the first keyword is not ADD, PRINT, or QUIT
    else {
      cout << "  Invalid command: 1st word must be 'add', 'print', or 'quit'." << endl ;
    }
  }
}


// standard C++ main function
int main( int argc, char* argv[] ) {
  // test1_BasicAndCaseInsensitiveMatches() ;
  // test2_BasicCommandParsing_v1() ;
  test2_BasicCommandParsing_v2() ;
  
  return 0 ;
}
