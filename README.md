# Relational_Algebra_Library
Division of code:
• A header file (rdb.h) which has all the Library API.
• A c++ file (rdb-basics.cpp) with implementations of all the basic operators.
• A c++ file (rdb-join.cpp) with implementation of the join operation.
• A c++ file (rdb-attr.cpp) with implementations of all supported attribute types.
• A c++ file (rdb-main.cpp) with implementation of the UI

Functionalities Provided:
1. Union: All records of both R1 and R2. Relation * union(Relation * R1, Relation * R2)
2. Difference: Records in R1 but not in R2
Relation * difference (Relation * R1, Relation * R2)
3. Cartesian Product: All possible pairs of records from R1 and R2
Relation * catersianproduct(Relation * R1, Relation * R2)
4. Projection: New relation with a subset of columns
Relation * projection(Relation * R1, list<string> projectattrs)
5. Selection: New relation with a subset of records matching a boolean
expression in the attribute values in disjunctive normal form.
Relation * union (Relation * R1, DNFformula * f)
where
struct DNFformula { list <list <tuple <string, char, Attr *> > 

6. Rename: rename an attribute in schema
Relation * difference (Relation * R1, string s1, string s2)
7. Natural Join



More Features:
• Create	a new	empty table:	the	user	can	interactively	enter	the	schema.
• Delete	an	existing	table	with	all	data	in	it.
• Add	a	record	to	a	table.
• Print	a table	in	appropriate	format.
• Create	a	table	from	existing	tables	using	the	above	developed	operations
