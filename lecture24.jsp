<%@ page contentType="text/html; charset=utf-8" language="java" import="java.sql.*" errorPage="" %>
<!DOCTYPE HTML>
<html>
<head>
  <meta charset="utf-8">
  
<!--
  File:  /~heines/91.204/91.204-2012-13f/204-lecs/lecture14.jsp
  Jesse M. Heines, UMass Lowell Computer Science, heines@cs.uml.edu
  Copyright (c) 2012 by Jesse M. Heines.  All rights reserved.  May be freely 
    copied or excerpted for educational purposes with credit to the author.
  updated by JMH on October 19, 2012 at 3:52 PM
-->

  <title>UMass Lowell 91.204</title>
  <meta name="Author" content="Jesse M. Heines, heines@cs.uml.edu" />

  <%@ include file="../../../common-jspfns.jsp" %>
  <%@ include file="../../../common-jspmenus.jsp" %>
  <script type="text/javascript" src="/~heines/cookies.js"></script>
  <script type="text/javascript" src="/~heines/common.js"></script>
  <script type="text/javascript" src="/~heines/jQuery/jquery-1.8.1.min.js"></script>

  <script type="text/javascript">
    goToTeaching() ;
  </script>
  
  <script type="text/javascript">
    // for Google Analytics
    // for more information, see 
    //    http://code.google.com/apis/analytics/docs/tracking/asyncTracking.html
    var _gaq = _gaq || [];
    _gaq.push(['_setAccount', 'UA-15092888-3']);
    _gaq.push(['_trackPageview']);
  
    (function() {
      var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
      ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
      var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
    })();
  </script>  

  <% 
    initHome( application, request, out, session ) ; 
    initLecture( application, request, out, session ) ;
  %>

  <!-- main CSS link for text - keep for Dreamweaver, which requires ../../, not /~heines/ -->
  <link type="text/css" rel="stylesheet" href="/~heines/blueverdana.css"></link>
  <script type="text/javascript">
    // setStylesheet() ;   // reset CSS link based on cookie value
    // console.log( '<link rel="stylesheet" type="text/css" href="' + strSiteHome + strBaseSupportLoc + 'blueverdana08pt.css" />' ) ;
    document.writeln( '<link rel="stylesheet" type="text/css" href="' + strSiteHome + strBaseSupportLoc + 'blueverdana08pt.css" />' ) ;
    
    document.title += " Notes for Class No. <%= intClassNo %>" ;
  </script>

  <!-- CSS for this page -->
  <link type="text/css" rel="stylesheet" href="/~heines/91.204/91.204-2012-13f/css/CourseHome.css"></link>
  <link type="text/css" rel="stylesheet" href="/~heines/91.204/91.204-2012-13f/css/LectureNotes.css"></link>
  <link type="text/css" rel="stylesheet" href="/~heines/css/EvanMulawski.css"></link>
  
  <style type="text/css">
    #assignmentstable {
      margin-left: -7px ;
    }
    #assignmentstable td, #assignmentstable th {
      padding: 0 3px ;
      border-collapse: collapse ;
    }
  </style>

  <!-- script for this page -->
  <script type="text/javascript" src="/~heines/scripts/FormatPreLineNumbers.js"></script>
  <script type="text/javascript">
    // remember that all references to IDs must be inside the $(document).ready function
    $(document).ready( function() {
      FormatPreLineNumbersJMH() ;
    } ) ;
  </script>
</head>

<body>
<%@ include file="../204pagehead.jsp" %>

<div id="prevnextlinks">
  <%= strPrevNextLinks( LECTURE ) %>
</div>

<div id="mainbody">

<h1 class="marginbot5">Notes for Class No. <%= intClassNo %></h1>
<h1 class="notop nobold marginbot5" ><%= strLectureTopic %></h1>
<h2 class="notop"><%= WeekdayMonthDayYear( strISO8601Date ) %></h2>

<p><em>A video of this class is (or will be) posted at: </em>&nbsp; <a href="<%= getClassVideosURL() %>" title="Class Videos" target="_blank"><%= getClassVideosURL() %></a></p>

<h2><br>
  Handouts and Materials</h2>
<ul>
  <li><a href="../../../91.461/resources/regular-expressions-cheat-sheet-v2.pdf" target="_blank">Regular Expression Cheat Sheet</a> (PDF)
    <ul>
      <li><a href="http://www.cheatography.com/davechild/cheat-sheets/regular-expressions/" target="_blank">www.cheatography.com/davechild/cheat-sheets/regular-expressions</a></li>
    </ul>
  </li>
  <li><a href="../204-assn/ParsingWithRegularExpressions-v01.jsp">Assignment No. 7</a></li>
  </ul>

<h2><br/>
  Openings / Announcements / Reminders</h2>
<h4> C++ Reference Websites&nbsp; <span class="nobold">(<em>for ease of reference during class</em>)</span></h4>
<ul>
  <li><a href="http://cplusplus.com/reference/", "_blank">http://cplusplus.com/reference</a></li>
  <li><a href="http://en.cppreference.com/w/Main_Page" target="_blank">http://en.cppreference.com/w/Main_Page</a></li>
</ul>
<h4><br>
  Boost Libaries Websites</h4>
<ul>
  <li><a href="http://www.boost.org" target="_blank">Boost C++ Libraries Home Page</a> -- <a href="http://www.boost.org" target="_blank">www.boost.org</a></li>
  <li><a href="http://www.boost.org/doc/libs/1_52_0/libs/regex/doc/html/index.html" target="_blank">Boost.Regex API Reference</a> -- <a href="http://www.boost.org/doc/libs/1_52_0/libs/regex/doc/html/index.html" target="_blank">www.boost.org/doc/libs/1_52_0/libs/regex/doc/html</a></li>
</ul>
<h2><br/>
  Class Notes</h2>
<p>
  <% 
  if ( strReading.length() > 0 )
    out.println( "<p><i>Related reading for this class:</i>&nbsp; " +
                 formatReadingLinkForLectureNotes() + "</p>" ) ;
%>
  <br />
</p>
<h3><br />
  The Sample Programs</h3>
<p>Location in a standard Windows installation</p>
<blockquote>
  <p><code>C:\Cygwin\lib\gcc\i686-pc-cygwin\3.4.4\include\c++\boost_1_48_0\libs\regex\example\snippets\</code></p>
</blockquote>
<p>Location on the teaching.cs.uml.edu server</p>
<blockquote>
  <p><a href="http://teaching.cs.uml.edu/~heines/91.204/Resources/Boost/regex" target="_blank">teaching.cs.uml.edu/~heines/91.204/Resources/Boost/regex</a></p>
</blockquote>
<p>Programs</p>
<ul>
  <li><code>captures_example.cpp</code></li>
  <li><code>credit_card_example.cpp</code></li>
  <li><code>    icu_example.cpp</code></li>
  <li><code>mfc_example.cpp</code></li>
  <li><code>partial_regex_grep.cpp</code></li>
  <li><code>partial_regex_iterate.cpp</code></li>
  <li><code>partial_regex_match.cpp</code></li>
  <li><code>regex_grep_example_1.cpp</code></li>
  <li><code>regex_grep_example_2.cpp</code></li>
  <li><code>regex_grep_example_3.cpp</code></li>
  <li><code>regex_grep_example_4.cpp</code></li>
  <li><code>regex_iterator_example.cpp</code></li>
  <li><code>regex_match_example.cpp</code></li>
  <li><code>regex_merge_example.cpp</code></li>
  <li><code>regex_replace_example.cpp</code></li>
  <li><code>regex_search_example.cpp</code></li>
  <li><code>regex_split_example_1.cpp</code></li>
  <li><code>regex_split_example_2.cpp</code></li>
  <li><code>regex_token_iterator_eg_1.cpp</code></li>
  <li><code>regex_token_iterator_eg_2.cpp</code></li>
</ul>
<p>Boost Documentation</p>
<ul>
  <li><a href="http://www.boost.org" target="_blank">Boost C++ Libraries Home Page</a> -- <a href="http://www.boost.org" target="_blank">www.boost.org</a></li>
  <li><a href="http://www.boost.org/doc/libs/1_52_0/libs/regex/doc/html/index.html" target="_blank">Boost.Regex API Reference</a> -- <a href="http://www.boost.org/doc/libs/1_52_0/libs/regex/doc/html/index.html" target="_blank">www.boost.org/doc/libs/1_52_0/libs/regex/doc/html</a> </li>
</ul>
</div>  
<!-- #mainbody -->

<%--
  @param bBreakBefore set to false to inhibit break before message
  @param bBreakMiddle set to true to add a break within the message before "Copyright"
  @param strClasses string containing space-separated list of class names to be applied
  @param bShowLinkToTeaching set to true to add a link to the page on teaching.cs.uml.edu
  @param bShowPageButtons set to false to inhibit display of page manipulation buttons
--%>
<%= PageFooter2012( false, true, "notop", false, true ) %>

<%
  OutputMsgArrayListToFirebugConsole( out, msg ) ;
%>

</body>
</html>
