<html>
<head>
	<title></title>
</head>
<body>
<p><span style="font-size:36px;">Approximate-String-Matching</span></p>

<p><span style="font-size:28px;">KAUST AMCS 260 algorithm</span></p>

<p><span style="font-size:22px;">Author: Gang Liao, Fatima Zohra Smailiy, Wentao Hu, Guangming Zang</span></p>

<p><span style="font-size:18px;">King Abdullah University of Science and Technology (KAUST)<br />
Computer, Electrical and Mathematical Sciences and Engineering (CEMSE) Division, Saudi Arabia</span></p>

<p><span style="font-size:28px;">Introduction</span></p>

<p>String matching algorithms are an important class of algorithms in Computer Science used to solve some famous problems mainly DNA strings matching, text processing, spell checking, spam filtering. The idea behind them is to quickly find the first or all occurrences of a string in a text. In other words, given a text string T and a pattern P, we need to find a quick way to find whether there is any occurrence in P and where it appears in case it exists. A slightly different but more interesting problem is approximate string matching problem, which is the problem we chose to work on for our project. For the approximate string matching problem we look for a substring that is similar to pattern P in text T. The word similar here refers to a string that needs a minimum number of operations (insertion, deletion and substitution) to be converted to P. This minimum number of operations is what we refer to as the edit distance. In the following sections, we will try to give a brief overview on the two approximate string matching algorithms we chose to work with.</p>

<p>Approximate string matching is one of the main problems in classical algorithms, with applications to text searching, computational biology, pattern recognition, etc. Many algorithms have been presented that improve approximate string matching, for instance [1-6]. We decide to implement two of them and compare them via the time and space complexity.</p>

<p><span style="font-size:28px;">TimeLine</span></p>

<p><s><span style="font-size:26px;"><span style="background-color:#A9A9A9;">September</span></span></s></p>

<p><span style="background-color:#A9A9A9;">(1) </span><s><span style="background-color:#A9A9A9;">Review and research on the topic and its applications</span></s></p>

<p><span style="background-color:#A9A9A9;">(2) </span><s><span style="background-color:#A9A9A9;">Review specific papers on the two algorithms chosen</span></s></p>

<p><span style="background-color:#A9A9A9;">(3) </span><s><span style="background-color:#A9A9A9;">Task dispatching among team members</span></s></p>

<p><s><span style="font-size:26px;"><span style="background-color:#A9A9A9;">October</span></span></s></p>

<p><span style="background-color:#A9A9A9;">(1) </span><s><span style="background-color:#A9A9A9;">Implementation of the algorithms</span></s></p>

<p>(2) Preparation of Midterm Presentation</p>

<p>(3) Preparation of Midterm Report</p>

<p><span style="font-size:26px;">November</span></p>

<p>(1) Evaluation of the implemented algorithms on different case studies</p>

<p>(2) Analysis of time and space complexity of the algorithms</p>

<p>(3) Synthesis and comparison of the algorithms</p>

<p>(4) Work on improving the existing algorithms as future work</p>

<p>(5) Preparation of Final Presentation and Report</p>

<p><span style="font-size:28px;">References</span></p>

<p>[1] E. Ukkonen, Finding approximate patterns in strings, Journal of algorithms, vol. 6, no. 1,pp. 132{137, 1985.</p>

<p>[2] G. Navarro and R. Baeza-Yates, Very fast and simple approximate string matching, In-formation Processing Letters, vol. 72, no. 1, pp. 65-70, 1999.</p>

<p>[3] G. M. Landau and U. Vishkin, Fast parallel and serial approximate string matching, Journal of algorithms, vol. 10, no. 2, pp. 157{169, 1989.</p>

<p>[4] R. A. Baeza-Yates and C. H. Perleberg, Fast and practical approximate string matching, in Combinatorial Pattern Matching. Springer, 1992, pp. 185-192.</p>

<p>[5] R. Baeza-Yates and G. Navarro, Faster approximate string matching, Algorithmica, vol. 23,no. 2, pp. 127-158, 1999.</p>

<p>[6] H. Hyyro, Bit-parallel approximate string matching algorithms with transposition, in String Processing and Information Retrieval. Springer, 2003, pp. 95-107.</p>

<p>[7] S. Wu and U. Manber,Fast text searching with errors. University of Arizona, Department of Computer Science, 1991</p>
</body>
</html>
